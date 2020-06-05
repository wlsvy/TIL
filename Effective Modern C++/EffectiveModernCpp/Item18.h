#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>

//소유권 독점 자원의 관리에는 std::unique_ptr를 사용하라

namespace Item18 {

	/*
	std::unique_ptr는 독점 소유권 의미론을 가진 자원의 관리를 위한, 작고 빠른 이동 전용 스마트 포인터이다.
	std::unique_ptr는 기본적으로 생 포인터와 같은 크기라고 가정할 수 있으며, 대부분의 연산(역참조를 비롯해서)에서 생 포인터와 정확히 동일한 명령들을 실행한다.

	std::unique_ptr는 독점적 소유권(exclusive ownership) 의미론을 체현하고 있다. 
	널이 아닌 std::unique_ptr는 항상 자신이 가리키는 객체를 소유한다. std::unique_ptr를 이동하면 소유권이 원본 포인터에서 대상 포인터로 옮겨진다(원본 포인터는 널로 설정된다).

	std::unique_ptr의 복사는 허용되지 않는다. 만일 복사가 허용되면, 두 std::unique_ptr가 같은 자원을 가리킬 뿐만 아니라 두 포인터 모두 자신이 그 자원을 소유하고 있다고(따라서 그 자원을 파괴해야 한다고) 생각하는 상황이 벌어질 것이다.

	널이 아닌 std::unique_ptr는 소멸 시 자신이 가리키는 자원을 파괴한다. 기본적으로, 자원 파괴는 std::unique_ptr 안에 있는 생 포인터에 delete를 적용함으로써 수행된다.

	std::unique_ptr는 두 가지 형태인데, 하나는 개별 객체를 위한 것(std::unique_ptr<T>)이고 또 하나는 배열을 위한 것(std::unique_ptr<T[]>)이다.

	이 때문에 생 포인터와 달리 std::unique_ptr는, 어떤 종류의 개채(배열인지 개별 객체인지)를 가리키는지에 관련된 애매함이 절대 발생하지 않는다.

	std::unique_ptr API는 사용 대상에 잘 맞는 형태로 설계되어 있다. 예를 들어 개별 객체 버전은 색인 적용 연산자(operator[])를 제공하지 않으며, 배열 버전은 역참조 연산자들(operator*와 operator->)을 제공하지 않는다.

	하지만, 내장 배열보다는 std::array나 std::vector, std::string이 거의 항상 더 나은 선택이다. 그러므로 std::unique_ptr의 배열 버전은, 힙에 생성된 배열을 가리키는 생 포인터를 돌려주는 C 스타일 API를 다루어야 하는 경우를 제외하면 마땅히 쓸 이유를 찾기 힘들다.
	기본적으로 자원 파괴는 delete를 통해 일어나나, 커스텀 삭제자를 지정할 수도 있다. 상태 있는 삭제자나 함수 포인터를 사용하면 std::unique_ptr 객체의 크기가 커진다.

	*/

	inline void RunSample()
	{
		/*
			생 포인터(이를테면 new 로 얻은 포인터)를 unique_ptr에 배정하는 문장은 컴파일 되지 않는다. 
			그런 문장을 허용한다면, 생 포인터에서 똑똑한 포인터로의 암묵적 변환이 성립하기 때문이다.

			그런 암묵적 변환에는 문제가 있으므로, C++11 의 똑똑한 포인터들은 그런 변환을 금지한다. 
			new로 생성한 객체의 소유권을 부여하기 위해서는 reset을 활용하는 방법이 따로있다.

			-> 책 설명과는 다르게 실제로는 아래 코드도 컴파일 가능
		*/
		int* p = new int(30);

		std::unique_ptr<int> up(p);
	}
	
}