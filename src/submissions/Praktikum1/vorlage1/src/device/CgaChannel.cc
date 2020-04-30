#include "device/CgaScreen.h"
#include "device/CgaChannel.h"
#include "io/OutputChannel.h"
#include "device/CgaAttr.h"

/**
 * Diese Klasse wird die Methoden in CgaChannel.h defniieren bzw. implementieren::
 * CgaChannel()
 * CgaChannel(const CgaAttr& attr)
 * write(const char* data, int size)
 * blueScreen(const char* error)
 */

// Ausgabekanal mit Standardattributen
CgaChannel::CgaChannel()
{

}

// Ausgabekanal mit spezifischen Attributen
CgaChannel::CgaChannel(const CgaAttr& attr)
{

}

// Die von OutputChannel deklarierte Ausgaberoutine
int CgaChannel::write(const char* data, int size)
{

}

// Bluescreen mit standard Fehlermeldung
void CgaChannel::blueScreen(const char* error)
{


}
