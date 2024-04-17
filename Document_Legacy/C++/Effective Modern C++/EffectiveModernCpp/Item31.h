#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <functional>

//기본 갈무리 모드를 피하라

namespace Item31 {

	/*
		람다 표현식(lambda expression)은 이름 그대로 하나의 표현식으로, 소스 코드의 일부이다
		
		클로저(closure)는 람다에 의해 만들어진 실행시점 객체이다. 
		갈무리 모드(capture mode)에 따라, 클로저가 갈무리된 데이터의 복사본을 가질 수도 있고 그 데이터에 대한 참조를 가질 수도 있다. 
		위 예제 코드의 std::find_if 호출에서 클로저는 실행시점에서 std::find_if의 셋째 인수로 전달되는 객체이다.

		클로저 클래스는 클로저를 만드는 데 쓰인 클래스를 말한다. 
		각각의 람다에 대해 컴파일러는 고유한 클로저 클래스를 만들어 낸다. 
		람다 안의 문장들은 해당 클로저 클래스의 멤버 함수들 안의 실행 가능한 명령들이 된다.
	*/

	using FilterContainer = std::vector<std::function<bool(int)>>;
	FilterContainer filters;

	namespace Case0 {
		/*
			기본 참조 캡쳐는 참조가 대상을 잃을 위험이 있다.

			기본 참조 갈무리를 사용한 람다에 의해 생성된 클로저의 수명이,
			캡쳐된 지역 변수나 매개변수의 수명보다 오래 지속되면, 클로저 안의 참조는 대상을 잃는다.
		*/

		template <typename C>
		void workWithContainer(const C& container)
		{
			auto divisor = 5; 
														
			if (std::all_of(std::begin(container), std::end(container),
				[&](const auto& value)
			{ return value % divisor == 0; })) 
			{
				//...
			}
			else 
			{
				//...
			}                                            
		}
		/*
			현재 문맥에서는 유효하지만 다른 문맥에서도 적합하다고 볼 수 없다.

			변수 캡쳐는 오직 람다가 생성된 범위 안에서 보이는, static이 아닌 지역 변수(매개변수 포함)에만 적용된다.
		*/

		inline void RunSample()
		{
			auto divisor = 5;

			filters.emplace_back(
				[&](int value) { return value % divisor == 0; }		// 위험! divisor에 대한 참조를 잃을 수 있다.
			);
			/*
				addDivisorFilter 함수가 종료될 때, 지역변수 divisor는 반환된다.
			*/
			filters.emplace_back(
				[&divisor](int value) { return value % divisor == 0; }		// 위험! divisor에 대한 참조를 잃을 수 있다.
			);
			/*
				마찬가지,
				하지만 명시적 캡쳐는 이 람다 표현식의 유효성이 divisor의 수명에 의존한다는 점이 명확히 나타난다는 장점이 있다.
			*/


		}

		class Widget {
		public:
			void f() {
				auto divisor = 5;

				filters.emplace_back(
					[&](int value)
				{
					return value % divisor == 0;
				}
				);

				filters.back()(3);
			}
		private:
			int m_Val = 3;
		};
	}

	namespace Case1 {
		class Gadget {
		public:
			Gadget() { std::cout << "default ctor" << std::endl; }
			Gadget(const Gadget& rhs) { std::cout << "copy ctor" << std::endl; }
			Gadget(Gadget&& rhs) { std::cout << "move ctor" << std::endl; }
		};

		class Widget {
		public:
			void f() {
				Gadget gadget;
				filters.emplace_back(
					[gadget](int value)		//값 복사 발생
				{ 
					auto g = gadget;
					return value % 5 == 0; 
				}		
				);
			}
		};

		inline void RunSample() {
			Widget w;
			w.f();
		}
	}

	namespace Case2 {
		/*
			기본 값 갈무리는 포인터(특히 this)가 대상을 잃을 수 있으며, 람다가 자기 완결적이라는 오해를 부를 수 있다.
		*/

		class Widget {
		public:
			void f() {
				/*filters.emplace_back(
					[divisor](int value) { return value % divisor == 0; }
				);*/	//컴파일 에러, divisor를 캡쳐할 수 없다.

				filters.emplace_back(
					[=](int value) { return value % divisor == 0; }
				);
				/*
					캡쳐 변수 divisor 는 값 복사 되니, 이후 Widget객체 생명주기가 끝나고 divisor가 사라지더라도 괜찮지 않을까?
					=> 절대 아니다


					갈무리는 오직 람다가 생성된 범위 안에서 보이는, static이 아닌 지역 변수(매개변수 포함)에만 적용된다.
					
					Widget::f의 본문에서 divisor는 지역 변수가 아니라 클래스의 한 데이터 멤버이므로 캡쳐될 수 없다.
					대신 위의 람다 표현식에서 [=]를 통해 값 복사하고 있는 것은 Widget의 this 포인터이다.
				*/

				auto thisObj = this;
				filters.emplace_back(
					[thisObj](int value) { return value % thisObj->divisor == 0; }
				);
				/*
					위의 형식으로 바뀐다.

					즉 객체가 파괴되고 this 포인터가 소멸된 이후 람다 객체를 호출한다면 미정의 행동을 유발한다.
				*/

				filters.emplace_back(
					[divisor = this->divisor](int value) { return value % divisor == 0; }
				);
				/*
					c++14 의 방법을 통해서(일반화된 람다 캡쳐)
					안전하게 값복사 하자.
				*/
			}
		private:
			int divisor = 5;
		};

		inline void RunSample() {
			Widget w;
			w.f();
		}
	}

	namespace Case3 {
		/*
			값에 의한 기본 캡쳐 모드의 또 다른 단점은, 
			해당 클로저가 자기 완결적이고 클로저 바깥에서 일어나는 데이터의 변화로부터 격리되어 있다는 오해를 부를 수 있다는 점이다.

			왜냐하면 람다가 지역 변수와 매개변수 (캡쳐가 가능한)뿐만 아니라 
			정적 저장소 수명 기간(static storage duration)을 가진 객체에도 의존할 수 있기 때문이다.

			정적 저장소 수명 기간을 가진 객체를 람다 안에서 사용할 수는 있지만, 캡쳐할 수는 없다.

			그러나 기본 값 캡쳐 모드의 표기는 마치 그런 객체도 모두 캡쳐된다는 느낌을 준다.
		*/

		void RunSample(void)
		{
			static auto divisor = 5;				//정적변수

			filters.emplace_back(
				[=](int value)                           
			{ return value % divisor == 0; }        //사실 아무것도 캡쳐하지 않는다. 위의 정적 변수를 지칭한다.
			);
			/*
				RunSample의 각 호출의 끝에서 divisor가 증가하며, 
				따라서 이 함수를 통해서 filters에 추가된 람다는 이전과는 다른 행동(divisor의 새 값에 상응하는)을 보이게 된다.

				애초에 기본 값 갈무리 모드를 사용하지 않는다면 이처럼 오해의 여지가 큰 코드가 만들어질 위험도 사라진다.
			*/

			++divisor;                                    
		}
	}

	
}