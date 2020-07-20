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

//remove와 비슷한 알고리즘을 포인터의 컨테이너에 적용할 때에는 각별히 조심하자

namespace Item33 {
	using namespace std;

	//c++11 스마트 포인터가 소개되기 이전의 내용
	/*
		동적으로 할당된 Widget 객체를 한무더기 만들고 이 객체들을 벡터에 넣어놓았다고 합시다. 
		이 중에서 품질 보증이 되지 않은 객체들을 제거하려고 합니다. 
		
		이 때 remove(혹은 그 비슷한 알고리즘)와 erase를 함께 사용하여 제거하려는 생각이 자연스럽게 들었을 것입니다. 
		하지만 항목 32에서 보았듯이, remove와 비슷한 알고리즘들은 "제거대상" 객체들을 따로 모아놓지 않습니다. 
		즉, 이 경우에는 "제거된" 포인터들을 잃어버려 메모리 누수로 이어질 수 있습니다.
	*/
}