/********************************************************************************* 
* Diwa Ashwini Vittala, dashwini
* 2022 Spring CSE101 PA1 
* ListTest.c 
* A program to test List.c
**********************************************************************************/

#include "List.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // checking constructor of list
    List A = newList();
    List B = newList();
    List C = NULL;
  
    // checking append() and prepend()
    for (int i = 0; i <= 35; i += 1) {
        append(A, i);
        prepend(B, i);
    }
    printf("List A: ");
    printList(stdout, A);
    printf("\nList B:");
    printList(stdout, B);
    printf("\n");

    // checking moveFront(), index(), moveNext() and get()
    printf("- Printing List A using moveFront and moveNext: ");
    for (moveFront(A); index(A) >= 0; moveNext(A)) {
        printf("%d ", get(A));
    }
    printf("\n- Printing List B using moveBack and movePrev: ");
    for (moveBack(B); index(B) >= 0; movePrev(B)) {
        printf("%d ", get(B));
    }
    printf("\n");
  
    // checking copyList(), equals()
    C = copyList(A);
    printf("Is A == B? %s\n", equals(A, B) ? "true" : "false");
    printf("Is B == copy(A)? %s\n", equals(B, C) ? "true" : "false");
    printf("Is copy(A) == A? %s\n", equals(C, A) ? "true" : "false");
  
    // checking insertBefore(), insertAfter(), moveNext(), and movePrev()
    moveFront(A); // start cursor from the beginning
    for (int i = 0; i < 10; i += 1) {
        moveNext(A);            // at index 10
    }
    insertBefore(A, -1);        // cursor now at index 11
    printf("List A after inserting -1 before 10:\n...");
    printList(stdout, A);
    printf("\n");

    for (int i = 0; i < 9; i += 1) {
        moveNext(A);            // at index 20
    }
    insertAfter(A, -2);
    printf("List A after inserting -2 before 20:\n...");
    printList(stdout, A);
    printf("\n");

    for (int i = 0; i < 5; i += 1) {
        movePrev(A);            // at index 15
    }
    delete(A);
    printf("List A after deleting cursor before 15:\n...");
    printList(stdout, A);
    printf("\n");
    
    // testing clear
    printf("The length of A is %d\n", length(A));
    clear(A);
    printf("The length of A after clearing the list is %d\n", length(A));
  
    // free up list memory 
    freeList(&A);
    freeList(&B);
    freeList(&C);
  
    return 0;
}

