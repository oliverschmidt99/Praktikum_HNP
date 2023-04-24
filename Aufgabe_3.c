
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 




/**
*   @brief  Ein String soll im "Memory Dumper" ausgegeben werden. Zudem soll
            die Adresse des dazugehörigen Sting angegeben werden.
*
*   @param kopie_string_1 Es wird die Kopie des String_1 übergeben und diese 
                        soll im Memory-Dumper ausgegeben werden.
*   @param länge_string Es wird die Länge des String_[1] übergeben. Die Länge
                        des Strings begrenzt die Ausgabe des Memory-Dumpers, sodass
                        nur so viele Zeilen gedruckt werden, wie nötig.
*/
void memdump(char *kopie_string_1_1, int länge_string);
/**
 * @brief Die Funktion findstring soll die gleiche Struktur wie im zweiten
 *        String finden, indem sie den ersten String durchsucht. Die gefundenen
 *        Elemente sollen gezählt werden. Die Adresse der ersten gefundenen Struktur
 *        soll ausgeben werden.
 * 
 * @param sucher_string_2 ist das Suchkriterium, um die Elemente im String_1 zu finden.
 * @param pointer_adressen zeigt auf die Anfangsadresse der Strings.
 * @return int zähler zählt die Summe der gefundenen Elemente im String_1.
 */
int findstring(char *sucher_string_2, char **pointer_adressen);



/**
 * @brief   In der Funktion Main werden die Strings der Eingabe selektiert, kopiert und übergeben an die Funktionen 
 *          memdumb und findstring. In Bytes wird die Größe des Strings ermittelt.  
 * 
 * @param argc gibt die Anzahl an Argumenten an. Bsp. ./Aufgabe_3 <string> <string> dann ist argc gleich 3.
 * @param argv gibt ein Arry der Argumente an. wenn <string> = "Hallo" beinhaltet bekommt argv "Hallo".
 * @return int der Rückgabewert return 0; ist dann, wenn das Programm kein Fehler hat. Wenn return 1;, dann Fehler.
 */
int main(int argc, char **argv){

printf("\n");

    
    /**
     * @if (argc != 3)
     * Bei der Ausführung des Programms müssen drei Strings angegeben werden.
     * @else
     * Wenn weniger oder mehr Elemente angegeben werden, wird das Programm
     * mit einem Fehler beendet und ein Fehler wird ausgegeben.
     */
    if(argc != 3)
    {
        printf("Usage: %s\n\n", argv[0]);
    return 1;
    }
    else{

    
    /**
     * @param   kopie_string_1 bekommt aus den ersten String mittels strcpy eine Kopie.
     */
    char *kopie_string_1;
    /**
     * @param   adresse Wird zweimal beschrieben. Die erste Adresse wird von
     *                  kopie_string_1 und die zweite von der erst gefundenen
     *                  Element von findstring beschrieben.
     */
    char *adresse;
    /**
     * @param länge_string hat die länge von dem ersten String.
     * 
     */
    int länge_string;
    /**
     * @param anzahl bekommt aus findstring die Anzahl von den gefundenen Elemente.
     * 
     */
    int anzahl;

   /**
    * @brief Bestimmt die Länge von dem ersten String und gibt die Länge + 1 zurück.
    *        Die Zeichenkette muss um 1 erhöht werden, wegen dem NULLByte.
    */
    länge_string = strlen(argv[1]) + 1;

    /**
     * @brief Die Zeichenkette muss auf dem Heap gespeicht werden
     * 
     * @param länge_string gibt die länge für den Speicher auf den Heap vor!
     * 
     * @return kopie
     */
    kopie_string_1 = malloc(länge_string);
    strcpy(kopie_string_1, argv[1]);


    if(*kopie_string_1 == 0)                     
    {
        printf("Speicher konnte nicht zugewiesen werden.\n\n");
        return 1;                        
    }



    printf("Laenge der Zeichenkette (inkl. \\0): %zu Byte(s)\n", (size_t)länge_string);
    printf("Suchkriterium: '%s'\n\n", argv[2]);

    memdump(kopie_string_1, länge_string);
    adresse = kopie_string_1;

    if(argv[2] == 0){
        anzahl = findstring(argv[2], &adresse);
    }
    else{
        anzahl = 0;
        adresse = 0;
    }


    printf("Die Suchzeichenkette wurde %d mal gefunden. (Zuerst an der Addresse: %p)\n", anzahl, adresse);
    free(kopie_string_1);
    }

printf("\n\n");
return 0;
}




//--------------------------------------------------------------------------
//-------------------------------------------------------------------memdump
//--------------------------------------------------------------------------




void memdump(char *kopie_string_1, int länge_string){

int i = 0;
int k = 0;

    printf("ADDR\t\t");
    for(i = 0; i < 16; i++){
        printf("%X", i);
    }
    printf("\n\n");

    for(i = 0; i < länge_string; i += 0xF){
        printf("%p\t", &kopie_string_1[i]);
 
        for(k = 0; k < 16; k++){
            if ((i + k)/16 < länge_string) {
                
                if(kopie_string_1[i+k] >= 0x20 && kopie_string_1[i+k] <= 0x7e){
                    printf("%c", kopie_string_1[k+i]);
                }
                else{
                    printf("."); 
                }
            }
        }  
        printf("\n");
    }
    printf("\n");
}





//--------------------------------------------------------------------------
//----------------------------------------------------------------findstring
//--------------------------------------------------------------------------






int findstring(char *sucher_string_2, char **pointer_adresse){

int zähler = 0;
char *gefunden = strstr(*pointer_adresse, sucher_string_2);
*pointer_adresse = gefunden;


    while(gefunden){
        zähler ++;
        gefunden = strstr(gefunden +  1, sucher_string_2);
    }

return zähler;
}
