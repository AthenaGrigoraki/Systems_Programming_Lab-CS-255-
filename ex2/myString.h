#include <stddef.h>
#include <stdio.h>
#include <assert.h>

/*
myString.h
@author Athena Grigoraki
HY-255 ask2

*/

/* Computes the length of the string str,but not including the terminating null character.
It is a checked runtime error for str to be NULL
 */
size_t ms_length(char str1[]);

/* Copies the string pointed to, by str1 to str2.
    This function returns a pointer to the resulting string str2
    It is a checked runtime error for str1 to be NULL
*/
char* ms_copy( char str1[], char str2[]);

/* Copies up to n characters from the string pointed
    to, by str1 to str2. In a case where the length of str1
    is less than that of n, the remainder of str2 will be
    padded with null bytes.
    This function returns a pointer to the resulting string str2
    It is a checked runtime error for str1 to be NULL
*/
char* ms_ncopy(char str1[], char str2[], size_t i);

/* Appends the string pointed to by str1 to the end of
    the string pointed to by str2.
    This function returns a pointer to the resulting string str2
    It is a checked runtime error for str2 to be NULL
*/
char* ms_concat(char str2[], char str1[]);

/* Appends the string pointed to by str1 to the end of the
    string pointed to by str2 up to n characters long.
    It is a checked runtime error for str2 and str1 to be NULL
*/
char* ms_nconcat(char str2[], char str1[], size_t n);

/* Compares the string pointed to, by str1 to the string pointed to by str2.
    Returns:
        -1 then str1 is less than str2.
        +1 then str2 is less than str1.
        0 then  str1 is equal to str2.
        It is a checked runtime error for str2 and str1 to be NULL
*/
int ms_compare(char str1[], char str2[]);

/* Compares at most the first n bytes of str1 and str2
    Returns:
        -1 then str1 is less than str2.
        +1 then str2 is less than str1.
        0 then  str1 is equal to str2.
        It is a checked runtime error for str2 and str1 to be NULL
*/
int ms_ncompare(char str1[], char str2[], size_t n);

/* Finds the first occurrence of the substring string
    haystack. The terminating '\0' characters are not compared
    This function returns the index to the first occurrence in haystack of
    any of the entire sequence of characters specified in needle, or a null
    pointer if the sequence is not present in haystack.
    It is a checked runtime error for str2 and str1 to be NULL
*/
char* ms_search(char str1[], char str2[]);

