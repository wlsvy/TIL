#include <iostream>
#include <vector>
#include <string>
using namespace std;

//템플릿으로 만들어진 기본 클래스 안의 이름에 접근하는 방법을 알아두자

namespace Item43 {

	class CompanyA {
	public:
		void sendClearText(const std::string& msg) {}
		void sendEncrypted(const std::string& msg) {}
	};

	class CompanyB {
	public:
		void sendClearText(const std::string& msg) {}
		void sendEncrypted(const std::string& msg) {}
	};

	class MsgInfo{
	public:
		std::string content;
	};

	template<typename Company>
	class MsgSender {
	public:
		void sendClear(const MsgInfo& info) {
			Company c;
			c.sendCleartext(info.content);
		}

		void sendSecret(const MsgInfo& info){}
	};
	/*
		여기까진 문제없이 돌아가는 코드
	*/

	template<typename Company>
	class LoggingMsgSender : public MsgSender<Company> {
	public:
		void sendClearMsg(const MsgInfo& info) {
			//sendClear(info);	//MsgSender<Company> 의 sendClear를 호출하는데, 컴파일이 되지 않는다
		}

		/*
			현재 LogginMsgSender 입장에서는 sendClear() 는 존재하지 않는다. 
			LogginMsgSender가 클래스 템플릿 정의와 마주칠 때 이 클래스가 어떤 형태인지 알 수 없기 때문
			MsgSender<Company> 가 객체로 만들어지기 전까지는 이것이 어떤 형태인지는 알 수 없다.

			아래의 코드를 확인해보면, 타입 매개변수로 CompanyZ를 받는 MsgSender 처럼 sendClear가 존재하지 않는 경우도 있기 때문.
		*/
	};

	class CompanyZ {
	public:
		void sendEncrypted(const std::string& msg) {}
	};

	//MsgSender의 완전 특수화 버전. sendClear 함수가 빠져있다.
	template<>	
	class MsgSender<CompanyZ> {
	public:
		void sendSecret(const MsgInfo& info) {}
	};
}

namespace Item43_2 {
	//해결책

	class MsgInfo {
	public:
		std::string content;
	};

	template<typename Company>
	class MsgSender {
	public:
		void sendClear(const MsgInfo& info) {
			Company c;
			c.sendCleartext(info.content);
		}

		void sendSecret(const MsgInfo& info) {}
	};

	template<typename Company>
	class LoggingMsgSender : public MsgSender<Company> {
	public:

		//첫번째 방법 - "this->" 활용
		void sendClearMsg1(const MsgInfo& info) {
			this->sendClear(info);	//컴파일 가능. sendClear가 상속되는 것으로 가정
		}

		//두번째 방법 - "using 선언" 활용
		using MsgSender<Company>::sendClear;	//컴파일러에게 sendClear함수가 기본 클래스에 있다고 가정하라 요청
		void sendClearMsg2(const MsgInfo& info) {
			sendClear(info);	//컴파일 가능. sendClear가 상속되는 것으로 가정
		}

		//세번째 방법 - 명시적 한정
		void sendClearMsg3(const MsgInfo& info) {
			MsgSender<Company>::sendClear(info);	//컴파일 가능. MsgSender<Company> 의 sendClear를 명시적으로 지정
			/*
				만약 이 경우 호출되는 함수가 가상함수일 경우, 명시적 한정을 해버리면 가상 함수 바인딩이 무시된다.
			*/
		}
	};

	/*
		물론 정작 사용할 때 호출하는 함수가 현재 MsgSender의 템플릿 버전에 존재하지 않는다면 c++은 컴파일 에러를 띄운다. 
	*/
}