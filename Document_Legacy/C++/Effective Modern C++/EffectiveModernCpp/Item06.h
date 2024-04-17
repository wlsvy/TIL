#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//auto �� ������ �ʴ� �������� ������ ������ ����� ������ �ʱ�ġ�� ����϶�

namespace Item06 {
	/*
		�����δ� ������ �ʴ� �븮�� Ÿ���� ������ ��.

		������ �ʴ� �븮�� ���� ������ auto�� �ʱ�ȭ ǥ������ ������ "�߸�" ������ �� �ִ�.
	*/

	inline vector<bool> CreateBoolVector() { return vector<bool>(10); }
	void TestBool(const bool b) { }

	inline void RunSample() {

		bool value = CreateBoolVector()[5];

		auto autoValue = CreateBoolVector()[5];

		/*
			autoValue �� Ÿ���� bool �� �ƴ϶� vector<bool>::reference �̴�.

			std::vector<bool> �� ���, bool ���� 1����Ʈ�� �ƴ� ��Ʈ������ ǥ���ϴµ�

			vector<bool>::reference �� std::vector<bool> �� �����ϴ� ��Ʈ���� ���� �ڷᱸ���� �� ���带 ����Ű�� ������
			+ �ش� ���忡�� ������ ��Ʈ�� �������� ��� �ִ�.
		*/

		TestBool(autoValue);	//��Ÿ�� ���� �߻�
		/*
			CreateBoolVector�� ������ ���ʹ� �ش� �ڵ� ������ ����� ������ �Ҹ�ȴ�. 
			
			�� vector<bool>::reference�� ����Ű�� �����ʹ� dangling �����Ͱ� �Ǹ�, bool ��ȯ �������� ������ �ൿ�� �����Ѵ�.
		*/

	}

	namespace UsingStaticCast {
		/*
			static_cast �� ���� ���� ��� �ʱ�ġ ���뱸�� auto�� ���ϴ� ������ �����ϵ��� �����Ѵ�.

			���� ����ȯ�� �ǵ��� ��Ȯ�ϰ� �巯�� �� �ִ�.
		*/

		inline void RunSample() {

			bool value = CreateBoolVector()[5];
			auto autoValue = static_cast<bool>(CreateBoolVector()[5]);	//autoValue�� �������� bool Ÿ������ ����ȴ�.

			TestBool(autoValue);	//��������
		}
	}
}
