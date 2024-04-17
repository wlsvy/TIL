#include <iostream>
#include <vector>
#include <string>
#include <functional>

//다중상속은 심사숙고해서 사용하자

namespace Item40 {
	using namespace std;

	//소위 다중 상속의 문제점이라고 여겨지는 죽음의 마름모꼴 상속은 
	//가상 기본 클래스(virtual base class) 상속 다른 말로 가상 상속(virtual inheritance)을 통해서 해결 가능하다.

	class File {};

	class InputFile : virtual public File {};
	class OutputFile : virtual public File {};

	class IOFile : public InputFile, public OutputFile {};

	/*
		가상 상속을 활용한다면 그렇지 않은 경우보다 해당 클래스는 크기가 더 커진다
		기본 클래스 데이터에 접근하는 속도 역시 느리다
		대입 연산도 느려진다.

		여기에 더해서 가상 기본 클래스에 관련된 규칙은 비가상 기본 클래스의 초기화보다 복잡하다.


		다중 상속을 적법하게 쓸 수 있는 경우가 있습니다. 
		여러 시나리오 중 하나는, 인터페이스 클래스로부터 public 상속을 시킴과 동시에 구현을 돕는 클래스로부터 private 상속을 시키는 것입니다.
	*/

	class IPerson {
	public:
		virtual ~IPerson();

		virtual std::string name() const = 0;
		virtual std::string birthday() const = 0;
	};

	class DatabaseID {};

	class PersonInfo {
	public:
		explicit PersonInfo(DatabaseID pid) {}
		virtual ~PersonInfo() {}

		virtual const char* theName() const { return name.c_str(); }
		virtual const char* theBirthDay() const { return birthday.c_str();}
		virtual const char* valueDelimOpen() const { return ""; }
		virtual const char* valueDelimClose() const { return ""; }

	private:
		std::string name;
		std::string birthday;
	};

	//인터페이스를 public 상속, PersonInfo를 private 상속
	class CPerson : public IPerson, private PersonInfo {	
	public:
		explicit CPerson(DatabaseID pid) : PersonInfo(pid) {}

		virtual std::string name() const { return PersonInfo::theName(); }
		virtual std::string birthDate() const { return PersonInfo::theBirthDay(); }
	private:
		virtual const char* valueDelimOpen() const { return "["; }
		virtual const char* valueDelimClose() const { return "]"; }

	};

	/*
		인터페이스 클래스를 public 상속 받고 동시에 구현을 돕는 클래스를 private 상속받는 방법은
		다중 상속을 적법하게 사용하는 방법 중 하나
	*/
}