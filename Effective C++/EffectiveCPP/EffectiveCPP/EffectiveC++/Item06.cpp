#include <iostream>
#include <vector>
#include <string>

class Widget {
public:

};

class HomeForSale {
public:

private:
	HomeForSale(const HomeForSale&);	//���� �޶� �ֽ��ϴ�.
	HomeForSale& operator=(const HomeForSale&);	//�� �������, ���� ������ �� ���� �����ڸ� ����� �� ������ ���ƹ�����.
};

class Uncopyable {
protected:
	Uncopyable() {}	//������ �Ҹ� ���
	~Uncopyable() {}
private:
	Uncopyable(const Uncopyable&);	//���� ����, ������ �����Ѵ�. ��ũ �������� ���� ����
	Uncopyable& operator=(const Uncopyable);
};

class HomeForSale2 : private Uncopyable {	//private ���
	//���������, ���� �����ڸ� �������� �� �� ����.
};