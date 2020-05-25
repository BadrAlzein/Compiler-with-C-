#include "device/CgaChannel.h"
#include "io/PrintStream.h"

CgaChannel cga;        // unser CGA-Ausgabekanal
PrintStream out(cga);    // unseren PrintStream mit Ausgabekanal verknuepfen
CgaAttr attr;

void test1(); //numbers
void test2(); //alphabhet
void test3(); //bluescreen
void test4(); //keyboard keys
void test5(); //octopus in tutu


int main() {

    cga.setCursor(0, 0);

    //test1();
    //for(int i=0; i<100; i++){
    //    cga.clear();
    //}
    //test3();

    //test2();

    test4();


    //test5();

    while (1) {};

    return 0;

}

void test1() {
    out.println("Hello World");

    for (int i = 0; i < 1000; i++) {
        out.print("Dezimal ");
        out.print(i);
        out.print(" Binaer ");
        out.print(i, 2);
        out.print(" Hexadezimal ");
        out.print(i, 16);
        out.println();
    }

    out.println("done");
}

void test2() {
    attr.setForeground(CgaAttr::CYAN);
    attr.setBackground(CgaAttr::RED);
    attr.setBlinkState(0);
    cga.setAttr(attr);
    cga.setCursor(15, 20);
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 80; j++) {
            cga.show('A' + (j % 8));
        }
    }
    cga.clear();
}

void test3() {

    cga.blueScreen(ERROR_NULL_POINTER, "Das ging nicht schief!");
}

void test4() {
    attr.setForeground(CgaAttr::CYAN);
    attr.setBackground(CgaAttr::RED);
    attr.setBlinkState(1);
    cga.setAttr(attr);
    out.println("; & * ( ) % ^ ~ ` #");
    out.println("/ ? < > , ] |  +");
}

