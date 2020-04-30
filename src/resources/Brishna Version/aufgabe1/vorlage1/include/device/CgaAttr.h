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
		foreground=0,
		background =4,
		blink=7
	};


public:
	/** 	Diese Aufz�hlung enth�lt die CGA-Farben als Farbkonstanten
	 *	Tragt hier *alle* CGA Farben mit den richtigen Werten ein
	 */
	enum Color {
		 BLACK = 0,
        BLUE = 1,
        BROWN = 6,
        CYAN = 3,
        GRAY = 8,
        GREEN = 2,
        LIGHT_BLUE = 9,
        LIGHT_CYAN = 11,
        LIGHT_GRAY = 7,
        LIGHT_GREEN = 10,
        LIGHT_MAGENTA = 13,
        LIGHT_RED = 12,
        MAGENTA = 5,
        RED = 4,
        WHITE = 15,
        YELLOW = 14
	};


	/** Konstruktor. Erzeugt ein CgaAttr-Objekt mit den uebergebenen Werten f�r
	  * Vorder- und Hintergrundfarbe. Werden keine Parameter uebergeben,
	  * so werden die Defaultwerte (Vordergrund weiss, Hintergrund schwarz, Blinken deaktiviert)
	  * verwendet.
	  */
	CgaAttr(Color fg=WHITE, Color bg=BLACK, bool blink=false)
	{
		setBackground(bg);
        setForeground(fg);
        setBlinkState(blink);
	}

	// setzen der Schriftfarbe
	void setForeground(Color col)
	{
		this->foreground=col;
	}

	// setzen der Hintergrundfarbe
	void setBackground(Color col)
	{
		this->background=col;
	}

	// setzen blinkender/nicht blinkender Text
	void setBlinkState(bool blink)
	{
		this->blink= blink;
	}

	// setzen aller Attribute
	void setAttr(CgaAttr attr)
	{
		this->foreground=attr.foreground;
		this->background=attr.background;
		this->blink=attr.blink;
	}
	

	// ermitteln der Schriftfarbe
	Color getForeground()
	{
		return foreground;
	}

	// ermitteln der Hintergrundfarbe
	Color getBackground()
	{
		return background;
	}

	// ermitteln ob Blink-Flag gesetzt ist
	bool getBlinkState()
	{
		return blink;
	}

private:
Color foreground,background;
bool blink;


};

#endif
