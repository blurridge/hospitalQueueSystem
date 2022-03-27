#ifndef HOSPHEADER_H
#define HOSPHEADER_H

// Prescription Structure

typedef struct node{

    char name[30];
    int age;
    char medName[25];
    int doseAmt;
    int prioNum;
    struct node *next;
    struct node *prev;
} NODE, *LL;

// Function Prototypes

void showMenu();
NODE *createNode();
void assign(NODE **new_node, char patName[], int patAge, char med[], int dose, int prio);
void enQueue(NODE *new_node, LL *head, LL *tail);
void deQueue(LL *head, LL *tail, int prio);
void adjustPrio(LL *head, int prio);
void sortList(LL *head);
void showList(LL head);
void clearScr();
void delay(int seconds);
void pause();

#endif