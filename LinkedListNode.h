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


Node *createLinkedList(int *array, int length);

Node *reverseLinkedList(Node *node);

void destroyLinkedList(Node *node);

void appendNode(Node *p, int val);

Node *loopTest(Node *head);

int loopLength(Node *);

Node *loopEntrance(Node *, int);

#endif //LINKEDLISTNODE_H
