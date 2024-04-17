#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <mutex>
using namespace std;

// 0�� NULL���� nullptr�� ��ȣ�϶�

namespace Item08 {

	/*
		NULL �� ��쿡 ���� �� �����͸� ��Ī�� �� ����ϴ� ��찡 �ִ�.

		������ NULL �� ������ ���� int Ȥ�� long �� ���� �ֱ� ������ �߸� ����Ѵٸ� ������ �߱��Ѵ�.
		��ǥ���� ���÷δ� �������İ� ������ ������ �����ε� �Ǿ� ���� ���.
	*/

	/*
		nullptr�� ������ �̰��� ���� ������ �ƴ� ��. ������ ���ĵ� �ƴϴ�. ��� ������ �����ͷ� �����ؾ��Ѵ�.

		nullptr�� ���� ������ std::nullptr_t �̸�, std::nullptr_t �� ��ȯ ���� ������� �ٽ� "nullptr�� ����"���� ���ǵȴ�.
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
		f(0);		//f(int) ȣ��
		f(NULL);	//f(int) ȣ��, f(void*)�� �ƴ�
		f(nullptr);	//f(void*) ȣ��

		std::nullptr_t np;

		auto result = finalResult();
		if (result == 0) {	// ���� ������ �ǹ��ϴ��� ������ �������� ��Ȯ���� �ʴ�.

		}


		if (result == nullptr) {

		}
		/*
			�࿩�� finalResult�� ��ȯ Ÿ���� �ľ��ϱⰡ ��ٷο� ���, 
			nullptr�� result�� ������ Ÿ������ ��Ȯ�ϰ� �˷��ش�.
		*/

		//���ؽ����� Ȱ��
		std::mutex f1m, f2m, f3m;	//f1, f2, f3�� ���ؽ���
		using MuxGuard = std::lock_guard<std::mutex>;

		{
			MuxGuard g(f1m);
			auto result = f1(0);
		}//���ؽ� ����
		{
			MuxGuard g(f2m);
			auto result = f2(NULL);
		}//���ؽ� ����
		{
			MuxGuard g(f3m);
			auto result = f3(nullptr);
		}//���ؽ� ����

		/*
			���� ���ô� ������

			�ڵ� �ݺ��� ������ �����Ƿ� ���ø�ȭ�� ���� �ٽ� �ۼ��ϸ�
		*/
		//auto result1 = LockAndCall(f1, f1m, 0);			//����
		//auto result2 = LockAndCall(f2, f2m, NULL);		//����
		auto result3 = LockAndCall(f3, f3m, nullptr);	//�����۵�

		/*
			0�� NULL�� ������ �������� �������� �ʱ� ������ ������ ������ �߻��Ѵ�.
			�ݸ� nullptr�� ��� �������� �����Ѵ�.
		*/
	}
}