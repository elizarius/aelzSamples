#include <stdio.h>
#include <string.h>

/* strpbrk example, first occurrence of "key" in str_1 */

int main(void)
{
    char str_1[] = "%1 Failed to activate.\n Router ID = %2";
    char key[] = "%";
    char *pch;
    int rawlen;

    pch = strpbrk(str_1, key);
    if (pch == NULL) {
        printf("Error: key not found in string\n");
        return 1;
    }

    pch += 2;
    rawlen = strcspn(pch, "%\n");

    printf("%.*s\n", rawlen, pch);

    return 0;
}
