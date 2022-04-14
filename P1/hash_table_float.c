#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#define TABLE_SIZE 20

typedef struct {
    char *fl_number;
    float fl;
    struct Ride *next;
} Ride;

Ride *hash_table[TABLE_SIZE];

unsigned int hash(char *fl_number);
char *fts(float fl);
void init_hash_table();
void print_table();
bool hash_table_insert(Ride *p);
Ride *hash_table_lookup(char *fl_number);
Ride *hash_table_delete(char *fl_number);

int main() {
    init_hash_table();

    Ride first = {.fl = 1145.57};
    Ride second = {.fl = 1163.38};
    Ride third = {.fl = 844.3};
    Ride fourth = {.fl = 865.02};
    Ride five = {.fl = 1145.57};
    Ride six = {.fl = 456.32};
    Ride seven = {.fl = 1111.33};

    first.fl_number = fts(first.fl);
    second.fl_number = fts(second.fl);
    third.fl_number = fts(third.fl);
    fourth.fl_number = fts(fourth.fl);
    five.fl_number = fts(five.fl);
    six.fl_number = fts(six.fl);
    seven.fl_number = fts(seven.fl);

    hash_table_insert(&first);
    hash_table_insert(&second);
    hash_table_insert(&third);
    hash_table_insert(&fourth);
    hash_table_insert(&five);
    hash_table_insert(&six);
    hash_table_insert(&seven);
    print_table();

    Ride *tmp = hash_table_lookup("844.3");

    if(tmp == NULL){
        printf("Not found!\n");
    } else {
        printf("Found %s.\n", tmp->fl_number);
    }
}

char *fts(float fl){
    char *chain;
    chain = malloc(7*sizeof(char));
    if(chain == NULL) exit(-1);
    gcvt(fl, 7, chain);
    return chain;
}

unsigned int hash(char *fl_number){
    int lenght = strnlen(fl_number, 6);
    unsigned int hash_value = 0;
    for(int i = 0; i < lenght; i++){
        hash_value += fl_number[i];
        hash_value = (hash_value*fl_number[i])%TABLE_SIZE;
    }
    return hash_value;
}

void init_hash_table(){
    if(hash_table == NULL)
        exit(-1);
    for(int i = 0; i < TABLE_SIZE; i++){
        hash_table[i] = NULL;
    }
} // Initialize an empty hash table

void print_table(){
    for(int i = 0; i < TABLE_SIZE; i++){
        if(hash_table[i] == NULL){
            printf("\t%i\t---\n", i);
        } else {
            printf("\t%i\t", i);
            Ride *tmp = hash_table[i];
            while(tmp != NULL){
                printf("%s - ", tmp->fl_number);
                tmp = tmp->next;
            }
            printf("\n");
        }
    }
}

bool hash_table_insert(Ride *p){
    if(p == NULL) return false;
    int index = hash(p->fl_number);
    p->next = hash_table[index];
    hash_table[index] = p;
    return true;
}

//find a person in the table by their name
Ride *hash_table_lookup(char *fl_number){
    int index = hash(fl_number);
    Ride *temp = hash_table[index];
    while(temp != NULL && strncmp(temp->fl_number,fl_number,6) != 0){
        temp = temp->next;
    }
    return temp;
}

Ride *hash_table_delete(char *fl_number){
    int index = hash(fl_number);
    Ride *temp = hash_table[index];
    Ride *prev = NULL;
    while(temp != NULL && strncmp(temp->fl_number,fl_number,6) != 0){
        prev = temp;
        temp = temp->next;
    }
    if(temp == NULL) return NULL;
    if(prev == NULL) {
        //deleting the head
        hash_table[index] = temp->next;
    } else {
        prev->next = temp->next;
    }
    return temp;
}
