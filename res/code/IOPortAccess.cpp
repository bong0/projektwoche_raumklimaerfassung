// IOPortAccess.cpp: Implementierung der Klasse IOPortAccess.
////

#include "IOPortAccess.h"
#define uchar unsigned char

////
// Konstruktion/Destruktion
////
IOPortAccess::IOPortAccess() {}

IOPortAccess::~IOPortAccess() {}

//Dummy-Methode; bei diesem Treiber nicht erforderlich
bool IOPortAccess::openDriver()
{return true;}

//Dummy-Methode; bei diesem Treiber nicht erforderlich
void IOPortAccess::closeDriver()
{}

//Einen 8-Bit Wert auf einen beliebigen Port schreiben
//Type-Cast wegen int-Typ der Klassenmethode
void IOPortAccess::writePort(int port, int value)
{
	DlPortWritePortUchar((ULONG)port, (UCHAR)value);
}

//Einen 8-Bit Wert von einem beliebigen Port lesen
//Type-Cast wegen int-Typ der Klassenmethode
int IOPortAccess::readPort(int port)
{
	return (int)DlPortReadPortUchar((ULONG)port);
}

void IOPortAccess::updateRegStates(){
	this->dataState = readPort(dataPort);
	this->statusState = readPort(statusPort);
	this->controlState = readPort(controlPort);
}

int IOPortAccess::getDataState(){
	return this->dataState;
}
int IOPortAccess::getStatusState(){
	return this->statusState;
}
int IOPortAccess::getControlState(){
	return this->controlState;
}
void IOPortAccess::setDataPort(int addr){
	this->dataPort = addr;
}
void IOPortAccess::setStatusPort(int addr){
	this->statusPort = addr;
}
void IOPortAccess::setControlPort(int addr){
	this->controlPort = addr;
}
int IOPortAccess::getDataPort(){
	return this->dataPort;
}
int IOPortAccess::getStatusPort(){
	return this->statusPort;
}
int IOPortAccess::getControlPort(){
	return this->controlPort;
}
void IOPortAccess::updateStatusState(){
	this->statusState = readPort(getStatusPort());
}