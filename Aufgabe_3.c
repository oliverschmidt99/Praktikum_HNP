#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>

///@param gf = Gänsefüße!"
const char gf = '"';



/**
*   @brief Ein String soll im "Memory Dumper" ausgegeben werden. Zudem soll die Adresse des dazugehörigen Sting angegeben werden.
*
*   @param kopie_string Es wird die Kopie des String_1 übergeben und diese soll im Memory-Dumper ausgegeben werden.
*   @param länge_string Es wird die Länge des String_[1] übergeben. Die Länge des Strings begrenzt 
*                       die Ausgabe des Memory-Dumpers, sodass nur so viele Zeilen gedruckt werden, wie nötig.
*/
void memdump(char *kopie_string, int länge_string);
/**
 * @brief 
 * 
 * @param such_string 
 * @param start_addresse 
 * @return int 
 */
int findstring(char *such_adresse, char **pointer_adresse);



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

    if(argc != 3){
    printf("Usage: %s\n\n", argv[0]);
    return 1;
}
    else{


/*  Die Zeichenkette muss um 1 erhöht werden, wegen dem NULLByte. 
    Die Zeichenkette muss auf dem Heap gespeicht werden
        -In C ist strcpy eine Funktion, die eine Zeichenkette
        (String) von einem Speicherbereich in einen anderen kopiert.

*/
    
    char *kopie_string = strdup(argv[1]);
    int länge_string = strlen(kopie_string); 
    char *gefunden = strdup(argv[2]);

    printf("%s %c%s%c %c%s%c \n", argv[0], gf, argv[1], gf, gf, argv[2], gf);
    printf("Laenge der Zeichenkette (inkl. \\0): %zu Byte(s)\n", (size_t)länge_string+ 1);
    printf("Suchkriterium: '%s'\n\n", argv[2]);

    memdump((char*)kopie_string, länge_string + 1);
    int anzahl = findstring(argv[2], &kopie_string);

    printf("Die Suchzeichenkette wurde %d mal gefunden", anzahl);
    free(kopie_string);
    }

printf("\n\n");
return 0;
}




//--------------------------------------------------------------------------
//-------------------------------------------------------------------memdump
//--------------------------------------------------------------------------




void memdump(char *kopie_string, int länge_string){

int i = 0;
int k = 0;

    printf("ADDR\t\t");
    for(i = 0; i < 16; i++){
        printf("%X", i);
    }
    printf("\n\n");

    for(i = 0; i < länge_string; i += 16){
        printf("%p\t", kopie_string);
 
        for(k = 0; k < 16; k++){
            if ((i + k)/16 < länge_string) {
                if(kopie_string[i+k] < 0x20 && kopie_string[i+k] <= 0x7e){
                    printf(".");
                }
                else{
                    printf("%c", kopie_string[k+i]);
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






int findstring(char *such_string, char **pointer_adresse){

int zähler = 0;
char *gefunden = strstr(*pointer_adresse, such_string);

while(gefunden){
    zähler ++;
    printf("(Zuerst an der %p)\n", gefunden);
    gefunden = strstr(gefunden + 1, such_string);
}
return zähler;
}