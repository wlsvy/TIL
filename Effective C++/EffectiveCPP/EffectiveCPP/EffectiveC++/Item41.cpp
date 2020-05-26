#include <iostream>
#include <vector>
#include <string>
using namespace std;

//���ø� ���α׷����� õ���浵 �Ͻ��� �������̽��� ������ Ÿ�� ����������

namespace Item41 {
	class Widget {
	public:
		Widget() {}
		virtual ~Widget() {}
		virtual std::size_t size() const { return 0; }
		virtual void normalize() {}
		void swap(Widget& other) { 
			using std::swap;
			swap(*this, other); 
		}
	};

	Widget someNastyWidget;

	template<typename T>
	void doProcessing(T& w) {
		if (w.size() > 10 && w != someNastyWidget) {
			T temp(w);
			temp.normalize();
			temp.swap(w);
			/*
				�Ͻ��� �������̽�
				-> Ÿ�� T�� normalize(), swap(T), operator !=(Widget) �޼ҵ带 �����ϰ� �־�� �Ѵ�
			*/
		}
	}

	/*
		W�� ���ݵǴ� �Լ� ȣ���� �Ͼ ��, 
		�̸��׸� operator > �� operator != �Լ��� ȣ��� ���� �ش� ȣ���� ������Ű�� ���� ���ø��� �ν��Ͻ�ȭ�� �Ͼ��. 
		
		�̷��� �ν��Ͻ�ȭ�� �Ͼ�� ������ ������ ����
		�ν��Ͻ�ȭ�� �����ϴ� �Լ� ���ø��� � ���ø� �Ű������� �����Ŀ� ���� ȣ��Ǵ� �Լ��� �޶����� ������, �̰��� ������ '������ Ÿ�� ������'�̶�� �Ѵ�.
		
		Ŭ���� �� ���ø��� ��� �������̽��� �������� �����Ѵ�. 

		�̶� Ŭ������ ���, �������̽��� ������̸� �Լ��� �ñ״�ó�� �߽����� �����Ǿ� �ִ�. 
		�������� ���α׷� ���� �߿� ���� �Լ��� ���� ��Ÿ����. 

		���ø� �Ű������� ���, �������̽��� �Ͻ����̸� ��ȿ ǥ���Ŀ� ����� �ξ� �����ȴ�. 
		�������� ������ �߿� ���ø� �ν��Ͻ�ȭ�� �Լ� �����ε� ��ȣ�� �ذ��� ���� ��Ÿ����.
	*/
}