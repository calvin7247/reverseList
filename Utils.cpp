//
// Created by sky7282 on 2020/12/4.
//

#include "Utils.h"
#include <unistd.h>
#include <stdio.h>


//get all available memory on Mac(unix)
// 17179869184(2GB) bits on my Mac
unsigned long long getTotalSystemMemory() {
    long pages = sysconf(_SC_PHYS_PAGES);
    long page_size = sysconf(_SC_PAGE_SIZE);
    return pages * page_size / BITS_TO_BYTE;
}


void printLinkedList(Node *head) {
    if (DEBUG) {
        return;
    }
    if (head == nullptr) {
        return;
    }
    while (head) {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}

void printArray(int *array, int length) {
    if (DEBUG) {
        return;
    }
    for (int i = 0; i < length; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
}


bool checkSame(int *arr, int length, Node *head, bool reverse) {
    if (arr && head && length > 0) {
        int i = 0;
        if (reverse) {
            i = length - 1;
            while (head) {
                if (i < 0) {
                    return false;
                }
                if (arr[i] == head->val) {
                    i--;
                    head = head->next;
                } else {
                    return false;
                }
            }
        } else {
            while (head) {
                if (i > length) {
                    return false;
                }
                if (arr[i] == head->val) {
                    i++;
                    head = head->next;
                } else {
                    return false;
                }
            }
        }
        if (i < length) {
            return false;
        }
        return true;
    }
    return false;
}