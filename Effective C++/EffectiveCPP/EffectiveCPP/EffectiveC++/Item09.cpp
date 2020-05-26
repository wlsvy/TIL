#include <iostream>
#include <vector>
#include <string>

class Transaction {
public:
	Transaction()
	{
		logTransaction();
	}
	virtual void logTransaction() const { std::cout << "Transaction" << std::endl; }
};

class BuyTransaction : public Transaction {
public:
	virtual void logTransaction() const { std::cout << "BuyTransaction" << std::endl; }
};

void Item09() {
	BuyTransaction tr;		//BuyTransaction 가 아닌 Transaction 출력
}