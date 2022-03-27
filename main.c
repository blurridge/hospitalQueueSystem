/* NOTES
1. In a prio queue, dequeue tail if a higher priority is received.
2. No need to adjust priority if:
    a. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure and Global Variables

typedef struct node{

    char name[30];
    int age;
    char medName[25];
    int doseAmt;
    int prioNum;
    struct node *next;
    struct node *prev;
} NODE, *LL;

int maxCap = 5, nodeCount = 0;

// Function Prototypes

void showMenu();
NODE *createNode();
void assign(NODE **new_node, char patName[], int patAge, char med[], int dose, int prio);
void enQueue(NODE *new_node, LL *head, LL *tail);
void deQueue(LL *head, LL *tail, int prio);
void adjustPrio(LL *head, int prio);
void sortList(LL *head);
void showList(LL head);

// Function definitions

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

void showMenu(){

    printf("[1.] Add new patient\n");
    printf("[2.] Show current list\n");
    printf("[3.] Exit\n");
}

NODE *createNode(){

    NODE *newNode = malloc(sizeof(NODE));
    if(newNode == NULL)
        printf("Not enough memory!\n");
    return newNode;
}

void assign(NODE **new_node, char patName[], int patAge, char med[], int dose, int prio){

    strcpy((*new_node)->name, patName);
    strcpy((*new_node)->medName, med);
    (*new_node)->age = patAge;
    (*new_node)->doseAmt = dose;
    (*new_node)->prioNum = prio;
}

void enQueue(NODE *new_node, LL *head, LL *tail){

    if(*head == NULL)
    {
        new_node->next = *head;
        new_node->prev = NULL;
        *head = new_node;
        *tail = new_node;
    }
    else
    {
        NODE *trav;
        for(trav = *head; trav->next != NULL; trav = trav->next){}
        new_node->next = trav->next;
        new_node->prev = trav;
        trav->next = new_node;
        *tail = new_node;
    }
    nodeCount++;
}

void deQueue(LL *head, LL *tail, int prio){

    if(nodeCount >= maxCap)
    {
        NODE *current_node = malloc(sizeof(NODE));
        if(prio == maxCap)
        {
            current_node = *head;
            *head = (*head)->next;
            (*head)->prev = NULL;
            free(current_node);
        }
        else
        {
            current_node = *tail;
            *tail = (*tail)->prev;
            (*tail)->next = NULL;
            free(current_node);
        }
        nodeCount--;
    }
}

void adjustPrio(LL *head, int prio){

    NODE *current_node = malloc(sizeof(NODE));
    if(prio < maxCap)
    {
        for(current_node = *head; current_node != NULL; current_node = current_node->next)
        {
            int currentPrioNum = current_node->prioNum;
            if(currentPrioNum >= prio)
                current_node->prioNum = currentPrioNum+1;
        }
    }
    else if(prio == maxCap && nodeCount >= maxCap)
    {
        for(current_node = *head; current_node != NULL; current_node = current_node->next)
        {
            int currentPrioNum = current_node->prioNum;
            current_node->prioNum = currentPrioNum-1;
        }
    }
}

void sortList(LL *head){

    int i, j, swapped;
    for(i = 0; i < nodeCount - 1; i++)
    {
        swapped = 0;
        char strTemp[30];
        int numTemp;
        NODE *current_node = *head, *next_node = current_node->next;
        for(j = 0; j < nodeCount - i - 1; j++)
        {
            if(current_node->prioNum > next_node->prioNum)
            {
                strcpy(strTemp, current_node->name);
                strcpy(current_node->name, next_node->name);
                strcpy(next_node->name, strTemp);

                numTemp = current_node->age;
                current_node->age = next_node->age;
                next_node->age = numTemp;

                strcpy(strTemp, current_node->medName);
                strcpy(current_node->medName, next_node->medName);
                strcpy(next_node->medName, strTemp);

                numTemp = current_node->doseAmt;
                current_node->doseAmt = next_node->doseAmt;
                next_node->doseAmt = numTemp; 

                numTemp = current_node->prioNum;
                current_node->prioNum = next_node->prioNum;
                next_node->prioNum = numTemp; 

                swapped = 1;              
            }
            current_node = current_node->next;
            next_node = current_node->next;
        }
        if(swapped == 0)
            break;
    }
}

void showList(LL head){

    NODE *trav = malloc(sizeof(NODE));
    printf("%d prescriptions available\n", nodeCount);
    for(trav = head; trav != NULL; trav = trav->next)
        printf("%-30s\t%d\t%-25s\t%d\t%d\n", trav->name, trav->age, trav->medName, trav->doseAmt, trav->prioNum);
    printf("\n");
}