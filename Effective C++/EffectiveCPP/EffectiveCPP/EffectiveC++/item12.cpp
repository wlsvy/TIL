//��ü�� ��� �κ��� �������� ��������
#include <iostream>
#include <vector>
#include <string>

namespace Item12 {
	class Customer {
	public:
		Customer(const Customer& rhs) : name(rhs.name) {}	//���������
		Customer& operator= (const Customer& rhs) {			//���Կ�����
			name = rhs.name;
			return *this;
		}
	private:
		std::string name;
	};

	class PriorityCustomer : public Customer {	//�Ļ�Ŭ������ ���, ������ ������ �� ������ ��
	public:
		PriorityCustomer(const PriorityCustomer& rhs) : priority(rhs.priority), 
			Customer(rhs) {}	//��� Ŭ������ ��������� �ݵ�� ȣ���ؾ� �Ѵ�. 
								//�׷��� ������ ���Ŭ���� �����ʹ� ���� X
		PriorityCustomer& operator= (const PriorityCustomer& rhs) {
			Customer::operator=(rhs); //���������� ��� Ŭ������ ���Կ����� ȣ�� 
			priority = rhs.priority;
			return *this;
		}
	private:
		int priority;
	};

	//��������ڿ� ���Կ������� �ڵ� �ߺ��� ���Ϸ��� ������ ������ �̿��ؼ� �ٸ�����
	//�����Ϸ��� �õ��� ���� ����� �ƴϴ�. ��������ڴ� ��ü ���� �� �ʱ�ȭ�� �Ҷ� ����Ǹ�
	//���� �����ڴ� �̹� �����ϴ� ��ü�� ���Խ�ų �� ����ȴ�. �и��� �ٸ� �������� Ȱ��ȴ�.
	//��� ���� ������ �� 3�� �Լ��� �и��� ���� ���ʿ��� �̰��� ȣ���ϴ� ����� Ȱ���� ���� �ִ�.

}