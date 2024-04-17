#include <iostream>
#include <vector>
#include <string>
using namespace std;

//���ø����� ������� �⺻ Ŭ���� ���� �̸��� �����ϴ� ����� �˾Ƶ���

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
		������� �������� ���ư��� �ڵ�
	*/

	template<typename Company>
	class LoggingMsgSender : public MsgSender<Company> {
	public:
		void sendClearMsg(const MsgInfo& info) {
			//sendClear(info);	//MsgSender<Company> �� sendClear�� ȣ���ϴµ�, �������� ���� �ʴ´�
		}

		/*
			���� LogginMsgSender ���忡���� sendClear() �� �������� �ʴ´�. 
			LogginMsgSender�� Ŭ���� ���ø� ���ǿ� ����ĥ �� �� Ŭ������ � �������� �� �� ���� ����
			MsgSender<Company> �� ��ü�� ��������� �������� �̰��� � ���������� �� �� ����.

			�Ʒ��� �ڵ带 Ȯ���غ���, Ÿ�� �Ű������� CompanyZ�� �޴� MsgSender ó�� sendClear�� �������� �ʴ� ��쵵 �ֱ� ����.
		*/
	};

	class CompanyZ {
	public:
		void sendEncrypted(const std::string& msg) {}
	};

	//MsgSender�� ���� Ư��ȭ ����. sendClear �Լ��� �����ִ�.
	template<>	
	class MsgSender<CompanyZ> {
	public:
		void sendSecret(const MsgInfo& info) {}
	};
}

namespace Item43_2 {
	//�ذ�å

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

		//ù��° ��� - "this->" Ȱ��
		void sendClearMsg1(const MsgInfo& info) {
			this->sendClear(info);	//������ ����. sendClear�� ��ӵǴ� ������ ����
		}

		//�ι�° ��� - "using ����" Ȱ��
		using MsgSender<Company>::sendClear;	//�����Ϸ����� sendClear�Լ��� �⺻ Ŭ������ �ִٰ� �����϶� ��û
		void sendClearMsg2(const MsgInfo& info) {
			sendClear(info);	//������ ����. sendClear�� ��ӵǴ� ������ ����
		}

		//����° ��� - ����� ����
		void sendClearMsg3(const MsgInfo& info) {
			MsgSender<Company>::sendClear(info);	//������ ����. MsgSender<Company> �� sendClear�� ��������� ����
			/*
				���� �� ��� ȣ��Ǵ� �Լ��� �����Լ��� ���, ����� ������ �ع����� ���� �Լ� ���ε��� ���õȴ�.
			*/
		}
	};

	/*
		���� ���� ����� �� ȣ���ϴ� �Լ��� ���� MsgSender�� ���ø� ������ �������� �ʴ´ٸ� c++�� ������ ������ ����. 
	*/
}