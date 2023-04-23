#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/// @brief 
/// @param start 
/// @param size 
void memdump(unsigned char *start, int size) {
    int i, j;
    printf("ADDR            ");


    for (i = 0; i < 16; i++) {
        printf("%X", i);
    }
    printf("\n");


    for (i = 0; i < size; i += 16) {
        printf("%p  ", start+0x16);

        for (j = 0; j < 16; j++) {
            if (i + j < size) {
                printf("%c", isprint(start[i + j]) ? start[i + j] : '.');
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int findstring(char *search, char **start) {
    int count = 0;
    char *found = strstr(*start, search);
    while (found) {
        count++;
        printf("Found at address %p\n", found);
        found = strstr(found + 1, search);
    }
    return count;
}




int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: %s <string> <substring>\n", argv[0]);
        return 1;
    }
    char *str = strdup(argv[1]);
    int len = strlen(str);
    printf("Laenge der Zeichenkette (inkl. \\0): %d Byte(s)\n", len + 1);
    printf("Suchkriterium: '%s'\n\n", argv[2]);
    memdump((unsigned char*)str, len + 1);
    printf("\nThe search string was found %d time(s).\n", findstring(argv[2], &str));
    free(str);
    return 0;
}