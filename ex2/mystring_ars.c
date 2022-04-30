/*Name : Athena Grigoraki
AM : csd4109
askisi : 2
mystring_ars.c
*/

#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include "myString.h"
#include <stdlib.h>

/* Computes the length of the string str,but not including the terminating null character.
It is a checked runtime error for str to be NULL
 */
size_t ms_length(char str1[]){
	size_t length= (size_t)0;
	assert(str1);
    int i;

    for (i=0; str1[i] != '\0'; i++){
    length++;
    }

	return length;
}

/* Copies the string pointed to, by str1 to str2.
    This function returns a pointer to the resulting string str2
    It is a checked runtime error for str1 to be NULL
*/
char* ms_copy( char str1[], char str2[]){

    assert(str1);
    int i=0;
    for (i=0; str1[i] != '\0'; i++){
        str2[i]=str1[i];
    }
    str2[i]='\0'; /*mpainei termatiko gia na min gemizei me skoupidia to array*/



return str2;
}

/* Copies up to n characters from the string pointed
    to, by str1 to str2. In a case where the length of str1
    is less than that of n, the remainder of str2 will be
    padded with null bytes.
    This function returns a pointer to the resulting string str2
    It is a checked runtime error for str1 to be NULL
*/
char* ms_ncopy(char str1[], char str2[], size_t i){
    size_t n;
    assert(str1);

    for (n=0; n<i; n++){
        str2[n]=str1[n];
    }
    str2[n]='\0';

    return str2;

}

/* Appends the string pointed to by str1 to the end of
    the string pointed to by str2.
    This function returns a pointer to the resulting string str2
    It is a checked runtime error for str2 to be NULL
*/
char* ms_concat(char str2[], char str1[]){
    int i=0;
    int j=0;
    assert(str2);
    while(str2[i] !='\0'){  /*vriskoyme to megethos tou dest str*/
        i++;
    }
    while(str1[j] != '\0'){  /* prosthetoume to src sto telos tou dst kai ayksanoyme megethos kai sta 2 array*/
        str2[i]=str1[j];
        j++;
        i++;
    }

str2[i]='\0';

return str2;
}

/* Appends the string pointed to by str1 to the end of the
    string pointed to by str2 up to n characters long.
    It is a checked runtime error for str2 and str1 to be NULL
*/
char* ms_nconcat(char str2[], char str1[], size_t n){
    int i=0;
    int j=0;
    assert(str2);
    assert(str1);
    while(str2[i] !='\0'){  /*vriskoyme to megethos tou dest str*/
        i++;
    }
    while(j<n){  /* prosthetoume to src sto telos tou dst kai ayksanoyme megethos kai sta 2 array mexri n char*/
        str2[i]=str1[j];
        j++;
        i++;
    }

str2[i]='\0';

return str2;
}

/* Compares the string pointed to, by str1 to the string pointed to by str2.
    Returns:
        -1 then str1 is less than str2.
        +1 then str2 is less than str1.
        0 then  str1 is equal to str2.
        It is a checked runtime error for str2 and str1 to be NULL
*/
int ms_compare(char str1[], char str2[]){
int i=0;
assert(str1);
assert(str2);

while(str1[i]!= '\0' && str2[i]!= '\0'){

    if (str1[i] != str2[i]){ /*an den einai idia stoixeia*/

            if (ms_length(str1)<ms_length(str2)){ /*an str1 mikrotero apo str2*/

                return -1;
            }
            else if(ms_length(str2)<ms_length(str1)){ /*an str2 mikrotero apo str1*/

                return 1;
            }

    }

    else{
        i++;
    }

}


if (str1[i] == '\0' && str2[i] != '\0'){
    return -1;
}
if (str2[i] == '\0' && str1[i] != '\0'){ /*ama idia stoixeia mexri ena simeio alla diaforetika megethi*/
    return 1;
}
else{ /*ama idio megethos kai idia stoixeia*/
    return 0;
}


}

/* Compares at most the first n bytes of str1 and str2
    Returns:
        -1 then str1 is less than str2.
        +1 then str2 is less than str1.
        0 then  str1 is equal to str2.
        It is a checked runtime error for str2 and str1 to be NULL
*/
int ms_ncompare(char str1[], char str2[], size_t n){
size_t i=0;
assert(str1);
assert(str2);
while(str1[i]!= '\0' && str2[i]!= '\0' && i<n){
    if (str1[i] != str2[i]){ /*an den einai idia stoixeia*/

            if (ms_length(str1)<ms_length(str2)){ /*an str1 mikrotero apo str2*/

                return -1;

            }
            else if(ms_length(str2)<ms_length(str1)){ /*an str2 mikrotero apo str1*/

                return 1;
            }

    }else{
        i++;
    }


}

if (str1[i] == '\0' && str2[i] != '\0'){

    return -1;
}
if (str2[i] == '\0' && str1[i] != '\0'){ /*ama idia stoixeia mexri ena simeio alla diaforetika megethi*/

    return 1;
}
else{ /*ama idio megethos kai idia stoixeia*/

    return 0;
}


}

/* Finds the first occurrence of the substring string
    haystack. The terminating '\0' characters are not compared
    This function returns the index to the first occurrence in haystack of
    any of the entire sequence of characters specified in needle, or a null
    pointer if the sequence is not present in haystack.
    It is a checked runtime error for str2 and str1 to be NULL
*/
char* ms_search(char str1[], char str2[]){
int i=0;
int j=0;
int location;
assert(str1);
assert(str2);
while(str1[i] != '\0' ){
    while(str1[i] != '\0' && str1[i] != str2[0]){ /*psaxnoume to str2 kapou mesa sto str1*/
        i++;
    }
        if (str1[i] == '\0'){ /*teleiwse to str1 xwris na vroume to str2 mesa tou*/

            return -1;
        }
        location=i; /*apothikeyoume to pote vrethike to prwto stoixeio tou substring*/

    while(str1[i] == str2[j] && str1[i] != '\0' && str2[j] != '\0'){ /*tsekaroume an antistoixoun oloi oi chars*/
        i++;
        j++;
    }
if(str2[j] == '\0'){ /*vrethike kai epistrefoume to index*/
    return location;
}
if (str1[i] == '\0'){ /*den vrethike kai epistrefoume -1*/
    return (-1);
}
i= location +1;
j=0;
    }


}

int main(){
char array[]="This is a string";
char array2[]="This is a";
int j;
int i=ms_length(array);
printf("length : %d\n",i);
char sec_array[]="string";
int a=ms_search(array,sec_array);
printf("substring location : %d\n",a);
char third_array[]="This is a string";
ms_copy(array,third_array);
ms_ncopy(array,third_array,4);
printf("%s\n", third_array);
ms_concat(array,third_array);
printf("%s\n",array);
ms_nconcat(array,third_array,2);
printf("%s\n", array);
j=ms_compare(array,array2);
printf("%d\n", j);
j=ms_ncompare(array,array2,5);
printf("%d\n", j);



return 0;
}

