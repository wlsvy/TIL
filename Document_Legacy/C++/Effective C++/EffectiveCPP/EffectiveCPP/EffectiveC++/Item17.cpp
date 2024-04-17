#include <iostream>
#include <vector>
#include <string>
using namespace std;

//new�� ������ ��ü�� ����Ʈ �����Ϳ� �����ϴ� �ڵ�� ������ �� �������� ������
namespace Item17 {

	class Widget{};

	//�������� ������ Widget�� ���� �켱������ ���� ó���ϴ� �Լ�
	void ProcessWidget(std::shared_ptr<Widget> pw, int priority) {}	

	//ó�� �켱������ �˷��ִ� �Լ�
	int priority(); 

	void Func() {

		/*
			�Ʒ������� ������ ����, 
			shared_ptr �����ڴ� explicit ������ �Ǿ��־�
			new Widget�� ��ȯ�ϴ� �����ͷ� �Ͻ��� ��ȯ�� �Ұ����ϴ�.
		*/
		//ProcessWidget(new Widget, priority());	
													
													
		//�� ������ �ڿ��� �긱 ���ɼ��� �ִ�
		ProcessWidget(std::shared_ptr<Widget>(new Widget), priority());	
		/*
			�����Ϸ��� ProcessWidget ȣ�� �ڵ带 ����� ���� �Ű������� �Ѱ����� ���ڸ� ���Ѵ�.

			std::shared_ptr<Widget>(new Widget) �� ������
			new Widget ǥ���� ���� -> std::shared_ptr<Widget>�� ������ ȣ��  �� ������ �̷������.

			�� ProcessWidget �Լ��� ȣ��Ǳ� ����
			priority() ȣ�� -> new Widget ȣ�� -> std::shared_ptr<Widget> ������ ȣ��
			������ �̷������ �� ��

			������ �����Ϸ����� �� �ٸ� ��찡 �ִµ� ���� ���� ������ �ٸ� ��찡 �ִ�.
			new Widget ȣ�� -> priority() ȣ�� ->  std::shared_ptr<Widget> ������ ȣ��
			�䷸�� �� �� ������, priority()�� ��� ����°�� ���� �� ���� �ִ� ��.

			������ ���࿡ priority�� �߰����� ȣ��� �� priority �ȿ��� ���ܰ� �߻��Ѵٸ�??
			new Widget���� ������� �ڿ��� shared_ptr�� ������� ���ϰ� �״�� �Ҿ������ �ȴ�.
		*/
	}

	void Func2() {

		/*
			������ ���ϱ� ���ؼ� 
			new�� ���� ��ü�� ����Ʈ �����Ϳ� ��� ������ ���� �� �������� ���� �� 
			�� ����� �����Ϸ��� �������� ���� ������ ���� ������ �ڿ� ���� ���ɼ��� �����Ѵ�.
		*/
		std::shared_ptr<Widget> pw(new Widget);	
		ProcessWidget(pw, priority());
	}


	int priority() {
		return 0;
	}
}