void test5() {

    attr.setBackground(CgaAttr::BLACK);
    attr.setForeground(CgaAttr::BLACK);
    attr.setBlinkState(0);
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            cga.setCursor(j, i);
            cga.setAttr(attr);
            cga.show(' ');
        }
    }
    attr.setBackground(CgaAttr::CYAN);
    attr.setForeground(CgaAttr::CYAN);
    for (int i = 8; i < 22; i++) {
        for (int j = 5; j < 18; j++) {
            cga.setCursor(i, j);
            cga.setAttr(attr);
            cga.show(' ');
        }
    }
    for (int i = 6; i < 8; i++) {
        for (int j = 6; j < 17; j++) {
            cga.setCursor(i, j);
            cga.setAttr(attr);
            cga.show(' ');
        }
    }
    cga.setCursor(7, 17);
    cga.setAttr(attr);
    cga.show(' ');
    for (int i = 7; i < 16; i++) {
        cga.setCursor(5, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 8; i < 15; i++) {
        cga.setCursor(4, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 9; i < 13; i++) {
        cga.setCursor(3, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 22; i < 24; i++) {
        for (int j = 6; j < 18; j++) {
            cga.setCursor(i, j);
            cga.setAttr(attr);
            cga.show(' ');
        }
    }
    for (int i = 6; i < 8; i++) {
        for (int j = 6; j < 17; j++) {
            cga.setCursor(i, j);
            cga.setAttr(attr);
            cga.show(' ');
        }
    }
    for (int i = 7; i < 17; i++) {
        cga.setCursor(24, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 10; i < 17; i++) {
        cga.setCursor(25, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    attr.setBackground(CgaAttr::LIGHT_GRAY);
    attr.setForeground(CgaAttr::LIGHT_GRAY);
    for (int i = 17; i < 19; i++) {
        for (int j = 15; j < 21; j++) {
            cga.setCursor(j, i);
            cga.setAttr(attr);
            cga.show(' ');
        }
    }
    for (int i = 15; i < 16; i++) {
        for (int j = 19; j < 21; j++) {
            cga.setCursor(j, i);
            cga.setAttr(attr);
            cga.show(' ');
        }
    }
    for (int i = 16; i < 17; i++) {
        for (int j = 17; j < 21; j++) {
            cga.setCursor(j, i);
            cga.setAttr(attr);
            cga.show(' ');
        }
    }
    for (int i = 12; i < 13; i++) {
        for (int j = 19; j < 21; j++) {
            cga.setCursor(j, i);
            cga.setAttr(attr);
            cga.show(' ');
        }
    }
    for (int i = 11; i < 12; i++) {
        for (int j = 17; j < 21; j++) {
            cga.setCursor(j, i);
            cga.setAttr(attr);
            cga.show(' ');
        }
    }
    for (int i = 9; i < 11; i++) {
        for (int j = 15; j < 21; j++) {
            cga.setCursor(j, i);
            cga.setAttr(attr);
            cga.show(' ');
        }
    }
    attr.setBackground(CgaAttr::BLUE);
    attr.setForeground(CgaAttr::BLUE);
    cga.setCursor(9, 6);
    cga.setAttr(attr);
    cga.show(' ');
    cga.setCursor(14, 7);
    cga.setAttr(attr);
    cga.show(' ');
    cga.setCursor(12, 6);
    cga.setAttr(attr);
    cga.show(' ');
    cga.setCursor(19, 5);
    cga.setAttr(attr);
    cga.show(' ');
    cga.setCursor(21, 7);
    cga.setAttr(attr);
    cga.show(' ');
    cga.setCursor(6, 10);
    cga.setAttr(attr);
    cga.show(' ');

    for (int i = 17; i < 19; i++) {
        for (int j = 19; j < 21; j++) {
            cga.setCursor(j, i);
            cga.setAttr(attr);
            cga.show(' ');
        }
    }
    for (int i = 10; i < 12; i++) {
        for (int j = 19; j < 21; j++) {
            cga.setCursor(j, i);
            cga.setAttr(attr);
            cga.show(' ');
        }
    }

    attr.setBackground(CgaAttr::RED);
    attr.setForeground(CgaAttr::RED);

    for (int i = 13; i < 18; i++) {
        cga.setCursor(41, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 12; i < 17; i++) {
        cga.setCursor(42, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 12; i < 17; i++) {
        cga.setCursor(43, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 13; i < 17; i++) {
        cga.setCursor(44, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 13; i < 18; i++) {
        cga.setCursor(45, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 14; i < 18; i++) {
        for (int j = 46; j < 49; j++) {
            cga.setCursor(j, i);
            cga.setAttr(attr);
            cga.show(' ');
        }
    }
    for (int i = 15; i < 18; i++) {
        for (int j = 49; j < 54; j++) {
            cga.setCursor(j, i);
            cga.setAttr(attr);
            cga.show(' ');
        }
    }
    for (int i = 15; i < 17; i++) {
        cga.setCursor(54, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 14; i < 17; i++) {
        cga.setCursor(55, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 14; i < 16; i++) {
        cga.setCursor(56, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 12; i < 13; i++) {
        cga.setCursor(56, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 12; i < 15; i++) {
        cga.setCursor(57, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 12; i < 14; i++) {
        cga.setCursor(58, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 2; i < 5; i++) {
        cga.setCursor(37, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 1; i < 5; i++) {
        cga.setCursor(36, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 0; i < 4; i++) {
        cga.setCursor(35, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 0; i < 2; i++) {
        cga.setCursor(34, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 0; i < 2; i++) {
        cga.setCursor(33, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 0; i < 2; i++) {
        cga.setCursor(32, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 1; i < 3; i++) {
        cga.setCursor(31, i);
        cga.setAttr(attr);
        cga.show(' ');
    }


    attr.setBackground(CgaAttr::CYAN);
    attr.setForeground(CgaAttr::CYAN);
    for (int i = 6; i < 11; i++) {
        for (int j = 33; j < 40; j++) {
            cga.setCursor(j, i);
            cga.setAttr(attr);
            cga.show(' ');
        }
    }
    for (int i = 6; i < 9; i++) {
        for (int j = 40; j < 42; j++) {
            cga.setCursor(j, i);
            cga.setAttr(attr);
            cga.show(' ');
        }
    }
    for (int i = 8; i < 11; i++) {
        cga.setCursor(43, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 9; i < 13; i++) {
        cga.setCursor(44, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 9; i < 13; i++) {
        cga.setCursor(45, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 9; i < 14; i++) {
        cga.setCursor(46, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 9; i < 14; i++) {
        cga.setCursor(47, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 11; i < 14; i++) {
        cga.setCursor(48, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 12; i < 16; i++) {
        cga.setCursor(49, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 18; i < 19; i++) {
        cga.setCursor(52, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 18; i < 20; i++) {
        cga.setCursor(53, i);
        cga.setAttr(attr);
        cga.show(' ');
    }

    for (int i = 17; i < 21; i++) {
        cga.setCursor(54, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 17; i < 21; i++) {
        cga.setCursor(55, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 18; i < 22; i++) {
        cga.setCursor(56, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 18; i < 23; i++) {
        cga.setCursor(57, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 20; i < 23; i++) {
        cga.setCursor(58, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 21; i < 23; i++) {
        cga.setCursor(59, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 23; i < 24; i++) {
        cga.setCursor(60, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 5; i < 12; i++) {
        for (int j = 23; j < 36; j++) {
            cga.setCursor(j, i);
            cga.setAttr(attr);
            cga.show(' ');
        }
    }
    for (int i = 5; i < 11; i++) {
        cga.setCursor(36, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 5; i < 10; i++) {
        cga.setCursor(37, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 4; i < 10; i++) {
        cga.setCursor(38, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 2; i < 8; i++) {
        cga.setCursor(39, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 2; i < 6; i++) {
        cga.setCursor(40, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 2; i < 4; i++) {
        cga.setCursor(41, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 2; i < 4; i++) {
        cga.setCursor(42, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 2; i < 4; i++) {
        cga.setCursor(43, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    cga.setCursor(44, 3);
    cga.setAttr(attr);
    cga.show(' ');
    cga.setCursor(45, 4);
    cga.setAttr(attr);
    cga.show(' ');

    for (int i = 14; i < 18; i++) {
        for (int j = 23; j < 28; j++) {
            cga.setCursor(j, i);
            cga.setAttr(attr);
            cga.show(' ');
        }
    }
    for (int i = 13; i < 19; i++) {
        for (int j = 27; j < 35; j++) {
            cga.setCursor(j, i);
            cga.setAttr(attr);
            cga.show(' ');
        }
    }
    for (int i = 14; i < 19; i++) {
        for (int j = 35; j < 39; j++) {
            cga.setCursor(j, i);
            cga.setAttr(attr);
            cga.show(' ');
        }
    }
    for (int i = 15; i < 19; i++) {
        for (int j = 39; j < 41; j++) {
            cga.setCursor(j, i);
            cga.setAttr(attr);
            cga.show(' ');
        }
    }
    for (int i = 20; i < 21; i++) {
        cga.setCursor(26, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 20; i < 22; i++) {
        cga.setCursor(27, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 20; i < 23; i++) {
        cga.setCursor(28, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 20; i < 24; i++) {
        for (int j = 29; j < 41; j++) {
            cga.setCursor(j, i);
            cga.setAttr(attr);
            cga.show(' ');
        }
    }
    for (int i = 21; i < 24; i++) {
        cga.setCursor(41, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 21; i < 24; i++) {
        cga.setCursor(42, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 22; i < 24; i++) {
        cga.setCursor(43, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 22; i < 24; i++) {
        cga.setCursor(44, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 23; i < 24; i++) {
        cga.setCursor(45, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    cga.setCursor(46, 23);
    cga.setAttr(attr);
    cga.show(' ');

    attr.setBackground(CgaAttr::MAGENTA);
    attr.setForeground(CgaAttr::MAGENTA);

    cga.setCursor(36, 3);
    cga.setAttr(attr);
    cga.show(' ');
    cga.setCursor(41, 14);
    cga.setAttr(attr);
    cga.show(' ');
    cga.setCursor(43, 13);
    cga.setAttr(attr);
    cga.show(' ');
    cga.setCursor(44, 15);
    cga.setAttr(attr);
    cga.show(' ');
    cga.setCursor(45, 16);
    cga.setAttr(attr);
    cga.show(' ');
    cga.setCursor(46, 13);
    cga.setAttr(attr);
    cga.show(' ');
    cga.setCursor(48, 15);
    cga.setAttr(attr);
    cga.show(' ');
    cga.setCursor(49, 18);
    cga.setAttr(attr);
    cga.show(' ');
    cga.setCursor(51, 14);
    cga.setAttr(attr);
    cga.show(' ');
    cga.setCursor(53, 16);
    cga.setAttr(attr);
    cga.show(' ');
    cga.setCursor(54, 15);
    cga.setAttr(attr);
    cga.show(' ');
    cga.setCursor(56, 16);
    cga.setAttr(attr);
    cga.show(' ');


    for (int i = 17; i < 20; i++) {
        cga.setCursor(25, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 4; i < 21; i++) {
        cga.setCursor(26, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 4; i < 22; i++) {
        cga.setCursor(27, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 3; i < 5; i++) {
        cga.setCursor(28, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 6; i < 21; i++) {
        cga.setCursor(28, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 5; i < 7; i++) {
        cga.setCursor(29, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 8; i < 16; i++) {
        cga.setCursor(29, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 17; i < 18; i++) {
        cga.setCursor(29, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 4; i < 6; i++) {
        cga.setCursor(30, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 7; i < 10; i++) {
        cga.setCursor(30, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 11; i < 13; i++) {
        cga.setCursor(30, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 14; i < 17; i++) {
        cga.setCursor(30, i);
        cga.setAttr(attr);
        cga.show(' ');
    }

    for (int i = 8; i < 11; i++) {
        cga.setCursor(31, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 12; i < 14; i++) {
        cga.setCursor(31, i);
        cga.setAttr(attr);
        cga.show(' ');
    }
    for (int i = 15; i < 17; i++) {
        cga.setCursor(31, i);
        cga.setAttr(attr);
        cga.show(' ');
    }


}
