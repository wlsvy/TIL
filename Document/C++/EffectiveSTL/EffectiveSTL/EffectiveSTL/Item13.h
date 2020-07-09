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

//동적으로 할당한 배열보다는 vector와 string이 낫다

namespace Item13 {
	using namespace std;

	/*
		언제든 배열을 동적으로 할당할 자세를 잡고 코딩에 들어가기 전에(이를테면 "new T[...]"라고 쓰려고 생각했다든지), 그 대신 vector나, string을 고려해 보세요
		(대개 T가 문자 타입이면 string을, T가 이외의 타입이면 vector를 사용합니다).

		- vector와 string은 자체적으로 메모리 관리를 하기 때문에 프로그래머가 져야 부담을 없애줍니다.
	*/
}