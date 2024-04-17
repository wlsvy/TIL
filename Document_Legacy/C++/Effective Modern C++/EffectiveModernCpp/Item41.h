#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>

//이동이 저렴하고 항상 복사되는 복사 가능 매개변수에 대해서는 값 전달을 고려하라

namespace Item41 {
	using namespace std;

	/*
		이동이 저렴하고 항상 복사되는 복사 가능 매개변수에 대해서는 
		값 전달이 참조 전달만큼이나 효율적이고, 구현하기가 더 쉽고, 산출되는 목적 코드의 크기도 더 작다.
	*/

	//오버로딩 방식
	namespace Case0 {
		class Widget {
		public:
			void addName(const std::string& newName)        // 좌측값을 받아서 복사한다.
			{
				names.push_back(newName);
			}

			void addName(std::string&& newName)                // 우측값을 받아서 이동한다
			{
				names.push_back(std::move(newName));
			}
		private:
			std::vector<std::string> names;
		};
	}

	//보편참조 방식
	namespace Case1 {
		class Widget {
		public:
			template <typename T>               //보편참조 활용           
			void addName(T&& newName)                      
			{                                              
				names.push_back(std::forward<T>(newName)); 
			}
		private:
			std::vector<std::string> names;
		};
		/*
			보편참조가 가지는 문제점들 
			1. 템플릿 함수는 헤더파일에 작성 + 오브젝트 파일 비대화
			2. 보편 참조로는 전달할 수 없는 인수 형식들이 존재.

			등을 제외하면 좋은 방법.
		*/
	}

	//값 전달 방식
	namespace Case2 {
		class Widget {	
		public:
			void addName(std::string newName)                // 좌측값이나 우측값을 받아서 이동한다.
			{
				names.push_back(std::move(newName));
			}        
		private:
			std::vector<std::string> names;
		};

		inline void RunSample() {
			Widget w;
			std::string name("Bart");

			w.addName(name);                // 좌측값으로 호출, 비용은 복사 1회 이동 1회
			w.addName(name + "Jenne");		// 우측값으로 호출, 비용은 이동 2회

			/*
				오버로딩 버전, 보편참조 버전의 경우, 
				좌측값 호출 비용 -> 복사 1회
				우측값 호출 비용 -> 이동 1회

				에 비해 값 참조는 확실히 비싸다는 단점이 있다.

				하지만 산출 코드의 양이 적고, 구현이 쉽다는 장점도 존재.
			*/
		}

		/*
			값 전달을 "사용하라"가 아니고 고려하라일 뿐이다. 
			값 전달 방식에는 함수를 하나만 작성하면 된다는 장점과 목적 코드에 함수 하나만 만들어진다는 장점, 
			그리고 보편 참조(universal reference)와 관련된 문제점이 없다는 장점이 있는 것이 사실이다. 
			그렇지만 다른 대안들보다 비용이 크며 또 다른 비용이 추가되는 경우도 있다.

			아래의 사항을 고려하자

			1. 복사 가능 매개변수에 대해서만 값 전달을 고려해야 한다. 

			복사할 수 없는 매개변수는 반드시 이동 전용 타입일 것이다
			(이를테면 std::unique_ptr - 복사 기능이 없으니 여기에 대해서는 우측값에 대한 버전만 작성하면 된다.) 

			값 전달 방식의 장점은 함수를 하나만 작성하면 되는 것인데 어차피 이동 연산만 있다면 우측값에 대한 버전만 작성하면 된다. 
			게다가 참조로 전달하면 이동을 1회만 하면 되지만, 값으로 전달하면 이동이 2회 일어난다.
			
			
			2. 값 전달은 이동이 저렴한 매개변수에 대해서만 고려해야 한다. 
			
			이동이 저렴한 경우에는 이동이 한 번 더 일어난다고 해도 큰 문제가 되지 않는다. 
			그러나 이동의 비용이 크다면, 불필요한 이동을 수행하는 것은 불필요한 복사를 수행하는 것과 비슷하다.

			3. 값 전달은 항상 복사되는 매개변수에 대해서만 고려해야 한다. 
			
			만일 매개변수를 항상 복사하는 것이 아니라, 매개변수가 어떤 조건을 만족하는 경우에만 복사하고, 
			그렇지 않은 경우에는 아무런 일도 하지 않는 함수가 있다고 하자. 
			
			이 함수의 매개변수를 참조로 받으면, 조건을 만족하는 매개변수를 받았을 때에는 복사가 일어나고 그렇지 않은 매개변수를 받았을 때에는 복사가 일어나지 않는다. 
			그러나 이 함수의 매개변수를 값으로 받으면, 어떤 경우에도 복사가 일어난다.

			4. 값 전달에서는 잘림 문제(slicing problem)가 발생할 수 있으므로, 일반적으로 기반 클래스 매개변수 타입에 대해서는 값 전달이 적합하지 않다.
			  잘림 문제(slicing problem) -> 파생클래스 객체를, 기반 클래스 값 타입으로 복사 생성할 시 파생클래스 메모리 부분이 잘리는 현상
		*/
	}
	
	/*
			좌측값 인수의 경우 값 전달(즉, 복사 생성) 다음의 이동 대입은 참조 전달 다음의 복사 대입보다 훨씬 비쌀 가능성이 있다.
	*/
	namespace Case3 {
		class Password {
		public:
			explicit Password(std::string pwd) : text(std::move(pwd)) {}        // 값 전달

			void changeTo(std::string newPwd)        // 값 전달
			{
				text = std::move(newPwd);
			}
			void changeToByRef(const std::string & newPwd)
			{
				text = newPwd;
			}
		private:
			std::string text;
		};

		
		inline void RunSample() {
			std::string initPwd("Supercalifragilisticexpialidocious");

			Password p(initPwd);		
			/*
				생성자에서 값 전달이 쓰이므로 복사생성 1회, 이동생성 1 회의 비용이 발생한다.

				오버로딩이나 보편참조였으면 피할 수 있는 비용이다.
			*/
										
										


			//비밀번호 변경시

			std::string newPassword = "Beware the Jabberwock";

			p.changeTo(newPassword);
			/*
				복사 생성 1회, 이동 대입 1회
				그리고 매개변수로 생성된 newPwd 객체가 파괴될 때 소멸자 호출 1회

				동적 메모리 관리 동작은 2번 일어난다.

				만약에 기존의 패스워드 길이가 새로운 패스워드 보다 짧았다면
				string 내부에서 재할당이 발생하기 때문에 추가 비용이 발생했을 것이다.
			*/

			p.changeToByRef(newPassword); //참조로 전달했다면 훨씬 효율적이었을 것이다.
			/*
				결론적으로, 최대한 빨라야 하는 소프트웨어에서는 값 전달 방식이 그리 바람직하지 않은 전략이다.
				저렴한 이동 연산이라도 피하는 것이 중요하기 때문이다.
				게다가 이동 연산이 몇 번 일어나는지가 확실하지 않은 경우도 있다.
			*/
		}
	}

}