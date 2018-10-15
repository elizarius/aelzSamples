#include <stdio.h>
#include <string.h>

/* strpbrk example, first occurence of "key"  in str_1  */

int main ()
{

 char str_1 [] = "%1 Failed to activate.\n Router ID = %2";
 char  key [] = "%";

// printf ("%s \n", str_1 );
 char *pch ;
 pch = strpbrk (str_1, key);
 pch++  ;
 pch++ ;
 int rawlen = strcspn (pch,"%\n");

 printf ("%.*s \n",rawlen, pch );

}
