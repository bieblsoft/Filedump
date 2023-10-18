#include <fstream>
#include <iostream>
using namespace std;

void Ausgabe(ofstream& Protokoll, char* Buffer, int Bufferposition)
{
	// Buffer ist voll, ausgeben
	for (int i = 0; i < Bufferposition; i++)
	{
		if (Buffer[i] < 0)
			Buffer[i] += 127;
		if ((Buffer[i] < 16) &&
			(Buffer[i] >= 0))
		{
			cout.width(1);
			cout << '0';
			Protokoll << '0';
			cout.width(1);
			cout << hex << (int)Buffer[i];
			cout.width(1);
			Protokoll << hex << (int)Buffer[i];
			cout.width(1);
			cout << ' ';
			Protokoll << ' ';
		}
		else
		{
			cout.width(2);
			cout << hex << (int)Buffer[i];
			Protokoll << hex << (int)Buffer[i];
			cout.width(1);
			cout << ' ';
			Protokoll << ' ';
		}
	}

	for (int x = 0; x < (50 - (Bufferposition * 3)); x++)
	{
		cout << ' ';
		Protokoll << ' ';
	}

	for (int j = 0; j < Bufferposition; j++)
	{
		if ((Buffer[j] < 0x20) ||
			(Buffer[j] > 0xF0))
		{
			cout << '.';
			Protokoll << '.';
		}
		else
		{
			cout << Buffer[j];
			Protokoll << Buffer[j];
		}
	}
	cout << endl;
	Protokoll << endl;

}

int main(int argc, char* Argv[])
{
	char* Dateiname;
	const char* Protokolldatei = "Filedump.dmp";
	char Zeichen;
	unsigned int Counter = 0;
	unsigned int Bufferposition = 0;
	char Buffer[16];

	// Prüfung der Kommandozeilenargumente
	if (argc < 2 || argc > 2)
	{
		cout << "Falsche Anzahl an Kommandozeilenargumenten !" << endl;
		cout << "Usage: Filedump Dateiname Protokolldatei" << endl;
		return 1;
	}

	// Kommandozeilenargumente sind ok
	ofstream Protokoll(Protokolldatei);

	cout << "Programm Filedump" << endl;
	Protokoll << "Programm Filedump" << endl;

	// Dateiname zuweisen und anzeigen
	Dateiname = Argv[1];
	cout << "Ausgabe der Datei " << Dateiname << endl;
	cout << endl;
	cout << "Hexadezimale Anzeige                              Ascii           " << endl;
	cout << "01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16   0123456789ABCDEF" << endl;
	cout << "__________________________________________________________________" << endl;

	Protokoll << "Ausgabe der Datei " << Dateiname << endl;
	Protokoll << endl;
	Protokoll << "Hexadezimale Anzeige                              Ascii           " << endl;
	Protokoll << "01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16   0123456789ABCDEF" << endl;
	Protokoll << "__________________________________________________________________" << endl;

	// Öffnen der Eingabedatei

	ifstream Eingabe(Dateiname);

	if (!Eingabe.is_open())
	{
		cout << "Fehler beim Öffnen der Eingabedatei !" << endl;
		return 1;
	}

	cout.setf(ios::fixed);

	// Eingabedatei ist geöffnet
	// lesen bis zum bitteren Ende
	while (true)
	{
		// Lesen eines Zeichens aus der Datei
		Eingabe.read(&Zeichen, 1);
		// Dateiende erreicht ?
		if (Eingabe.eof()) break;
		// Zeichen erfolgreich gelesen
		// Erhöhen der Zähler
		Counter++;

		if (Bufferposition < 16)
		{
			// Es passt noch ein Zeichen in den Buffer
			Buffer[Bufferposition++] = Zeichen;
		}
		else
		{
			// Buffer ist voll, ausgeben
			Ausgabe(Protokoll, Buffer, Bufferposition);
			Bufferposition = 0;
			Buffer[Bufferposition++] = Zeichen;
		}
	} // end of while

	// Eventuell ist der Buffer noch zum Teil gefüllt
	Ausgabe(Protokoll, Buffer, Bufferposition);


	// Ende des Programmes 
	cout << "__________________________________________________________________" << endl;
	cout << endl;
	cout << "Auf Wiedersehen !" << endl;

	Protokoll << "__________________________________________________________________" << endl;
	Protokoll << endl;
	Protokoll << "Auf Wiedersehen !" << endl;

	// Schliessen der Datei
	Eingabe.close();
	Protokoll.close();
	return 0;
} // end of main