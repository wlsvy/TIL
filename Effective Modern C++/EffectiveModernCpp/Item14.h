#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//���ܸ� �������� ���� �Լ��� noexcept�� �����϶�
//���� http://ajwmain.iptime.org/programming/book_summary/%5B03%5Deffective_modern_cpp/effective_modern_cpp.html#I13

namespace Item14 {

	/*
		noexcept�� �Լ��� �������̽��� �Ϻ��̴�. �̴� ȣ���ڰ� noexcept ���ο� ������ �� ������ ���Ѵ�.
		�� noexcept �Լ� �ȿ����� ������ �߸��Ǿ��ٸ� ������ �߻��� �� �ִ� ��.

		

		c++11���� ���ԵǾ�����, c++ 98 �� throw() ���� ����ȭ ������ �� ����.
	*/

	// C++98 ���, f0�� ���ܸ� �������� ����: ����ȭ ������ ����
	int f0(int x) throw() { return 0; }

	// C++11 ���, f1�� ���ܸ� �������� ����: ����ȭ ������ ũ��.
	int f1(int x) noexcept { return 0; }

	/*
		C++11�� ���� ���������� ������� �ൿ�� �ణ �ٸ���. C++11������ ���α׷� ������ ����Ǳ� ���� ȣ�� ������ Ǯ�� ���� �ְ� Ǯ���� ���� ���� �ִ�.

		noexcept �Լ����� �����Ϸ��� ����ȭ��(optimizer)�� ���ܰ� �Լ� �ٱ����� ���ĵ� �� �ִٰ� �ص� ������� ������ Ǯ�� ���� ���·� ������ �ʿ䰡 ����. ����, ���ܰ� noexcept �Լ��� ����ٰ� �ص� noexcept �Լ� ���� ��ü���� �ݵ�� ������ �ݴ� ������ �ı��ؾ� �ϴ� �͵� �ƴϴ�.
		�׷��� ���� ������ "throw()"�� �Լ����� �׷��� ����ȭ �������� ������, ���� ������ �ƿ� ���� �Լ� ���� ���������� �׷� �������� ����.
	*/

	


	//���Ǻ� noexcept ��� ����, �迭/pair swap
	template <class T, size_t N>
	void swap(T(&a)[N],
		T(&b)[N]) noexcept(noexcept(swap(*a, *b)));

	template <class T1, class T2>
	struct pair {
			void swap(pair& p) noexcept(noexcept(swap(first, p.first)) &&
				noexcept(swap(second, p.second)));
	};
	/*
		���� ����� �� swap�� noexcept�� ���� ǥ���ĵ��� noexcept������ �����Ѵ�.

		���� ��� Widget �迭�鿡 ���� swap�� Widget�鿡 ���� swap�� noexcept�� ������ noexcept�� ���̴�.
	*/




	/*
		�Ҹ����� noexcept

		noexcept�� �����ϴ� ���� ���� �߿��� �Ϻ� �Լ����� �⺻������ noexcept�� ����ȴ�.
		�⺻������ ��� �޸� ���� �Լ�(operator delete�� operator delete[] ��)�� ��� �Ҹ��ڴ� �Ϲ������� noexcept�̴�.

		�Ҹ��ڰ� �Ϲ������� noexcept�� ������� �ʴ� ������ ����, 
		���� ���� ���ɼ��� ��������� ����(��, noexcept(false)�� �����) �Ҹ��ڸ� ���� Ÿ���� ������ ����� Ŭ������ ���� �� ���̴�.
	*/


	/*
		std::vector ���� ���Ұ� ���Եɶ� ������ ����� �ʰ��ϸ�, �� ū ũ���� �޸𸮸� ���� �Ҵ��Ѵ�. 
		�� ���, ������ ���ҵ��� �ű�� ������ �����ؾ� �� ��.

		copy semantic�� Ȱ���Ѵٸ� ���� ���Ҹ� �ű� �� �߰��� ������ �߻��ص� ū ������ ������ vector�� ���´� ������ �ʴ´�.

		������ move semantic�� Ȱ���Ѵٸ�, ���� �߿� ������ �߻��� �� ���Ҵ� �۾��� �߰��� ���߰�, vector�� ���´� �������� ���� �״�� ���� �����ǹ�����.
		
		���� std::vector::push_back ���� �Լ��� std::move_if_noexcept�� ȣ���ϴµ�, 
		�̰��� Ÿ���� �̵� �������� noexcept ���ο� ���� ������������ ���Ǻ� ĳ������ �����ϴ�, std::move�� �� �����̴�
	*/
	class Widget {
	public:
		Widget() { cout << "default ctor" << endl; }
		Widget(const Widget& rhs) { cout << "copy ctor" << endl; }
		Widget(Widget&& rhs) { cout << "move ctor" << endl; }
	};

