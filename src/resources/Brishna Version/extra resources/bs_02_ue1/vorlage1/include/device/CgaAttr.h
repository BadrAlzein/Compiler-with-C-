#ifndef CgaAttr_h
#define CgaAttr_h

/*
 * CgaAttr: 	Softwareprototyp fuer CGA Darstellungsattribute
 *		Hier braucht man Bitoperationen!
 *
 *		Da *alle* Operationen sehr einfach und kurz sind,
 *		duerft Ihr sie direkt in der Klasse
 *		als inline Methoden deklarieren.
 *		Inline Methoden Aufrufe ersetzen den Aufruf durch 
 * 		den Methoden Body 
 */

class CgaAttr {
private:
	enum AttrMaskAndShifts {
		// character und attr masken 
		// TODO Berechnung der Bitfolge fuer die Darstellung der Attribute
		// bits of CGA attributes from 0 up to 7
		// lieber hexadezimal
		FOREGROUND = 0b00001111,
		BACKGROUND = 0b01110000,
		BLINK = 0b10000000,
		// inverted mask is for selecting all the binarys which are not FG or BG or BLINK
		_FOREGROUND = 0b11110000,
		_BACKGROUND = 0b10001111,
		_BLINK = 0b01111111
		/*
		inverted masks
		_FOREGROUND = 0b11110000,
		_BACKGROUND = 0b10001111,
		_BLINK = 0b01111111

		FOREGROUND_BITS_SIZE = 4,
		BACKGROUND_BITS_SIZE = 3,
		BLINK_BITS_SIZE = 1
		*/
	};


public:
	/** 	Diese Aufzählung enthält die CGA-Farben als Farbkonstanten
	 *	Tragt hier *alle* CGA Farben mit den richtigen Werten ein
	 */
	enum Color {
		// automatically set values from 0 to 15
		// needs 3 bits
		BLACK = 0b000,
		BLUE = 0b001,
		GREEN = 0b010,
		CYAN = 0b011,
		RED = 0b100,
		MAGENTA = 0b101,
		BROWN = 0b110,
		LIGHT_GRAY = 0b111,
		// needs 4 bits
		GRAY = 0b1000,
		LIGHT_BLUE = 0b1001,
		LIGHT_GREEN = 0b1010,
		LIGHT_CYAN = 0b1011,
		LIGHT_RED = 0b1100,
		LIGHT_MAGENTA = 0b1101,
		YELLOW = 0b1110,
		WHITE = 0b1111
	};


	/** Konstruktor. Erzeugt ein CgaAttr-Objekt mit den uebergebenen Werten für
	  * Vorder- und Hintergrundfarbe. Werden keine Parameter uebergeben,
	  * so werden die Defaultwerte (Vordergrund weiss, Hintergrund schwarz, Blinken deaktiviert)
	  * verwendet.
	  */
	CgaAttr(Color fg=WHITE, Color bg=BLACK, bool blink=false)
	{
		// could be another solution when commented
		if (bg > 7) {
			bg = (Color) ((short) bg & BACKGROUND);
		}
		if (fg > 15) {
			fg = (Color) ((short) fg & FOREGROUND);
		}

		// 0b BLINK | BACKGGROUND | FOREGROUND
		setInitial(fg, bg, blink);
	}

	/*
	char getAttrByte()
	{
		// get the attribute byte
		// fg = WHITE or 15
		short fgValue = (short) this->getForeground();
		short bgValue = (short) this->getBackground();
		// TRUE IS 1 False is 0 
		bool blinkValue = this->getBlinkState();
		// short blinkValue = (short) blink;

		// wrong order
		// int bytes = (fgValue << AttrMaskAndShifts.FOREGROUND_BITS_SIZE) | bgValue;
		// bytes = (bytes << AttrMaskAndShifts.BACKGROUND_BITS_SIZE) | blinkValue;
		// returns 1 byte = 8 Bits like default 11110000
		char fgBytes = FOREGROUND & fgValue;
		char bgBytes = BACKGROUND & (bgValue << 4);
		char blinkBytes = BLINK & (blinkValue << 7);
		// sizeof(oneByte) = 1
		char oneByte = (fgBytes | bgBytes) | blinkBytes;
		this->oneByte = oneByte;
		return oneByte;
	}
	*/
	inline void setInitial(Color fg, Color bg, bool blink)
	{
		this->oneByte = ((blink << 7) | (bg << 4)) | (fg << 0);
	}

	inline void setOperation(Color col, short shift, AttrMaskAndShifts invertedMask)
	{
		this->oneByte = (col << shift) | (invertedMask & this->oneByte);
	}

	/*
	inline setOperationBlink(bool blink, short shift, AttrMaskAndShifts invertedMask)
	{
		this->oneByte = (blink << shift) | (invertedMask & this->oneByte);
	}
	*/

	inline Color getOperation(short shift, AttrMaskAndShifts mask) 
	{
		return (Color) ((this->oneByte & mask) >> shift);
	}

	// setzen der Schriftfarbe
	void setForeground(Color col)
	{
		// set the foreground attribute mask
		// _FOREGROUND & this->oneByte deletes every other BACKGROUND and BLINK Value
		// imagine this->oneByte = 0b10100101
		// _FOREGROUND = 0b11110000
		// oneByte & _FOREGROUND = 0b10100000 = temp
		// inverted mask is for selecting all the binarys which are not FOREGROUND
		
		// imagine col = 0b1101
		// 0b1101 << 0 = 0b1101
		// | (or) is for combine the passed Color and all the binarys which are not FOREGROUND
		// 0b1101 | 0b10100000 (temp) = 0b10101101
		setOperation(col, (short) 0, _FOREGROUND);
	}

	// setzen der Hintergrundfarbe
	void setBackground(Color col)
	{
		if (col > 7) {
			col = BLACK;
		}
		setOperation(col, (short) 4, _BACKGROUND);
	}

	// setzen blinkender/nicht blinkender Text
	void setBlinkState(bool blink)
	{
		setOperation((Color) blink, (short) 7, _BLINK);
	}

	// setzen aller Attribute
	void setAttr(CgaAttr attr)
	{
		setOperation(attr.getForeground(), (short) 0, _FOREGROUND);
		setOperation(attr.getBackground(), (short) 4, _BACKGROUND);
		setOperation((Color) attr.getBlinkState(), (short) 7, _BLINK);
	}

	// ermitteln der Schriftfarbe
	Color getForeground()
	{
		// FOREGROUND = 0b00001111
		// imagine this->oneByte = 0b11010111
		// oneByte & FOREGROUND = 0b00000111 => 0b0111
		return getOperation((short) 0, FOREGROUND);
	}

	// ermitteln der Hintergrundfarbe
	Color getBackground()
	{
		return getOperation((short) 4, BACKGROUND);
	}

	// ermitteln ob Blink-Flag gesetzt ist
	bool getBlinkState()
	{
		return (bool) getOperation((short) 7, BLINK);
	}

	char getByte() 
	{
		return this->oneByte;
	}

private:
	// the class member variables should only hold 1 byte so one char!!!!
	char oneByte;
};

#endif
