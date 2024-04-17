#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <thread>
#include <future>

//스레드 기반 프로그래밍보다 task 기반 프로그래밍을 선호하라
//**이번 장은 설명이 많으니 자세한 사항은 직접 책을 봅시다.
//혹은 http://ajwmain.iptime.org/programming/book_summary/%5B03%5Deffective_modern_cpp/effective_modern_cpp.html#I29

namespace Item35 {
	using namespace std;

	/*
		std::thread API에서는 비동기적으로 실행된 함수의 반환값을 직접 얻을 수 없으며, 만일 그런 함수가 예외를 던지면 프로그램이 종료된다.
	*/

	int doAsyncWork(void) { return 0; }

	

	inline void RunSample() {
		/*
			doAsyncWork라는 함수를 비동기적으로 실행한다고 하자. 
			방법은 크게 두 가지이다. 
			
			하나는 std::thread 객체를 생성해서 그 객체에서 doAsyncWork를 실행하는 것이다. 이는 스레드 기반(thread-based) 프로그래밍에 해당한다.

			또 하나는 doAsyncWork를 std::async에 넘겨주는 것이다. 이는 task 기반(task-based) 프로그래밍에 해당한다.
			(원서 정오표는 단지 std::async를 사용한다고 해서 저절로 task 기반 프로그래밍이 되는 것은 아니다)
		*/
		std::thread t(doAsyncWork);
		auto future = std::async(doAsyncWork);

		/*
			이런 호출에서, std::async에 절달된 함수 객체는 하나의 task로 간주된다.

			doAsyncWork는 반환값을 돌려주는데, 스레드 기반 호출에서는 그 반환값에 접근할 방법이 없다. 
			그러나 task 기반 접근방식에서는, std::async 객체가 돌려주는 future 객체에있는 get이라는 멤버 함수를 통해 반환값에 접근할 수 있다.

			doAsyncWork가 예외를 방출한 경우, get을 통해서 그 예외에 접근할 수도 있다. 
			스레드 기반 접근방식에서는, doAsyncWork가 예외를 던지면 프로그램이 죽는다(std::terminate 호출을 통해서).
		*/
	}

	/*
		스레드 기반 프로그래밍에서는 스레드 고갈, 과다구독(oversubscription), 부하 균형화, 새 플랫폼으로의 적응을 여러분이 직접 처리해야 한다.

		소프트웨어 스레드는 제한된 자원이다. 
		시스템이 제공할 수 있는 것보다 많은 소프트웨어 스레드를 생성하려고 하면 std::system_error 예외가 발생한다. 
		이는 스레드에서 실행하고자 하는 함수가 예외를 던질 수 없는 경우에도 마찬가지이다.

		스레드 기반 프로그래밍에서는 이런 스레드 부족을 프로그래머가 직접 처리해야 한다. 
		한 가지 접근방식은 doAsyncWork를 그냥 현재 스레드에서 실행하는 것이지만, 그러면 현재 스레드에 부하(load)가 과중하게 걸릴 수 있다. 
		만일 현재 스레드가 GUI 스레드라면 사용자 입력에 대한 반응성 문제가 발생할 수 있는 것이다.

		가용 스레드가 모자라지 않는다고 해도, 과다구독(oversubscription) 때문에 문제가 발생할 수 있다. 
		과다구독(oversubscription)이란 실행 준비가 된 소프트웨어 스레드가 하드웨어 스레드보다 많은 상황을 가리킨다.

		과다구독(oversubscription)이 발생하면 스레드 스케줄러(보통의 경우 OS의 일부)는 하드웨어상의 실행 시간을 여러 조각으로 나누어 소프트웨어 스레드들에게 배분한다. 
		이 과정에서 문맥 전환(context switch)이 수행된다. 그러한 문맥 전환은 시스템의 전반적인 스레드 관리 부담을 증가시킨다.

		결과적으로 여러분이 과다구독(oversubscription)을 피하도록 응용 프로그램을 잘 조율한다고 해도, 그 해법이 다른 종류의 컴퓨터에서도 잘 작동하리라는 보장은 없다.
	*/

	/*
		std::async와 기본 시동 방침(launch policy)을 이용한 task 기반 프로그래밍은 그런 대부분의 문제를 알아서 처리해준다.

		std::async를 사용하면 스레드 부족으로 인해 예외가 발생할 가능성이 크게 줄어든다. 
		기본 시동 방침(launch policy)을 지정한 호출에서는 std::async가 새 소프트웨어 스레드를 생성하지 않을 수도 있다.

		대신 std::async는 지정된 함수를 doAsyncWork의 결과가 필요한 스레드(즉, fut에 대해 get이나 wait를 호출하는 스레드)에서 실행하라고 스케줄러에게 요청할 수 있으며, 
		합리적인 스케줄러는 시스템이 과다구독(oversubscription)되었거나 스레드가 부족한 상황에서 그러한 자유의 장점을 취한다.

		최신의 스레드 스케줄러는 시스템 전역 스레드 풀을 이용해서 과다구독(oversubscription)을 피하며, 
		작업 훔치기(work-stealing) 알고리즘을 이용해서 부하를 하드웨어 코어들에 좀 더 균형 있게 분산한다.

		스레드를 직접 다루는 게 적합한 경우도 존재한다. 이를테면
		1. 바탕 스레드 적용 라이브러리의 API에 접근해야 하는 경우
		2. 응용 프로그램의 스레드 사용량을 최적화해야 하는, 그리고 할 수 있어야 하는 경우
		3. C++ 동시성 API가 제공하는 것 이상의 스레드 적용 기술을 구현해야 하는 경우.

	*/
}