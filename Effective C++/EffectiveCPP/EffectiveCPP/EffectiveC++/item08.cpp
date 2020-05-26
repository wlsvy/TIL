/*

#include <iostream>
#include <vector>
#include <string>

class Widget {
public:
	~Widget() {}	
	//�Ҹ��ڿ��� ������ �߻��Ѵٰ� ����
	//c++ �� ���ܸ� �ѱ�� �Ҹ��ڸ� �������� �ʴ´�
};

void DoSomething() {
	std::vector<Widget> v(10);	
	//���Ϳ� ����� Ŭ���� ��ü�� ��ȯ�Ҷ� �� å���� ���Ϳ� �ִ�.
	//���� ������ ��ü�� �Ҹ�� �� ������ �����ٸ�?? 
}

class DBConnection {
public:
	static DBConnection create() { return DBConnection(); }
	void close();	//������ �ݱ�, �̶� ������ �����ϸ� ���� �߻�
};

class DBConn {
public:
	DBConn(DBConnection target) : db(target) {}

	void close() {	
		//public ���� �����Ͽ� ���α׷��Ӱ� ����� �� �ֵ���
		//1������ ���������� ������ ���α׷��ӿ���
		db.close();
		closed = true;
	}
	~DBConn() {	//���ܴ� �Ҹ��尡 �ƴ� �ٸ� �Լ����� ��ԵǾ�� �Ѵ�

		if (!closed) {	//����ڰ� ������ �� �ݾ����� ���⼭ �ݱ�
			try {
				db.close();
			}
			catch (std::exception& e) {
				//close ���� �α� �ۼ� - ���� �˸���
				//std::abort(); - ���α׷� �����ϴ� ����� ����
			}
		}
	}

private:
	DBConnection db;
	bool closed;
};

void DoSomething2() {
	DBConn dbc(DBConnection::create());	
	//DBConn ��ü ������ �Ҹ��� �̷��������, ���ÿ� DBConnection �� ���� ������ �Ҹ굵 �߻�
}

*/