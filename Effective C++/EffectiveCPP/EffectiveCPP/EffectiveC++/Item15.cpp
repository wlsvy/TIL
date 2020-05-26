#include <iostream>
#include <vector>
#include <string>
using namespace std;

namespace Item15 {
	//�ڿ� ���� Ŭ�������� �����Ǵ� �ڿ��� �ܺο��� ������ �� �ֵ��� ����

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
		//int days = daysHeld(pInv); <- ����. ����Ʈ ������ ��ü�� ����� ���� ����
		int days = daysHeld(pInv.get());	//get��ɾ�� pInv ���� ���� �����͸� �ѱ��
		int days2 = daysHeld(*pInv);		//operator* �� ������ ����� �����Ѵ�
	}



	class FontHandle{};				//��Ʈ �ڵ�. C API ���Ǵ� ����
	void releaseFont(FontHandle fh) {};

	class Font {		//RAII Ŭ����
	public:
		explicit Font(FontHandle fh) : f(fh) {}		//C API�� �ϱ⶧���� ���������� �ƴ� ������
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

		changeFontSize(f.get(), newFontSize); //Font���� FontHandle�� �ٲ��� �ѱ��
												//����Ҷ����� ��������� ��ȯ(get())�ؾ� �ϴ� ���� ���ŷο� �� �ִ�.

		changeFontSize(f, newFontSize);		//Ŭ���� �ȿ� operator()�� �����Ǿ� �ִٸ� �Ͻ��� ��ȯ�� ����!(���ϴ�)
											//������ �Ͻ��� ��ȯ�� �Ǽ��� ������ ������ �����

		//�����/�Ͻ��� ��ȯ�� ���ؼ��� Ŭ���� ���� �ǵ��� ���� �޶��� �� �ִ�.
	}

	//RAIIŬ������ �ڿ��� �����ϴ� ������ �þ����� ĸ��ȭ�� ���ؼ��� ¤�� �Ѿ�� �Ѵ�.
	//shared_ptr �� ��� ���۷��� ī���ÿ� ���õ� �ڿ����� ���� ���������� �ڽ��� �����ϴ� �ڿ��� ���ؼ��� ���� ��θ� �����ϰ� �ִ�.
}