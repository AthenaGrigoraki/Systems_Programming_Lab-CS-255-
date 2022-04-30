/*
Πρώτη άσκηση HY-255
Αθηνά Γρηγοράκη
AM:csd4109*/

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#define  M_KEFALAIO 204
#define  M_MIKRO  236
#define  N_KEFALAIO 205
#define  N_MIKRO 237

#define TONOS 39
#define DIALITIKA 34



void encoding(char map[255][3]){
int i,j;

	for (i=0; i<255; i++){
		for (j=0; j<3; j++){
           map[i][j]=0;
		}
	}  /*arxikopoiisi*/

    map[10][0] = 10; /*nl*/
	map[32][0] = 32; /*space*/
	map[168][0] = DIALITIKA; /*dialytika*/
    map[180][0] = TONOS; /*tonos*/
    map[181][0] = TONOS; /*dialytika me tono se tono*/
    map[181][1] = DIALITIKA; /*dialytika me tono se dialitika*/
    map[182][1] = 65; /*A me tono*/
    map[182][0] = TONOS; /*A me tono*/
    map[184][1] = 69; /*E me tono*/
    map[184][0] = TONOS; /*E me tono*/
    map[185][1] = 72; /*H me tono*/
    map[185][0] = TONOS; /*H me tono*/
    map[186][1] = 73; /*I me tono*/
    map[186][0] = TONOS; /*I me tono*/
    map[188][1] = 79; /*O me tono*/
    map[188][0] = TONOS; /*O me tono*/
    map[190][1] = 89; /*Y me tono*/
    map[190][0] = TONOS; /*Y me tono*/
    map[191][1] = 87; /*W me tono*/
    map[191][0] = TONOS; /*W me tono*/
    map[192][0] = 105; /*i me dialytika kai tono*/
    map[192][1] = TONOS; /*i me dialytika kai tono*/
    map[192][2] = DIALITIKA; /*i me dialytika kai tono*/
	map[193][0]=65;
	map[194][0] = 86; /*V*/
    map[195][0] = 71; /*G*/
    map[196][0] = 68; /*D*/
    map[197][0] = 69; /*E*/
    map[198][0] = 90; /*Z*/
    map[199][0] = 72; /*H*/
    map[200][0] = 56; /*8*/
    map[201][0] = 73; /*I*/
    map[202][0] = 75; /*K*/
    map[203][0] = 76; /*L*/
    map[204][0] = 77; /*M*/
    map[205][0] = 78; /*N*/
    map[206][0] = 75; /*KS*/
    map[206][1] = 83; /*KS*/
    map[207][0] = 79; /*O*/
    map[208][0] = 80; /*P*/
    map[209][0] = 82; /*R*/
    map[211][0] = 83; /*S*/
    map[212][0] = 84; /*T*/
    map[213][0] = 89; /*Y*/
    map[214][0] = 70; /*F*/
    map[215][0] = 88; /*X*/
    map[216][0] = 80; /*PS*/
    map[216][1] = 83; /*PS*/
    map[217][0] = 87; /*W*/

     map[218][0] = 73; /*I me dialytika*/
    map[218][1] = DIALITIKA; /*I me dialytika*/
    map[219][0] = 89; /*Y me dialytika*/
    map[219][1] = DIALITIKA; /*Y me dialytika*/
    map[220][0] = 97; /*a me tono*/
    map[220][1] = TONOS; /*a me tono*/
    map[221][0] = 101; /*e me tono*/
    map[221][1] = TONOS; /*e me tono*/
    map[222][0] = 104; /*h me tono*/
    map[222][1] = TONOS; /*h me tono*/
    map[223][0] = 105; /*i me tono*/
    map[223][1] = TONOS; /*i me tono*/
    map[224][0] = 121; /*y me dialytika kai tono*/
    map[224][1] = TONOS; /*y me dialytika kai tono*/
    map[224][2] = DIALITIKA; /*y me dialytika kai tono*/

    map[225][0]=97;   /*a*/
    map[226][0] = 118; /*v*/
    map[227][0] = 103; /*g*/
    map[228][0] = 100; /*d*/
    map[229][0] = 101; /*e*/
    map[230][0] = 122; /*f*/
    map[231][0] = 104; /*h*/
    map[232][0] = 56; /*8*/
    map[233][0] = 105; /*i*/
    map[234][0] = 107; /*k*/
    map[235][0] = 108; /*l*/
    map[236][0] = 109; /*m*/
    map[237][0] = 110; /*n*/
    map[238][0] = 107; /*ks*/
    map[238][1] = 115; /*ks*/
    map[239][0] = 111; /*o*/
    map[240][0] = 112; /*p*/
    map[241][0] = 114; /*r*/
    map[242][0] = 115; /*s teliko*/
    map[243][0] = 115; /*s*/
    map[244][0] = 116; /*t*/
    map[245][0] = 121; /*y*/
    map[246][0] = 102; /*f*/
    map[247][0] = 120; /*x*/
    map[248][0] = 112; /*ps*/
    map[248][1] = 115; /*ps*/
    map[249][0] = 119; /*w*/

    map[250][0] = 105; /*i me dialytika*/
    map[250][1] = DIALITIKA; /*i me dialytika*/
    map[251][0] = 121; /*y me dialytika*/
    map[251][1] = DIALITIKA; /*y me dialytika*/
    map[252][0] = 111; /*o me tono*/
    map[252][1] = TONOS; /*o me tono*/
    map[253][0] = 121; /*y me tono*/
    map[253][1] = TONOS; /*y me tono*/
    map[254][0] = 119; /*w me tono*/
    map[254][1] = TONOS; /*w me tono*/







	for (i=0; i<255; i++){
		if(map[i][0] == -1){
			map[i][0]=i;

		}
	}
}

void state_machine(char map[255][3],int c){

  int previous;
  switch(c){


case M_KEFALAIO :
     previous=c;
     c = getchar();
     if ( c== 208 || c == 240){  /*case MP or Mp*/
         putchar(66);
     }
     else{
        putchar(map[previous][0]);
        putchar(map[c][0]);
        putchar(map[c][1]);
        putchar(map[c][2]);
     }
    break;


case M_MIKRO:
    previous = c;
        c = getchar();
        if (c == 208 || c == 240) { /*case mP or mp*/
            putchar(98);
        }
        else{
        putchar(map[previous][0]);
        putchar(map[c][0]);
        putchar(map[c][1]);
        putchar(map[c][2]);
     }
	break;

case N_KEFALAIO :
        previous = c;
        c = getchar();
        if (c == 212 || c == 244) { /*case Nt or NT*/
            putchar(68);
        }
        else{
        putchar(map[previous][0]);
        putchar(map[c][0]);
        putchar(map[c][1]);
        putchar(map[c][2]);
     }
     break;


case N_MIKRO:
        previous = c;
        c = getchar();
        if (c == 212 || c == 244) { /*case nT or nt*/
            putchar(100);
        }
        else{
        putchar(map[previous][0]);
        putchar(map[c][0]);
        putchar(map[c][1]);
        putchar(map[c][2]);
     }

    break;

default:
    putchar(map[c][0]);

    putchar(map[c][1]);
    putchar(map[c][2]);
    break;
}

}



int  main(){
int c;
char map1[255][3];

	encoding(map1);

    while(( c = getchar()) != EOF ){


        state_machine(map1,c);
    }


	return 0;

}
