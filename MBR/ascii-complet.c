/* Nom du fichier: ascii.c
 * Auteur:
 * Révision: 1
 * Programme: Demander un nombre N et calcule la somme 1+2+3..+N
 * Compilation: gcc -o ascii acsii.c -Wall
 */

#include <stdio.h>
#include <stdlib.h>

char *char2bin(char c)
{
    static char buffer[9] = {'0', '0', '0', '0', '0', '0', '0', '0', '\0'};

    char *p = buffer + 8;
	int i;
    
	for (i = 0; i < 8; i++)
	{
        *--p = '0' + (c & 1);
        c >>= 1;
    }

    return buffer;
}

int main()
{
    unsigned char i;

	// Titre du tableau
	printf("caractère décimal  octal   hexa   binaire\n");
 
    i = 0;
    while (i < 127)
    {
        if (i > 31)
            printf("      '%c'     %3u   0%03o   0x%02x   %s\n", i, i, i, i, char2bin(i));
        else
            printf("              %3u   0%03o   0x%02x   %s\n", i, i, i, char2bin(i));
        ++i;
    }

    return EXIT_SUCCESS;
}
