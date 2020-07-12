#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <set>
#include <list>
#include <regex>

//삽입 대신 생성 삽입을 고려하라

namespace Item42 {
	using namespace std;

	class Widget {
	public:
		Widget() { std::cout << "default ctor" << std::endl; }
		Widget(int i) : val(i) { std::cout << "default ctor(int)" << std::endl; }
		Widget(const Widget& rhs) : val(rhs.val) { std::cout << "copy ctor" << std::endl; }
		Widget(Widget&& rhs) noexcept : val(rhs.val) { std::cout << "move ctor" << std::endl; }
		~Widget() { std::cout << "dtor" << std::endl; }
		Widget& operator= (const Widget & rhs) = default;
		int val = 0;
	};
	bool operator== (const Widget& lhs, const Widget& rhs) noexcept { return lhs.val == rhs.val; }
	bool operator< (const Widget& lhs, const Widget& rhs) noexcept { return lhs.val < rhs.val; }
	bool operator> (const Widget& lhs, const Widget& rhs) noexcept { return lhs.val > rhs.val; }

	/*
		생성 삽입 함수들은 삽입 함수들이 하는 모든 일을 할 수 있다.
		게다가 좀 더 효율적으로 수행될 수 있는 경우가 있으며, 적어도 이론적으로는, 덜 효율적으로 수행되는 경우는 결코 없다.
	*/
	namespace Case0 {
		inline void RunSample() {
			std::vector<std::string> vs;

			vs.push_back("xyzzy");

			// 문자열 리터럴은 std::string과 타입이
			// 다르므로, push_back을 호출하는 문장은
			// 다음과 같이 해석된다.

			vs.push_back(std::string("xyzzy"));

			// 그 결과 임시 std::string 객체가 생성되고
			// 그 임시 객체(우측값)가 std::vector 안의
			// 문자열로 이동한다.

			// 하지만 emplace_back 멤버 함수를
			// 사용하면 더 효율적으로 만들 수 있다.

			vs.emplace_back("xyzzy");

			// emplace_back은 완벽 전달을 이용하므로
			// 문자열 리터럴이 std::vector 안의
			// std::string 생성자에게 그대로 전달된다.

			// 따라서 임시 객체의 생성과 소멸 비용이
			// 들지 않는다.
		}
	}

	/*
		실질적으로, 만일 
		
		(1) 추가하는 값이 컨테이너로 대입되는 것이 아니라 생성되고, 
		(2) 인수 타입(들)이 컨테이너가 담는 타입과 다르고, 
		(3) 그 값이 중복된 값이어도 컨테이너가 거부하지 않는다면, 
		
		생성 삽입 함수가 삽입 함수보다 빠를 가능성이 아주 크다.
	*/

	//(1) 추가할 값이 컨테이너에 대입되는 것이 아니라 컨테이너 안에서 생성된다
	namespace Case1 {
		inline void RunSample() {

			std::vector<std::string> vs;
			vs.emplace(vs.begin(), "xyzzy");	//시작 지점에 추가하는 경우
			
			std::vector<Widget> vec(3, Widget(3)); 
			vec.reserve(40); 
			//vec.push_back(Widget(1));		//사실 push_back 도 임시 객체를 만드는 것 같다. 임시 객체 생성/파괴, 이동 생성 1회
			//vec.push_back(Widget(2));
			cout << "========" << endl << endl;
			vec.emplace(vec.begin(), 3);	//임시 객체 생성/파괴, 이동 생성 1회
			cout << "========" << endl << endl;
			vec.emplace_back(2);			//생성 1회
			cout << "========" << endl << endl;


			/*
				이런 경우에, 기존의 객체가 차지하고 있던 메모리 장소에 
				새 객체를 생성하는 표준 라이브러리 구현은 드물다. 대신 구현들은 그 값을 해당 장소로 이동 대입한다.	

				그런데 이동 대입을 수행하려면 이동의 원본이 필요하며, 
				따라서 이동 원본이 될 임시 객체를 생성해야 한다. 
				
				삽입에 비한 생성 삽입의 주된 장점은 임시 객체를 생성, 파괴하는 일이 없다는 것이므로, 
				이처럼 값을 대입을 통해서 컨테이너 안에 넣을 때에는 생성 삽입의 장점이 사라지는 경향이 생긴다.
			*/
		}

		/*
			노드 기반 컨테이너들은 거의 항상 생성을 통해서 새 값을 추가하며, 표준 컨테이너들은 대부분 노드 기반이다. 
			노드 기반이 아닌 표준 컨테이너는 std::vector와 std::deque, std::string 뿐이다
			(std::array도 아니지만, 이 컨테이너는 삽입과 생성 삽입을 둘 다 지원하지 않는다).

			노드 기반이 아닌 컨테이너에서는 emplace_back이 항상 대입 대신 생성을 이용해서 새 값을 컨테이너에 넣는다고 간주해도 무방하다. 
			그리고 std::deque의 경우에는 emplace_front 역시 마찬가지이다.
		*/
	}

	//(2)추가할 인수 타입(들)이 컨테이너가 담는 타입과 다르다.
	/*
		일반적으로 삽입에 비한 생성 삽입의 장점은 
		유연한 인터페이스 덕분에 전달된 인수 타입들이 컨테이너가 담는 타입과 달라도 임시 객체의 생성과 파괴가 일어나지 않는다는 점이다. 
		
		어떤 컨테이너<T>에 T 타입의 객체를 추가할 때에는 생성 삽입이 삽입보다 빠를 이유가 없다. 
		
		그럴 때에는 삽입 인터페이스에서도 임시 객체를 생성할 필요가 없기 때문이다.
	*/
	
