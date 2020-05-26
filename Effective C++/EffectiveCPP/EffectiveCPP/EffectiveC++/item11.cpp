#include <iostream>
#include <vector>
#include <string>

namespace Item11 {
	//operator= ������ �ڱ� ���Կ� ���� ó���� ������ �ʵ��� ����.

	class Bitmap {};
	class Widget0 {
	public:
		Widget0& operator= (const Widget0& rhs) {	//�������� �ʰ� ������ operator=
			delete pb;
			pb = new Bitmap(*rhs.pb); //�ڱ� ������ �ϴ� ���, �������� �����͸� ���������� ���� �߻�
			return *this;
		}
	private:
		Bitmap *pb;
	}; 

	class Widget1 {
	public:
		Widget1& operator= (const Widget1& rhs) {	//�ڱ� ������ ��� ����
			if (this == &rhs) return *this; // ���� �ڱ� �ڽ����� �˻�.

			delete pb;
			pb = new Bitmap(*rhs.pb);	//�׷��� �� �κ��� �Ҿ�. ���⼭ ������ ������, pb�� ��۸� �����ͷ� ���´�.
			return *this;
		}
	private:
		Bitmap *pb;
	}; 
	
	class Widget2{
	public:
		Widget2& operator= (const Widget2& rhs) {	//new ��ɾ� ���� ����
			if (this == &rhs) return *this;		// <== �ڱ� ���� �˻�� �ڵ尡 �þ�� ������尡 �����ϴ� �� �ָ�.

			Bitmap *pOrig = pb;			//pb �ּڰ��� �ٸ����� ������ѳ���,
			pb = new Bitmap(*rhs.pb);	//pb�� �纻�� ������ �� �������� ����
			delete pOrig;
			return *this;
		}
	private:
		Bitmap *pb;
	};

	class Widget {
	public:
		void swap(Widget& rhs);	//*this �� rhs�� ������ ��ü
		Widget& operator= (const Widget& rhs) {	//swap and copy ������� ����/�ڱ���� ������ ����
			Widget temp(rhs);
			swap(temp);	//rhs�� �纻�� ����� *this�� ������ ��ȯ
			return *this;
		}
		Widget& operator= (Widget rhs) {	//���� ���� ������ �ϸ� ���簡 �̷�� ���� �� Ȱ��.
			swap(rhs);	//�纻 ���縦 �Լ� ������ �ƴ� �Ű��������� ���
			return *this;
		}
	private:
		Bitmap *pb;
	};
}
