//
// Created by sky7282 on 2020/12/4.
//

#ifndef UTILS_H
#define UTILS_H

#include "LinkedListNode.h"

const int BITS_TO_BYTE = 8;

//get all available memory on Mac(unix)
// 17179869184(2GB) bits on my Mac
unsigned long long getTotalSystemMemory();

void printLinkedList(Node *head);

void printArray(int *array, int length);


bool checkSame(int *arr, int length, Node *head, bool reverse);

#endif //UTILS_H
