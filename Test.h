//
// Created by sky7282 on 2020/12/4.
//

#ifndef TEST_H
#define TEST_H

#include "LinkedListNode.h"

// check head is null or not
void headNullCheck(Node *head);

// createLinkedNode with invalid length
void createIllegalLengthCheck();

// createLinkedNode with very large array
void createBigArrayCheck();

// randomly generate a loop in LinkedList
void generateLoop(Node *head, int length);

// createLinkedNode, reverseLinkedList and destroyLinkedList func with nullptr parameter check
void parameterTest();

// randomly generate an array with proper length, test its create, reverse and destroy
void normalCaseTest();

// test whether all functions work under LinkedList with loop
void loopCaseTest();

#endif //TEST_H
