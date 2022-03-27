#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hospHeader.h"

int maxCap = 5, nodeCount = 0;

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
    printf("SUCCESS : New prescription enqueued!\n");
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
    if(prio < maxCap) // If the priority number is less than the max capacity, all priority numbers after it will be incremented.
    {
        for(current_node = *head; current_node != NULL; current_node = current_node->next)
        {
            int currentPrioNum = current_node->prioNum;
            if((currentPrioNum == prio) || (currentPrioNum >= prio && nodeCount >= maxCap))
                current_node->prioNum = currentPrioNum+1;
        }
    }
    else if(prio == maxCap && nodeCount >= maxCap) // If the priority number is equal to the max capacity and there are 
    {                                              // already 5 records, all priority numbers before it will be decremented.
        for(current_node = *head; current_node != NULL; current_node = current_node->next)
        {
            int currentPrioNum = current_node->prioNum;
            current_node->prioNum = currentPrioNum-1;
        }
    }
    else if(prio == maxCap)
    {
        for(current_node = *head; current_node != NULL; current_node = current_node->next)
        {
            int currentPrioNum = current_node->prioNum;
            if(currentPrioNum == maxCap)
                current_node->prioNum = currentPrioNum-1;
        }
    }
}

void sortList(LL *head){

    int i, j, swapped;
    for(i = 0; i < nodeCount - 1; i++) // Program uses a basic bubble sort to sort the nodes.
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

    if(head == NULL)
        printf("ERROR : No prescriptions available!\n");
    else
    {
        NODE *trav = malloc(sizeof(NODE));
        char nameLabel[] = "NAME";
        char ageLabel[] = "AGE";
        char medLabel[] = "MEDICINE";
        char doseLabel[] = "DOSAGE";
        char prioLabel[] = "PRIORITY";
        printf("%d prescriptions available\n", nodeCount);
        printf("%-30s\t%-4s\t%-25s\t%-6s\t%s\n", nameLabel, ageLabel, medLabel, doseLabel, prioLabel);
        for(trav = head; trav != NULL; trav = trav->next)
            printf("%-30s\t%d\t%-25s\t%d\t%d\n", trav->name, trav->age, trav->medName, trav->doseAmt, trav->prioNum);
        printf("\n");
    }
}

void clearScr(){

    printf("\e[1;1H\e[2J");
}

void delay(int seconds){

    int milli_seconds = 1000 * seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}

void pause(){

    #ifdef _WIN32
        delay(2);
    #elif __APPLE__
        delay(2000);
    #elif __unix__
        delay(2000);
    #endif
}