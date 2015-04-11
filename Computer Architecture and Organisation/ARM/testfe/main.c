/*
 * Student  : Phu Nguyen
 * Nummer   : 4377273
 * Opdracht : 4.8
 */

#include <stdio.h>
#include <string.h>

/* Functie waarbij argumenten worden gebruikt dmv program arguments */

int main(int argc, char *argv[])
{
    /* Stelt de volgende variabelen op: Invoer heeft maximaal 1024 karakters + newline karakter
     *                                : inv is een pointer naar invoer (string), var is een pointer naar de program argument
     *                                : sum1 is de som van het aantal keren dat het woord voorkomt, N is de grote van de program argument (aantal letters)
     */

    char invoer[1026];
    char *inv = invoer;
    char *var = argv[1];
    int sum1 = 0, N = strlen(var);

    /* Wanneer argc geen 2 aangeeft zal de programma stoppen (er kan maar 1 argument worden ingevoerd) */

    if(argc != 2)
    {
        return 0;
    }

    /* While loop die zal doorlopen tot dat de invoer en #EOF aan elkaar gelijk zijn, dan volgt er een break
     * Als ze niet aan elkaar gelijk zijn zal de beide strings met elkaar vergeleken worden totdat het einde van de invoer wordt bereikt
     * Wanneer de invoer en argument aan elkaar gelijk zijn (dus ook met dezelfde lengte), zal sum1 met 1 verhogen
     * Hierna zal de invoer 1 plaats naar rechts opschuiven
     */

    while (fgets (inv, 1025, stdin) != NULL)
    {
        if (strcmp(inv, "#EOF\n") == 0)
        {
            break;
        }
        else
        {
            while(*inv != '\0')
            {
                if (strncmp(inv, var, N) == 0)
                {
                    sum1++;
                }
                inv ++;
            }
        }
    }

    /* Print de totale som van het aantal keren dat het argument en de invoer aan elkaar gelijk zijn
     */

    printf("%d\n", sum1);

    return 0;
}
