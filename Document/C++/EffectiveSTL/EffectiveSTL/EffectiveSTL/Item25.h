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
#include <unordered_map>

//현재는 표준이 아니지만, 해쉬 컨테이너에 대해 충분히 대비해 두자

namespace Item25 {
	using namespace std;

	/*
		c++ 11 이후 실제로 unordered_map/set이 등장하였습니다.
	*/

	/*
		SGI 버전의 해쉬 컨테이너인 hash_set의 타입은 다음과 같이 나타낼 수 있습니다(보기 좋은 형태로 조금 바꾸었습니다).
	*/

	template <typename T,
		typename HashFunction = hash<T>,
		typename CompareFunction = equal_to<T>,
		typename Allocator = allocator<T> >
		class hash_set;
	/*
		눈여겨 볼 점은 비교 함수에 대한 기본 타입으로 equal_to를 사용하고 있다는 것입니다.
		즉, 두 객체가 같은지 알아볼 때 동등성이 아닌 상등성 검사를 한다는 말입니다.

		해쉬 테이블을 생각해 보면, 표준 컨테이너가 목숨 걸고 지키는 정렬 순서가 해쉬 컨테이너에겐 무의미하기 때문에 이런 구현이 어이없는 구현은 아닙니다.

		추가적으로 해쉬 테이블 구현 시, 충돌 처리는 체이닝chaining 기법을 자주 활용합니다. 
		개방주소법 open addressing은 구현이 힘들고 비효율적인 연산과정(해쉬 함수를 두 번 호출하는 등)을 포함할 수 있기 때문입니다.
	*/
}
