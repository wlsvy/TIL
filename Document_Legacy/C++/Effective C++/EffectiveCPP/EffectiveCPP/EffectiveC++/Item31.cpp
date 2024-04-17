#pragma once
#include "Item31.h"
#include "Item31_Impl.h"

namespace Item31 {
	PersonHandle::PersonHandle(const std::string & name, const Date & birthday, const Address & addr)
		: pImpl(new PersonImpl(name, birthday, addr)) {}

	std::string PersonHandle::name() const { return pImpl->name(); }
	Date PersonHandle::birthday() const { return pImpl->birthday(); }
	Address PersonHandle::address() const { return pImpl->address(); }

	shared_ptr<PersonInterface> PersonInterface::create(const std::string& name, const Date& birthday, const Address& addr) {
		return shared_ptr<PersonInterface>(new RealPerson(name, birthday, addr));
	}

	void func0() {
		PersonHandle ph("Smith", Date(), Address());
		auto pi = PersonInterface::create("Ben", Date(), Address());

		cout << ph.name() << endl << pi->name();
	}
}