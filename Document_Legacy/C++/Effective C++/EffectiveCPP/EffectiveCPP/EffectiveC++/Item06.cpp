#include <iostream>
#include <vector>
#include <string>

//�����Ϸ��� ���� �Լ��� �ʿ� ������ Ȯ���� �̵��� ����� ���� ������

namespace Item06 {
	/*
		�����Ϸ����� �ڵ����� �����ϴ� ����� ���ġ ��������, 
		�����Ǵ� ��� �Լ��� private�� ������ �Ŀ� ������ ���� ���� ä�� �νʽÿ�.
		
		Uncopyable�� ����� �⺻ Ŭ������ ���� �͵� �� ����Դϴ�.
	*/

	class HomeForSale {
	private:
		//���� �޶� �ֽ��ϴ�.
		//�� �������, ���� ������ �� ���� �����ڸ� ����� �� ������ ���ƹ�����.
		HomeForSale(const HomeForSale&);	
		HomeForSale& operator=(const HomeForSale&);
	};

	class Uncopyable {
	protected:
		//������ �Ҹ� ���
		Uncopyable() {}	
		~Uncopyable() {}
	private:
		//���� ����, ������ �����Ѵ�. ��ũ �������� ���� ����
		Uncopyable(const Uncopyable&);	
		Uncopyable& operator=(const Uncopyable);
	};

	//private ���
	class HomeForSale2 : private Uncopyable {	
		//���������, ���� �����ڸ� �������� �� �� ����.
	};
}
