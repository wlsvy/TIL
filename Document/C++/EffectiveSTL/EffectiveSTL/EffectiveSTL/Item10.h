#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <string>
#include <array>

//할당자(allocator)의 일반적인 사항과 제약 사항에 대해 잘 알아두자

namespace Item10 {
	using namespace std;

	/*
		1. 할당자를 템플릿으로 만듭니다. 템플릿 매개 변수에는 여러분이 메모리를 할당하고자 하는 객체의 타입을 나타내는 T를 사용합니다.

		2. pointer와 reference라는 typedef 타입을 제공하되, 항상 pointer는 T*, reference는 T&이도록 합니다.

		3. 할당자에는 객체별 상태를 절대로 주지 않습니다. 일반적으로, 할당자는 비정적 데이터 멤버를 가질 수 없습니다.

		이렇게 되어야 하는 근거는 list::splice 멤버 함수에서 찾을 수 있습니다.

		기억하고 계시겠지만, splice에 의해 어떤 리스트 요소를 다른 리스트 요소에 옮겨 붙일 때에는 복사가 일어나지 않습니다. 
		포인터 몇 개가 바뀌면서 원래의 리스트에 있던 노드가 다른 리스트로 자리를 찾아갈 뿐입니다. 
		이 때문에 splice 동작은 빠르고 예외 안전성을 갖추고 있습니다.
		
		splice함수를 사용하여, list L1에서 list L2로 일부 요소를 옮겼다고 생각해 봅시다. 
		그리고 이제 L2가 소멸된다고 생각해 봅시다.
		
		L2의 요소들의 일부는 L1에서 왔으므로, 그 요소들은 L1의 할당자가 메모리를 해제하는 방법과 동일한 방법으로 메모리를 해제해야 합니다. 
		이 때 L2와 L1의 할당자가 서로 다른 방식으로 메모리를 해제한다면 매우 골치가 아플 것이 뻔합니다.
		
		이러한 이유로 표준안에서 STL 제작자는 동일한 타입의 할당자가 동등한 것으로 가정하도록 한 것입니다.

		4. 할당자의 allocate 멤버 함수에는 필요한 객체의 개수를 매개 변수로 넘깁니다. 바이트 수가 아닙니다. 
		또한, 이 함수는 T* 포인터(pointer라는 typedef 타입을 통해)를 반환(비록 T 객체는 아직 생성되지 않았지만)한다는 것도 잊지 맙시다.

		즉 operator new의 프로토타입이 다음과 같다면,

		void* operator new(size_t bytes);
		
		할당자자 allocate 멤버 함수의 프로토타입은 다음과 같을 것입니다.
		
		pointer allocator<T>::allocate(size_type numObjects);
		
		"pointer"는 거의 항상 T* 에 대응된 typedef 타입이라는 사실을 기억하세요.
	*/

	/*
		5. 표준 컨테이너(노드 기반 컨테이너)에서 필요로 하는 rebind라는 중첩 템플릿을 꼭 제공합니다.
	*/
	//리스트 구현이 이렇게 되어있다고 가정한다면
	template <typename T, typename Allocator = allocator<T>> 
		class list {
		private:
			// 타입 T의 객체에 대한 할당자
			Allocator alloc;   

			// 연결 리스트 내의 노드
			struct ListNode {                        
				T data;
				ListNode *prev;
				ListNode *next;
			};
	};

	//표준 할당자는 실제로 이렇게 선언되어 있지만, 사용자가 작성한 할당자 템플릿이 될 수도 있습니다.
	template <typename T>                     
	class allocator {                         
	public:                             
		/*
			list<T>를 구현한 코드를 보면 우리가 T에 대해 만든 할당자에 대응하는, ListNode에 대한 할당자 타입을 결정해야 한다는 것을 알 수 있습니다.
 
			리스트 노드의 구조를 본다면, 타입 T를 바로 할당하는 것이 아닌, T를 타입 매개변수로 가지는 ListNode를 할당하는 할당자가 필요한 것을 알 수 있습니다.

			우리가 T에 대해 만든 할당자 타입은 템플릿 매개 변수인 Allocator입니다.
		*/
		template <typename U>
		struct rebind {
			typedef allocator<U> other;
		};
	};
}
