#pragma once
#include "Item31.h"

namespace Item31 {

	class Date{};
	class Address {};

	class PersonImpl {
	public:
		PersonImpl(const std::string& name, const Date& birthday, const Address& addr) : theName(name), birthDay(birthday), Address(addr) {}
		std::string name() const { return theName; }
		Date birthday() const { return birthDay; }
		Address address() const { return Address; }
	private:
		std::string theName;
		Date birthDay;
		Address Address;
	};

	class RealPerson : public PersonInterface {
	public:
		RealPerson(const std::string& name, const Date& birthday, const Address& addr) : theName(name), birthDay(birthday), Address(addr) {}
		std::string name() const { return theName; }
		Date birthday() const { return birthDay; }
		Address address() const { return Address; }
	private:
		std::string theName;
		Date birthDay;
		Address Address;
	};
}