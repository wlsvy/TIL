#include <iostream>
#include <vector>

class Rational {};

const Rational operator* (const Rational& lhs, const Rational& rhs);	//��ȯ ���� const �� ������ ������

void DoSomething() {
	Rational a, b, c;

	//(a * b) = c;	//���⼭ a*b�� ����� �ΰ� operator = �� ȣ���ϴ� ���� ���� ����
					//const �� �� ���� �Ұ���
}

class TextBlock {
public:
	TextBlock(std::string str) : text(str) {}

	//const char& operator[](std::size_t position) const { return text[position]; }	//��� ��ü�� ���� operator[]
	//char & operator[](std::size_t position) { return text[position]; }				//���� ��ü�� ���� operator[]
	const char& operator[](std::size_t position) const { return text[position]; }
	char & operator[] (std::size_t position) {				//�ڵ� �ߺ� ��ó ���(���� ������ ��� ���� ȣ��)
		return const_cast<char&>(							//c++ ���� ĳ������ �� ���� ���� ���̵������, �ڵ� �ߺ��� ���� �ѱ� �� ����.
			static_cast<const TextBlock&>(*this)[position]	//��� ���� operator[]�� ȣ��, *this�� const�� ���̰�, ��ȯ Ÿ�Կ��� const�� ����.
			);												//operator[]�ӿ��� operator[] �� ȣ���ϸ� ��������� ��� ȣ���ϰ� �Ǵ�,
	}														//const operator[]�� ȣ���ϱ� ���� ������� *this �� const �� ���δ�.(Ź���� ����� �ƴ����� ����å)			

private:
	std::string text;
};

void DoSomething2() {
	TextBlock tb("Hello");
	std::cout << tb[0];	//���� ��� ȣ��

	const TextBlock ctb("World");
	std::cout << ctb[0];	//��� ��� ȣ��

	tb[0] = 'x'; //���� ����
	//ctb[0] = 'x'; // ������ ����
}

void print(const TextBlock& ctb) {
	std::cout << ctb[0];	//��� ��� ȣ��
}

class CTextBlock {
public:
	CTextBlock(char * str) : pText(str) {}
	char & operator[] (std::size_t position) const { return pText[position]; }	//�������� 
																				//(�׷��� ��Ʈ���� ������� �־ ���Ǵ�) -> �����ڸ� ��ȯ�ϵ� pText�� ���� ��ġ�� �κ��� ������
																				//operator[] �� ����
	std::size_t Length() const;
private:
	char *pText;
	mutable std::size_t textLength;		//�� ������ ������� � �������� ���� ����
	mutable bool lengthIsValid;			//������ ��� ����Լ� ���̶� ����
};

void DoSomething3() {
	const CTextBlock cctb((char*)"Hello");	//��� ��ü ����
	char *pc = &cctb[0];					//��� ������ operator[]�� ȣ���Ͽ� cctb��
											//���� �����Ϳ� ���� �����͸� ����ϴ�.
	*pc = 'j';		//cctb�� ���� jello ��� ���� �����ϴ�. -> �и� ��� ��ü�ӿ��� ���� ��� ������ ����Ǿ���.
}

std::size_t CTextBlock::Length() const {
	if (!lengthIsValid) {
		textLength = std::strlen(pText);	//��� ��� �Լ��ȿ����� �Ϲ������� �ȵ�����
		lengthIsValid = true;				//mutable Ű���尡 �پ ����
	}

	return textLength;
}
