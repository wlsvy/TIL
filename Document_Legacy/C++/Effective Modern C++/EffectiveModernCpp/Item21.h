#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <Windows.h>
#include <malloc.h>
#include "MemoyUsage.h"

using namespace std;

//new�� ���� ����ϴ� �ͺ��� std::make_unique�� std::make_shared �� ��ȣ�϶�

namespace Item21 {

	/*
		new�� ���� ��뿡 ����, make �Լ��� ����ϸ� �ҽ� �ڵ� �ߺ��� ������ ��������, ���� �������� ���ǰ�, 
		std::make_shared�� std::allocate_shared�� ��� �� �۰� ���� �ڵ尡 ����ȴ�.

		std::make_shared�� C++11�� �Ϻ�������, std::make_unique�� C++14������ ǥ�� ���̺귯���� ���ԵǾ���. 
	*/

	/*
		make �Լ��� ����ϸ� �׷��� ���� ������ ���� �������� ���Ǵ� ȿ���� �ִ�.
	*/

	namespace Make_Exception {
		class Widget{};
		inline void processWidget(std::shared_ptr<Widget> spw, int priority) {}
		inline int computePriority() { return 0; }

		inline void RunSample() {

			//Make_Shared/Unique �� �� ����.

			processWidget(std::shared_ptr<Widget>(new Widget), computePriority());   // �ڿ� ���� ������ ����
			/*
				1. ǥ���� "new Widget"�� �򰡵ȴ�.
				��, Widget�� ���� �����ȴ�.

				2. new�� ������ �����͸� �����ϴ�
				std::shared_ptr<Widget>�� �����ڰ� ����ȴ�.

				3. computePriority�� ����ȴ�.

				������ 1 �� 2 ���� ���� ����Ǿ�� �Ѵٴ� ���� �����ϰ�, �� �� �۾��� ���� ������
				������ ���� �ʾƼ� �����Ϸ����� ������ �޶��� �� �ִٴ� ���̴�.

				�� ������ ���� ������ ����� ���� �ִ�.


				1. ǥ���� "new Widget"�� �򰡵ȴ�.
				
				2. computePriority�� ����ȴ�.
				
				3. std::shared_ptr<Widget>�� �����ڰ� ȣ��ȴ�.

				�̷� ������ ����Ǵ� ��쿡 computePriority����
				���ܰ� �߻��ϸ� "new Widget"�� ���� �Ҵ��
				�޸𸮰� ����.
			*/

			processWidget(std::make_shared<Widget>(), computePriority());   // �ڿ� ������ ������ ����
		}
	}

	namespace MakeShared_AllocationEfficiency {

		class Widget {};

		inline void RunSample() {

			// ����ó�� new�� ���� ����Ѵٰ� ����.

			std::shared_ptr<Widget> spw1(new Widget);

			/*
				�� �ڵ尡 �� ���� �޸� �Ҵ��� �����ϴ� �� ó�� ��������, �����δ� �� ���� �Ҵ��� �Ͼ��.
				
				
				�׸� 19���� �����ϵ���, ��� std::shared����
				����Ī ��ü�� ���� ī��Ʈ�� ����� ���� ����
				���� �����͸� ��� ���� ����� ����Ű�� �����Ͱ� �ִ�.
				
				
				std::shared_ptr �����ڴ� �� ���� ����� ���� �޸𸮸� �Ҵ��Ѵ�.
				
				�� new�� ���� ����ؼ� std::shared_ptr�� �����ϸ� Widget ��ü�� ���� �޸� �Ҵ��
				���� ����� ���� �� �ٸ� �޸� �Ҵ��� �Ͼ��.
			*/

			auto spw2 = std::make_shared<Widget>();
			/*
				�� ���� �Ҵ����� ����ϴ�.
				
				�̴� std::make_shared�� Widget ��ü�� ���� ��� ��θ� ���� �� �ִ� ũ����
				�޸� ������ �� ���� �Ҵ��ϱ� �����̴�.
				
				���� �Ҵ� Ƚ���� �پ�� �Ӹ� �ƴ϶�, ���� ��Ͽ� ���� ������ ���� ������
				
				������ ������ �ʿ䰡 �������� ���α׷��� ��ü���� �޸� ��뷮�� �پ�� ������ �����.
				
				��� ���캻 ������� std::allocate_shared����
				���� �״�� ����ȴ�.
			*/
		}
	}

