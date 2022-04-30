#include <stdio.h>
#include <stdlib.h>
#include "symtable.h"



int main(int argc, char** argv){
    char result[20];
    int i;
   SymTable_T table = SymTable_new();
   SymTable_put(table,"foititis1","A");
   SymTable_put(table,"foititis2","B");
   SymTable_put(table,"foititis3","C");
   SymTable_put(table,"foititis4","D");
   SymTable_put(table,"foititis5","E");

   if(SymTable_contains(table, "foititis5")){
       printf("Input success\n");
   }
   else {
       printf("Input failed\n");
   }
    
printf("Length of list: %d \n", SymTable_getLength(table));


SymTable_remove(table, "foititis4");
if(SymTable_contains(table, "foititis4")){
       printf("Remove failed\n");
   }
   else {
       printf("Remove success\n");
   }

printf("Length of list: %d \n", SymTable_getLength(table));

printf("%s\n", (char*) SymTable_get(table, "foititis3"));

if (SymTable_get(table,"foititis3")){
    printf("Get function success\n");
}else{
    printf("Get function fail\n");
}

if (SymTable_get(table, "foititis4")){
    printf("Remove failed\n");
}
else{
    printf("Remove success\n");
}


for(i=0;i<20;i++){
        sprintf(result, "number %d", i);
        SymTable_put(table, result ,"value");
    }

if(SymTable_remove(table,"number 18")){
        printf("Removed number 18 element\n");
}
    else {
        printf("SymTable_remove failed\n");
    }

    if(!SymTable_get(table,"number 18"))
        printf("removed successfully element\n");
    else 
        printf("SymTable_remove failed\n");
    
    if(SymTable_get(table, "number 10"))
        printf("Got number 10: %s element\n",(char*)SymTable_get(table, "number 10"));
    else 
        printf("SymTable_get failed\n");

        SymTable_map(table,print,"");

    SymTable_free(table);

     return 0;

}





