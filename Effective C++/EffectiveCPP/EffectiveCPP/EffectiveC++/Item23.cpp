#include <iostream>
#include <vector>
#include <string>
using namespace std;

namespace Item23 {
	//��� �Լ����ٴ� ���� �������� �Լ��� �� ���������

	class WebBrowser {	//�� �������� ��Ÿ���� Ŭ������ �ϳ� �ִٰ� ����
	public:
		void clearCache() {}
		void clearHistory() {}
		void removeCookies() {}


		//�� �������� �ʱ�ȭ ��Ű�� �Լ��� �ʿ��ϴٰ� �� ��.(�� ���, public ��� �Լ����� ����Ѵ�)
		//�Ʒ��� clearBrowser �Լ��� ��� �Լ� Ȥ�� ���� �������� �Լ� �߿��� � ������ �����Ǵ� ���� ������?

		void clearBrowser() {	//��� �Լ�
			clearCache();
			clearHistory();
			removeCookies();
		}
	};

	void clearBrowser(WebBrowser &wb) {	//���� �������� �Լ�
		wb.clearCache();
		wb.clearHistory();
		wb.removeCookies();
	}

	/*
		ĸ��ȭ ���鿡�� �Ǵ��Ѵٸ� ���� �������� �Լ� ���� �� ���� �����̴�.

		��� �Լ��� �ش� Ŭ������ private ����� ������ �� �ִ� �ݸ�, ���� ���������� ��� �׷� �� ���� ����.
		(������ �Լ��� �̾߱Ⱑ �޶����� -> Ŭ������ private ����� ������ �� �ִ�)
	*/

	//Ȯ���� ����Ҷ��� ���� �������� �Լ��� �����ϴ�
	//�� ������ Ŭ������ �����Ͽ�, ��Ű Ȥ�� �ϸ�ũ ���� �Լ��� �߰��Ϸ� �� ��

	//"webbrowser.h" ���
	namespace WebBrowserStuff {
		//�� ������ �ٽɱ�� ���� -> ���� ��� ����ڰ� ����ϴ� ���� �Լ����� �̰��� ����
	}

	//"webbrowserBookmark.h" ���
	namespace WebBrowserStuff {
		//�ϸ�ũ ���� �Լ����� ����.
	}

	//"webbrowserCookie.h" ���
	namespace WebBrowserStuff {
		//��Ű ���� �Լ����� ����.
	}

	//�� ó�� ��� ������ ���� �׸񺰷� �Լ��� ������ �����ϴ� ���� �����ϴ�.
	//Ŭ���� ����Լ���� ����� �ɰ��� ���� �Ұ����ϸ� ��ü�� ������ ���ǵǾ�� �Ѵ�.
}