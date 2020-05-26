#include <iostream>
#include <vector>
#include <string>
using namespace std;

namespace Item17 {
	//new�� ������ ��ü�� ����Ʈ �����Ϳ� �����ϴ� �ڵ�� ������ �� �������� ������

	class Widget{};

	void ProcessWidget(std::shared_ptr<Widget> pw, int priority) {}	//�������� ������ Widget�� ���� �켱������ ���� ó���ϴ� �Լ�
	int priority(); //ó�� �켱������ �˷��ִ� �Լ�

	void Func() {
		//ProcessWidget(new Widget, priority());	������ X, 
													//shared_ptr �����ڴ� explicit ������ �Ǿ��־�
													//new Widget�� ��ȯ�ϴ� �����ͷ� �Ͻ��� ��ȯ�� �Ұ����ϴ�.

		ProcessWidget(std::shared_ptr<Widget>(new Widget), priority());	//�� ������ �ڿ��� �긱 ���ɼ��� �ִ�
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
		std::shared_ptr<Widget> pw(new Widget);	//������ ���ϱ� ���ؼ� 
												//new�� ���� ��ü�� ����Ʈ �����Ϳ� ��� ������ ���� �� �������� ���� �� 
												//�� ����� �����Ϸ��� �������� ���� ������ ���� ������ �ڿ� ���� ���ɼ��� �����Ѵ�.

		ProcessWidget(pw, priority());
	}


	int priority() {
		return 0;
	}
}
