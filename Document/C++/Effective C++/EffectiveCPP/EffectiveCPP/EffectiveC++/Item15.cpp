#include <iostream>
#include <vector>
#include <string>
using namespace std;

//�ڿ� ���� Ŭ�������� �����Ǵ� �ڿ��� �ܺο��� ������ �� �ֵ��� ����
namespace Item15 {

	class Investment {};

	Investment* CreateInvestment() { return new Investment(); }
	int daysHeld(const Investment *pi) {
		return 0;
	}
	int daysHeld(const Investment& pi) {
		return 0;
	}

	void func() {
		std::auto_ptr<Investment> pInv(CreateInvestment());

		//int days = daysHeld(pInv); //������ ����. ����Ʈ ������ ��ü�� ����� ���� ����

		int days = daysHeld(pInv.get());	//get��ɾ�� pInv ���� ���� �����͸� �ѱ��
		int days2 = daysHeld(*pInv);	//operator* �� ������ ����� �����Ѵ�
	}


	//��Ʈ �ڵ�. C API ���Ǵ� ����
	class FontHandle{};				
	void releaseFont(FontHandle fh) {};

	//RAII Ŭ����
	class Font {		
	public:

		//C API�� �ϱ⶧���� ���������� �ƴ� ������
		explicit Font(FontHandle fh) : f(fh) {}		
		FontHandle get() const { return f; }
		~Font() { releaseFont(f); }

		operator FontHandle() const { return f; }
	private:
		FontHandle f;
	};

	FontHandle getFont() { return FontHandle(); };
	void changeFontSize(FontHandle f, int newSize) {} //��Ʈ API �Ϻ�

	void Func2() {
		Font f(getFont());
		int newFontSize = 0;

		/*
			Font���� FontHandle�� �ٲ��� �ѱ��
			����Ҷ����� ��������� ��ȯ(get())�ؾ� �ϴ� ���� ���ŷο� �� �ִ�.
		*/
		changeFontSize(f.get(), newFontSize);	
												
		/*
			Ŭ���� �ȿ� operator()�� �����Ǿ� �ִٸ� �Ͻ��� ��ȯ�� ����(���ϴ�)
			������ �Ͻ��� ��ȯ�� �Ǽ��� ������ ������ �����
		*/
		changeFontSize(f, newFontSize);
									

		//�����/�Ͻ��� ��ȯ�� ���ؼ��� Ŭ���� ���� �ǵ��� ���� �޶��� �� �ִ�.
	}

	//RAIIŬ������ �ڿ��� �����ϴ� ������ �þ����� ĸ��ȭ�� ���ؼ��� ¤�� �Ѿ�� �Ѵ�.
	//shared_ptr �� ��� ���۷��� ī���ÿ� ���õ� �ڿ����� ���� ���������� �ڽ��� �����ϴ� �ڿ��� ���ؼ��� ���� ��θ� �����ϰ� �ִ�.
}