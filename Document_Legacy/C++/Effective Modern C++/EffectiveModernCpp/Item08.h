#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <mutex>
using namespace std;

// 0과 NULL보다 nullptr을 선호하라

namespace Item08 {

	/*
		NULL 은 경우에 따라 널 포인터를 지칭할 때 사용하는 경우가 있다.

		하지만 NULL 은 구현에 따라 int 혹은 long 일 수도 있기 때문에 잘못 사용한다면 문제를 야기한다.
		대표적인 예시로는 정수형식과 포인터 형식이 오버로딩 되어 있을 경우.
	*/

	/*
		nullptr의 장점은 이것이 정수 형식이 아닌 것. 포인터 형식도 아니다. 모든 형식의 포인터로 생각해야한다.

		nullptr의 실제 형식은 std::nullptr_t 이며, std::nullptr_t 은 순환 정의 방식으로 다시 "nullptr의 형식"으로 정의된다.
	*/

	class Widget{};

	inline void f(int) { cout << "f(int)" << endl; }
	inline void f(bool) { cout << "f(bool)" << endl; }
	inline void f(void*) { cout << "f(void*)" << endl; }

	auto finalResult = []() { return nullptr; };
	auto f1 = [](shared_ptr<Widget> spw)	{ return 0; };
	auto f2 = [](unique_ptr<Widget> upw)	{ return 0.0; };
	auto f3 = [](Widget* pw)				{ return false;};

	template<typename FuncType,
		typename MuxType,
		typename PtrType>
	decltype(auto) LockAndCall(FuncType func, MuxType& mutex, PtrType ptr)
	{
		using MuxGuard = std::lock_guard<std::mutex>;

		MuxGuard g(mutex);
		return func(ptr);
	}

	inline void RunSample() {
		f(0);		//f(int) 호출
		f(NULL);	//f(int) 호출, f(void*)가 아님
		f(nullptr);	//f(void*) 호출

		std::nullptr_t np;

		auto result = finalResult();
		if (result == 0) {	// 정수 형식을 의미하는지 포인터 형식인지 명확하지 않다.

		}


		if (result == nullptr) {

		}
		/*
			행여나 finalResult의 반환 타입을 파악하기가 까다로운 경우, 
			nullptr은 result가 포인터 타입임을 명확하게 알려준다.
		*/

		//뮤텍스에서 활용
		std::mutex f1m, f2m, f3m;	//f1, f2, f3용 뮤텍스들
		using MuxGuard = std::lock_guard<std::mutex>;

		{
			MuxGuard g(f1m);
			auto result = f1(0);
		}//뮤텍스 해제
		{
			MuxGuard g(f2m);
			auto result = f2(NULL);
		}//뮤텍스 해제
		{
			MuxGuard g(f3m);
			auto result = f3(nullptr);
		}//뮤텍스 해제

		/*
			위의 예시는 정상동작

			코드 반복의 여지가 있으므로 템플릿화를 통해 다시 작성하면
		*/
		//auto result1 = LockAndCall(f1, f1m, 0);			//오류
		//auto result2 = LockAndCall(f2, f2m, NULL);		//오류
		auto result3 = LockAndCall(f3, f3m, nullptr);	//정상작동

		/*
			0과 NULL을 포인터 형식으로 추측하지 않기 때문에 컴파일 오류가 발생한다.
			반면 nullptr의 경우 문제없이 동작한다.
		*/
	}
}