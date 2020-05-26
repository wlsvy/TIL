#include <iostream>
#include <vector>
#include <string>
using namespace std;

namespace Item23 {
	//멤버 함수보다는 비멤버 비프렌드 함수와 더 가까워지자

	class WebBrowser {	//웹 브라우저를 나타내는 클래스가 하나 있다고 가정
	public:
		void clearCache() {}
		void clearHistory() {}
		void removeCookies() {}


		//웹 브라우저를 초기화 시키는 함수가 필요하다고 할 때.(이 경우, public 멤버 함수들을 사용한다)
		//아래의 clearBrowser 함수는 멤버 함수 혹은 비멤버 비프렌드 함수 중에서 어떤 것으로 구현되는 것이 좋은지?

		void clearBrowser() {	//멤버 함수
			clearCache();
			clearHistory();
			removeCookies();
		}
	};

	void clearBrowser(WebBrowser &wb) {	//비멤버 비프렌드 함수
		wb.clearCache();
		wb.clearHistory();
		wb.removeCookies();
	}

	/*
		캡슐화 측면에서 판단한다면 비멤버 비프렌드 함수 쪽이 더 나은 선택이다.

		멤버 함수는 해당 클래스의 private 멤버에 접근할 수 있는 반면, 비멤버 비프렌드의 경우 그럴 수 없기 때문.
		(프렌드 함수는 이야기가 달라진다 -> 클래스의 private 멤버에 접근할 수 있다)
	*/

	//확장을 고려할때도 비멤버 비프렌드 함수가 유리하다
	//웹 브라우저 클래스에 관련하여, 쿠키 혹은 북마크 관련 함수를 추가하려 할 때

	//"webbrowser.h" 헤더
	namespace WebBrowserStuff {
		//웹 브라우저 핵심기능 선언 -> 거의 모든 사용자가 써야하는 비멤버 함수들이 이곳에 선언
	}

	//"webbrowserBookmark.h" 헤더
	namespace WebBrowserStuff {
		//북마크 관련 함수들이 들어간다.
	}

	//"webbrowserCookie.h" 헤더
	namespace WebBrowserStuff {
		//쿠키 관련 함수들이 들어간다.
	}

	//위 처럼 헤더 파일을 나눠 항목별로 함수를 나누어 구분하는 것이 가능하다.
	//클래스 멤버함수라면 기능을 쪼개는 것이 불가능하며 전체가 통으로 정의되어야 한다.
}