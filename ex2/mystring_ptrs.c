/*Name : Athena Grigoraki
AM : csd4109
askisi : 2
mystring_ptrs.c
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
    assert(str1);
    char *p_array=str1; /*pointer sto string parametro*/

    int length=0; /*arxikopoihsh length gia na min petaei tixaies times*/
    while(*p_array != '\0'){
        length++;
        p_array++;

    }

	return length;

}

/* Copies the string pointed to, by str1 to str2.
    This function returns a pointer to the resulting string str2
    It is a checked runtime error for str1 to be NULL
*/
char* ms_copy( char str1[], char str2[]){
    assert(str1);
    char *src_str=str1; /*arxiko string*/
    char *dst_str=str2;  /*teliko antigrameno string*/

    while(*src_str != '\0'){
        *dst_str=*src_str;
        dst_str++;
        src_str++;
    }
    *dst_str='\0'; /*gia na min mpainoun skoupidia sto ipoloipo megethos */




    return *str2;

}


/* Copies up to n characters from the string pointed
    to, by str1 to str2. In a case where the length of str1
    is less than that of n, the remainder of str2 will be
    padded with null bytes.
    This function returns a pointer to the resulting string str2
    It is a checked runtime error for str1 to be NULL
*/
char* ms_ncopy(char str1[], char str2[], size_t i){
    assert(str1);
    char *src_str=str1; /*arxiko string*/
    char *dst_str=str2;  /*teliko antigrameno string*/
    size_t j=0;
    while(j<i){
        *dst_str=*src_str;
        dst_str++;
        src_str++;
        j++;
    }
    *dst_str='\0'; /*gia na min mpainoun skoupidia sto ipoloipo megethos */



    return *str2;

}

/* Appends the string pointed to by str1 to the end of
    the string pointed to by str2.
    This function returns a pointer to the resulting string str2
    It is a checked runtime error for str2 to be NULL
*/
char* ms_concat(char str2[], char str1[]){
    assert(str1);
    assert(str2);
    char *dst_str=str2; /*teliko string mazi me kai me ta 2*/
    char *src_str=str1;  /*string poy prosthetoyme sto telos toy dest*/
    while(*dst_str != '\0'){ /*pame sto telos tou str2*/
        dst_str++;
    }
    while(*src_str != '\0'){  /*prosthetoume to str1 sto telos toy str2*/
        *dst_str=*src_str;
        dst_str++;
        src_str++;
    }
    *dst_str='\0';

    return *str2;


}

/* Appends the string pointed to by str1 to the end of the
    string pointed to by str2 up to n characters long.
    It is a checked runtime error for str2 and str1 to be NULL
*/
char* ms_nconcat(char str2[], char str1[], size_t n){
    assert(str1);
    assert(str2);
    char *dst_str=str2; /*teliko string mazi me kai me ta 2*/
    char *src_str=str1;  /*string poy prosthetoyme sto telos toy dest*/
    size_t j=0;
    while(*dst_str != '\0'){ /*pame sto telos tou str2*/
        dst_str++;
    }
    while(j<n){  /*prosthetoume to str1 sto telos toy str2*/
        *dst_str=*src_str;
        dst_str++;
        src_str++;
        j++;
    }
    *dst_str='\0';

    return *str2;

}

/* Compares the string pointed to, by str1 to the string pointed to by str2.
    Returns:
        -1 then str1 is less than str2.
        +1 then str2 is less than str1.
        0 then  str1 is equal to str2.
        It is a checked runtime error for str2 and str1 to be NULL
*/
int ms_compare(char str1[], char str2[]){
    assert(str1);
    assert(str2);
    char *sec_str=str2;
    char *fir_str=str1;


    while(*fir_str != '\0' && *sec_str != '\0'){
        if (*fir_str !=  *sec_str){
            if(ms_length(fir_str)<ms_length(sec_str)){
                return -1;
            }else if(ms_length(sec_str)< ms_length(fir_str)){
                return 1;
            }
        }else{
        fir_str++;
        sec_str++;

        }
    }
    if (*fir_str == '\0' && *sec_str != '\0'){
        return -1;

    }
    if(*sec_str == '\0' && *fir_str != '\0'){
        return 1;
    }else{
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
    assert(str1);
    assert(str2);
    char *sec_str=str2;
    char *fir_str=str1;
    size_t i=0;

    while(i<n && *fir_str != '\0' && *sec_str != '\0'){
        if (*fir_str !=  *sec_str){
            if(ms_length(fir_str)<ms_length(sec_str)){
                return -1;
            }else if(ms_length(sec_str)< ms_length(fir_str)){
                return 1;
            }
        }else{
        fir_str++;
        sec_str++;
        i++;
        }
    }
    if (*fir_str == '\0' && *sec_str != '\0'){
        return -1;

    }
    if(*sec_str == '\0' && *fir_str != '\0'){
        return 1;
    }else{
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
int n=0;

assert(str1);
assert(str2);
char *string1=str1;
char *string2=str2;

while(*string1 != '\0' ){
    while(*string1 != '\0' && *string1 != *string2){ /*psaxnoume to str2 kapou mesa sto str1*/
        string1++;
        i++;

    }
        if (*string1 == '\0'){ /*teleiwse to str1 xwris na vroume to str2 mesa tou*/

            return -1;
        }
        location=i; /*apothikeyoume to pote vrethike to prwto stoixeio tou substring*/

    while(*string1 == *string2 && *string1 != '\0' && *string2 != '\0'){ /*tsekaroume an antistoixoun oloi oi chars*/
        string1++;
        string2++;
    }
if(*string2 == '\0'){ /*vrethike kai epistrefoume to index*/
    return location;
}
if (*string1 == '\0'){ /*den vrethike kai epistrefoume -1*/
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
