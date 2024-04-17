#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <functional>

//객체를 클로저 안으로 이동하려면 초기화 갈무리를 사용하라

namespace Item32 {
	/*
		객체를 클로저 안으로 이동할 때에는 C++14의 초기화 갈무리를 사용하라.
		초기화 갈무리로는 다음과 같은 것들을 지정할 수 있다.

		1. 람다로부터 생성되는 클로저 클래스에 속한 데이터 멤버의 이름
		2. 그 데이터 멤버를 초기화하는 표현식
	*/

	/*
		이동가능한 객체의 경우 값 캡쳐, 참조 캡쳐도 적절하지 않다. c++11 에는 정식으로 이를 지원하는 방법은 없지만
		c++14 부터는 초기화 갈무리로 객체를 이동시킬 수 있다.
	*/

	class Widget {
	public:
		Widget() { std::cout << "default ctor" << std::endl; }
		Widget(const Widget& rhs) { std::cout << "copy ctor" << std::endl; }
		Widget(Widget&& rhs) { std::cout << "move ctor" << std::endl; }
		~Widget() { std::cout << "dtor" << std::endl; }
		
		int val = 0;
	};

	namespace Case0 {
		inline void RunSample() {
			auto pw = std::make_unique<Widget>();
			pw->val = 3;

			{
				auto func = [pw = std::move(pw)]()	//C++ 14
				{
					std::cout << pw->val << std::endl;
				};
				func();
			}
			std::cout << "==============" << std::endl;
		}
		/*
		[]안쪽 부분이 초기화 갈무리이다.
		"="의 좌변은 클로저 클래스 안의 데이터 멤버 (클로저에서 사용할)의 이름이고, 우변은 그것을 초기화하는 표현식이다.

		"="의 좌변과 우변의 범위가다르다는 것이다.

		 좌변의 범위는 해당 클로저 클래스의 범위이고,
		 우변의 범위는 람다가 정의되는 지점의 범위와 동일하다.
	*/
	}
	

	namespace Case1 {
		/*
			C++11에서는 직접 작성한 클래스나 std::bind로 초기화 갈무리를 흉내 낼 수 있다.
			C++11에서는 객체를 클로저 안으로 이동할 방법이 없다. 이런 상황에서는, 직접 작성한 클래스나 std::bind로 초기화 갈무리를 흉내내는 방법을 써야 한다.

			바인드 객체를 이용한 방법의 요점은 다음과 같다.

			객체를 C++11 클로저 안으로 이동 생성하는 것은 불가능하나, 객체를 C++11 바인드 객체 안으로 이동 생성하는 것은 가능하다.
			C++11에서 이동 갈무리를 흉내 내는 방법은, 객체를 바인드 객체 안으로 이동 생성하고, 이동 생성된 객체를 람다에 참조로 전달하는 것이다.
			바인드 객체의 수명이 클로저의 수명과 같으므로, 바인드 객체 안의 객체들을 마치 클로저 안에 있는 것처럼 취급하는 것이 가능하다.
		*/

		inline void RunSample() {
			std::vector<double> vec = { 0.0, 1.0, 2.0, 3.0 };
			auto func = std::bind // C++11에서 초기화 캡쳐 흉내
				(                                    
					[](const std::vector<double>& data)        
					{ 
						for (int i = 0; i < data.size(); i++)
						{
							std::cout << data[i] << " ";
						} 
						std::cout << std::endl;
					},               
					std::move(vec)
				);
			func();


			/*
				기본적으로, 람다로부터 만들어진 클로저 클래스의 operator() 멤버 함수는 const이다.
		
				이 때문에 람다 본문 안에서 클로저의 모든 데이터 멤버는 const가 된다.
				=> 이 부분 실제 실행해보면 값 수정이 가능하다. const 가 아닌가 보다
			
				그러나 바인드 객체 안의 이동 생성된 data 복사본은 const가 아니다.

				만일 람다를 mutable로 선언하면, 
				해당 클로저 클래스의 operator()는 const로 선언되지 않을 것이므로 
				람다의 매개변수 선언에서 const를  제거해야 마땅하다.
			*/
			auto val = std::vector<double>{ 1, 1, 1, 1, 1 };
			auto func2 = std::bind
			(
				[](std::vector<double>& data) mutable
				{
					for (int i = 0; i < data.size(); i++)
					{
						data[i] = i;
					}
					for (int i = 0; i < data.size(); i++)
					{
						std::cout << data[i] << " ";
					}
					std::cout << std::endl;
				},
				val
			);
			func2();
			std::cout << "==============" << std::endl;
		}
	}
	
}