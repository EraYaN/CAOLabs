/*
 * Student:     G.M. Willemsen
 * Nummer:      436662
 * Opdracht:    4.8 - Woorden Tellen
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc,char *argv[])    /*Main function met arguments */
{
    char buf[1025],last='x';        /*Variables declareren en voorkomen dat last leeg is*/
    int i,l_arg,teller=0,l_buf;     /*Variables declareren*/

    if(argc<=1)                     /*Foutmelding als er geen arguments zijn meegegeven */
    {
        printf("%s\n","Geen programma argument meegegeven");
    }
    else
    {
        l_arg = strlen(argv[1]);    /*Woordlengte berekenen */
        while(1)
        {
            fgets(buf,1025,stdin);  /*Woorden inlezen*/
            l_buf = strlen(buf);    /*Woord lengte bereken */

            if(strncmp(buf,"#EOF",4)==0 && last=='\n'){
                break;              /*Als het woord #EOF op een nieuwe zin wordt gegeven de loop afbreken*/
            }
            last = buf[l_buf-1];    /*In de variabele last de laatste waarde van het woord geven*/

            for(i=0; i<=l_buf; i++)
            {
                if(strncmp(buf+i,argv[1],l_arg) == 0)
                    teller++;       /*Voor elk woord gelijk aan het argument de teller op laten lopen, ook overlappende woorden */
            }
        }
        printf("%d\n",teller);      /*Het aantal getelde woorden tonen */
    }
    return 0;
}




