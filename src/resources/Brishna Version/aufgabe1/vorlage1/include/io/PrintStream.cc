#include "io/PrintStream.h"
#include "io/OutputChannel.h"
/*
 * PrintStream:	Diese Klasse ist aehnlich der Java-PrintStream Klasse
 *		Sie konvertiert u.A. numerische Werte in sichtbare Zeichen
 *		und gibt Sie auf dem im Konstruktor spezifizierten
 *		Ausgabekanal aus.
 *		Daraus ergeben sich 2 Teilaufgaben:
 *
 *		1. Die Feststellung der Ziffern einer Zahl
 *		2. Die Umwandlung der Ziffern in darstellbare Zeichen
 *
 *		Man beachte, dass diese Klasse unabhaengig
 *		von dem tatsaechlich verwendeten Ausgabekanal arbeitet.
 *
 *		Anmerkung: Diese Klasse werden wir spaeter noch in
 *		C++ konforme Ausgabe umwandeln.
 */
//constructor initailisinglist because of the explicit defined in Printstreem.h


 PrintStream::PrintStream(OutputChannel* Chan): channel(*chan){}
 PrintStream::PrintStream(OutputChannel& Chan): channel(&chan){}

// Ausgabe eines mit einem NULL-Byte terminierten Strings
	void print(const char* str){
        //channel.write(str); or
        // int i =0;
        //while (str[i] !='\0')
        //i++
        //return i;
        for (int i=0;str[i]!='\0';i++){}
        return i;
    }
    void print(char ch){
        channel.write(ch);
    }

// Ausgabe eines Strings mit anschliessendem Zeilenvorschub
	void println(const char* str){
        print(str);
		println();
    }

    // Zeilenvorschub
	void println(){
        channel.write('\n');
        //print('\n');
    }

	// numerische Werte werden zur Basis 'base' Ausgegeben
	// implementiere die Basen 2, 10 und 16
	//void print(int x, int base = DECIMAL);
    void print(int x, int base ){
          if(base==DECIMAL||base==BINARY||base==HEX){
		  if (x<0){
			  x*=(-1);
			  print("-1");
		  }
		  print(unsigned(x),base);
	  }else{
		  println("undefined basis");
	  }

	}
    void PrintStream:: print(unsigned x, int base ){
		char output[32];
		int num,i=0;
		if(base==DECIMAl){
			
			if (x>0){
				num=x%base;
				Output[i]=num;
				x=x/base;
				i++;
			}
			while(i>=0) {
			print(Table[output[i]]);// ascii table
			i--;

		}
	} else if(base==BINARY){
		print('0b');
		while(x>0){
			num=x%base;
			output[i]=num;
			x=x/base;
			i++;
}
	}		for ( i=0;i>=0;i--){
		print(Table[output[i]]);
		}
	}else if (base==HEX){
		print('0x');
		if (x>0){
			num=x%base;
			output[i]=num;
			x=x/base;
			i++;

		}
		if(i>0){
			i--;
			println(Table[output[i]]);
		}
	}else{
		println("undefined basis");
	}
	
	// Zeigertypen werden immer zur Basis 16 ausgegeben!
	void PrintStream::print(void* p){
		print((unsigned int)p,Hex);
	}
	private:
	OutputChannel& channel
};


