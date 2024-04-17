#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <string>
#include <array>
#include <set>

//단일 요소를 단위로 동작하는 멤버 함수보다 요소의 범위를 단위로 동작하는 멤버 함수가 더 낫다

namespace Item05 {
	using namespace std;

	class Widget{};
	inline void RunSample() {
		vector<Widget> v1, v2;      
		
		// v1의 내용을 v2의 뒷쪽 반과 똑같이 만드는 가장 빠른 방법은 무엇일까요?

		//멤버함수 assign을 활용하는 것이 best입니다.
		v1.assign(v2.begin() + v2.size() / 2, v2.end());


		// 반복문을 사용하면
		v1.clear();
		for (auto ci = v2.begin() + v2.size() / 2; ci != v2.end(); ++ci) {
			v1.push_back(*ci);
		}

		//비멤버 함수 copy를 사용하면
		v1.clear();
		copy(v2.begin() + v2.size() / 2, v2.end(), back_inserter(v1));

		//copy의 경우 내부구현상 루프문을 활용하고 있다는 사실을 알아 둡시다.

	}

	/*
		단일 요소 멤버 함수보다 범위 멤버 함수가 더 좋은 이유
		1. 범위 멤버 함수를 사용한 코드가 대개 짧다(즉, 프로그래머의 손이 덜 아프다).
		2. 범위 멤버 함수는 훨씬 명확하고 간결한 의미를 전달한다.

		그리고 불필요한 실행 비용들(vector)

		첫째, 단일 요소 함수는 배열의 멤버 수 만큼 호출되어야 하지만, 범위 멤버 함수는 딱 한 번만 호출되면 되므로 함수 호출 비용이 적게 듭니다

		둘째, 벡터에 들어 있던 기존의 데이터들을 미는 횟수에서 차이가 납니다. 
		단일 요소 함수는 배열의 요소들을 하나 씩 삽입하기 때문에 총 복사 횟수는 (배열의 총 요소 수) * (벡터에 들어 있던 요소의 수) 만큼이 됩니다. 
		반면 범위 멤버 함수의 경우 몇 개가 삽입되는지를 미리 알 수 있기 때문에, (벡터에 들어 있던 요소의 수) 만큼만 복사(딱 한번만 밉니다)가 일어납니다.

		셋째, 메모리 할당에 관한 것입니다. 대부분의 경우 벡터는 메모리가 꽉 찰 때마다 자신의 용량을 두 배로 늘리도록 구현이 되어 있습니다. 
		즉 n개의 새 데이터 요소를 하나씩 삽입하려고 하면 메모리 할당을 log2n번이나 하게 되는 셈입니다. 
		반면 범위 멤버 함수를 쓰면 삽입할 요소의 수를 미리 알 수 있으므로 딱 한 번 필요한 메모리를 할당하면 됩니다.

		vector에 대해서 설명드린 내용은 string에서도 동일하게 적용됩니다. 
		deque의 경우 다른 메모리 관리 방식을 취하므로 반복적인 메모리 재할당의 경우는 맞지 않습니다.
		list의 경우 비싼 비용이 아니지만, 내부 노드의 prev, next 포인터 재설정이 더 많이 발생합니다.
		연관 컨테이너에 대해서는 어떨까요? 단일 요소 버전의 insert에서 여전히 반복 함수 호출의 오버헤드가 있긴 하지만 딱 부러지게 효율이 어떻다라고는 말씀드리기 힘듭니다.
	*/

	

	inline void Example() {
		/*
			범위를 지원하는 멤버 함수는 어떤 것인지 미리 알아놓고 정리해 두면, 나중에 이것들을 사용할 기회를 포착하기가 매우 쉬울 것입니다.

			아래는 벡터를 예시로 작성해두었습니다.
		*/

		vector<int> v;

		// ※ 범위 생성(Range Construction) : 모든 표준 컨테이너는 다음과 같은 형태의 생성자를 지원하고 있습니다.
		/*
			container::container(InputIterator begin,        // 범위의 시작
                    InputIterator end);            // 범위의 끝
		*/
		vector<int> newVec(v.begin(), v.end());

		// ※ 범위 삽입(Range Insertion) : 모든 표준 컨테이너는 다음과 같은 형태의 insert를 지원하고 있습니다.
		/*
			void container::insert(iterator position,        // 범위를 삽입할 위치
                    InputIterator begin,        // 삽입할 범위의 시작
                    InputIterator end);            // 삽입할 범위의 끝
		*/
		newVec.insert(newVec.begin(), v.begin(), v.end());
		/*
			연관 컨테이너는 자신이 가지고 있는 비교 함수를 사용하여 삽입될 요소가 놓일 위치를 결정하기 때문에 위치 매개 변수를 가지고 있지 않은 시그너쳐를 제공합니다.
			void container::insert(InputIterator begin, InputIterator end);
		*/

		// ※ 범위 삭제(Range Erasure) : 역시 표준 컨테이너에서 범위 버전의  erase를 제공하고 있지만, 반환 타입은 시퀸스 컨테이너와 연관 컨테이너에 대해서 각각 다릅니다.
		/*
			시퀸스 컨테이너에선 다음과 같은 형태를 쓸 수 있고,
			iterator container::erase(iterator begin, iterator end);

			반면에 연관 컨테이너에서는 다음과 같은 형태를 쓸 수 있습니다.
			void container::erase(iterator begin, iterator end);

			연관 컨테이너의 경우, 삭제한 반복자의 바로 뒤에 있는 요소를 가리키게 한다면 상당한 성능저하가 나타난다고 합니다.
			(현재는 연관 컨테이너도 반환값을 가진다)
		*/
		auto iter = newVec.erase(newVec.begin(), newVec.end());

		// ※ 범위 대입(Range Assignment) : 모든 표준 시퀸스 컨테이너는 범위 버전의 assign을 제공하고 있습니다.
		/*
			void container::assign(InputIterator begin, InputIterator end);
		*/
		newVec.assign(v.begin(), v.end());
	}
}