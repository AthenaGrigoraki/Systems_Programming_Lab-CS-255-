#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include"symtable.h"

struct binding{ //zeugos desmeuseis
    char *key;
    void *value; //mporoun na deiksoun se dedomena opoiodipote tipoy
    struct binding *next;
};

struct symtable{ //symbol table, sillogi apo zeugi desmeusewn
    unsigned int size;
    struct binding *head;
};

/* Η συνάρτηση SymTable_new επιστρέφει ένα καινούργιο SymTable_T που είναι
 * άδειο (δεν περιέχει καθόλου binding). */
SymTable_T SymTable_new(void){
 SymTable_T new_symtable=malloc(sizeof(struct symtable));
 new_symtable->head=NULL;
 new_symtable->size=(unsigned)0;

 return new_symtable;
}

/* Η συνάρτηση SymTable_free ελευθερώνει όλη τη μνήμη που
 * χρησιμοποιείται από το oSymTable. Αν το oSymTable είναι NULL, τότε η
 * συνάρτηση δεν κάνει τίποτε. */

void SymTable_free(SymTable_T oSymTable){
    assert(oSymTable);
  struct binding *tmp,*tmp1;
  tmp=oSymTable->head;
  while(tmp!= NULL){
    tmp1=tmp->next;
    free(tmp->key);
    free(tmp);
    tmp=tmp1;
  }
  free(oSymTable);
}

/* Η συνάρτηση SymTable_getLength επιστρέφει τον αριθμό του size
 * στο oSymTable. Είναι ελεγχόμενο λάθος χρόνου εκτέλεσης του προγράμματος
 * (checked runtime error) το oSymTable να είναι NULL. */
unsigned int SymTable_getLength(SymTable_T oSymTable){
  assert(oSymTable);
  unsigned int i=oSymTable.size;

    return i;
}

/*  Η συνάρτηση SymTable_contains επιστρέφει 1 (TRUE) αν το oSymTable
 *  περιέχει ένα binding του οποίου το κλειδί είναι pcKey, και 0 (FALSE) διαφορετικά.
 *  Είναι ελεγχόμενο λάθος χρόνου εκτέλεσης (checked runtime error) αν το oSymTable
 *  ή το pcKey είναι NULL.*/
int SymTable_contains(SymTable_T oSymTable, const char *pcKey){
    assert(oSymTable);
    assert(pcKey);
   struct binding *tmp;
   tmp=oSymTable->head;
   while(tmp != NUll){
    if (tmp->key == pcKey){
        return 1;
    }else{
        tmp=tmp->next;
        }

   }
return 0;
}

/* Η συνάρτηση SymTable_put, αν δεν υπάρχει binding με κλειδί pcKey στο
 * oSymTable, προσθέτει ένα καινούργιο binding στο oSymTable που αποτελείται
 * από το κλειδί pcKey και την τιμή pvValue, και επιστρέφει 1
 * (TRUE). Διαφορετικά, η συνάρτηση δεν αλλάζει το oSymTable, και
 * επιστρέφει 0 (FALSE). Είναι ελεγχόμενο λάθος χρόνου εκτέλεσης
 * (checked runtime error) αν το oSymTable ή το pcKey είναι NULL. */
int SymTable_put(SymTable_T oSymTable, const char *pcKey,const void *pvValue){
   struct binding *tmp;
   assert(oSymTable);
   assert(pcKey);

   tmp=oSymTable->head;
    if (SymTable_contains(oSymTable,pcKey) == 1){
        return 0;
    }
   tmp=(struct binding*)malloc(sizeof(struct binding));
   tmp->key=malloc((strlen(pcKey)+1)*sizeof(char));

   strcpy(tmp->key,pcKey);
   tmp->value=(void *)pvValue;
   tmp->next=oSymTable->head;
    oSymTable->size++;

   return 1;

}

/*Η συναρτηση SymTable_remove , αν υπαρχει binding με pcKey στο oSymTable, αφαιρει το binding και επιστρεφει 1(TRUE).
Διαφορετικα,η συναρτηση δεν αλλαζει το oSymTable, και επιστρεφει 0(FAlSE).Είναι ελεγχομενο
λαθος χρονου εκτελεσης(checked runtime error) αν ο oSymTable η το pcKey ειναι NULL
 */
int SymTable_remove(SymTable_T oSymTable, const char *pcKey){

struct binding *tmp1, *tmp2;
if(SymTable_contains(oSymTable,pcKey) == 0){
    return 0;
}else{
oSymTable->size--;
tmp1=oSymTable->head;
tmp2=tmp1;
while(tmp1 != NULL){
    if(strcmp(tmp1->key,pcKey)){
      if(tmp1==tmp2){
        oSymTable->head=tmp1->next;
      }else{
      tmp2->next=tmp1->next;
      }
      free(tmp1->key);
      free(tmp1);
      return 1;

    }
    tmp2=tmp1;
    tmp1=tmp1->next;
}

}

}

/*
Η συναρτηση SymTable_get επιστρεφει την τιμη του binding στο oSymTable που εχει την τιμη pcKey, αλλιως NULL αν δεν υπαρχει
τετοιο binding. Είναι ελεγχομενο λαθος χρονου εκτελεσης(checked runtime error) αν ο oSymTable η το pcKey ειναι NULL
*/
void* SymTable_get(SymTable_T oSymTable, const char *pcKey){
    struct binding *temp;
	assert(pcKey && oSymTable);

	temp=oSymTable->head;
	while(temp!=NULL){
	  if(strcmp(pcKey,temp->key)==0){
	    return  temp->value;
	  }
	  temp = temp->next;
	}
	return NULL;
}

/* Η συνάρτηση SymTable_map εφαρμόζει τη συνάρτηση *pfApply σε κάθε
 * binding στο oSymTable, περνώντας το pvExtra ως επιπλέον παράμετρο. Είναι
 * ελεγχόμενο λάθος χρόνου εκτέλεσης (checked runtime error) αν το oSymTable
 * ή το pfApply είναι NULL */
void  SymTable_map(SymTable_T oSymTable,
                   void (*pfApply)(const char *pcKey, void *pvValue,
                                   void *pvExtra),
                   const void *pvExtra){
                    assert(oSymTable && pvExtra);
                  struct binding *tmp;
                  tmp=oSymTable->head;
                  while( tmp != NULL){
                      pfApply(tmp->key,tmp->value,pvExtra);
                      tmp=tmp->next;
                  }



            }

void print(const char *pcKey, void *pvValue, void *pvExtra){
   assert(pcKey);
   printf("%s %s \n", pcKey, (void*)pvValue);

}
