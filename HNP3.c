 #include <stdio.h> //Benötigt für Ein/Ausgabe
#include <stdlib.h> //Benötigt für Zahlen etc
#include <string.h> 

//Prototypen
void memdump(unsigned char *string, int zeilen);
int memreplace(char *string, char cin_, char cout_, char **caddr);

int main(int argc, char *argv[]) {
												//Code nur ausführen wenn die richtige Anzahl an argumenten vorhanden ist
	if (argc == 5) {							
		char *adresse = NULL; 								//adresse des letzten ersetzten Zeichens
		int anzahlChar = 0; 								// Anzahl der ersetzten Zeichen
		int laengeChar = 0; 								// Länge der Zeichenkette


		memdump((unsigned char*)argv[0], atoi(argv[2])); 				// Alle Argumente ausgeben für anzahl der der angegebenen zeilen atoi wandelt eine zeichenkette in eine dezimale zahl um

		laengeChar = (strlen(argv[1]) + 1); 						// +1 wegen dem NullByte am Ende der Zeichenkette

		char *kopie = malloc(laengeChar); 						// Kopie auf dem Heap erzeugen
		strcpy(kopie, argv[1]); // kopie der zeichen

		printf("\nLaenge der Zeichenkette (inkl. \\0): %i Byte(s) \n", laengeChar);

		anzahlChar = memreplace(kopie, (char)*argv[3], (char)*argv[4], &adresse); 	//Aufruf der memreplace funktion und rückgabe der Anzahl der ersetzten Zeichen
			
		printf("Ersetzen '%c' mit '%c' \n", *argv[3], *argv[4]);
		printf("  Suchzeichen wurde %i mal gefunden und ersetzt\n", anzahlChar);
		printf("  zuletzt an Addr. %p \n \n", adresse);

		memdump((unsigned char*)kopie, atoi(argv[2])); 					// Ausgabe der Zeichenkopie

		free(kopie); 									//freigabe des Speichers auf dem Heap
	
	} else {
		printf("Falsche Anzahl an Argumenten \n");
	}
	return 0;

}



void memdump(unsigned char *string, int zeilen) {
	printf("ADDR");
	printf("\t\t ");
	printf("00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F 0123456789ABCDEF \n");

	//Benutzt für den Anfang an Adressen die durch 16 Teilbar sind.
	string = string - ((unsigned long)string % 16);

	for (int i = 0; i < zeilen; i++) {							//Wiederholung für anzahl der Zeilen

		printf("%p\t", string);									// Adresse am Anfang ausgeben

		for (int k = 0; k < 16; k++) {
																//Wiederholung für 16 Bytes

			printf(" %02x", string[k]); 						//Hex wert ausgeben

		}
		printf(" ");
		
		for(int k = 0; k < 16; k++){
													//Wiederholung für 16 Zeichen
													//prüfung ob es druckbare Zeichen sind
			if (((string[k] >= 0x20) && (string[k] <= 0x7E))) {
				printf("%c", string[k]);
			}
			else {
				printf("."); 
			}		
		}

		printf("\n");

													//Adresse um 16 erhöhen
		string += 16;

	}
}

int memreplace(char *string, char cin_, char cout_, char **caddr) {

	int anzahl = 0;

	

	for (int i = 0; string[i] != '\0' ; i++) {
													//Wenn das aktuelle Zeichen gleich dem zu ersetzenden Zeichen
		if (string[i] == cin_) {
			string[i] = cout_; 						//aktuelles Zeichen wird ersetzt
			*caddr = &string[i];					//adresse wird gespeichert in caddr
			anzahl++;								//Anzahl der ersetzen Zeichen
		}
	}

	return anzahl;

}
//Mittels malloc() reserviert man für die Laufzeit des Programms Speicherplatz.(RAM)
//Mittels free() wird der reservierte Speicher in diesem Falle von malloc() wieder freigegeben
//strncpy() Copy characters from string (function )
//Ein Heap, auf Deutsch auch Haldenspeicher gennant, ist eine Datenstruktur, die Daten sortiert und kompakt speichert und schnelles Einfügen und Löschen zulässt. Sie ist damit für das Sortieren von Daten und als Prioritätswarteschlange (priority queue) sehr gut geeignet ist.