	class Gadget {
	public:
		Gadget() noexcept { cout << "default ctor" << endl; }
		Gadget(const Gadget& rhs) noexcept  { cout << "copy ctor" << endl; }
		Gadget(Gadget&& rhs) noexcept  { cout << "move ctor" << endl; }
	};

	inline void RunSample() {

		vector<Widget> vw;
		for (int i = 0; i < 7; i++) {
			vw.push_back(Widget());
		}

		cout << "===============with noexcept=====================" << endl;

		vector<Gadget> gv;
		for (int i = 0; i < 7; i++) {
			gv.push_back(Gadget());
		}
	}

	//���� ���(wide contract),	���� ���(narrow contract)
	/*
		���� ����� ���� �Լ��� ���������� ���� �Լ��� ���Ѵ�. 
		���α׷��� ���¿� �����ϰ� ȣ���� �� ������, ȣ���ڰ� �����ϴ� �μ��鿡 �� � ���൵ ������ �ʴ´�. 
		���� ��� �Լ��� ���� ������ �ൿ�� ������ �ʴ´�.
		
		���� ����� ���� �Լ��� �ƴ� �Լ����� ��� ���� ����� ���� �Լ��̴�. 
		�׷� �Լ��� ��� �Լ��� ���������� ���ݵǸ� �� ����� ������ �ൿ�̴�.
		
		���� ����� ���� �Լ��� �ۼ��ϴ� ���, ���� �� �Լ��� ���ܸ� ������ ������ �˰� �ִٸ� noexcept�� �����ϴ� ���� ���� ���̴�.
		
		���� ����� ���� �Լ��� �Լ� ������ ���������� �����Ͽ����� �˸��� ���ܸ� ���� ���ɼ��� �ִ�. 
		������ ���ܸ� ������ϴ� ���� ������ �ൿ�� ������ �����ϴ� �ͺ��� �� ���� �����̴�.
		
		�̷� ������, ���� ���� ���� ����� �����ϴ� ���̺귯�� �����ڵ��� ���� ����� ���� �Լ��鿡 ���ؼ��� noexcept�� ����ϴ� ������ �ִ�
	*/



	// ������ �ڵ�� �Ϻ��� ������ �ڵ��̴�.
	void setup(void) {}
	void cleanup(void) {}

	void doWork(void) noexcept
	{
		setup();        
		cleanup();      
	}

	/*
		���⼭ doWork�� noexcept �Լ�
		setup�� cleanup�� noexcept�� �ƴϴ�
		
		�̴� ����� �Ϸ� ��������, ��¼��
		�׳� ����ȭ�� ������ ���� �ִ�.
		
		��, setup�� cleanup�� ��� noexcept��
		����Ǿ� ������ ������, �����δ� ���ܸ� ����� ������ ���� ���� �ִ�.
		
		�̸��׸�, C�� �ۼ��� ���̺귯���� �Ϻδ� ���ܸ� ������ �������� noexcept ������ �ȵ� ��찡 �ִ�.
		
		�ƴϸ�, C++98�� ���� ������ ������� �ʱ�� ������, 
		�׸��� C++11�� �°� ���ŵ����� ���� � C++98 ���̺귯���� �Ϻ��� ���� �ִ�.
		
		��ó�� noexcept �Լ��� ������ ������ noexcept ������ ���� �ڵ忡 �����ϴ�
		��찡 �����Ƿ�, C++�� �̷� �ڵ带 ����ϸ�, �Ϲ������� �����Ϸ��� �̿� ���� ��� �޽����� ǥ������ �ʴ´�.
	*/
}