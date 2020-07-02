#include <iostream>
#include <vector>
#include <string>

//��ü�� ��� �κ��� �������� ��������

namespace Item12 {

	/*
		��ü ���� �Լ��� �־��� ��ü�� ��� ������ ��� �� ��� �⺻ Ŭ���� �κ��� ���߸��� ���� �����ؾ� �մϴ�.

		���� ���� �����ڿ��� ���� �����ڸ� ȣ������ �� ��. 
		���� ��ü�� �� �����Ѵ�. �� �ݴ뵵 ��������. �����ڴ� ��ü�� �ʱ�ȭ�ϴ� �������� ���� ������ �ʱ�ȭ�� ��ü�� ���� �ִ� ���̴�.
	*/

	class Customer {
	public:
		//���������
		Customer(const Customer& rhs) : name(rhs.name) {}	

		//���Կ�����
		Customer& operator= (const Customer& rhs) {			
			name = rhs.name;
			return *this;
		}
	private:
		std::string name;
	};

	//�Ļ�Ŭ������ ���, ������ ������ �� ������ ��
	class PriorityCustomer : public Customer {	
	public:
		/*
			��� Ŭ������ ��������� �ݵ�� ȣ���ؾ� �Ѵ�. 
			�׷��� ������ ���Ŭ���� �����ʹ� ���� ���� �ʴ´�.
		*/
		PriorityCustomer(const PriorityCustomer& rhs) : priority(rhs.priority), Customer(rhs) {}
				
		PriorityCustomer& operator= (const PriorityCustomer& rhs) {

			//���������� ��� Ŭ������ ���Կ����� ȣ�� 
			Customer::operator=(rhs); 

			priority = rhs.priority;
			return *this;
		}
	private:
		int priority;
	};

	/*
		��������ڿ� ���Կ������� �ڵ� �ߺ��� ���Ϸ��� ������ ������ �̿��ؼ� �ٸ�����
		�����Ϸ��� �õ��� ���� ����� �ƴϴ�. ��������ڴ� ��ü ���� �� �ʱ�ȭ�� �Ҷ� ����Ǹ�
		���� �����ڴ� �̹� �����ϴ� ��ü�� ���Խ�ų �� ����ȴ�. �и��� �ٸ� �������� Ȱ��ȴ�.
		��� ���� ������ �� 3�� �Լ��� �и��� ���� ���ʿ��� �̰��� ȣ���ϴ� ����� Ȱ���� ���� �ִ�.
	*/
}