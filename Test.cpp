//
// Created by sky7282 on 2020/12/4.
//
#include "Test.h"
#include "Utils.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

//if normal, it should not have any results
void createNullCheck() {
    printf("**Test for CreateLinkedList with illegal length start.**\n");

    int array[] = {1, 2, 3};
    Node *head = nullptr;
    head = createLinkedList(array, -1);
    headNullCheck(head);
    head = createLinkedList(array, 0);
    headNullCheck(head);

    printf("**Test for CreateLinkedList with illegal length end.**\n\n");
}

void headNullCheck(Node *head) {
    if (head) {
        printf("Null check error.\n");
    }
}

//Only focus on large memory for LinkNode
//2^31*8bit=2^31Byte=2GB
void createBigArrayCheck() {
    printf("**Test for CreateLinkedList with big array start.**\n");

    long long actualMemory = getTotalSystemMemory();
    long ARRAY_LENGTH_MAX = actualMemory * 0.9f / (INT_NODE_LENGTH);
    int length = 1.2f * ARRAY_LENGTH_MAX;

    srand((unsigned) time(nullptr));
    int *array = (int *) malloc((long) length * sizeof(int));
    for (int i = 0; i < length; i++) {
        array[i] = rand();
    }

    Node *head = createLinkedList(array, length);
    if (head == nullptr) {
        printf("CreateLinkedList for big array failed.\n");
    }
    free(array);
    array = nullptr;
    destroyLinkedList(head);

    printf("**Test for CreateLinkedList with big array end.**\n\n");
}

//test for destroyLinkedList, reverseLinkedList with nullptr
void parameterTest() {
    printf("**Parameter test start.**\n");

    printf("Null pointer for createLinkedList method");
    Node *head = nullptr;
    //these case should return nullptr
    head = createLinkedList(nullptr, -1);
    headNullCheck(head);
    head = createLinkedList(nullptr, 0);
    headNullCheck(head);
    head = createLinkedList(nullptr, 10);
    headNullCheck(head);

    printf("Null pointer for destroyLinkedList method");
    destroyLinkedList(nullptr);
    printf("Null pointer for reverseLinkedList method");
    Node *res = reverseLinkedList(nullptr);
    if (res == nullptr && DEBUG) {
        printf("Parameter test ok\n");
    }

    printf("**Parameter test end.**\n\n");
}


void normalCaseTest() {
    printf("**Test for CreateLinkedList with normal array start.**\n");

    int NORMAL_LENGTH = 20;
    srand((unsigned) time(nullptr));
    int *normalArray = (int *) malloc(NORMAL_LENGTH * sizeof(int));
    for (int i = 0; i < NORMAL_LENGTH; i++) {
        normalArray[i] = rand();
    }
    Node *head = createLinkedList(normalArray, NORMAL_LENGTH);
    if (DEBUG) {
        bool checkRes = checkSame(normalArray, NORMAL_LENGTH, head, false);
        printArray(normalArray, NORMAL_LENGTH);
        printLinkedList(head);
        if (!checkRes && DEBUG) {
            printf("Got some error\n");
        } else {
            printf("Arrays are same as LinkListNodes.\n");
        }

    }
    head = reverseLinkedList(head);
    if (DEBUG) {
        bool checkRes = checkSame(normalArray, NORMAL_LENGTH, head, true);
        printArray(normalArray, NORMAL_LENGTH);
        printLinkedList(head);
        if (!checkRes) {
            printf("Got some error\n");
        } else {
            printf("Arrays are same as ReverseLinkListNodes.\n");
        }
    }

    free(normalArray);
    normalArray = nullptr;
    destroyLinkedList(head);

    printf("**Test for CreateLinkedList with normal array end.**\n\n");
}

void generateLoop(Node *head, int length) {
    int randPos = rand() % length;
    Node *tail = head;
    Node *loopPos = head;
    while (tail->next) {
        tail = tail->next;
    }
    for (int i = 0; i < randPos; ++i) {
        loopPos = loopPos->next;
    }

    tail->next = loopPos;
}


void loopCaseTest() {
    printf("**Test for CreateLinkedList with LinkedList with loop start.**\n");

    int NORMAL_LENGTH = 20;
    srand((unsigned) time(nullptr));
    int *normalArray = (int *) malloc(NORMAL_LENGTH * sizeof(int));
    for (int i = 0; i < NORMAL_LENGTH; i++) {
        normalArray[i] = rand();
    }
    Node *head = createLinkedList(normalArray, NORMAL_LENGTH);
    bool checkRes = checkSame(normalArray, NORMAL_LENGTH, head, false);
    printArray(normalArray, NORMAL_LENGTH);
    printLinkedList(head);
    if (DEBUG) {
        if (!checkRes) {
            printf("Got some error\n");
        } else {
            printf("Arrays are same as LinkListNodes.\n");
        }
    }

    //generate loop for
    generateLoop(head, NORMAL_LENGTH);

    head = reverseLinkedList(head);
    //reverse = false, do nothing
    if (DEBUG) {
        checkRes = checkSame(normalArray, NORMAL_LENGTH, head, false);
        if (checkRes) {
            printf("Got some error\n");
        } else {
            printf("Reverse do nothing\n");
        }
    }
    free(normalArray);
    normalArray = nullptr;
    destroyLinkedList(head);

    printf("**Test for CreateLinkedList with LinkedList with loop end.**\n\n");
}
