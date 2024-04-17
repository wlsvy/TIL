#include <iostream>
#include <vector>
#include <string>
using namespace std;

//�������̽� ����� ����� ���⿣ ����, ���͸��� ���⿣ ��ư� ����
namespace Item18 {

	//���� 1 : ��¥
	struct Day {
		explicit Day(int d) : val(d) {}
		int val;
	};

	class Month {	//�ϳ��� 12�����̹Ƿ� �� ���� �������� Ȱ���� �� �ִ�.
	public:
		/*
			static �Լ��� �̸� �����ϴ� ���

			������ü�� �ƴ� �����Լ��� ������ ���� Ư¡�ε�  
			��ü�� �ʱ�ȭ ������ ������ ���� �ʾ����� ��찡 �ִٸ� ������ �߻��� �� �ֱ� ����(�׸� 4 ����)
		*/
		static Month Jan() { return Month(1); }	
		static Month Fab() { return Month(2); }	
		//....

	private:
		explicit Month(int m) : val(m) {}
		int val;
	};

	struct Year {
		explicit Year(int y) : val(y) {}
		int val;
	};

	class Date {
	public:
		/*
			�� ����� ���ڸ� ���� �Է��ϴ� �������� �Ǽ��� �߻��� �� �ִ�.
			Date d(30, 3, 1995);	��¥�� �� ���� ���ٴ���
			Date d(3, 40, 1995);	3�� 4�� �߸� ���� �ִ� �ϼ�(31 & 30) �� �ѱ�ٴ���
		*/
		Date(int month, int day, int year) {}

		/*
			����ϴ� ���忡�� �Ǽ��� ���� �� �ְ� �ϴ� ���
			Ÿ���� �ٸ� ��� �ﰢ Ȯ���� �� �ְ� �����Ǿ���.
			Date(Month::Jan(), Day(30), Year(1995));
		*/
		Date(const Month& m, const Day& d, const Year& y) {}
	};

	//���� 2 : Ÿ�Կ� const���� �ο��ϱ�
	/*
		if(a * b = c) <= ���� �߻��� �� �ִ� �Ǽ��� �����Ϸ���
		operator* �� ��ȯ Ÿ�Կ� const�� �����Ѵٸ� ����ڰ� ���� �Ŀ��� �ٷ� �Ǽ��� Ȯ���� �� �ִ�.
	*/

	//���� 3 : ���丮 �Լ�
	class Investment{};

	//Investment* createInvestment();	//�����͸� ��ȯ�ϴ� ���丮 �Լ�

	/*
		�ƿ� ����Ʈ �����͸� ��ȯ�ϰ� �������� ���� �ִ�
		����ڰ� �ڿ� ��ȯ�� �����ϰ� ����� ��� ����
	*/
	std::shared_ptr<Investment> createInvestment();
													

	//�߰������� ����Ʈ�������� ������ �߰�
	void getRidOfInvestment(Investment* ptr) {}

	std::shared_ptr<Investment> createInvestment() {
		std::shared_ptr<Investment> retVal(static_cast<Investment*>(0), getRidOfInvestment);	
		//�� �����Ϳ� �����ڸ� ���� ����Ʈ ������

		//retVal �� ��ü�� ����Ű���� �۾�

		return retVal;
	}
	//�����ڸ� Ȱ���Ѵٸ� �����͸��� ������ �����ڸ� ����ǵ��� ������ �� �ִ�.

	//���� DLL ����(cross-DLL problem)���� ������ �����ϴ�
	//new/delete ¦�� �ϳ��� DLL�� ���ԵǾ� �ִ°� �ƴ϶� �� �� �̻��� DLL�� �и��Ǿ� �ִ� ��� ������ �߻��ϴµ�
	//�� ������δ� �����ϴ� DLL���� �����ڵ� ���� ����Ʈ �����Ϳ� �����ϴ°� �����ϹǷ� ������ ������ �� �ִ�.
}
