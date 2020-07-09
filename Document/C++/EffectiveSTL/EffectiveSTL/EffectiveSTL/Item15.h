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

//잊지 말자! string은 여러 가지 방식으로 구현되어 있다는 사실을

namespace Item15 {
	using namespace std;

	/*
		STL을 효과적으로 사용하기로 결정한 분이라면 현재 나와 있는 제품들이 string을 어떻게 구현해 놓았는지를 알 필요가 있습니다. 
		특히 여러 개의 STL 플랫폼에서 동작하는 코드를 작성하고 있으며 까다로운 수행 성능 조절이 필요한 경우라면 특히 그렇습니다.

		1. string의 문자열 값은 참조 카운팅이 될 수도, 되지 않을 수도 있습니다. 
		기본적으로 많은 라이브러리에서 참조 카운팅을 사용하고 있습니다만, 이 기능의 동작을 막는 방법(대개 전처리자 매크로를 통해)도 제공하고 있습니다.

		2. 참조 카운팅 기능을 막거나 사용해야 하는 경우가 있습니다. 전처리기 매크로 값을 변경하는 방법으로 기능 사용여부를 바꿀 수 있습니다.
		예를 들어, 동일한 문자열이 아주 자주 복사되고 어떤 애플리케이션 자체에서 문자열 복사를 많이 하지 않을 때에만 참조 카운팅이 효과적입니다.

		3. string 객체 자체의 크기(sizeof(string))는 포인터 크기의 한 배에서 일곱 배까지 다양합니다.
		
		4. 문자열을 새로 생성할 때 필요한 메모리 할당의 회수는 0번, 1번, 또는 2번이 될 수도 있습니다.
		
		5. 둘 이상의 string 객체가 문자열 크기나 용량 정보를 함께 가지고 있을 수도, 가지고 있지 않을 수도 있습니다.
		
		6. 문자 버퍼를 위해 할당하는 메모리의 최소량에 대한 정책은 구현된 라이브러리마다 천차만별입니다.

		string 구현 예시는 본 책에서 네 가지 타입이 소개되었습니다. 
	*/
}