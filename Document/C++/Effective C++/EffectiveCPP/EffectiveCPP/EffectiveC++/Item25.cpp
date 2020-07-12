#include <iostream>
#include <vector>
#include <string>
using namespace std;

//���ܸ� ������ �ʴ� swap�� ���� ������ ������ ����

namespace Item25 {

	//Effective C++ �� ���� �ø�ƽ(move semantic) �� C++�� �Ұ��Ǳ� ������ ���� å�ΰ��� ����� ��
	//���� ǥ�� swap�� �̵� ����/������ Ȱ���ϱ� ������ ���� ����/������ Ȱ���ϴ� ���� swap���� �ٸ�

	//�Ϲ� Ŭ������ �������� Ŭ ���, ����� ���� swap ����
	class WidgetImpl {
	private:
		int a, b, c;
		std::vector<double> v;	//���� �����͸� ������ ������ ���� ����� ���ٰ� ����
	};
	class Widget {
	public:
		/*
			using Ű���带 ����ϸ�, swap �Լ��� ȣ���� ��, 
			���� Ŭ������ ���� ���ӽ����̽��� swap �Լ��� ���� ã�� �� ������ ȣ���ϰ� 
			Ȥ�� ���ٸ� �ٸ� std::swap �Լ��� ����ϰڴٴ� �ǹ�	
			-> ���� ��� Ž��(argument-dependent lookup) & ��ϱ� Ž��(koenig lookyp)
		*/
		void swap(Widget& other) {
			using std::swap;	

			swap(pImpl, other.pImpl);
		}
	private:
		WidgetImpl *pImpl;	//���� �����͸� ���� ��ü�� ���� ������
	};
}

namespace std {

	//std::swap �� ���ø� Ư��ȭ
	template<>	
	void swap<Item25::Widget>(Item25::Widget& a, Item25::Widget& b) {
		a.swap(b);
	}
}
/*
	std:: ���ӽ����̽��� swap ���ø� Ư��ȭ �Լ����� ��ģ ���, �����ϵ� �����ϰ� STL �����̳ʿ� �ϰ����� ������ �� �ִ�.
*/



namespace Item25_2 {

	//�Ϲ� Ŭ������ �ƴ� Ŭ���� ���ø�(class template)�� ���
	template<typename T>	 
	class WidgetImpl {
	private:
		T a, b, c;
		std::vector<T> v;
	};

	template<typename T>
	class Widget {
	public:
		void swap(Widget<T>& other) {
			using std::swap;	

			swap(pImpl, other.pImpl);
		}
	private:
		WidgetImpl<T> *pImpl;	//���� �����͸� ���� ��ü�� ���� ������
	};

	/*
		Ŭ������ �ƴ� Ŭ���� ���ø��� ���, 

		namespace std {
			template<typename T>
			void swap<Widget<T>>(Item25_2::Widget<T>& a, Item25_2::Widget<T>& b) {
				a.swap(b);
			}
		}

		Ŭ������ ���ؼ��� ���ø� �κ� Ư��ȭ�� ���������, �Լ� ���ø��� ���ؼ��� ������� �ʵ��� ������ �־
		�� �ڵ�� ������ ���� �ʴ´�.
	*/

	/*
		���ø� �κ� Ư��ȭ�� �ƴ� �Լ� �����ε带 Ȱ���غ��� ��� ����

		namespace std{
			template<typename T>
			void swap(Item25_2::Widget<T>& a, Item25_2::Widget<T>& b) {
				a.swap(b);
			}
		}

		std�� ���� Ư���� ���ӽ����̽��̱� ������ �ٸ� ��Ģ�� ����ȴ�.
		������ std ���� ���ø��� ���� ���� Ư��ȭ�� ����������, ���ο� ���ø��� �߰��ϴ� ���� �Ұ���
		(std �� ������� �߰��� �����ؼ��� �������� c++ ǥ�� ����ȸ�� �޷��ִ�)

		std �� ���ø� �Լ��� ���ؼ� �����ε��� �߰��ϴ� ���� ������ ����� �ʷ��� �� �ִ�.
	*/

	//���� swap �Լ� Ȱ��, std ���ӽ����̽��� �Ϻΰ� �ƴϴ�
	template<typename T>
	void swap(Widget<T>& a, Widget<T>& b) {
		a.swap(b);
	}

	//� �Լ����� swap�� ����ϴ� ���
	template<typename T>
	void doSomething(T& obj1, T& obj2) {	
		using std::swap;	//using Ű����� std::swap�� ����� �� �ֵ��� �Ѵ�.

		swap(obj1, obj2);	//T Ÿ�� ������ swap ���, ���� �ش� ���ӽ����̽��� swap�� ���ٸ� using���� ����� std::swap ���

		/*
			std::swap(obj1, obj2); 
			
			���� �����̽��� std::�� �����ϰ� �Ǹ�, �ٸ� ���� �ŵ鶰������ ���� std::�� swap�� ����϶�� �����ϴ� ��
			�ش� ���ӽ����̽��� �ٸ� swap�� ������ ���� �����Ϸ��� ������ std::swap�� ����ϰ� �ȴ�.
		*/
	}
}

/*
	1. ǥ�ؿ��� �����ϴ� swap�� ����� ���� Ŭ������ ���ؼ� ������ ���� ������ ���δٸ� �׳� �ƹ��͵� ���� ����. 
	-> �״�� std::swap �� ȣ���� �� �ֵ���
	-> ���� ��� swap�� ����� ���ܸ� ������ �ʵ��� �� ��

	2. ǥ�� swap�� ��븸ŭ ȿ�������� �ʴٸ� (���� Widget ����ó��) 
		- ����� ���� Ŭ������ ������ swap �Լ��� ����� public ����Լ��� �� ��. -> �� �Լ��� ���� ���ܸ� �������� �ȵȴ�
		- ����� ���� Ŭ������ ������ ���ӽ����̽��� ���� swap�� �����. 1������ ���� swap ��� �Լ��� �� ���� �Լ��� ȣ���ϵ��� �Ѵ�.
		- ���ο� Ŭ����(Ŭ���� ���ø��� �ƴ϶�)�� ����� �ִٸ�, �� Ŭ������ ���� std::swap�� Ư��ȭ ������ �غ��� �д�. �׸��� �� Ư��ȭ ���������� swap ��� �Լ��� ȣ���ϵ��� �Ѵ�.

	3. ����� ���忡�� swap�� ȣ���� ��, swap�� ȣ���ϴ� �Լ��� std::swap�� �� �� �ֵ��� using ������ �ݵ�� ���Խ�Ų��. �� ������ swap�� ȣ���ϵ�, ���ӽ����̽� �����ڴ� ������ �ʴ´�.

	��� swap�� ����� ���ܸ� ������ �ȵǴ� ����
	 - ������ ���� ������ ����(strong exception-safety guarantee) ���� -> � ������ ����Ǵٰ� ���ܰ� �߻��ϸ� �� ������ ���۵Ǳ� ������ ���� �� �ִٴ� ����
	 - ���� ������ ���, ǥ�� swap �� ���� ������ ���� ���Կ� ����ϰ� �ִµ�, �� ���� ���� �߻��� ���Ǳ� ������ ������ ���� �ʴ´�.
*/