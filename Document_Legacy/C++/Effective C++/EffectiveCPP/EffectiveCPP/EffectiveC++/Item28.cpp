#include <iostream>
#include <vector>
#include <string>
using namespace std;

//���ο��� ����ϴ� ��ü�� ���� '�ڵ�'�� ��ȯ�ϴ� �ڵ�� �ǵ��� ������

namespace Item28 {

	/*
		� ��ü�� ���ο�ҿ� ���� �ڵ�(������, ������, �ݺ���)�� ��ȯ�ϴ� ���� �ǵ��� ���ϼ���. 
		ĸ��ȭ ������ ���̰�, ��� ��� �Լ��� ��ü�� ������� ������ ä�� ������ �� �ֵ��� �ϸ�, ��ȿ���� �ڵ��� ����� ��츦 �ּ�ȭ�� �� �ֽ��ϴ�.
	*/

	class Point {
	public:
		Point(int x, int y) : X(x), Y(y) {}
		void SetX(int x) { X = x; }
		void SetY(int y) { Y = y; }
	private:
		int X, Y;
	};

	struct RectData {
		Point ulhc;
		Point lrhc;
	};

	class Rectangle {
	public:
		Point& upperLeft() const { return pData->ulhc; }
		Point& lowerRight() const { return pData->lrhc; }
	private:
		std::shared_ptr<RectData> pData;
	};


	void func() {
		//�� �ڵ��� ������

		//Rectangle�� �����ʹ� private ����Ǿ������� �ұ��ϰ� ����ڴ� �������� ��ǥ���� ������ �� �ִ�.
		const Rectangle rec;
		rec.upperLeft().SetX(3);	

		/*
			Ŭ���� ������ ����� �ƹ��� ���ܺ��� �� ����� �����ڸ� ��ȯ�ϴ� �Լ����� �ִ� ���ٵ��� ���� ĸ��ȭ�� ������ �����ȴ�.
			���� ���������� Rectangle Ŭ������ upperLeft, lowerRight �Լ��� ��ȯŸ���� const Point& �� �ٲٸ� �ذ�ȴ�.
		*/
	}

	class GUIObject {};

	const Rectangle boundingBox(const GUIObject& obj);

	void func2() {
		GUIObject *pgo = new GUIObject();

		//�簢 �׵θ� �������κ��� ���� �� �������� �ּҰ� ȹ��
		const Point *pUpperLeft = &(boundingBox(*pgo).upperLeft()); 

		/*
			�����ؾ��� �� -> boundingBox(*pgo) �� ������ Rectangle �� �ӽð�ü�̹Ƿ� ������ ���� �� �Ҹ�ȴ�.
			�� pUpperLeft �� ��۸� �����Ͱ� �Ǵ� ��.

			� ��ü�� ���ο�ҿ� ���� �ڵ�(Handle, �ٸ� ��ü�� �� �� �� �ְ� �ϴ� �Ű��� - ������, ������, �ݺ���)�� ��ȯ�ϴ� ���� �ǵ��� ������
			ĸ��ȭ ������ ���̰�, ��� ��� �Լ��� ��ü�� ������� ������ ä�� ������ �� �ֵ��� �ϸ�, ��ȿ���� �ڵ��� ����� ��츦 �ּ�ȭ�� �� �ִ�.
		*/
	}

	const Rectangle boundingBox(const GUIObject& obj) {
		return Rectangle();
	}

}