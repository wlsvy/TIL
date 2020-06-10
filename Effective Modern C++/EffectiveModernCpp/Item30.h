#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>

//�Ϻ� ������ �����ϴ� ������ �� �˾Ƶζ�

namespace Item30 {

	/*
		�Ϻ� ������ �ܼ��� ��ü���� �����ϴ� ���� �ƴ϶� �� ��ü���� �ֿ� Ư¡,
		�� �� ����, �ް� �Ǵ� ������ ����, const �� volatile ���α����� �����ϴ� ���� ���Ѵ�.

		�����Լ��� �׳� ���ø� �Լ��� �ƴ϶� ���� �μ� ���ø�(variadic template), �� ������ ���İ� ������ �μ����� �޴� ���ø��̾�� �Ѵ�.
	*/
	inline void f()									{ std::cout << "Void" << std::endl; }
	inline void f(int)								{ std::cout << "int" << std::endl; }
	inline void f(std::size_t)						{ std::cout << "std::size_t" << std::endl; }
	inline void f(std::initializer_list<int>)		{ std::cout << "initializer_list<int>" << std::endl; }
	inline void f(void*)							{ std::cout << "void *" << std::endl; }
	//inline void f(int(*)(int))						{ std::cout << "int(*)(int)" << std::endl; }

	template <typename... Ts>
	void fwd(Ts&&... params)               
	{
		f(std::forward<Ts>(params)...);    
	}

	/*
		f( ǥ���� );
		fwd( ǥ���� );
		
		��� �Լ� f�� ���� �Լ� fwd �ִٰ� �� ��, ��� �μ��� f�� ȣ������ �� ���۰�, fwd�� ȣ������ �� ������ �ٸ��ٸ� �Ϻ������� ������ ���̴�.

		Ex)
		1. fwd�� �Ű������� �� �ϳ� �̻� ���� �����Ϸ��� Ÿ���� �߷����� ���Ѵ�. �� ��� �ڵ�� �����ϵ��� �ʴ´�.
		2. fwd�� �Ű������� �� �ϳ� �̻� ���� �����Ϸ��� Ÿ���� �߸� �߷��Ѵ�.  "�߸���" Ÿ�� �߷� ������ fwd���� ȣ��Ǵ� f�� f�� ���� ȣ������ �� ���õǴ� �����ε��� �Լ��� �ٸ� ��� ����
	*/

	namespace Case0 {
		//�߰�ȣ �ʱ�ġ
		/*
			�׸� 2���� �����ϵ���, ���ø� Ÿ�� �߷��� �߰�ȣ �ʱ�ġ�� �߷����� ���Ѵ�. 
			�߰�ȣ �ʱ�ġ�� Ÿ�� �߷��� �����ϹǷ� �߰�ȣ �ʱ�ġ�� �Ϻ� ���޵� �����Ѵ�.
		*/

		inline void RunSample() {
			//fwd({ 1, 2, 3 });	//������ ����

			//��ȸå
			auto il = { 1, 2, 3 };
			fwd(il);	// initializer_list<int>
		}
	}

	namespace Case1 {
		//nullptr
		/*
			0 �� NULL �� ��������, nullptr�� ����� ��
		*/

		inline void RunSample() {
			int* i0 = 0, *i1 = NULL;
			fwd(i0);		// void*
			fwd(i1);		// void*

			fwd(0);			// int
			fwd(NULL);		// int

			fwd(nullptr);	// void*
		}
	}

	namespace Case2 {
		//���� �� ���� static const �� constexpr ������ ���
		/*
			�Ϲ����� ��Ģ����, ���� static const ������ ����� ���� static constexpr ������ ����� Ŭ���� �ȿ��� ������ �ʿ䰡 ����. 
			���� �ϸ� �ȴ�. �̴� �׷� ����� ���� ���� �����Ϸ��� const ����(const propagation)�� �����ؼ�, 
			�׷� ����� ���� ���� �޸𸮸� ���� ������ �ʿ䰡 �������� �����̴�.

			������, ���� �׷� ������� �ּҸ� ���ϴ� �ڵ�(�̸��׸� �׷� ����� ����Ű�� �����͸� ����ٸ�)�� ����ٸ�, 
			�׷� ����� ���� ����Ұ� �ʿ�������, �׷��� �� �ڵ�� �����ϵǱ� ������ ��ũ�� �����Ѵ�.

			�����Ϸ��� ������ �ڵ忡�� ������ ������ó�� ��޵Ǵ� ���� �����̴�(��, �ּҸ� ���Ѵ�). 
			���� �׷� ������� ���� ����(universal reference)�� ������ �ϸ� ��ũ�� �����ϴ� �ڵ尡 ������� ���ɼ��� ũ��. 
			���� ��ũ�� �ȴٰ� �ϴ��� ǥ���� �ƴϹǷ� �̽ļ��� ��������.
			
			����, �׷��� ������� �Ϻ��ϰ� �����Ϸ��� �׷� ������� ���Ǹ� ����� �ָ� �ȴ�

		*/

