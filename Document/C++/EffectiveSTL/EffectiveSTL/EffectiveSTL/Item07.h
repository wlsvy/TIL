#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <string>
#include <array>

//new로 생성한 포인터의 컨테이너를 사용할 때에는 컨테이너가 소멸되기 전에 포인터를 delete하는 일을 잊지 말자

namespace Item07 {
	using namespace std;

	//c++11 스마트 포인터가 소개되기 이전의 내용
	/*
		컨테이너는 자신이 소멸될 때 각 요소 자체를 없애 주기는 합니다. 
		하지만 요소의 타입이 포인터인 경우엔 포인터의 소멸자가 아무런 일도 하지 않기 때문에, 
		new로 동적할당한 객체의 포인터를 담는 컨테이너가 소멸될 때에 각 요소를 delete 해 주지 않으면 메모리 누수가 일어납니다.
	*/

	class Widget{};

	namespace BadCase {
		inline void RunSample() {
			static unsigned int SOME_MAGIC_NUMBER = 100;

			{
				vector<Widget*> vwp;
				for (int i = 0; i < SOME_MAGIC_NUMBER; ++i)
				{
					vwp.push_back(new Widget);
				}
			}// Widget은 여기서 샙니다!!

			{
				vector<Widget*> vwp;
				for (auto i = vwp.begin(); i != vwp.end(); ++i) {
					delete *i;
				}

				// 이 코드는 무난하지만 여전히 문제가 남아 있습니다.
				/*
					한 가지 문제는 for_each가 하는 일을 for 루프로 대신하고 있는데, 이것은 for_each 만큼 명확하지 못하다(항목 43을 참조)는 것입니다.

					또 한 가지의 문제는 이 코드는 예외 안전성(exception safety)을 갖추고 있지 않다는 것입니다.
					delete를 수행하는 for문 직전에 예외가 발생하면, 불쌍한 메모리는 다시 샙니다.
				*/
			}
		}
	}

	namespace UsingFunctionObject {
		template<typename T>
		struct DeleteObject : public unary_function<const T*, void> {
			void operator()(const T* ptr) const {
				delete ptr;
			}
		};
		//unary_function은 항목 40에서 설명

		struct DeleteObject2 {

			// 템플릿이 여기서 선언됩니다.
			template<typename T>
			void operator()(const T* ptr) const {
				delete ptr;
			}
		};

		inline void RunSample() {
			{
				vector<Widget*> vwp;
				for_each(vwp.begin(), vwp.end(), DeleteObject<Widget>());

				/*
					여기서는 DeleteObject가 삭제하려고 하는 객체의 타입을 직접 지정해 주어야 합니다.
					이는 추적이 힘든 버그를 일으킬 수 있습니다.
					-> 가상 소멸자를 선언하지 않은 객체에 대해서 기반 클래스 포인터로 delete하는 경우(예를 들어 string을 상속한 클래스)
				*/
			}
			{
				vector<Widget*> vwp;
				for_each(vwp.begin(), vwp.end(), DeleteObject2());
				/*
					이제 예상한 대로 동작합니다!
					
					하지만 예외 안전성이 없다는 슬픈 현실은 여전히 남아 있습니다.
					for_each가 호출되기 전에 오류가 발생한다면 자원은 그대로 누수되어버립니다.
				*/
			}
			
		}

		/*
			예외 안전성을 갖추는 가장 간단한 방법은 아마도, 포인터의 컨테이너 대신에 스마트 포인터의 컨테이너를 사용하는 것입니다.
		*/

	}
}

