//
// Created by sky7282 on 2020/12/4.
//

#ifndef LINKEDLISTNODE_H
#define LINKEDLISTNODE_H

#define DEBUG false

typedef struct Node {
    Node *next;
    int val;
} Node;

const int NODE_LENGTH = sizeof(Node);
const int INT_NODE_LENGTH = sizeof(Node) + sizeof(int);

// create a LinkedList with array, and return its header
Node *createLinkedList(int *array, int length);

// reverse the linkedList and return new head
// if loop found, do not reverse
Node *reverseLinkedList(Node *node);

// free space for LinkedList
// if loop found, break the chain, and release all the head
void destroyLinkedList(Node *head);

// add the node with val to p
void appendNode(Node *p, int val);

// if loop found, return the first place founded
Node *loopTest(Node *head);

// based on loop entry and calculate the length
int loopLength(Node *);

// return loop entry
Node *loopEntrance(Node *, int);

#endif //LINKEDLISTNODE_H