		class Widget {
		public:
			static constexpr std::size_t MinVals = 28;
		};

		inline void RunSample() {
			f(Widget::MinVals);
			fwd(Widget::MinVals);	//�����Ϸ��� ���� ��ũ�� ������ �� �ִ�. static ������ cpp�� ������ų ��.

			const size_t * ptr = &Widget::MinVals;
			/*
				�ϵ����� ���α׷� ������ �����ڵ忡�� ������ �����Ϳ� ���������� �����ϴ�.

				MinVals�� ������ �����ϴ� ���� ��ǻ� �����ͷ� �Ѱ��ִ� ���̸�, �׷��� �����Ͱ� ����ų ������ �ʿ��ϴ�.
				�Ϲ������� ���� static const �� constexpr �ڷ� ����� ������ �����Ϸ��� �� ����� ������ �ʿ䰡 �ִ�.
			*/
		}
	}

	namespace Case3 {
		//�ߺ������ �Լ� �̸��� ���ø� �̸�

		inline int processVal(int) { return 0; }
		inline int processVal(int, int) { return 0; }

		template<typename T>
		T workOnVal(T) { return T(); }

		inline void RunSample() {
			//fwd(processVal);	//������ ����, fwd�� � processVal �����ؾ� ���� �𸥴�.
			//fwd(workOnVal);		//��������

			//��ȸå
			using FuncType = int(*)(int);
			FuncType pv = processVal;

			fwd(pv);								//����� ����
			fwd(static_cast<FuncType>(workOnVal));	//���ø� �Լ� ���� ����� ����
		}
	}

	namespace Case4 {
		//��Ʈ�ʵ�
		/*
			�޸��� �ּҴ� ����Ʈ ������ �Ҵ�ȴ�. ���� ������ ����Ʈ�� ����Ű�� �����͸� ���� �� ������, 
			������ ��Ʈ�� ����Ű�� �����ʹ� ���� �� ����. �������� ���������, �����Ϸ��� ������ �ڵ忡�� ������ ������ó�� ��޵Ǵ� ���� �����̴�. 
			�� ������, ��Ʈ �ʵ�� ���� ����(universal reference)�� ���� ���� ��� �Ϻ� ���޿� �����Ѵ�.

			��Ʈ�ʵ带 �Ű������� �����ϴ� ����� �� �� ������, �ϳ��� ������ �����ϴ� ���̰�, �ٸ� �ϳ��� const�� ���� ������ �����ϴ� ���̴�.

			�� ���� �Ű������� ��� ȣ��� �Լ��� ��Ʈ�ʵ� ���� ���纻�� �޴´�. �׸��� const ���� �Ű������� ���, 
			ǥ�ؿ� ������ �� ������ ������ � ǥ�� ���� Ÿ��(�̸��׸� int)�� ��ü�� ����� ��Ʈ�ʵ� ���� ���纻�� ������ �Ѵ�. 
			��, �� const ������ ��Ʈ�ʵ� ��ü�� �ƴ�, ��Ʈ�ʵ� ���� ����� '����'��ü�� ���δ�.

			���� ��Ʈ�ʵ带 �Ϻ� ���� �Լ��� �Ѱ��ַ���, ��Ʈ�ʵ� ���� ���纻�� ���� �����ؼ� �� ���纻�� �����ϸ� �ȴ�.
		*/

		struct IPv4Header {
			std::uint32_t 
				version : 4,
				IHL : 4,
				DSCP : 6,
				ECN : 2,
				totalLength : 16;
		};

		inline void RunSample() {
			IPv4Header h;
			h.totalLength = 16;
			std::cout << sizeof(IPv4Header) << std::endl;
			f(h.totalLength);
			//fwd(h.totalLength);            // ����, ��Ʈ�ʵ�� �ּҰ��� ����

			//��ȸå
			auto length = static_cast<std::uint16_t>(h.totalLength);
			fwd(length);					// ���纻�� �����Ѵ�.
		}
	}
}