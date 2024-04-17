#include "Item22.h"

namespace Item22 {
	struct Impl {                    // Widget::ImplÀÇ Á¤ÀÇ
		std::string name;                    
		std::vector<double> data;
	};

	Case1::Widget::Widget() : pImpl(std::make_unique<Impl>()) {}

	Case1::Widget::~Widget() {}

	Case2::Widget::Widget() : pImpl(std::unique_ptr<Impl>(new Impl())) {}
		
	Case2::Widget::~Widget() {}

	Case2::Widget::Widget(Case2::Widget && rhs): pImpl(std::move(rhs.pImpl)) {}

	Case2::Widget & Case2::Widget::operator=(Case2::Widget && rhs)
	{
		pImpl = std::move(rhs.pImpl);
		return *this;
	}
}


