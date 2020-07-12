#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <unordered_map>

//std::shared_ptr처럼 작동하되 대상을 잃을 수도 있는 포인터가 필요하면 std::weak_ptr를 사용하라

namespace Item20 {

	/*
		대체로 std::weak_ptr는 std::shared_ptr를 이용해서 생성한다. 
		std::weak_ptr는 자신을 생성하는 데 쓰인 std::shared_ptr가 가리키는 것과 동일한 객체를 가리키나, 
		그 객체의 참조 카운트에는 영향을 주지 않는다.

		대상을 잃은 std::weak_ptr를 가리켜 만료되었다(expired)라고 말한다. std::weak_ptr의 만료 여부는 멤버 함수 expired가 돌려주는 값으로 판단할 수 있다.
		만료되지 않은 std::weak_ptr이라고 해도 피지칭 객체에 직접 접근하는 것은 불가능하다. std::weak_ptr에는 역참조 연산이 없기 때문이다.

		역참조 연산이 가능하도록 하더라도, 만료 점검과 참조를 분리하면 경쟁 조건이 발생할 수 있다.	
		즉, expired 호출과 역참조 사이에서 다른 어떤 스레드가 해당 객체를 가리키는 마지막 std::shared_ptr를 재대입 또는 파괴할 수도 있기 때문이다. 
		그러면 해당 객체가 파괴되며, 포인터를 역참조하면 미정의 행동이 나온다.

		제대로 된 용법은, std::weak_ptr로부터 std::shared_ptr를 생성하여 사용하는 것이다.
	*/

	/*
		효율성 면에서 std::weak_ptr는 std::shared_ptr와 본질적으로 동일하다.

		std::weak_ptr 객체는 그 크기가 std::shared_ptr 객체와 같으며, 
		std::shared_ptr가 사용하는 것과 같은 제어 블록을 사용하며, 생성이나 파괴, 대입 같은 연산에 원자적 참조 카운트 조작이 관여한다.

		앞에서 언급했듯이 제어 블록에는 '두 번째' 참조 카운트가 있으며 그것이 std::weak_ptr가 조작하는 참조 카운트이다.
		std::weak_ptr의 잠재적인 용도로는 캐싱, 관찰자 목록, 그리고 std::shared_ptr 순환 고리 방지가 있다.
	*/

	class Widget{};

	inline void RunSample() {

		// std::weak_ptr는 std::shared_ptr로부터 얻을 수 있다.

		auto spw = std::make_shared<Widget>(); // spw가 생성된 후, 참조 Widget의 참조 카운트(이하간단히 카운트)는 1이다

		std::weak_ptr<Widget> wpw(spw);        // wpw는 spw와 같은 Widget을 가리킨다; 카운트는 여전히 1이다.

		spw = nullptr;                        // 카운트가 0이 되고 Widget이 파괴된다; 이제 wpw는 대상을 잃은 상태이다.

		// std::weak_ptr가 만료되었는지 알고 싶으면,  expired 멤버 함수가 돌려주는 값을 점검하면 된다.
		if (wpw.expired()) {
			std::cout << "If Expired" << std::endl;
		}


		// std::weak_ptr가 가리키는 피지칭 객체를 역참조 하려면 std::weak_ptr로부터 std::shared_ptr를 얻고 그 std::shared_ptr을 역참조한다.

		// 방법 1: lock 멤버 함수를 사용한다.
		std::shared_ptr<Widget> spw1 = wpw.lock();   
		auto spw2 = wpw.lock();          
										

		// 방법 2: std::shared_ptr의 생성자에 std::weak_ptr를 넘겨준다.
		std::shared_ptr<Widget> spw3(wpw);    // wpw가 만료이면 std::bad_weak_ptr(예외)가 발생
	}

	/*
			캐싱에서 weak_ptr 활용

			loadWidget의 비용이 크고 ID들이 되풀이해서 쓰이는 경우가 많다고 하자.
			그렇다면 loadWidget과 같은 일을 하되 호출 결과들을 캐싱하는 함수를 작성하여 최적화를 할 수 있을 것이다.

			그런데 요청된 모든 Widget을 캐시에 담아 둔다면 그 자체로 성능상의 문제가 발생할 것이므로,
			더 이상 쓰이지 않는 Widget은 캐시에서 삭제하는 것이 자연스럽다.

			이러한 캐시 적용 팩터리 함수의 반환 타입을 std::unique_ptr로 두는 것은 그리 바람직하지 않다.

			호출자가 캐싱된 객체를 가리키는 스마트 포인터를 받아야 한다는 점은 확실하며, 캐시에 있는 포인터들은 자신이 대상을 잃었음을 검출할 수 있어야 한다.
			즉 std::weak_ptr이어야 한다.
	*/

	std::shared_ptr<const Widget> loadWidget(int) {
		return std::make_shared<Widget>();
	}

	std::shared_ptr<const Widget> fastLoadWidget(int id)
	{
		static std::unordered_map<int, std::weak_ptr<const Widget> > cache;

		auto objPtr = cache[id].lock();     
		if (!objPtr) {                      
			objPtr = loadWidget(id);        
			cache[id] = objPtr;             
		}

		return objPtr;
	}
}