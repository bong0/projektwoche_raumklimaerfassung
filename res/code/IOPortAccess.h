// IOPortAccess.h: Schnittstelle für die Klasse IOPortAccess.
// Autor: <!\input{coder.txt}?>
// Last Edit: /*16.09.2009*/ 16.9.2011
// Editor: <!\input{editor.txt}?>
/////

#if !defined(_IOPORTACCESS_H_)
#define _IOPORTACCESS_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//Für bestimmte Windows-Datentypen wie z.B. UCHAR
#include <wtypes.h>

//Die Headerdatei dlportio.h und die
//Bibliotheksdatei dlportio.lib befinden
//sich im gleichen Verzeichnis, wie die
//Codedateien
#include "Dlportio.h"

#define uchar unsigned char
//Nur, wenn eine DLL erzeugt werden soll
//class __declspec(dllexport) IOPortAccess  
class IOPortAccess  
{
private:
	int dataState;
	int statusState;
	int controlState;
	int dataPort;
	int statusPort;
	int controlPort;
public:
	IOPortAccess();
	virtual ~IOPortAccess();
	bool openDriver();
	void closeDriver();
	void writePort(int port, int value);
	int readPort(int port);
	
	void updateRegStates();
	int getDataState();
	int getStatusState();
	int getControlState();
	void setDataPort(int addr);
	void setStatusPort(int addr);
	void setControlPort(int addr);
	int getDataPort();
	int getStatusPort();
	int getControlPort();
	void updateStatusState();
};

#endif // !defined(_IOPORTACCESS_H_)
