#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hospHeader.h"

extern int nodeCount, maxCap;

int main(){

    NODE *new_node;
    LL head = NULL;
    LL tail = NULL;
    char patName[30], med[25];
    int choice, patAge, dose, prio;
    while(choice != 3)
    {
        showMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        if(choice == 1)
        {
            new_node = createNode();
            printf("Name:");
            scanf(" %[^\n]s", patName);
            printf("Age:");
            scanf("%d", &patAge);
            printf("Medicine name:");
            scanf(" %[^\n]s", med);
            printf("Dosage amount:");
            scanf("%d", &dose);
            printf("Priority number:");
            scanf("%d", &prio);
            assign(&new_node, patName, patAge, med, dose, prio);
            adjustPrio(&head, prio);
            deQueue(&head, &tail, prio);    
            enQueue(new_node, &head, &tail);
            sortList(&head);
        }

        if(choice == 2)
            showList(head);
    }
    return 0;
}