	//(3)컨테이너가 기존 값과의 중복 때문에 새 값을 거부할 우려가 별로 없다. 
	namespace Case2 {
		

		inline void RunSample() {
			set<Widget> s;

			cout << "Emplace =====================" << endl;
			s.emplace(1);
			s.emplace(2);
			s.emplace(3);
			s.emplace(1);	//중복 원소 여부를 확인하기 위해 임시 객체 생성/ 그리고 중복된다면 파괴
			cout << "Clear =====================" << endl;
			s.clear();


			cout << "Create Object =====================" << endl;
			Widget w1(1);
			Widget w2(2);
			Widget w3(3);
			Widget w4(1);

			cout << "Insert =====================" << endl;
			s.insert(w1);
			s.insert(w2);
			s.insert(w3);
			s.insert(w4); //Insert의 경우 중복 원소 확인을 위한 임시 객체를 생성하지 않는다.
			cout << "Clear =====================" << endl;
			s.clear();
		}
		/*
		이는 컨테이너가 중복을 허용하거나, 또는 추가할 값들이 대부분 고유한 경우에 해당한다.
		이 조건이 중요한 이유는, 중복 제한이 있는 경우 일반적으로 생성 삽입 구현은 새 값으로 노드를 생성해서 그것을 기존 컨테이너 노드들과 비교한다는 것이다.

		만일 추가할 값이 컨테이너에 없으면 그 노드를 컨테이너에 연결한다(link). 그러나 값이 이미 있으면 생성 삽입이 취소되고 그 노드가 파괴된다.
		따라서 생성과 파괴 비용이 낭비되고 만다. 이런 노드들은 삽입 함수보다 생성 삽입 함수에서 더 자주 생성된다.

		Ex) set을 생각하면 된다. set은 중복 원소를 허용하지 않으니, emplace로 중복되는 값을 삽입하려 할 때 위의 설명대로 임시 객체를 생성 후 파괴한다.
	*/
	}
	

	/*
		자원 관리 객체를 컨테이너에 추가한다면, 
		그리고 자원 획득과 그 자원을 자원 관리 객체로 변환하는 시점 사이에 아무것도 끼어들지 못하게 하라는 조언(항목 21 참고)을 제대로 따른다면, 
		생성 삽입이 삽입 함수보다 더 나은 성능을 보일 가능성은 별로 없다.
	*/
	namespace Case3 {
		auto killWidget = [](Widget* pWidget) 
		{
			cout << "Delete With CustomDeleter" << endl;
			delete pWidget;
		};

		inline void RunSample() {
			std::list<std::shared_ptr<Widget>> ptrs;


			//객체 삽입 방법 두 가지 
			ptrs.push_back(std::shared_ptr<Widget>(new Widget(0), killWidget));
			ptrs.push_back({ new Widget, killWidget });

			/*
				1. 두 호출 모두, "new Widget"으로 만들어진 생 포인터를 담는 임시 std::shared_ptr<Widget> 객체가 생성된다.

				 2. push_back은 그 임시 객체를 참조로 받는다.
				 복사본을 담을 리스트 노드를 할당하는 도중에 메모리 부족(out-of-memory) 예외가 발생한다.

				 3. 예외가 push_back 바깥으로 전파되면서 임시 객체가 안전하게 파괴된다. 할당한 메모리도 안전하게 반환된다.

				 문제없음
			*/

			//객체 삽입 생성
			ptrs.push_back({ new Widget, killWidget });
			/*
				1. "new Widget"으로 만들어진 생 포인터가 emplace_back으로 완벽 전달된다.
				emplace_back은 새 값을 담을 리스트 노드를 할당한다.

				2. 리스트 노드를 만들 때 메모리 부족(out-of-memory) 예외가 발생한다.

				3. 예외가 emplace_back 밖으로 전파되면서, 힙에 있는 Widget 객체에 도달하는 유일한 수단인 생 포인터가 사라진다.

				 자원 누수
			*/

			/*
				아래의 방식이 적합하다.
			*/
			std::shared_ptr<Widget> spw(new Widget, killWidget); 
			ptrs.push_back(std::move(spw));
			//or
			ptrs.emplace_back(std::move(spw));
		}
	}

	
	/*
		초기화 방식은 두 가지가 있다. 하나는 복사 초기화(copy initialization)이고, 다른 하나는 직접 초기화(direct initialization)이다.

		explicit 생성자에서는 복사 초기화를 사용할 수 없지만 직접 초기화는 사용할 수 있다. 
		std::regex는, const char* 타입의 인수를 받고 explicit으로 선언된 생성자를 제공한다.

		생성 삽입 함수를 다룰 때는 혹시 모를 오류를 방지하기 위해 매개변수를 넘길 때 신경쓸 것.
	*/
	//초기화 방식에 따른 차이
	namespace Case4 {
		inline void RunSample() {
			//std::regex r1 = nullptr;
			// 복사 초기화; 오류! 컴파일 안 됨

			std::regex r2(nullptr);
			// 직접 초기화; 컴파일됨



			//따라서 다음의 코드는 둘다 엉터리지만 생성 삽입 함수는 컴파일 오류가 뜨지 않는다.

			std::vector<std::regex> regexes;

			regexes.emplace_back(nullptr);
			// 컴파일됨; 직접 초기화에서는 포인터를 받는, explicit으로
			// 선언된 std::regex 생성자를 사용할 수 있다.

			//regexes.push_back(nullptr);
			// 오류! 복사 초기화에서는  그런 생성자를 사용할 수 없다.

		}
	}
}