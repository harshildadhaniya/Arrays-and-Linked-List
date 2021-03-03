#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* Define Linked List node */

typedef struct intlist_t{
    int head;
    struct intlist_t* tail;
} intlist;

/* How to add a node */

intlist* cons(int h, intlist* t){
    intlist* res;
    res = malloc(sizeof(intlist));

    res->head = h;
    res->tail = t;

    return res;
}

/* Free a linked list */

void free_list(intlist* t){

    intlist* temp;
    while (t != NULL){
        temp = t;
        t = t->tail;
        free(temp);
    } 
}

/* Print a linked list */

void print_list(intlist* t){

    intlist* temp = t;
    printf("[ ");
    while (temp != NULL){
        printf("%d ", temp->head);
        temp = temp->tail;
    }
    printf("]\n");
}

/* Calculate the length of the list recursively */
int list_length(intlist* t){

    if(t == NULL){
        return 0;
    }
    else{
        return 1 + list_length(t->tail);
    }
    
}

/* This function creates a copy of the linked list */

intlist* list_copy(intlist* t){

    intlist* result = NULL;

    if (t == NULL){
        return result;
    }
    else{
        result = cons(t->head, list_copy(t->tail));
    }

    return result;
}

/* This function creates a copy of the linked list (Loop) */

intlist* list_copy_loop(intlist* t){

    intlist* temp = t;
    intlist* current;
    intlist* prev = NULL;
    intlist* start;

    if(t == NULL){
        return prev;
    }
    else{

        while(temp != NULL){
            /* Create a new node with value from the original and tail as null pointer */
            current = cons(temp->head, NULL);
            if (prev == NULL){
                /* If beginning of the list, set to start */
                start = current;
            }
            else{
                /* Else point the previous tail to the current node */ 
                prev-> tail = current;
            }
            /* Since we are moving to the next iteration, */ 
            /* now the previous is updated to the current. */
            prev = current;

            /* Move to the next head of the input. */
            temp = temp->tail;
        }
    }

    /* Return the head of the linked list, where it started from */
    return start;
}

/* Convert a list to an array */

int* list2array(intlist* t){

    int size = list_length(t);
    intlist* temp = t;
    int* a = malloc(size * sizeof(int));

    for (int i = 0; i < size; i++){
        a[i] = temp->head;
        temp = temp->tail;
    }

    return a;

}

/* Print an array */
void print_arr(int* a, int size){

    printf("{ ");

    for (int i = 0; i < size; i++){
        printf("%d ", a[i]);
    }

    printf("}\n");

}

/* Convert an array to list */

intlist* array2list(int* arr, int size){

    int* ARR = arr;
    intlist* current;
    intlist* prev = cons(ARR[0], NULL);

    intlist* start = prev;

    for(int i = 1; i < size; i++){

        intlist* current = cons(ARR[i], NULL);
        prev->tail = current;
        prev = current;
    }

    return start;

}


int main(){
    intlist* L1 = cons(5, cons(6, cons(9, cons(200, cons(30, NULL)))));

    print_list(L1);

    printf("\nNow we can create a copy of this list:\n");

    intlist* L1_copy1 = list_copy(L1);
    print_list(L1_copy1);

    intlist* L1_copy2 = list_copy_loop(L1);
    print_list(L1_copy2);

    printf("\nLet us check, if the copy that has been createtd is indeed a deep copy.\n");
    printf("Modify the elements within the two copies and compare with the original.\n");

    L1_copy1->head = 789;
    L1_copy2->tail->head = 789;

    printf("The modified copies:\n");
    print_list(L1_copy1);
    print_list(L1_copy2);

    printf("\nThe original list:\n");
    print_list(L1);

    int* A = list2array(L1);

    printf("\nNow the list can be converted to an array\n");
    print_arr(A, list_length(L1)); 

    printf("\nLet us now convert this array back to a list.\n");
    intlist* L2 = array2list(A, list_length(L1));
    print_list(L2);

    free_list(L1);
    free_list(L1_copy1);
    free_list(L1_copy2);
    
    return 0;
}