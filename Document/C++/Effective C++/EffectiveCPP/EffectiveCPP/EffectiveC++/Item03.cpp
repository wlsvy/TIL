#include <iostream>
#include <vector>

//������ ���̸� const�� ���̴� ����!
namespace Item03 {
	using namespace std;

	/*
		const�� �ٿ� �����ϸ� �����Ϸ��� ������ ������ ��Ƴ��� �� ������ �ݴϴ�. 

		const�� � ��ȿ������ �ִ� ��ü���� ���� �� ������, 
		�Լ� �Ű����� �� ��ȯ Ÿ�Կ��� ���� �� ������, 
		��� �Լ����� ���� �� �ֽ��ϴ�.

		const�� ���� ��� ���� ������ �� �ִ�.

		��� ������
		STL �� const_iterator 
		const ��� �Լ� ����
	*/

	class Rational {};

	//�Լ� ��ȯ ���� ����� ���� �ָ�, �������̳� ȿ���� �������� �ʰ� ��������� ���� ���� ��Ȳ�� ���̴� ȿ���� �� ���� �� �� �ְ� �ȴ�
	const Rational operator* (const Rational& lhs, const Rational& rhs);

	void DoSomething() {
		Rational a, b, c;

		/*
			���⼭ a*b�� ����� �ΰ� operator = �� ȣ���ϴ� ���� ����.
			const ��ü�� �� ������ �Ұ����ؼ� �Ʒ� �ڵ�� ������ ����
		*/
		//(a * b) = c;
	}

	class TextBlock {
	public:
		TextBlock(std::string str) : text(str) {}

		//��� ��ü�� ���� operator[]
		//const char& operator[](std::size_t position) const { return text[position]; }	
		
		//���� ��ü�� ���� operator[]
		//char & operator[](std::size_t position) { return text[position]; }				

		//��� ��� �� ���� ��� �Լ����� �ڵ� �ߺ��� ���ϴ� ���.
		/*
			���� ������ ��� ������ ȣ���Ѵ�.

			c++ ���� ĳ������ �� ���� ���� ���̵������, �ڵ� �ߺ��� ���� �ѱ� �� ����.

			��� ���� operator[]�� ȣ��, *this�� const�� ���̰�, ��ȯ Ÿ�Կ��� const�� ����.
			operator[]�ӿ��� operator[] �� ȣ���ϸ� ��������� ��� ȣ���ϰ� �Ǵ�,
			const operator[]�� ȣ���ϱ� ���� ������� *this �� const �� ���δ�.(Ź���� ����� �ƴ����� ����å)	
		*/
		const char& operator[](std::size_t position) const { return text[position]; }
		char & operator[] (std::size_t position) {				
			return const_cast<char&>(							
				static_cast<const TextBlock&>(*this)[position]	
				);												
		}																

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

	/*
		��Ʈ���� �����bitwise constness : �ٸ� ���� ������ ������̶�� �Ѵ�. 
		
		� ��� �Լ��� �� ��ü�� � ������ ����� �ǵ帮�� �ʾƾ�(���� ��� ����) �� ��� �Լ��� 'const' ���� �����ϴ� ����. 
		�� �� ��ü�� �����ϴ� ��Ʈ�� �� � �͵� �ٲٸ� �� �ȴٴ� ��.

		���� ������̶� ��� ��� �Լ���� �ؼ� ��ü�� �� ��Ʈ�� ������ �� ���� ���� �ƴ϶� �Ϻ� �� ��Ʈ ������ �ٲ� �� �ֵ�, 
		�װ��� ����������� �˾�ä�� ���ϰԸ� �ϸ� ��� ��� �ڰ��� �ִٴ� ��
	*/

	class CTextBlock {
	public:
		CTextBlock(char * str) : pText(str) {}

		/*
			������������ ��Ʈ���� ������� �־ ���ȴ�.
			 -> �����ڸ� ��ȯ�ϵ� pText�� ���� ��ġ�� �κ��� ��� �����ϴ�.
			operator[] �� ����
		*/
		char & operator[] (std::size_t position) const { return pText[position]; }	
																					
																					
		std::size_t Length() const;
	private:
		char *pText;
		
		//mutable Ű���尡 ���� ����Լ��� const ��� �Լ� ���ο����� ������ �����ϴ�.
		mutable std::size_t textLength;	
		mutable bool lengthIsValid;		
	};

	void DoSomething3() {
		/*
			��� ��ü�� ���ؼ� operator[]�� ȣ���� �� ���� �������� �����͸� ȹ���Ѵ�.
		*/
		const CTextBlock cctb((char*)"Hello");
		char *pc = &cctb[0];					
		
		//cctb�� ���� jello ��� ���� ���´�. -> �и� ��� ��ü�ӿ��� ���� ��� ������ ����Ǿ���.
		*pc = 'j';		

		/*
			���� ������̶� �̷� Ȳ���� ��Ȳ�� �����ϴ� �������� �����Ͽ���.

			���� ������̶� ��� ��� �Լ���� �ؼ� ��ü�� �� ��Ʈ�� ������ �� ���� ���� �ƴ϶� �Ϻ� �� ��Ʈ ������ �ٲ� �� �ֵ�,
			�װ��� ����������� �˾�ä�� ���ϰԸ� �ϸ� ��� ��� �ڰ��� �ִٴ� ��
		*/
	}

	std::size_t CTextBlock::Length() const {
		//��� ��� �Լ� ���������� mutable Ű���尡 ���� ����� ���� ����
		if (!lengthIsValid) {
			textLength = std::strlen(pText);
			lengthIsValid = true;			
		}

		return textLength;
	}
}