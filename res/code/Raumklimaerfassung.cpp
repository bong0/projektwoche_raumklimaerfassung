#include "IOPortAccess.h" //Klasse, zum Zugriff auf einen IO-Port
#include <iostream>	//Textausgabe
#include <ctime> // clock()
#include <Windows.h> // Sleep()
#include <math.h> // sqrt()

using namespace std;

//Einige Konstanten per define
//für die anzusprechenden Ports
#define	DATA	0x378 // Adresse des Datenegisters der parallelen Schnittstelle
#define	STATUS	DATA+1 // Status-Register
#define	CONTROL	STATUS+1 // Control-Register
#define MESSUNGEN 2 // maximale Anzahl der Messungen vor Mittlung
#define VERSCHIEBUNG 7 // Kompensation der Bauteilungenauigkeiten

#define uchar unsigned char

int main() {
	double avg=0, oldavg=0; // speichert den alten und neuen Mittelwert
	IOPortAccess port; // erzeugt ein Objekt der Klasse IOPortAccess
	clock_t start, end; // speichert Start- und Endzeit der Messung
	double temp=0; // speichert die Temperatur in Grad Celsius
	double	// Parameter für die Annäherungsfkt. der Kennlinie des KTY_81-121; ermittelt mit gnuplot
		a=0.018771, // Parameter a 
		b=6.96983, // Parameter b
		c=822.037; // Verschiebung auf y-Achse
	//setze die zu verwendeten Adressen der IO-Ports im port Objekt
        port.setDataPort(DATA); 
	port.setStatusPort(STATUS);
	port.setControlPort(CONTROL);

        //beschreibe alle Ports mit Daten um einen definierten Ausgangszustand zu erreichen
	port.writePort(port.getDataPort(), 0xff); //alle Pins auf high, da Trigger an Pin 2 liegt, Rest irrelevant 
	port.writePort(port.getStatusPort(), 0x80); // 00000001  # Busy (7) ist invertiert; setze alle auf Low
	port.writePort(port.getControlPort(), 0xD0); // 11010000 # Pin 1,3 sind invertiert; setze alle auf Low

	port.updateRegStates();
	while(getchar()!='q') { // wartet auf Tastendruck, bei q wird das Programm beendet
		int i=MESSUNGEN;  // Zählvariable
		oldavg=avg; // letzte Messung speichern
		avg=0; // Mittelwert rücksetzen
	
		while(i>0){ // läuft bis 1
			Sleep(800); // experimentell bestimmt: Pause zum entladen von C1
			port.writePort(port.getDataPort(), port.getDataState()&(~0x01)); // start trigger
			while( !((port.readPort(port.getStatusPort())&0x40)>>6) ); // warte bis output=1 (high)
			port.updateRegStates();
			port.writePort(port.getDataPort(), port.getDataState()|(0x01)); // stop trigger

			start = clock(); // speichere Start der Messung
			while( (port.readPort(port.getStatusPort())&0x40)>>6 ); // warte bis output=0 -> Messung beendet
			end = clock(); // ende der Messung

				cout<< "Diff " << ((double)(end-start)/CLOCKS_PER_SEC) << endl; // Zeigt Zeitdifferenz der Messung an
				avg+=((double)(end-start)/CLOCKS_PER_SEC); // addiere Messwert 
				i--; // iteriere
		}
		cout<<"Mittelwert:\t"<<avg/MESSUNGEN<<endl;
		temp = (( -(b/(2.0)) + sqrt( (b*b)/4 + ( (avg/MESSUNGEN)/( 1.03e-3*log(3.0) ) -c )*a ) )/a) - VERSCHIEBUNG;  // Formel f. Zuordnung Zeit-Temperatur
		std::cout.precision (3);  // setze auf eine Nachkommastelle
		cout<<"Temp:\t"<< temp << (uchar)248 <<"C"<<endl;  // gebe Temperatur in °C aus
		cout<<"Alter Mittelwert:\t"<< oldavg/MESSUNGEN <<endl; // gebe letztes Mittel als Vergleichswert aus
	}
	port.closeDriver();
	return 0;
}
