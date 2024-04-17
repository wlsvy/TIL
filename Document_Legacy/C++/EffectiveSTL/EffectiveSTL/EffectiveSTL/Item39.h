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
#include <numeric>

//술어 구문은 순수 함수로 만들자

namespace Item39 {
	using namespace std;

	/*
		1. 술어 구문(predicate)이란 bool 값(아니면 내부적으로 bool로 변환될 수 있는 어떤 값)을 반환하는 함수를 일컫습니다. 
		STL에서 폭넓게 사용되는 함수이지요. 표준 연관 컨테이너의 비교 함수가 우선 술어 구문이고요, 
		술어 구문은 공통적으로 find_if 같은 알고리즘과 여러 정렬 알고리즘의 매개 변수로 넘겨집니다.

		2. 순수 함수(pure function)란 이 함수가 반환하는 값이 그 함수의 매개 변수에 종속되는 함수를 일컫습니다.
		특정 클래스의 멤버함수가, 클래스 멤버의 상태에 따라 동작이 영향을 받는다면 그것은 순수 함수가 아닙니다.

		예를 들어, f가 순수 함수이고 x와 y가 객체이면 f(x, y)의 반환 값은 x나 y의 값이 바뀔 때에만 변할 수 있습니다. 
		C++ 에서는, 순수 함수가 사용하는 모든 데이터는 매개 변수로 넘겨지든가 함수가 동작할 동안에 변하지 않은 상태로 있게 됩니다(쉽게 말해 상수 데이터를 말합니다). 
		
		어떤 순수 함수가 있는데, 그 함수가 사용하는 데이터는 함수가 호출될 때마다 변한다고 하면, 이 함수에 똑같은 매개 변수를 넘겨서 여러 번 호출했을 때 매번 다른 결과를 가지게 되므로 "순수 함수"라는 정의에 맞지 않습니다.

		3. 술어 구문 클래스(predicate class)란 operator()가 술어 구문인 함수자 클래스를 말합니다. 
		즉, 이 클래스의 operator()가 true나 false를 반환하는 것입니다. 
		예상하셨겠지만, STL에서 술어 구문을 요구하는 모든 경우에 대하여 술어 구문이나 술어 구문 클래스의 객체를 사용해야 합니다.
	*/

	/*
		함수 객체는 값으로 전달되기 때문에, 여러분은 함수 객체를 설계할 때 복사에 신경 써야 합니다. 
		술어 구문인 함수 객체를 설계할 때에는 이점에 더욱 각별히 주의해야 합니다.

		알고리즘은 내부적으로 함수자의 사본을 만들어 가지고 있을 수가 있는데, 몇몇 알고리즘이 이런 자유도를 이용하여 구현되어 있습니다.
	
		이 사실이 알려주는 가장 큰 교훈은 "술어 구문 함수는 반드시 순수 함수이어야 한다"라는 것입니다.
	*/

	struct BadPredicate {
		//아래는 멤버 변수의 영향을 받으니 순수 함수가 아닙니다. 따라서 STL 알고리즘에 Predicate로 사용하기에는 위험합니다.
		template<typename T>
		bool operator()(const T&) {
			return ++timesCalled == 3;
		}
	private:
		size_t timesCalled = 0;
	};

	inline void RunSample() {
		vector<int> vi(8);
		iota(vi.begin(), vi.end(), 1);
		auto vi2 = vi;

		/*
			아래의 코드는 3번째 원소만 지우는 것이 아니라, 6번째 원소도 같이 삭제합니다.
			remove_if 내부에서 BadPredicate 객체는 값복사 된 후, 

			find_if의 루프 그리고 remove_if 내부 루프에서
			총 두번 제거대상을 찾기 때문입니다.
		*/
		vi.erase(remove_if(vi.begin(), vi.end(), BadPredicate()), vi.end());
	}
}