//
// Created by sky7282 on 2020/12/4.
//

#include "Utils.h"
#include "LinkedListNode.h"
#include <stdio.h>
#include <stdlib.h>


//bad case
//1. array points to a null pointer
//2. an illegal length for array, may be a negative number, zero, or a large number
//3. index across its actual length (cannot process this exception)
Node *createLinkedList(int *array, int length) {
    if (array == nullptr) {
        printf("CreateLinkedList method, null pointer error\n");
        return nullptr;
    }
    if (length <= 0) {
        printf("CreateLinkedList method, illegal linkedList length %d.\n", length);
        return nullptr;
    }

    long long actualMemory = getTotalSystemMemory();
    // 0.9 is a experienced value, we can't allocate all memory for process
    // Assume that you have 2GB RAM on 64-bit operation system
    // the total node length is about 1.6^30, and size is 1.6GB
    // the total array length is same as node, and size is 0.4GB
    // the calculation course:
    // 2GB/(16+4)B=0.1*2^30, 0.1*2^30*16B=1.6GB
    // 0.1*2^30*4B=0.4GB
    long NODE_MAX = actualMemory * 0.9f / INT_NODE_LENGTH;
    if (length > NODE_MAX) {
        printf("CreateLinkedList method, too large memory for allocation\n");
        return nullptr;
    }

    //Create a head node.
    Node *head = (Node *) malloc(NODE_LENGTH);
    head->val = array[0];
    if (length == 1) {
        return head;
    }

    Node *p = head;
    for (int i = 1; i < length; ++i) {
        appendNode(p, array[i]);
        p = p->next;
    }
    return head;
}


Node *reverseLinkedList(Node *head) {
    //loop test, if loop found, do nothing
    Node *res = loopTest(head);
    if (res != nullptr) {
        printf("Loop founded, do not reverse\n");
        return head;
    }

    Node *cur = nullptr, *pre = head;
    while (pre) {
        Node *temp = pre->next;
        pre->next = cur;
        cur = pre;
        pre = temp;
    }
    return cur;
}

void destroyLinkedList(Node *head) {
    if (head == nullptr) {
        printf("DestroyLinkedList method, null pointer error.\n");
        return;
    }

    //loop test, break the chain and release the head
    Node *res = loopTest(head);
    if (res != nullptr) {
        int length = loopLength(head);
        Node *entrance = loopEntrance(head, length);
        Node *end = entrance;
        for (int i = 0; i < length - 1; i++) {
            end = end->next;
        }
        end->next = nullptr;
        printLinkedList(head);
    }

    Node *p;
    while (head) {
        p = head->next;
        free(head);
        head = nullptr;
        head = p;
    }
}

//append a new node to p
//p is not null
void appendNode(Node *p, int val) {
    Node *q = (Node *) malloc(NODE_LENGTH);
    q->val = val;
    q->next = nullptr;
    p->next = q;
}

Node *loopTest(Node *head) {
    if (!head) {
        printf("LoopTest method with null pointer error.\n");
        return nullptr;
    }
    Node *slow = head->next;
    if (slow == nullptr) {
        return nullptr;
    }
    Node *fast = slow->next;
    while (fast && slow) {
        if (slow == fast) {
            return slow;
        }
        slow = slow->next;
        fast = fast->next;
        if (fast != nullptr) {
            fast = fast->next;
        }
    }
    return nullptr;
}

int loopLength(Node *head) {
    Node *loopEnt = loopTest(head);
    if (!loopEnt) {
        return 0;
    }
    int length = 1;
    Node *p = loopEnt->next;
    while (p != loopEnt) {
        ++length;
        p = p->next;
    }
    return length;
}

Node *loopEntrance(Node *head, int length) {
    if (length > 0) {
        Node *entrance = head;
        for (int i = 0; i < length; i++) {
            entrance = entrance->next;
        }
        while (head != entrance) {
            head = head->next;
            entrance = entrance->next;
        }
        return entrance;
    } else {
        return nullptr;
    }
}

