#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <tuple>
using namespace std;

//���� ���� enum ���� ���� �ִ� enum�� ��ȣ�϶�

namespace Item10 {

	namespace Unscoped {
		//���� ���� enum�� enum�� �����ϴ� ������ ���Ѵ�. -> namespace ���� ����� �ִ�.
		enum Color {black, white, red};

		//auto white = false; ����, �̹� white�� ����Ǿ� �ִ�.
	}

	namespace Scoped {
		//���� Color ������ ���ϰ� �ȴ�.
		enum class Color { black, white, red };

		auto white = false; //���� ����
	}

	enum SystemStatus;

	void DoSomething(size_t) { cout << "DoSomething(size_t)" << endl; }
	void DoSomething(SystemStatus) { cout << "DoSomething(SystemStatus)" << endl; }

	/*
		���� ���� enum�� �������� å������ ���漱���� �ȵȴٰ� ��޵�����, ���� �غ��� ���漱���� �����ϴ�!
		�� ���漱���� ���� ������ �������� ���� �� �ִ�.
	*/
	enum SystemStatus
	{
		good = 0,
		failed = 1,
		incomplete = 100,
		corrupt = 200,
		indeterminate = 0xfffffff
	};

	inline void RunSample() {
		/*
			�������� enum�� ����. �Ϲ������� ���� �������� ��ȯ�ǹǷ� ������ �߻���ų �� �ִ�.
		*/
		auto uc = Unscoped::red;
		if (uc < 14.5) {	//�Ͻ������� double �� ��, size_t�� ����ȯ
			DoSomething(uc);	//"DoSomething(size_t)"
		}


		auto sc = Scoped::Color::red;
		/*if (sc < 14.5) {	//���� :���� �ִ� enum�� �Ͻ������� �ٸ� �������� ��ȯ���� �ʴ´�.
			DoSomething(sc);
		}*/

		DoSomething(good);	//"DoSomething(SystemStatus)"
	}

	

	namespace Unscoped {
		/*
		�޸𸮸� ȿ�������� ����ϱ� ���� �����Ϸ����� �־��� enum�� ������ ������ ������ ǥ���� �� �ִ� ���� ���� ���� ������ �����Ѵ�.
		Ex) Color ���� ��� char �� ǥ��, SystemStatus ���� ��� int

		���� �ִ� enum�� �⺻ ���� ������ int �̸� ���α׷��Ӱ� ��������� �ٸ� ������ ���� �����ϴ�.
		*/
		enum UserInfoFields : std::uint8_t;	//���漱��� ���ÿ� ���� ���� ����

		enum UserInfoFields : std::uint8_t	//���ǿ� ���ÿ� ���� ���� ����
		{
			uiName,
			uiEmail,
			uiReputation
		};

		using UserInfo = std::tuple<string, string, size_t>;

		void RunUserInfoSample() {
			UserInfo uInfo;
			auto name = std::get<uiName>(uInfo);	//�Ͻ������� ������ ��ȯ�Ǵ� Ư¡ Ȱ��.(������ �ð��� ��ȯ�ǹǷ� get<size_t> �� ���� ���� �� �ִ�.)
			auto mail = std::get<uiEmail>(uInfo);
			auto reputation = std::get<uiReputation>(uInfo);
		}
	}

	namespace Scoped {
		/*
			���� ���� enum ���� ���� �ִ� enum �� �� ������ ���,
		*/
		enum class UserInfoFields : std::uint8_t
		{
			uiName,
			uiEmail,
			uiReputation
		};

		template<typename E>
		constexpr auto toUTtype(E enumerator) noexcept {
			return static_cast<std::underlying_type_t<E>>(enumerator);	//enum ���� �ٲٴ� �Լ��� �ʿ��ϴ�. Ʃ���� ���� ��� get �Լ��� ����ϱ� ���ؼ� constexpr ����
		}

		using UserInfo = std::tuple<string, string, size_t>;

		void RunUserInfoSample() {
			UserInfo uInfo;
			auto name = std::get<toUTtype(UserInfoFields::uiName)>(uInfo);	//���ŷο� Ÿ���� �۾� �ʿ�
			auto mail = std::get<toUTtype(UserInfoFields::uiEmail)>(uInfo);
			auto reputation = std::get<toUTtype(UserInfoFields::uiReputation)>(uInfo);
		}
	}
	

	
}