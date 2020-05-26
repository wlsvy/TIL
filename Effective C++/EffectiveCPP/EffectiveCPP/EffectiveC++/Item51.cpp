#include <iostream>
#include <vector>
#include <string>
using namespace std;

//new �� delete �� �ۼ��� �� ����� �� ������ ���ʸ� �� �˾� ����

namespace Item51 {
	/*
		operator new ���� �䱸����
		
		: �ϴ� ��ȯ ���� ����� �Ǿ� �־�� �ϰ�, 
		
		���� �޸𸮰� ������ ��쿡�� new ó���� �Լ��� ȣ���ؾ� �ϸ�, 
		
		ũ�Ⱑ ���� �޸� ��û�� ���� ���å�� ����ξ�� �Ѵ�. 
		
		������ �Ǽ��� "�⺻(normal)" ������ new �� �������� �ʵ��� �ؾ��Ѵ�.
	*/

	class Base {
	public:
		//����� ���� operator new�� �ٸ� �Ű������� �߰��� ���� �� �ִ�
		void * operator new(std::size_t size) throw(std::bad_alloc) {

			//0����Ʈ�� ������ 1����Ʈ �䱸�� �����ϰ� ó��
			if (size == 0) {
				size = 1;
			}

			//new ó���� ȣ��
			while (true) {

				//�޸� �Ҵ� �� ������ �Ҵ��� �޸� �ּ� ��ȯ
				//if(�Ҵ� ����) return �Ҵ�� �޸� ������;

				//�Ҵ��� �������� ���, ������ new ó���� �Լ��� ��������� ã�Ƴ��� ȣ��
				new_handler globalHandler = set_new_handler(0);
				set_new_handler(globalHandler);

				if (globalHandler) (*globalHandler)();
				else throw std::bad_alloc();
			}
		}
	};

	/*
		������

		��� Ŭ�������� ���ǵ� operator new�� �Ļ�Ŭ������ ��ӹ��� �� �ִ�.

		�̶� sizeof(Base) != sizeof(Derived) �� �����, 
		����� ���� operator new �Ļ�Ŭ������ ������ �� Base ũ���� �޸𸮸� �Ҵ��� �� �ִ� ��
	*/

	class Derived : public Base {};

	void func() {
		//Base::operator new �� ȣ��
		Derived *d = new Derived; 
	}
}

namespace Item51_2 {

	class Base {
	public:
		void * operator new(std::size_t size) throw(std::bad_alloc) {

			/*
				Ʋ�� ũ�Ⱑ ������ ǥ�� operator new������ �ѱ��.

				C++���� ���� ��ü�� 0 ����Ʈ�� ���� �� ���� ������
				0����Ʈ �޸� ��û�� �Ʒ� if������ �ݵ�� false�� �ȴ�.
			*/
			if (size != sizeof(Base)) {
				return ::operator new(size);
			}

			//�´� ũ�Ⱑ ������ �̰����� �޸� �Ҵ�. �������� ����
		}

		/*
			Operator new[] �� ������ ���� Ư�� ������ ��.

			����� ���� operator new[] �ȿ��� �� �� ���� �ܼ��� ���� �޸��� ����� �Ҵ��ϴ� �͹ۿ� ����.
			�� ���������� �迭 �޸𸮿� ���� �������� ���� Ŭ���� ��ü�� ���ؼ� �ƹ��͵� �� �� ����.

			������ �� ��ó�� �Ļ�Ŭ������ ��ü �迭 ũ�⸦ ���ؾ� �� ���,
			��ü�� ũ�Ⱑ sizeof(Base) ���� Ŭ ���� �ֱ� ������ �迭�� ������ (�䱸�Ǵ� ����Ʈ ��) / sizeof(Base) �� ���� �� ���� ���� �翬.

			�Դٰ� �����Ҵ����� �迭�� �����Ǵ� ��� ��⿡ �� ���� �޸� �纸�� �� ���� ������ �� �ִ�.(�׸� 16)
			�迭 ������ ������ ��� ���� ������ ������ �߰��� ���� ����.
		*/

		//delete�� ����. new ���� �����ѵ� �� �����Ϳ� ���� delete ������ �����ϵ��� ���常 �ϸ� ok
		void operator delete(void *rawMemory, std::size_t size) throw()
		{
			//�� �����Ͱ� delete �Ƿ��� ��� �ƹ��͵� ���� �ʵ��� ����
			if (rawMemory == 0) return;

			/*
				�Ļ�Ŭ���� ��ü�� ��� Ŭ������ �޸� ũ�Ⱑ �ٸ� �� �ִ�

				������ ����, ���� �Ҹ��ڰ� ���� �⺻Ŭ�������� �Ļ��� Ŭ���� ��ü�� �����ҽ�
				delete�� �Ѿ���� size ���� ���͸��� �� �ִ�.
			*/
			if (size != sizeof(Base)) {
				::operator delete(rawMemory); // �ٸ� �� ǥ�� delete ���
				return;
			}

			//���⼭ rawMemory�� ����Ű�� �޸� ����
		}
	};

	
}