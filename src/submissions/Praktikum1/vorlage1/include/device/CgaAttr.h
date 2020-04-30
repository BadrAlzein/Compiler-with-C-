#ifndef CgaAttr_h
#define CgaAttr_h

/*
 * CgaAttr: 	Softwareprototyp fuer CGA Darstellungsattribute
 *		Hier braucht man Bitoperationen!
 *
 *		Da *alle* Operationen sehr einfach und kurz sind,
 *		duerft Ihr sie direkt in der Klasse
 *		als inline Methoden deklarieren.
 */

class CgaAttr {
private:
	enum AttrMaskAndShifts {

		//die drei attr sind true also FOREGROUND | BACKGROUND | BLINK = 0b 1 111 1111
		//used to get only one color from the attribut
		FOREGROUND = 0b00001111,
		BACKGROUND = 0b01110000,
		BLINK = 0b10000000,

		// das Komplemet von jedem Attr, um der Attribut mit setter ändern zu können 
		// ex. (FOREGROUND_mask & charachter) will make the fg in charachter 0 :: 0b B XXX 0000
		FOREGROUND_mask = 0b11110000,
		BACKGROUND_mask = 0b10001111,
		BLINK_mask = 0b01111111
	};


public:
	/** 	Diese Aufz�hlung enth�lt die CGA-Farben als Farbkonstanten
	 *	Tragt hier *alle* CGA Farben mit den richtigen Werten ein
	 */
	enum Color {
		BLACK = 0b000,
		BLUE = 0b001,
		GREEN = 0b010,
		CYAN = 0b011,
		RED = 0b100,
		MAGENTA = 0b101,
		BROWN = 0b110,
		LIGHT_GRAY = 0b111,
		/*
		cga secound level of colors (Erweitung) with more color Intensity  
		after adding one bit more to every color
		*/
		GRAY = 0b1000,
		LIGHT_BLUE = 0b1001,
		LIGHT_GREEN = 0b1010,
		LIGHT_CYAN = 0b1011,
		LIGHT_RED = 0b1100,
		LIGHT_MAGENTA = 0b1101,
		YELLOW = 0b1110,
		WHITE = 0b1111
	};


	/** Konstruktor. Erzeugt ein CgaAttr-Objekt mit den uebergebenen Werten f�r
	  * Vorder- und Hintergrundfarbe. Werden keine Parameter uebergeben,
	  * so werden die Defaultwerte (Vordergrund weiss, Hintergrund schwarz, Blinken deaktiviert)
	  * verwendet.
	  */
	 	//blink:: true is 1 false is 0 also 0b1... | 0b0...
	CgaAttr(Color fg=WHITE, Color bg=BLACK, bool blink=false) 
	{
		//calling setter
		setBackground(bg);
		setBlinkState(blink);
		setForeground(fg);
	}

	// setzen der Schriftfarbe
	void setForeground(Color col)
	{
		/*the format of any charachter is : 0b B XXX YYYY (B:=Blinker, X:=bg , Y:=fg)
		changing Y means: 
		1. mask the current charachter to change all Y's to 0000
		2. change old Y with new Y with the or | operation
		ps. Y is already in the right place and dont need shifting because the entered color value 
		should look like this: 0b 0 000 YYYY and the current character is 0b B XXX YYYY 
		so no shifting is needed.
		*/
		this->character = col | (FOREGROUND_mask & this->character);
	}

	// setzen der Hintergrundfarbe
	void setBackground(Color col)
	{
		/*the format of any charachter is : 0b B XXX YYYY (B:=Blinker, X:=bg , Y:=fg)
		changing X means: 
		1. mask the current charachter to change all X's to 000
		2. X is not in the right place and need shifting because the entered color value 
		should look like this: 0b 0 000 0XXX and the current character is 0b B XXX YYYY 
		so shifting is needed so shift (0b 0 000 0XXX) 4 places to the left --> 0b 0 XXX 0000.
		3. change old X with new X with the or | operation
		*/
		this->character = (col<<4) | (BACKGROUND_mask & this->character);
	}

	// setzen blinkender/nicht blinkender Text
	void setBlinkState(bool blink)
	{
		/*the format of any charachter is : 0b B XXX YYYY (B:=Blinker, X:=bg , Y:=fg)
		changing B means: 
		1. mask the current charachter to change the B to 0 in the current one
		2. Y is not in the right place and need shifting because the entered color value 
		should look like this: 0b 0 000 00b and the current character is 0b B XXX YYYY 
		so shifting is needed so shift (0b 0 000 00b) 7 places to the left --> 0b b 000 0000.
		3. change old b with new b with the or | operation
		*/
		this->character = (blink<<7) | (BLINK_mask & this->character);
	}

	// setzen aller Attribute
	void setAttr(CgaAttr attr)
	{
		setAttrHelper(attr.getForeground(),attr.getBackground(), (Color) attr.getBlinkState()); 
		//ps. casting blinker is needed cuz blinker is a bool 
	}
	/* take all three colors and update the current attribut */
	inline void setAttrHelper(Color fg, Color bg,Color blinker)
	{
			setBlinkState(fg);
			setBackground(bg);
			setBlinkState(blinker);
	}

	// ermitteln der Schriftfarbe
	Color getForeground()
	{
		/*the format of any charachter is : 0b B XXX YYYY (B:=Blinker, X:=bg , Y:=fg)
		returning Y means: 
		1. mask the current charachter -> change everything but Y's to 0 than means
		0b 0 000 YYYY
		2. caste it (from bits to color) and return it
		*/
			return (Color) (this->character & FOREGROUND);
	}

	// ermitteln der Hintergrundfarbe
	Color getBackground()
	{
		/*the format of any charachter is : 0b B XXX YYYY (B:=Blinker, X:=bg , Y:=fg)
		returning Y means: 
		1. mask the current charachter -> change everything but X's to 0 than means
		0b 0 XXX 0000
		2. the output should be 0b 0 000 0XXX (X's on the right side) that mean shifting to the right 
		is needed
		3. change 0b 0 XXX 0000 to 0b 0 000 0XXX by shifting 4 digits to the right
		4. caste it (from bits to color) and return it
		*/

			return (Color) ((this->character & BACKGROUND)>>4);
	}

	// ermitteln ob Blink-Flag gesetzt ist
	bool getBlinkState()
	{
			/*the format of any charachter is : 0b B XXX YYYY (B:=Blinker, X:=bg , Y:=fg)
		returning Y means: 
		1. mask the current charachter -> change everything but b to 0 than means
		0b b 000 0000
		2. the output should be 0b 0 000 000b (b on the right side) that mean shifting to the right 
		is needed
		3. change 0b b 000 0000 to 0b 0 000 000b by shifting 7 digits to the right
		4. caste it (from bits to bool) and return it
		*/
			return (bool) ((this->character & BLINK)>>7);
	}

	/*getter for the char attribut*/
	char getCharacter(){
		return this->character;
	}

private:
	char character;
};

#endif
