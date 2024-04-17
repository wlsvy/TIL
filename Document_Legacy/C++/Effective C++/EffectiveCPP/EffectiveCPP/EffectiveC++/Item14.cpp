#include <iostream>
#include <vector>
#include <string>
#include <mutex>
#include <thread>
using namespace std;

//자원 관리 클래스의 복사 동작에 대해 진지하게 고찰하자

namespace Item14 {

	
	class Lock {
	public:
		explicit Lock(mutex *pm) : mutexPtr(pm) 
		{ 
			//자원 획득 시 뮤텍스 잠금
			mutexPtr->lock(); 
		}	
		~Lock() 
		{ 
			//소멸 시 뮤텍스 잠금 해제
			mutexPtr->unlock(); 
		}	
	private:
		mutex *mutexPtr;
	};

	void doSomething() {
		mutex m;

		//스코프를 통해 활용 영역지정
		{	
			//뮤텍스에 잠금 설정
			Lock m1(&m);	

			//... -> 임계 영역에서 연산 수행
		}					
		//블록을 벗어날 경우 뮤텍스 잠금 해제


		{
			//Lock 복사하는 경우는 어떻게 처리해야 하는지??
			Lock m1(&m);
			Lock m2(m1);	

			/*
				1. 복사를 금지 : 
				복사기능이 적합하지 않은 RAII 클래스는 
				애초에 복사를 막아 두는 것이 권장된다.

				class Lock : private Uncopyable {...};

				2. 관리하고 있는 자원에 대해 참조 카운팅 수행 :
				shared_ptr 를 활용하는 방법이 있다.

				3.관리하고 있는 자원을 진짜로 복사
				string 을 예시로 들 수 있다. 
				깊은 복사를 활용하여 힙 메모리의 데이터까지 복사
				
				4. 관리하고 있는 자원의 소유권을 이전
				unique_ptr 의 소유권 이전과 같은 방식으로 동작하게끔 설계
			*/
		}
	}

	class SharedLock {
	public:
		//삭제자로 unlock 함수를 사용해서 mutex 객체를 반환하는 것이 아닌 다시 잠금해제하는 것으로 변경
		explicit SharedLock(mutex* pm) : mutexPtr(pm, SharedLock::Unlock) 
		{
			mutexPtr->lock(); 
		}	
		
	private:
		//삭제자(deleter) 로 사용할 함수
		static void Unlock(mutex* pm) { pm->unlock(); }	

		//shared_ptr 사용
		std::shared_ptr<mutex> mutexPtr;	
	};
}