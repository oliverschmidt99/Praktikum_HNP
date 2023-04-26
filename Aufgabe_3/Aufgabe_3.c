
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 




/**
*   @brief  Ein String soll im "Memory Dumper" ausgegeben werden. Zudem soll
            die Adresse des dazugehörigen Sting angegeben werden.
*
*   @param kopie_string_1 Es wird die Kopie des String_1 übergeben und diese 
                        soll im Memory-Dumper ausgegeben werden.
*   @param länge_string_1 Es wird die Länge des String_[1] übergeben. Die Länge
                        des Strings begrenzt die Ausgabe des Memory-Dumpers, sodass
                        nur so viele Zeilen gedruckt werden, wie nötig.
*/
void memdump(unsigned char *kopie_string_1, int länge_string_1);
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
 * @param argv gibt ein Array der Argumente an. wenn <string> = "Hallo" beinhaltet bekommt argv "Hallo".
 * @return int der Rückgabewert return 0; ist dann, wenn das Programm kein Fehler hat. Wenn return 1;, dann Fehler.
 */
int main(int argc, char **argv){
    
    /**
     * @if (argc != 3)
     * Bei der Ausführung des Programms müssen drei Strings angegeben werden.
     * @else
     * Wenn weniger oder mehr Elemente angegeben werden, wird das Programm
     * mit einem Fehler beendet und ein Fehler wird ausgegeben.
     */
    if(argc != 3)
    {
        printf("\nUsage: %s <string 1> <string 2>\n\n", argv[0]);
        return -1;
    }
    else{

    
    /**
     * @param   kopie_string_1 bekommt aus den ersten String mittels strcpy eine Kopie.
     */
    char* kopie_string_1;
    /**
     * @param   adresse Wird zweimal beschrieben. Die erste Adresse wird von
     *                  kopie_string_1 und die zweite von der erst gefundenen
     *                  Element von findstring beschrieben.
     */
    char *adresse;
    /**
     * @param länge_string_1 hat die länge von dem ersten String.
     * 
     */
    int länge_string_1;
    /**
     * @param anzahl bekommt aus findstring die Anzahl von den gefundenen Elemente.
     * 
     */
    int anzahl;

   /**
    * @brief Bestimmt die Länge von dem ersten String und gibt die Länge + 1 zurück.
    *        Die Zeichenkette muss um 1 erhöht werden, wegen dem NULLByte.
    */
    länge_string_1 = strlen(argv[1])+1;

    /**
     * @brief Die Zeichenkette muss auf dem Heap gespeicht werden
     * 
     * @param länge_string_1 gibt die länge für den Speicher auf den Heap vor!
     * 
     * @return kopie
     */
    kopie_string_1 = malloc(länge_string_1);
    strcpy((char*)kopie_string_1, argv[1]);


    if(*argv[1] == 0)                     
    {
        printf("Usage: %s <empty> <string 2>\n\n", argv[0]);
        return -2;                        
    }
    else if(*argv[2]== 0)  {
        printf("Usage: %s <string 1> <empty>\n\n", argv[0]);
        return -3;                        
    }


    printf("Laenge der Zeichenkette (inkl. \\0): \x1B[32m%zu\x1B[0m Byte(s)\n", (size_t)länge_string_1);
    printf("Suchkriterium: '\x1B[35m%s\x1B[0m'\n\n", argv[2]);

    memdump((unsigned char*)kopie_string_1, länge_string_1);
    adresse = kopie_string_1;

    
        anzahl = findstring(argv[2], &adresse);
   
    

    printf("Die Suchzeichenkette '\x1B[35m%s\x1B[0m' wurde %d mal gefunden in: '\x1B[36m%s\x1B[0m'. (Zuerst an der Addresse: %p)\n", argv[2], anzahl, argv[1], adresse);
    free(kopie_string_1);
    }

printf("\n\n");
return 0;
}




//--------------------------------------------------------------------------
//-------------------------------------------------------------------memdump
//--------------------------------------------------------------------------




void memdump(unsigned char *kopie_string_1, int länge_string){

/**
 * @param i Das ist eine Laufvariable, die die Zeilen des memdumps zählt.
 * 
 */
int i = 0x0;
/**
 * @param k Zählt die Zeichen, die im memdump dargestellt werden sollen, sodass nur 16 Zeichen in eine Zeile kommen.
 * 
 */
int k = 0x0;

    printf("ADDR\t\t0123456789ABCDEF\n");

    /*Die Schleife zählt die Zeilen, bis die länge_string erreicht ist. Die Adresse
    wird um 0x10 aufaddiert, da sie nicht bei null anfangen darf.
    */
    for(i = 0x0; i < länge_string; i += 0x10){
        printf("%p\t", kopie_string_1);
        /*Die Schleife gibt jedes Zeichen des kopierten Strings in das Memdump aus.
         Nur Zeichen bis 0xF werden angezeigt, da nur 16 ASCII-Zeichen in einer Zeile passen.
        */
        for(k = 0x0; k <= 0xF; k++){

            if ((i + k)/0xF < länge_string) {
                
                if(*kopie_string_1 >= 0x20 && *kopie_string_1 <= 0x7e){
                    printf("%c", *kopie_string_1);
                }
                else{
                    printf("."); 
                }
            }
            kopie_string_1++;
        }  
        printf("\n");
    }
printf("\n");
return;
}





//--------------------------------------------------------------------------
//----------------------------------------------------------------findstring
//--------------------------------------------------------------------------






int findstring(char *sucher_string_2, char **pointer_adresse){

int zähler = 0;
char *fundort_adresse = strstr(*pointer_adresse, sucher_string_2);
*pointer_adresse = fundort_adresse;


    while(fundort_adresse){
        zähler ++;
        fundort_adresse += strlen(sucher_string_2);
        fundort_adresse = strstr(fundort_adresse, sucher_string_2);
    }

return zähler;
}
