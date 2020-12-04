//
// Created by sky7282 on 2020/12/4.
//

#ifndef UTILS_H
#define UTILS_H

#include "LinkedListNode.h"

const int BITS_TO_BYTE = 8;

// get all available memory on Mac(unix)
unsigned long long getTotalSystemMemory();

// print all val from head
void printLinkedList(Node *head);

// print all arrays from start
void printArray(int *array, int length);

// check array and LinkedList results for normal sequence and reverse sequence
bool checkSame(int *arr, int length, Node *head, bool reverse);

#endif //UTILS_H