	namespace Make_Disadvantage{
		/*
			Make_Unique/Shared �� ������ �������� �������δ� Ŀ���� �����ڸ� �����ؾ� �ϴ� ���� �߰�ȣ �ʱ�ġ�� �����ؾ� �ϴ� ��찡 �ִ�.

			std::initializer_list�� �޴� �����ڿ� ���� �ʴ� �����ڸ� ��� ���� Ÿ���� ��ü�� ������ ��, 
			������ �μ����� �߰�ȣ�� ���θ� �����ε� �ؼ� �������� std::initializer_list�� �޴� ������ ���õǰ�, 
			��ȣ�� ���θ� std::initializer_list�� ���� �ʴ� ������ ���õȴ�.

			make �Լ����� ���������� �Ű��������� �Ϻ� ������ �� �߰�ȣ�� �ƴ϶� ��ȣ�� ����Ѵ�. 
			�� ������, ����Ī ��ü�� �߰�ȣ �ʱ�ġ�� �����Ϸ��� �ݵ�� new�� ���� ����ؾ� �Ѵ�.
		*/

		inline void RunSample() {
			auto initList = { 10, 20 };

			// �� std::initializer_list ��ü�� �̿��ؼ� std::vector�� ����
			auto spv = std::make_shared<std::vector<int> >(initList);	//(10,20) -> ���� 2�� ����
		}
	}

	namespace MakeShared_MemoryTest {


		/*
		shared_ptr �� ��ü�� ���� �ϸ�
		1. shared_ptr �� ����Ű�� ��¥ ��ü
		2. ControlBlock ���� �̷������.

		shared_ptr ������ (Ex : shared_ptr<Widget>(new Widget());) �� ȣ���ϸ�
		�޸� �Ҵ��� �� �� ��, Widget ��ü��, ControlBlock �� �����ϸ鼭 �� �� �߻��Ѵ�.

		shared_ptr�� ����� �Ǵٸ� �Լ�, (Ex : make_shared<Widget>();) �� ȣ���ϸ�
		�޸� �Ҵ��� �� ��, Widget ��ü ũ�� + ControlBlock ũ�⸦ ��ģ ��ŭ �Ҵ�޴´�.



		shared_ptr �� controlBlock ����
		1. shared_ptr �� ���� Ƚ���� ī�����ϴ� strong reference Counter ��
		2. weak_ptr �� ���� Ƚ���� ī�����ϴ� weak reference Counter �� �̷������.
		3. ��Ÿ ������ ���� ������ �ϴ� �н�

		shared_ptr �����ڷ� ������� ���,
		strong reference Counter == 0 �� ��, �����ϴ� ��ü�� ��ȯ�ϰ�
		strong reference Counter == 0 && weak reference Counter == 0 �� ��, shared_ptr �� controlBlock �� ��ȯ�Ѵ�.

		shared_ptr �����ڴ� ���� �޸𸮸� '������' �Ҵ�ޱ� ������ ��ȯ�� ���� '������' �ϴ� ���� �����ϴ�.

		������ make_shared<Widget>() ��� ��
		strong reference Counter == 0 �� ��, �����ϴ� Widget ��ü�� �Ҹ��� ȣ��.
		������ �޸𸮸� ��ȯ���� �ʴ´�.(Widget ��ü�� ������ ������⸸ �Ѵ�.)
		strong reference Counter == 0 && weak reference Counter == 0 �� ��, shared_ptr �� controlBlock�� ��ü�� '����' ��ȯ�Ѵ�.

		make_shared<Widget>()�� ���� �޸𸮸� '����' �Ҵ�ޱ� ������ ��ȯ�� ���� '����' �ؾ� �Ѵ�.
		*/

		class Widget {
		public:
			Widget() { cout << "Constructor Called" << endl; }
			~Widget() { cout << "Destructor Called" << endl; }
			char veryveryBig[100000000];
		};

		struct ControlBlock {
			void * ref = nullptr;
		};

		inline void RunSample() {

			cout << "Default Size : " << GetCurrentMemoryUsage() << "MB" << endl;

			{
				weak_ptr<Widget> pw;
				{
					pw = shared_ptr<Widget>(new Widget());
				}
				cout << "Memory Usage 1 = " << GetCurrentMemoryUsage() << "MB" << endl;
			}


			{
				weak_ptr<Widget> pw;
				{
					pw = make_shared<Widget>();
				}
				cout << "Memory Usage(make_shared) 1 = " << GetCurrentMemoryUsage() << "MB" << endl;
			}
			cout << "Memory Usage(make_shared) 2 = " << GetCurrentMemoryUsage() << "MB" << endl;

			/*
				�뷫������ �����غ� make_shared Ȱ�� ��ü ����
			*/

			//�Ҵ� ����
			unsigned char * mem = static_cast<unsigned char *>(malloc(sizeof(Widget) + sizeof(ControlBlock)));
			Widget * w = reinterpret_cast<Widget*>(mem);
			ControlBlock * c = reinterpret_cast<ControlBlock*>(mem + sizeof(Widget));
			c->ref = (void*)w;


			//��ü �ı�(�޸� ��ȯ ����)
			w->~Widget();
			ZeroMemory(w, sizeof(Widget));
			c->ref = nullptr;


			//������ ����
			free(mem);

		}

	}
}