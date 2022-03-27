#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hospHeader.h"

extern int nodeCount, maxCap;

int main(){

    NODE *new_node;
    LL head = NULL;
    LL tail = NULL;
    char patName[30], med[25];
    int choice, patAge, dose, prio;
    clearScr();
    printf("Welcome to blurridge's Hospital Queue system!\n");
    printf("Loading...\n");
    pause();
    while(choice != 3)
    {
        clearScr();
        showMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        while(choice > 3 || choice < 1)
        {
            printf("You have entered an invalid number.\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
        }

        if(choice == 1)
        {
            clearScr();
            new_node = createNode();
            printf("Name: ");
            scanf(" %[^\n]s", patName);
            printf("Age: ");
            scanf("%d", &patAge);
            printf("Medicine name: ");
            scanf(" %[^\n]s", med);
            printf("Dosage amount: ");
            scanf("%d", &dose);
            printf("Priority number: ");
            scanf("%d", &prio);
            while(prio > 5 || prio < 1)
            {
                printf("Invalid priority number.\n");
                printf("Priority number:");
                scanf("%d", &prio);
            }
            assign(&new_node, patName, patAge, med, dose, prio);
            adjustPrio(&head, prio);
            deQueue(&head, &tail, prio);    
            enQueue(new_node, &head, &tail);
            sortList(&head);
            pause();
        }

        else if(choice == 2)
        {
            clearScr();
            showList(head);
            printf("Press ENTER key to continue...");
            fflush(stdin);
            getchar();
        }

        else if(choice == 3)
        {
            clearScr();
            printf("Goodbye!\n");
            pause();
        }
    }
    return 0;
}