#include <iostream>
#include <vector>
#include <string>
#include <functional>

//���߻���� �ɻ�����ؼ� �������

namespace Item40 {
	using namespace std;

	//���� ���� ����� �������̶�� �������� ������ ������� ����� 
	//���� �⺻ Ŭ����(virtual base class) ��� �ٸ� ���� ���� ���(virtual inheritance)�� ���ؼ� �ذ� �����ϴ�.

	class File {};

	class InputFile : virtual public File {};
	class OutputFile : virtual public File {};

	class IOFile : public InputFile, public OutputFile {};

	/*
		���� ����� Ȱ���Ѵٸ� �׷��� ���� ��캸�� �ش� Ŭ������ ũ�Ⱑ �� Ŀ����
		�⺻ Ŭ���� �����Ϳ� �����ϴ� �ӵ� ���� ������
		���� ���굵 ��������.

		���⿡ ���ؼ� ���� �⺻ Ŭ������ ���õ� ��Ģ�� �񰡻� �⺻ Ŭ������ �ʱ�ȭ���� �����ϴ�.


		���� ����� �����ϰ� �� �� �ִ� ��찡 �ֽ��ϴ�. 
		���� �ó����� �� �ϳ���, �������̽� Ŭ�����κ��� public ����� ��Ŵ�� ���ÿ� ������ ���� Ŭ�����κ��� private ����� ��Ű�� ���Դϴ�.
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

	//�������̽��� public ���, PersonInfo�� private ���
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
		�������̽� Ŭ������ public ��� �ް� ���ÿ� ������ ���� Ŭ������ private ��ӹ޴� �����
		���� ����� �����ϰ� ����ϴ� ��� �� �ϳ�
	*/
}