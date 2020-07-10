#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <string>
#include <array>
#include <set>
#include <memory>

//상등 관계(equality)와 동등 관계(equivalence)의 차이를 파악하자

namespace Item19 {
	using namespace std;

	//두 객체가 "같으냐?"를 알아보는 방법은 상등 관계와 동등 관계를 구분하는 방식으로 나눠집니다.

	class Widget { 
	public:
		int val;
		bool other;
	};

	//객체를 비교할 때 모든 멤버를 확인하지는 않는다고 합시다.
	bool operator==(const Widget & lhs, const Widget & rhs) {
		return lhs.val == rhs.val;
	}
	bool operator< (const Widget& lhs, const Widget& rhs) {
		return lhs.val < rhs.val;
	}

	inline void RunSample() {
		Widget x, y;
		x.val = 3;
		y.val = 3;

		/*
			상등성은 operator== 개념에 뿌리를 둡니다.

			이때 Widget의 모든 데이터 멤버가 같다는 의미는 아닙니다.
			operator==가 일부 데이터 멤버를 무시하도록 구현되었을 수도 있기 때문입니다.
		*/
		auto equality = x == y;
		if (equality) {
			//x와 y는 같(상등)습니다
		}
		else {
			//x와 y는 다릅니다
		}

		/*
			반면, STL에서 동등성은 정렬된 범위 안에 있는 객체 값들의 상대적인 순서에 준하고 있습니다.

			컨테이너 c에 저장되어 있는 어떤 객체 x, y가 있다고 할 때, x와 y 모두가 c의 정렬 순서에 대해 서로의 앞에 오지 않으면 x와 y는 동등하다고 합니다.

		*/
		auto equivalence = !(x < y) && !(y < x);
		if (equivalence) {
			//x와 y는 같(동등)습니다;
		}
		else {
			//x와 y는 다릅니다
		}
		
		/*
			표준 연관 컨테이너에 저장되는 데이터 요소는 정렬된 순서로 관리됩니다. 
			이 때문에 모든 연관 컨테이너에는 요소들을 정렬하는데 사용되는 비교 함수(comparison function)이 반드시 필요합니다.
			
			동등성은 바로 이 비교함수의 동작 원리에 따라 정해지며,
			따라서 컨테이너를 인스턴스화 할 때 비교 함수를 딱 '하나' 지정해 주는 것입니다.(정렬 순서를 정하는 기준이 2개 이상이면 곤란하니까요)
			만일 두 객체의 값이 같은지를 결정할 때 쓰는 기준이 상등성이었다면, 연관 컨테이너는 정렬용 비교 함수 말고도 값이 같은지를 확인하는 함수가 하나 더 필요했을 것입니다.

			대신 STL에서는 상등성이 필요하다면 operator==를 바로 때려 버리는 것이 상례입니다. 
			find 알고리즘이 그 예시입니다.
		*/

		/*
			문자열의 대소문자 구분을 하지 않고 동등성 비교를 하는 set 컨테이너 s가 있다고 가정합시다.

			s.insert("Persephone");
			s.insert("persephone");
			이 경우 중복된 값을 허용하지 않는 set 에는 첫 번째 문자열은 삽입되지만 두 번째 문자열은 무시될 것입니다.(동등성 비교)

			s.find("persephone");
			이 경우 find는 상등성 비교연산을 수행합니다. 즉 해당 탐색은 실패할 것입니다.
		*/
	}
}