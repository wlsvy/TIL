#include <iostream>
#include <vector>
#include <string>

// �ڿ� �������� ��ü�� �׸�!

namespace Item13 {
	

	/*
		���α׷��� �о߿��� �ڿ�(Resource)�̶�,  ����� �ϴ� ��ġ�� �� �Ŀ� �ý��ۿ� �����־�� �ϴ� ��� ���� ���´´�.

		����Ʈ ������ Ȱ���� ��. �ڿ� ���� ��ü�� Ȱ���Ͽ� �ڿ��� �����ϴ� ���� �߿��մϴ�.
	*/

	class Investment{};

	Investment* CreateInvestment() { return new Investment(); }

	void f(){
		Investment *pInv = CreateInvestment();

		/*
			������ Investment ��ü�� ����ϴ� �κ�

			���� ���⼭ ������ �߻��ϰų�, 
			goto, continue, break, return ������ ���� ���ڱ� ������ ������ ���������ٸ�

			�״�� �޸� ������ �̾�����
		*/

		delete pInv;
	}

	void f2() {
		/*
			���α׷��Ӱ� delete�� ���� �ʿ� ���� �������� ����������
			�ڵ����� auto_ptr �Ҹ��ڿ��� �޸� ��ȯ
		*/
		std::auto_ptr<Investment> pInv(CreateInvestment());
	}

	/*
		�ڿ� ������ ��ü�� ����ϴ� ����� �� ���� Ư¡

		1. �ڿ��� ȹ���� �Ŀ� �ڿ� ���� ��ü���� �ѱ�� - 
		RAII(Resource Acqusition Is Initialization) �ڿ� ȹ�� �� ��ٷ� �ڿ� ���� ��ü �ʱ�ȭ
		�ڿ� ȹ��� �ڿ� ���� ��ü �ʱ�ȭ�� �� ���忡�� �̷������ �Ǵ� ��

		2. �ڿ� ���� ��ü�� �ڽ��� �Ҹ��ڸ� ����ؼ� �ڿ��� Ȯ���� �����ǵ��� �Ѵ�.
		��ȿ������ ����� ��� �� �ڿ� ������ü�� �Ҹ��ڰ� ȣ��Ǵ� ������ �ڿ� ������ �ڵ������� �����Ǵ� ��

	*/
}