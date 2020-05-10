
#include "device/CgaChannel.h"
#include "io/PrintStream.h"

CgaChannel cga;		// unser CGA-Ausgabekanal
PrintStream out(cga);	// unseren PrintStream mit Ausgabekanal verknuepfen

int main()
{

	for (int i = 0; i < 200; i++) {
		out.print(i); out.print(";");
	}
	const CgaAttr attr;
	//const CgaAttr* attrptr = &attr;
	//const CgaAttr& attr1 = (CgaAttr&) attrptr;
	const char* p = "Test";
	//funktioniert

	out.println("Hello World");

	for (int i = 0; i < 1000; i++) {
		out.print("Dezimal ");
		out.print(i);
		out.println();
		cga.setCursor(0, 0);

		out.print("Binaer ");
		out.print(i, 2);
		out.println();

		cga.setCursor(0, 0);
		out.print("Hexadezimal ");
		out.print(i, 16);
		out.println();
		for (int k = 0; k <= 10000; k++) {

		}
		cga.setCursor(0, 0);

		cga.scroll();
	}
	for (int k = 0; k <= 1000000; k++) {

	}

	cga.blueScreen("ERROR");

	for (int k = 0; k <= 1000000; k++) {

	}

	cga.clear();

	for (int i = 0; i < 1; i++) {

		char string = 's';
		const char* str = &string;
		int y = 1;
		int f = 0;
		unsigned z = 23;
		void* d = &z;
		cga.setCursor(f, y);
		cga.show('a', attr);
		cga.setCursor(10, 1);
		out.println("show(char ch, const CgaAttr& attr)");

		cga.setCursor(0, 2);
		out.println("println");
		cga.setCursor(10, 2);
		out.println("println()");

		cga.setCursor(0, 4);
		out.print('c');
		cga.setCursor(10, 4);
		out.println("print(char ch)");

		cga.setCursor(0, 7);
		out.print(234, 10);
		cga.setCursor(10, 7);
		out.println("print(int x, int base = decimal) Fehlerhaft");

		cga.setCursor(0, 8);
		out.print(z, 16);
		cga.setCursor(10, 8);
		out.println("print(unsigned z, int base = decimal)");

		cga.setCursor(0, 9);
		cga.write(p, 4); //funktioniert
		cga.setCursor(10, 9);
		out.println("write(const char* data, int size)");

		cga.setCursor(0, 10);
		out.print(d);
		cga.setCursor(10, 10);
		out.println("print(void* p)");
		i = 1;
	}
	for (int k = 0; k <= 50000000; k++) {

	}

	cga.setCursor (0, 24);
	out.println("This was the CgaScreen.cc and Printstream.cc Class");

	out.println("__________________________________________________________________________________________________________________________________");
	cga.scroll();

	for (int k = 0; k <= 50000000; k++) {

	}

	for (int j = 0; j < 25; j++) {
		for (int i = 0; i < 80; i++) {

			for (int k = 0; k <= 10000; k++) {

			}
			cga.setCursor(i, j);
			out.print("X");
		}
	}
	cga.clear();
	for (int k = 0; k <= 10000000; k++) {

	}
	cga.scroll();
	for (int k = 0; k <= 10000000; k++) {

	}
	cga.scroll();
	for (int k = 0; k <= 10000000; k++) {

	}
	cga.scroll();
	for (int k = 0; k <= 10000000; k++) {

	}

	for (int c = 0; c <= 1; c++) {
		for (int b = 0; b < 7; b++) {
			for (int a = 0; a < 15; a++) {
				cga.setAttr(CgaAttr((CgaAttr::Color) (a), (CgaAttr::Color) (b), (CgaAttr::Color) (c)));
				out.print("A");
			}
		}
	}
	for (int i = 0; i < 10000000; i++) {

	}

	cga.clear();
	cga.setAttr(CgaAttr((CgaAttr::Color) CgaAttr::WHITE, (CgaAttr::Color) CgaAttr::LIGHT_GRAY, (CgaAttr::Color) false));
	cga.setCursor(0, 0);
	out.print("##############################################################");
	cga.setCursor(0, 1);
	out.print("### Test finished, please close the Bochs x86-64-Emulator! ###");
	cga.setCursor(0, 2);
	out.print("##############################################################");


	//cga.blueScreen("ERROR");
	//println/print cursor in der nächsten zeile mit offset+1 ungerade nicht gefixt

	while (1) {}

	return 0;
}