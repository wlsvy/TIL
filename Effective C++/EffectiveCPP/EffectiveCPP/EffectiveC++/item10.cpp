#include <iostream>
#include <vector>
#include <string>

namespace Item10 {

	class Widget {
	public:
		//���� �����ڴ� *this�� �����ڸ� ��ȯ�ϰ� ����
		Widget& operator= (const Widget& rhs) {	//��ȯ Ÿ���� ������ Ŭ������ ���� ������
			//....
			return *this;	//�º� ��ü(�� ������)�� ��ȯ
		}
		Widget& operator+=(const Widget& rhs) {	//�ٸ� ������(+=,-=, *= ��)���� ������ �Ծ� ����
			//....
			return *this;
		}
		Widget& operator=(int rhs) {	//�Ű����� Ÿ���� �ٸ����� ������ �Ծ� ����
			//....
			return *this;
		}
	};
}
