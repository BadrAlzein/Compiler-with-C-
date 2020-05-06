#include "device/CgaChannel.h"
#include "io/PrintStream.h"

/*
    constants for the waiting time 
    30000 = 3s
    50000 = 5s 
    100000 = 10 s
*/
#define OneSecound_WAIT 5000
#define SHORT_WAIT 30000
#define NORMAL_WAIT 50000
#define LONG_WAIT 100000

CgaChannel cga;        // unser CGA-Ausgabekanal
PrintStream out(cga);    // unseren PrintStream mit Ausgabekanal verknuepfen


/* this func will make the screen wait until a given Time in secounds*/
void wait(int time){
      for(int i = 0; i < time; i++)
    {
        out.print("\r\r\r\r\r\r");
    };

}


int main()
{
    
/****************** Converstions Test ******************/   

    out.println("Test der formatierten Ausgabe zur Basis:");

    for(int i = -30; i < 30; i++)
    {
        if (i % 6 == 0)
        {
            out.print("Dezimal: ");
            out.print(i);
            out.print(" ; Binaer: ");
            out.print(i, 2);
            out.print(" ; Hexadezimal: ");
            out.print(i, 16);
            out.println();
        }
    }
    
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

    out.println();        
    out.println("Es folgen alle Farbkombinationen:");
    for(int blink = 0; blink < 2; blink++)
    {
        for(int bg = 0; bg < 8; bg++)
        {
            for(int fg = 0; fg < 16; fg++)
            {
                cga.setAttr(CgaAttr((CgaAttr::Color) (fg), (CgaAttr::Color) (bg), (CgaAttr::Color) blink));
                out.print("X");
            }
        }
    }

    out.println("\n");
   
    //delay for 5s 
    wait(NORMAL_WAIT);
    
    //~ int i = 0;
	bool sharpBlink = false;	
	CgaAttr attr;

	cga.clear();
	cga.setAttr(CgaAttr((CgaAttr::Color) CgaAttr::WHITE, (CgaAttr::Color) CgaAttr::BLACK, (CgaAttr::Color) false));
	out.println();
	out.println("Hier Bildschirm sollten im unteren Bereich bunte Spalten erscheinen. Bei diesen sollten jeweils im Wechsel acht Spalten ohne und acht Spalten mit dem #-Zeichen versehen sein. Darueber hinaus sollten diese kaskadierend blinken. Das Bild muss mit einer schwarzen Spalte beginnen.");
	out.println();
	
	
	for (int k = 0; k < ((19 * 80) -1); k++) {
		
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
	}

	attr.setForeground(attr.WHITE);
	attr.setBackground(attr.BLACK);
	attr.setBlinkState(false);
	cga.setAttr(attr);
	
    //delay for 5s 
    wait(NORMAL_WAIT);

    cga.setAttr(CgaAttr());
    cga.clear();
    
    cga.setAttr(CgaAttr(CgaAttr::RED, CgaAttr::YELLOW, false));
    for(int i = 0; i < 19; i++)
    {
	    cga.setCursor(i, (i < 9)?i:(18-i));
        out.println("x");
		
        cga.setCursor(i+19, (i < 9)?i:(18-i));
        out.println("x");

        cga.setCursor(i+38, (i < 9)?i:(18-i));
        out.println("x");

        cga.setCursor(i+57, (i < 9)?i:(18-i));
        out.println("x");
    }
    cga.setCursor(0,11);
    cga.setAttr(CgaAttr());

    out.println("Test der Sonderzeicheninterpretation:");
    out.println("Hier stehen jetzt fuenf Worte\nund auf der naechsten Zeile geht es weiter.\nHier wird gleich \"Hier\" ueberschrieben");


    //delay for 5s 
    wait(NORMAL_WAIT);
    
    out.print("\r ");
	
	int row, column;
	cga.getCursor(column, row);
	cga.setCursor(column,row - 1);
    cga.setAttr(CgaAttr(CgaAttr::GREEN, CgaAttr::BLUE, false));
    
    out.println("\rDort\n");
    
    out.println("Das ist ein Testsatz, der laenger als 80 Zeichen sein soll. Mal sehen, ob der Zeilenumbruch klappt. Haha Haha Haha Haha Haha Haha Haha Haha.\n");
    
     //delay for 5s 
    wait(NORMAL_WAIT);
     cga.clear();
     
     /******************Blue-Screen Test ******************/   

    cga.blueScreen("Error 101:\n This is a Test of the blue Screen from the cga.\n powerd by Team 14. \n ");

    //delay for 5s 
    wait(NORMAL_WAIT);
     cga.clear();
   /******************Scrolling Test ******************/ 
    cga.setAttr(CgaAttr());
    out.println(" Scrolling Test will start in:: \n");
      out.println(" 5 \n");
    wait(OneSecound_WAIT);
      out.println(" 4 \n");
    wait(OneSecound_WAIT);
      out.println(" 3 \n");
    wait(OneSecound_WAIT);
    out.println(" 2 \n");
      wait(OneSecound_WAIT);
    out.println(" 1 \n");
    //delay for 5s 
    wait(OneSecound_WAIT);
    
    for (int i = 0; i < 120; i++)
    {
        if (i%2==0){
             cga.setAttr(CgaAttr(CgaAttr::WHITE, CgaAttr::BLACK, false));
        }
        else if (i%3==0){
             cga.setAttr(CgaAttr(CgaAttr::RED, CgaAttr::BLACK, false));
        }
        else{
             cga.setAttr(CgaAttr(CgaAttr::BLUE, CgaAttr::BLACK, false));
        }
        out.print("this line will test Scrolling. so now the Scrolling will is be tested. Team 14 \n");
        out.println("\n");
    };
    //delay for 5s 
    wait(SHORT_WAIT); 

/******************Special character Test ******************/
    cga.clear();
    cga.setAttr(CgaAttr(CgaAttr::WHITE, CgaAttr::BLACK, false));
    out.println("Sonderzeichentest:\näöü;,:.-_");
    
     out.println("***************** Special character Test *****************");
    
    out.println();

    out.println("Ausgabe von Adressen...");
    out.println("Wie weit liegen sie auseinander? Warum?");
    int x = 5;
    int y = 6;
    out.print("x: ");
    out.print(&x);
    out.print("; y: ");
    out.print(&y);
	out.println("\n");
    //delay for 5s 
    wait(NORMAL_WAIT); 
/****************** Limit Test ******************/
    cga.clear();
    out.println("\n");
    out.println("***************** Limit Test *****************");
    out.println("\n");
     
    unsigned ux = 0;
    out.print("0x0: ");
    out.print(ux, 16);
    out.println();
    ux = 0xFFFFFFFF;
    out.print("0xFFFFFFFF: ");
    out.print(ux, 16);

    out.println("\n");
    out.println("***************** CGA Test Is Over *****************");
    out.println("\n");

    //delay for 5s 
    wait(NORMAL_WAIT); 
    
    //wait until the user close the window
   while(true){};
    return 0;
}
