#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//���� ������ ������ �������� �ִ�� ������

namespace Item31 {

	/*
		���� include �����ڿ��� #include <string>, string �� ���漱���� �ؼ� �ȵȴ�

		string�� ��� Ŭ������ �ƴ϶� typedef�� ������ Ÿ�Ե��Ǿ� (basic_string<char>�� typedef �� ��)
		string�� ���漱���� ���� ���� ����.

		ǥ�� ���̺귯�� ����� �Ϲ����� ��� ������ �� ��������� ���� �ʴ´�. #include <string> �� ����.
	*/

	class PersonImpl;	//���漱��
	class Date;
	class Address;

	/*
		������/ ������ �ڿ� ���� ��ü �����θ� ����ٸ� ����ϴ� �������� �ش� Ÿ�Կ� ���� ��Ȯ�� ���� ���ϴ��� �����Ͽ��� ������ ����.
		���Ǻο� ���� ������(dependencies on definitions)�� ����ο� ���� ������(dependencies on declarations)���� �ٲپ� ���� ��

		��ü ������ �� �����ͷ� ����� ��쿡�� ��ü�� ���� ������� �ʴ´�

		� Ŭ������ ����ϴ� �Լ��� ������ ���� �� Ŭ������ ���Ǹ� �������� �ʾƵ� �ȴ�.
		-> �ش� Ŭ������ �� ���� �Ű������� �����ϰų� ��ȯ�ϴ��� Ŭ���� ���ǰ� �ʿ� ����.
		-> �Լ��� ȣ��Ǳ� ������ �ش� Ÿ�� ������ �����Ϸ��� �˰� �ȴٸ� ok

		����ο� ���Ǻο� ���� ������ ��� ������ �����Ѵ�.
	*/

	//���� �����ϴ� ��� 1 -> �ڵ� Ŭ����
	//PersonHandle Ŭ���� ����δ�, Date, address, PersonImpl �� ���� ���Ǹ� ���� ���漱���̸� ���.
	class PersonHandle {
	public:
		PersonHandle(const std::string& name, const Date& birthday, const Address& addr);
		std::string name() const;
		Date birthday() const;
		Address address() const;
	private:
		std::shared_ptr<PersonImpl> pImpl;
	};

	//���� �����ϴ� ��� 2 -> �������̽� Ŭ����
	//� ����� ��Ÿ���� �������̽��� �߻� �⺻ Ŭ������ ���� ������ ����, �� Ŭ�����κ��� �Ļ� Ŭ������ ���� �� �ְ� �ϴ� ��
	class PersonInterface {
	public:
		static shared_ptr<PersonInterface> create(const std::string& name, const Date& birthday, const Address& addr);
		virtual ~PersonInterface() {}
		virtual std::string name() const = 0;
		virtual Date birthday() const = 0;
		virtual Address address() const = 0;
	};

	
	//����� �������� Item31.h ����/ Date, Address Ŭ���� ���� �� ���Խ�Ű�� ���� �������̽����� �������� ��밡���ϴ�.
	void func0();

	/*
		���̺귯�� ����� �� ��ü�� ��� ���� ���߾�� �ϸ� ����θ� ���� �ִ� ���¿��� �մϴ�. �� ��Ģ�� ���ø��� ���̰ų� ������ �ʰų� �����ϰ� �����սô�.
	*/
}