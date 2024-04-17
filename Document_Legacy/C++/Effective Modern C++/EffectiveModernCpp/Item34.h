#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <functional>
#include <chrono>

//std::bind보다 람다를 선호하라

namespace Item34 {
	using namespace std;
	using namespace placeholders;
	using namespace chrono;
	using Time = steady_clock::time_point;
	using Duration = steady_clock::duration;

	enum class Sound { Beep, Siren, Whistle };
	

	namespace Case0 {
		/*
			std::bind를 사용하는 것보다 람다가 더 읽기 쉽고 표현력이 좋다. 그리고 더 효율적일 수 있다.
		*/

		using namespace literals;            // C++14 접미사들을 통해 더 간결하게 표현

		void setAlarm(Time t, Sound s, Duration d)	// 시간 t에서 소리 s를 기간 d만큼 출력한다.
		{
			//...	
		}
		inline void RunSample() {
			auto setSoundL =
				[](Sound sound)
			{
				setAlarm(steady_clock::now() + hours(1),
					sound,
					seconds(30));
			};

			auto setSoundL2 =
				[](Sound sound)
			{
				setAlarm(steady_clock::now() + 1h,        // C++14 버전 의미는 위와 동일
					sound,
					30s);
			};

			//bind를 활용하는 경우
			auto setSoundB =                                // B는 bind를 뜻함
				std::bind(setAlarm,
					steady_clock::now() + 1h,            // 문제 : SetAlarm 이 호출되는 시점이 아닌, binding 객체가 만들어지는 시점에 시간을 계산
					_1,
					30s);

			//문제점을 고쳐보면
			/*
				위의 문제점을 고쳐보면

				* 추가적으로 nested bind 표현식의 경우(bind 매개변수로 bind 객체를 넘길 때) 가장 바깥쪽 bind 객체의 operator() 가 호출될 때.
				내부 bind 객체의 operator()가 먼저 호출되고 그 반환 값이 바깥쪽 bind 객체의 operator()의 매개변수로 전달됩니다.

				-> bind 객체가 그대로 매개변수로 전달되는 것이 아닙니다.
			*/
			auto setSoundB2 =
				std::bind(setAlarm,
					std::bind(std::plus<>(),			//c++14 에서는 표준 연산자 템플릿에 대한 템플릿 타입 인수를 생략할 수 있다. c++11는 그렇지 못하므로 타입을 작성해야한다.
						std::bind(steady_clock::now),
						1h),
					_1,
					30s);
		}
	}

	namespace Case1 {
		//만약에 오버로딩까지 추가된다면

		enum class Volume { Normal, Loud, LoudPlusPlus };
		 
		void setAlarm(Time t, Sound s, Duration d)	
		{
			//...	
		}
		void setAlarm(Time t, Sound s, Duration d, Volume v)  
		{ 	
			//...
		}

		inline void RunSample() {

			//람다는 문제되지 않는다.
			auto setSoundL =
				[](Sound s)
			{
				setAlarm(steady_clock::now() + 1h,  
					s,                              
					30s);                           
			};

			// 반면 std::bind 버전은 컴파일되지 않는다.
			//auto setSoundB =                                // 오류! 어떤 setAlarm인지 모른다.
			//	std::bind(setAlarm,                           
			//		std::bind(std::plus<>(),
			//			std::bind(steady_clock::now),
			//			1h),
			//		_1,
			//		30s);

			using SetAlarm3ParamType = void(*)(Time t, Sound s, Duration d, Volume v);

			auto setSoundB =                                            
				std::bind(static_cast<SetAlarm3ParamType>(setAlarm),    //오버로딩 버전을 명시적으로 지정해줘야 한다.
					std::bind(std::plus<>(),
						std::bind(steady_clock::now),
						1h),
					_1,
					30s);
		}

		/*
			이 경우 람다와 std::bind의 차이점이
			 
			람다의 경우 setAlarm의 호출을 인라인화 (inlining)할 수 있는 보통의 함수 호출이다.
			반면, std::bind의 경우 setAlarm을 함수 포인터를 통해 호출하는데, 함수 포인터를 통한 함수의 호출은 인라인화가 될 가능성이 작다.
			
			즉, 실행속도 측면에서 람다를 사용하는 것이 더 효율적이다.
		*/
	}

	namespace Case2 {
		//코드가 복잡해지면
		inline void RunSample() {

			int lowVal = 0;
			int highVal = 100;

			auto betweenL = [lowVal, highVal](const auto& val)  // C++14
			{ 
				return lowVal <= val && val <= highVal; 
			};

			//bind 활용한 경우, 더 읽기가 힘들다
			auto betweenB =                                    // C++14
				std::bind(std::logical_and<>(),
					std::bind(std::less_equal<>(), lowVal, _1),
					std::bind(std::less_equal<>(), _1, highVal));

		}
	}

	namespace Case3 {
		//

		class Widget {	};

		enum class CompLevel { Low, Normal, High };      

		void compress(const Widget& w, CompLevel lev) {}
			

		inline void RunSample() {

			Widget w;

			auto compressRateB = std::bind(compress, w, _1);
			/*
				w 를 binding 객체에 묶을 때는 값으로 전달된다.

				문제는, 명시적으로 드러나지 않기 때문에 std::bind의 작동 방식을 알고 있어야 이를 알 수 있다는 것이다.

				반면 람다 접근방식에는 w가 값으로 갈무리되는지 아니면 참조로 갈무리되는지 소스 코드에 명백히 드러난다.
			*/

			auto compressRateL = [w](CompLevel lev) // w는 값으로 캡쳐되고 lev는 값으로 전달된다.
			{ 
				return compress(w, lev); 
			};

			compressRateL(CompLevel::High);
			compressRateB(CompLevel::High);
		}
	}
}