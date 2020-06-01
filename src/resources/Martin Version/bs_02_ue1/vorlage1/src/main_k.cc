#include "device/CgaChannel.h"
#include "io/PrintStream.h"

CgaChannel cga;		// unser CGA-Ausgabekanal
PrintStream out(cga);	// unseren PrintStream mit Ausgabekanal verknuepfen

int main()
{	
	for (int i = 0; i < 100; i++) {
		out.print("Dezimal ");
		out.print(i);
		out.print(" Binaer ");
		out.print(i, 2);
		out.print(" Hexadezimal ");
		out.print(i, 16);
		out.println();
		for (int k = 0; k <= 100000; k++) {

            
            
		}
	}


	out.println("done");

	out.println();
	out.print("Test mit falscher Basis: out.print(133,7): ");
	out.print(133, 7);
	out.println();
	out.print("Test mit falscher Basis: out.print(133,1): ");
	out.print(133, 1);
	out.println();
	out.print("Test mit falscher Basis: out.print(133,0): ");
	out.print(133, 0);
	out.println();
	out.print("Test mit falscher Basis: out.print(133,-2): ");
	out.print(133, -2);
	out.println();
	out.print("Test mit falscher Basis: out.print(133,120): ");
	out.print(133, 120);
	out.println();

	for (int k = 0; k <= 10000000; k++) {

	}

	out.println();
	out.println("Es folgen alle Farbkombinationen:");

	cga.setCursor(0, 0);

	for (int blink = 0; blink < 2; blink++)
	{
		for (int bg = 0; bg < 8; bg++)
		{
			for (int fg = 0; fg < 16; fg++)
			{
				cga.setAttr(CgaAttr((CgaAttr::Color) (fg), (CgaAttr::Color) (bg), (CgaAttr::Color) blink));
				out.print("X");
			}
		}
	}

	for (int k = 0; k <= 10000; k++) {

	}

	out.println();
	//kurze Pause
	cga.setAttr(CgaAttr((CgaAttr::Color) CgaAttr::WHITE, (CgaAttr::Color) CgaAttr::BLACK, (CgaAttr::Color) false));



	bool sharpBlink = false;
	CgaAttr attr;

	cga.setAttr(CgaAttr((CgaAttr::Color) CgaAttr::WHITE, (CgaAttr::Color) CgaAttr::BLACK, (CgaAttr::Color) false));
	out.println();
	out.println("Hier Bildschirm sollten im unteren Bereich bunte Spalten erscheinen. Bei diesen sollten jeweils im Wechsel acht Spalten ohne und acht Spalten mit dem #-Zeichen versehen sein. Darueber hinaus sollten diese kaskadierend blinken. Das Bild muss mit einer schwarzen Spalte beginnen.");
	out.println();

	for (int k = 0; k < ((19 * 80) - 1); k++) {

		attr.setBlinkState(sharpBlink);
		sharpBlink = not sharpBlink;

		switch (k % 16) {
		case 0:
			attr.setForeground(attr.BLACK);
			attr.setBackground(attr.BLACK);
			break;
		case 1:
			attr.setForeground(attr.BLUE);
			attr.setBackground(attr.BLUE);
			break;
		case 2:
			attr.setForeground(attr.GREEN);
			attr.setBackground(attr.GREEN);
			break;
		case 3:
			attr.setForeground(attr.CYAN);
			attr.setBackground(attr.CYAN);
			break;
		case 4:
			attr.setForeground(attr.RED);
			attr.setBackground(attr.RED);
			break;
		case 5:
			attr.setForeground(attr.MAGENTA);
			attr.setBackground(attr.MAGENTA);
			break;
		case 6:
			attr.setForeground(attr.BROWN);
			attr.setBackground(attr.BROWN);
			break;
		case 7:
			attr.setForeground(attr.LIGHT_GRAY);
			attr.setBackground(attr.LIGHT_GRAY);
			break;
		case 8:
			attr.setForeground(attr.GRAY);
			attr.setBackground(attr.GRAY);
			break;
		case 9:
			attr.setForeground(attr.LIGHT_BLUE);
			attr.setBackground(attr.LIGHT_BLUE);
			break;
		case 10:
			attr.setForeground(attr.LIGHT_GREEN);
			attr.setBackground(attr.LIGHT_GREEN);
			break;
		case 11:
			attr.setForeground(attr.LIGHT_CYAN);
			attr.setBackground(attr.LIGHT_CYAN);
			break;
		case 12:
			attr.setForeground(attr.LIGHT_RED);
			attr.setBackground(attr.LIGHT_RED);
			break;
		case 13:
			attr.setForeground(attr.LIGHT_MAGENTA);
			attr.setBackground(attr.LIGHT_MAGENTA);
			break;
		case 14:
			attr.setForeground(attr.YELLOW);
			attr.setBackground(attr.YELLOW);
			break;
		case 15:
			attr.setForeground(attr.WHITE);
			attr.setBackground(attr.WHITE);
			break;
		}
		cga.setAttr(attr);
		out.print('#');
		for (int k = 0; k <= 100000; k++) {

		}
	}

	cga.setAttr(CgaAttr());
	

	while (1) {
	};

	return 0;
}
