#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<stdlib.h>
#include<stddef.h>
#include"symtable.h"

#define HASH_MULTIPLIER 33  /*it seems that historically 33 is the best multiplier value.*/
#define BUCKETS 509

struct binding {
    char *key;
    void *value;
    struct binding *next;
};

struct symtable {
    unsigned int size;
    struct binding *table[BUCKETS];
};

/* Return a
 code for pcKey. */
static unsigned int SymTable_hash(const char *str)
{
  unsigned int hashval;
        hashval = 0; /* we start our hash out at 0 */


        /* for each character, we multiply the old hash by 31 and add the current
     * character.  Remember that shifting a number left is equivalent to
     * multiplying it by 2 raised to the number of places shifted.  So we
     * are in effect multiplying hashval by 32 and then subtracting hashval.
     * Why do we do this?  Because shifting and subtraction are much more
     * efficient operations than multiplication.
     */
        for(; *str != '\0'; str++) hashval = *str + (hashval << 5) - hashval;

        /* we then return the hash value mod the hashtable size so that it will
     * fit into the necessary range
     */
        return hashval % 509;
}

/* Η συνάρτηση SymTable_new επιστρέφει ένα καινούργιο SymTable_T που είναι
 * άδειο (δεν περιέχει καθόλου bindings). */
SymTable_T   SymTable_new(void){
    size_t i;
  SymTable_T newSymtable=malloc(sizeof(struct symtable));
  struct binding *new=malloc(sizeof(struct binding));
  new->key=NULL;
  new->value=NULL;
  new->next=NULL;
  newSymtable->size=0U;
  for(i=0U; i!='\0'; i++){
      newSymtable->table[i]=new;
  }

 return newSymtable;
}

/* Η συνάρτηση SymTable_free ελευθερώνει όλη τη μνήμη που
 * χρησιμοποιείται από το oSymTable. Αν το oSymTable είναι NULL, τότε η
 * συνάρτηση δεν κάνει τίποτε. */
void SymTable_free(SymTable_T oSymTable){
  size_t i;
  assert(oSymTable);
  while(i <BUCKETS){
      if(oSymTable->table[i] != NULL){
          free(oSymTable->table[i]);
          oSymTable->table[i]=NULL;
      }
      i++;
  }
free(oSymTable);
}


/* Η συνάρτηση SymTable_getLength επιστρέφει τον αριθμό του size
 * στο oSymTable. Είναι ελεγχόμενο λάθος χρόνου εκτέλεσης του προγράμματος
 * (checked runtime error) το oSymTable να είναι NULL. */
unsigned int SymTable_getLength(SymTable_T oSymTable){
    assert(oSymTable);
    return oSymTable->size;

}

/*  Η συνάρτηση SymTable_contains επιστρέφει 1 (TRUE) αν το oSymTable
 *  περιέχει ένα binding του οποίου το κλειδί είναι pcKey, και 0 (FALSE) διαφορετικά.
 *  Είναι ελεγχόμενο λάθος χρόνου εκτέλεσης (checked runtime error) αν το oSymTable
 *  ή το pcKey είναι NULL.*/
int SymTable_contains(SymTable_T oSymTable, const char *pcKey){


    assert(oSymTable && pcKey);
    unsigned int i;
    i=SymTable_hash(pcKey);
    struct binding *tmp=oSymTable->table[i];
    while( tmp != NULL){
        if (tmp->key && strcmp(tmp->key,pcKey) == 0){
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

    struct binding *new;
    unsigned int i;
    assert(oSymTable && pcKey);
    if (SymTable_contains(oSymTable, pcKey) == 1) {
        return 0;
    }

    new = malloc(sizeof (struct binding));
    new->key = malloc((strlen(pcKey)) * sizeof (char));
    strcpy(new->key, pcKey);

    new->value = (void *) pvValue;
    i = SymTable_hash(pcKey);

    new->next = oSymTable->table[i];
    oSymTable->table[i] = new;
    oSymTable->size++;
    return 1;
}

/*Η συναρτηση SymTable_remove , αν υπαρχει binding με pcKey στο oSymTable, αφαιρει το binding και επιστρεφει 1(TRUE).
Διαφορετικα,η συναρτηση δεν αλλαζει το oSymTable, και επιστρεφει 0(FAlSE).Είναι ελεγχομενο
λαθος χρονου εκτελεσης(checked runtime error) αν ο oSymTable η το pcKey ειναι NULL
 */
int SymTable_remove(SymTable_T oSymTable, const char *pcKey){

    unsigned int i=SymTable_hash(pcKey);

    struct binding *temp;
    struct binding *temp2;
    assert(oSymTable);
    assert(pcKey);
    if (SymTable_contains(oSymTable, pcKey) == 0) {
        return 0;
    } else {
        oSymTable->size--;
        temp2 = oSymTable->table[i];
        temp = temp2;
        while (temp2 != NULL) {
            if (strcmp(temp2->key, pcKey) == 0) {
                if (temp2 == temp) {
                    oSymTable->table[i] = temp2->next;
                } else {
                    temp->next = temp2->next;
                }
                free(temp2->key);
                free(temp2);
                return 1;
            }
            temp = temp2;
            temp2 = temp2->next;
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
	unsigned int i=SymTable_hash(pcKey);
	temp=oSymTable->table[i];
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
                       unsigned int i;

                       for (i=0U; i<BUCKETS; i++){
                           tmp=oSymTable->table[i];

                           while(tmp != NULL){

                           pfApply(tmp->key,tmp->value,pvExtra);
                           tmp=tmp->next;
                           }

                         }

                   }

void print(const char *pcKey, void *pvValue,void *pvExtra){
   assert(pcKey);
   printf("%s %s \n", pcKey, (void*)pvValue);

}
