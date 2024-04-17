#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>

//������ ���� �ڿ��� �������� std::unique_ptr�� ����϶�

namespace Item18 {
	using namespace std;
	/*
	std::unique_ptr�� ���� ������ �ǹ̷��� ���� �ڿ��� ������ ����, �۰� ���� �̵� ���� ����Ʈ �������̴�.
	std::unique_ptr�� �⺻������ �� �����Ϳ� ���� ũ���� ������ �� ������, ��κ��� ����(�������� ����ؼ�)���� �� �����Ϳ� ��Ȯ�� ������ ��ɵ��� �����Ѵ�.

	std::unique_ptr�� ������ ������(exclusive ownership) �ǹ̷��� ü���ϰ� �ִ�. 
	���� �ƴ� std::unique_ptr�� �׻� �ڽ��� ����Ű�� ��ü�� �����Ѵ�. std::unique_ptr�� �̵��ϸ� �������� ���� �����Ϳ��� ��� �����ͷ� �Ű�����(���� �����ʹ� �η� �����ȴ�).

	std::unique_ptr�� ����� ������ �ʴ´�. ���� ���簡 ���Ǹ�, �� std::unique_ptr�� ���� �ڿ��� ����ų �Ӹ� �ƴ϶� �� ������ ��� �ڽ��� �� �ڿ��� �����ϰ� �ִٰ�(���� �� �ڿ��� �ı��ؾ� �Ѵٰ�) �����ϴ� ��Ȳ�� ������ ���̴�.

	���� �ƴ� std::unique_ptr�� �Ҹ� �� �ڽ��� ����Ű�� �ڿ��� �ı��Ѵ�. �⺻������, �ڿ� �ı��� std::unique_ptr �ȿ� �ִ� �� �����Ϳ� delete�� ���������ν� ����ȴ�.

	std::unique_ptr�� �� ���� �����ε�, �ϳ��� ���� ��ü�� ���� ��(std::unique_ptr<T>)�̰� �� �ϳ��� �迭�� ���� ��(std::unique_ptr<T[]>)�̴�.

	�� ������ �� �����Ϳ� �޸� std::unique_ptr��, � ������ ��ä(�迭���� ���� ��ü����)�� ����Ű������ ���õ� �ָ����� ���� �߻����� �ʴ´�.

	std::unique_ptr API�� ��� ��� �� �´� ���·� ����Ǿ� �ִ�. ���� ��� ���� ��ü ������ ���� ���� ������(operator[])�� �������� ������, �迭 ������ ������ �����ڵ�(operator*�� operator->)�� �������� �ʴ´�.

	������, ���� �迭���ٴ� std::array�� std::vector, std::string�� ���� �׻� �� ���� �����̴�. �׷��Ƿ� std::unique_ptr�� �迭 ������, ���� ������ �迭�� ����Ű�� �� �����͸� �����ִ� C ��Ÿ�� API�� �ٷ��� �ϴ� ��츦 �����ϸ� ������ �� ������ ã�� �����.
	�⺻������ �ڿ� �ı��� delete�� ���� �Ͼ��, Ŀ���� �����ڸ� ������ ���� �ִ�. ���� �ִ� �����ڳ� �Լ� �����͸� ����ϸ� std::unique_ptr ��ü�� ũ�Ⱑ Ŀ����.

	*/

	inline void TestDestructor();

	inline void RunSample()
	{
		/*
			�� ������(�̸��׸� new �� ���� ������)�� unique_ptr�� �����ϴ� ������ ������ ���� �ʴ´�. 
			�׷� ������ ����Ѵٸ�, �� �����Ϳ��� �ȶ��� �����ͷ��� �Ϲ��� ��ȯ�� �����ϱ� �����̴�.

			�׷� �Ϲ��� ��ȯ���� ������ �����Ƿ�, C++11 �� �ȶ��� �����͵��� �׷� ��ȯ�� �����Ѵ�. 
			new�� ������ ��ü�� �������� �ο��ϱ� ���ؼ��� reset�� Ȱ���ϴ� ����� �����ִ�.

			-> å ������� �ٸ��� �����δ� �Ʒ� �ڵ嵵 ������ ����
		*/
		int* p = new int(30);

		std::unique_ptr<int> up(p);

		/*
			std::unique_ptr�� �����ڸ� �����ϴ� ��� ��ü�� ũ�Ⱑ �ٲ�ϴ�.

			- �Լ� �����͸� �����ڷ� ������ ��� std::unique_ptr �� ũ��� 1���忡�� 2����� �����մϴ�.
			- �����ڰ� �Լ� ��ü�� ��쿡�� ���������� �Լ� ��ü�� ����� ũ�⸸ŭ �����մϴ�.
			- ���� ���� �Լ� ��ü(�̸��׸� ������ ���� ���� ǥ����)�� ��쿡�� ũ�Ⱑ �������� �ʽ��ϴ�.

			���� �����ڸ� ������ �Լ� �����ͷ� �����ϰų� ������ ���� ���� ǥ�������� ������ �� �ִٸ� ���� ���� ��ȣ�ϴ� ���� �����ϴ�.
		*/
		TestDestructor();
	}

	struct OnDestroy {
		void operator()() {
			cout << "On Destroy" << endl;
		}
	};

	//�����ڷ� Ÿ���� �����ϵ�, ��ü�� ũ��� ������Ű�� �ʴ� ����� �����ϰ� �����غ��ҽ��ϴ�.
	template<typename T, typename Dtor>
	class Sample {
	public:
		~Sample() {
			Dtor d;
			d();
		}
	};

	//private ��� Ȱ��. ���� std::unique_ptr�� destructor�� ������ �� private ����� Ȱ���մϴ�.
	template<typename T>
	struct DtorWithNoMemory : private T {
		template<typename U>
		DtorWithNoMemory(U&& val) : T(forward<U>(val)) {}

		~DtorWithNoMemory() {
			(*this)();
		}

	private:
		bool oneByte = true;
	};

	inline void TestDestructor() {
		Sample<int, OnDestroy> s;

		auto dtorLambda = [] { cout << "On Destroy" << endl; };

		DtorWithNoMemory<decltype(dtorLambda)> s(dtorLambda);
		cout << sizeof(s) << endl;	//1����Ʈ
	}
	
}