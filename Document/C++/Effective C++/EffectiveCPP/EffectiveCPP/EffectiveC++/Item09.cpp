#include <iostream>
#include <vector>
#include <string>

//��ü ���� �� �Ҹ� ���� �߿��� ����� ���� �Լ��� ȣ������ ����.
namespace Item09 {

	/*
		 �⺻Ŭ������ �����Ǵ� ������, �Ļ�Ŭ������ ���� ��������� ���� ���´�. 
		 �̶� �����Լ��� �����ϰ� �Ǹ� �Ļ�Ŭ������ �Լ��� ������ �� ���°� �翬�ϴ�. 

		�Ҹ����� ��쵵 ��������, �Ļ�Ŭ������ �Ҹ�� ������ �⺻Ŭ������ �Ҹ��� ���ο� �����Լ��� �ִٸ� ���α׷��Ӱ� ���ϴ� ������ ���� ���� �� �ִ�.

		�Ļ�Ŭ���� ��ü�� �⺻ Ŭ���� �κ��� �����Ǵ� ������ �� ��ü�� Ÿ���� ���� �⺻ Ŭ������ �����ǹǷ�, 
		�����Լ��� �����ؼ� dynamic_cast / typeid �� ����� �� ������ ��ģ��.
	*/

	class Transaction {
	public:
		Transaction()
		{
			logTransaction();
		}
		virtual void logTransaction() const { std::cout << "Transaction" << std::endl; }
	};

	class BuyTransaction : public Transaction {
	public:
		virtual void logTransaction() const { std::cout << "BuyTransaction" << std::endl; }
	};

	void RunSample() {
		BuyTransaction tr;		//BuyTransaction �� �ƴ� Transaction ���
	}
}

