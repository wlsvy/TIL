#include <iostream>
#include <vector>
#include <string>
using namespace std;

//ĳ������ ����, �� ����! ���� ����

namespace Item27 {

	void Func2() {
		int x = 1, y = 5;

		double d = static_cast<double>(x) / y;
		/*
			int Ÿ���� x�� double Ÿ������ ĳ�����ϴ� �κп��� �ڵ尡 ���������. 
			��κ��� ��ǻ�� ��Ű��ó���� int�� ǥ�������� double�� ǥ�������� �ƿ� �ٸ��� ����
		*/
	}

	class Base {};
	class Derived : public Base {};

	void Func1() {
		Derived d;

		Base *pb = &d; //Derived * => Base* ���� �Ͻ��� ��ȯ

		/*
			���⼭ ������ ��ü������ Base �� Derived �������� �ּڰ��� ���� �ٸ���. 
			�������� ����(offset)�� Derived* �����Ϳ� �����Ͽ� ������ Base* �������� ���� ���ϱ� ����

			�ϳ��� ��ü�� ���ؼ��� �׿� �ش��ϴ� �ּڰ��� �ϳ��� �ƴ� �� �ִ�.
		*/
	}

	class Window {
	public:
		virtual void onResize(){}
	};

	class SpecialWindow : public Window {
	public:
		virtual void onResize() {
			static_cast<Window>(*this).onResize();	//����ġ ���� ������ �� �� �ִ�

			Window::onResize();						//�� ����� ����
		}
	};

	/*
		���� static_cast�� �����ؾ� �ϴµ� ĳ������ �̷�����鼭 ��ü�� Window(���Ŭ����)�κ��� �ӽ� �纻�� ��������� ����!
		�� ���� ��ü�� ���ؼ� ����Լ��� ����Ǵ� ���� �ƴ϶� �ӽ� �纻���� ����Ǵ� ��. 
	*/


	/*
		�ٸ� ����� �����ϴٸ� ĳ������ ���Ͻʽÿ�. 
		Ư�� ���� ���ɿ� �ΰ��� �ڵ忡�� dynamic_cast�� �� ���̰� �ٽ� �����Ͻʽÿ�. 
		
		���� �߿� ĳ������ �ʿ������ٸ�, ĳ������ ���� �ʴ� �ٸ� ����� �õ��� ���ʽÿ�.

		const_cast: ��ü�� ������� ���ִ� �뵵�� ���˴ϴ�.

		dynamic_cast: ������ �ٿ�ĳ����(safe downcasting)�� �� �� ����ϴ� ������ �Դϴ�. �Ű澲�� ������ ��Ÿ�� ����� ���� ���� �ʴ� ���� �����ϴ�.

		reinterpret_cast: �����͸� int�� �ٲٴ� ���� �Ϻ� ���� ĳ������ ���� �����ڷμ�, 
		�̰��� �ۿ� ����� ����ȯ�濡 �������Դϴ�.(�̽ļ��� �����ϴ�.) �̷� ĳ��Ʈ�� �Ϻ� ���� �ڵ� �ܿ��� ���� ����� �մϴ�.

		static_cast: �Ͻ��� ��ȯ[���� ��ü�� ��� ��ü�� �ٲٰų�(�ݴ�� const_cast�� ����) int�� double�� �ٲٴ� ���� ��ȯ]�� ������ ������ �� ����մϴ�.
	*/
}