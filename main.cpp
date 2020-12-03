#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct Node {
    Node *next;
    int val;
};

const int NODE_LENGTH = sizeof(Node);
bool DEBUG = true;

Node *createLinkedList(int *array, int length);

Node *reverseLinkedList(Node *node);

void destroyLinkedList(Node *node);

void appendNode(Node *p, int val);

void print(Node *head);

void headNullCheck(Node *head);

void createNullCheck();

Node *createLinkedList(int *array, int length) {
    if (array == nullptr) {
        return nullptr;
    }
    if (length <= 0) {
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

//append a new node to p
//p is not null
void appendNode(Node *p, int val) {
    Node *q = (Node *) malloc(NODE_LENGTH);
    q->val = val;
    p->next = q;
}

void destroyLinkedList(Node *node) {
    if (node == nullptr) {
        return;
    }
    Node *p;
    while (node) {
        p = node->next;
        free(node);
        node = p;
    }
}

Node *reverseLinkedList(Node *head) {
    Node *cur = nullptr, *pre = head;
    while (pre) {
        Node *temp = pre->next;
        pre->next = cur;
        cur = pre;
        pre = temp;
    }
    return cur;
}

void print(Node *head) {
    if (!DEBUG) {
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

void createNullCheck() {
    int *array = nullptr;
    //if normal, it should not have any results
    Node *head = nullptr;
    head = createLinkedList(array, -1);
    headNullCheck(head);
    head = createLinkedList(array, 0);
    headNullCheck(head);
    head = createLinkedList(array, 10);
    headNullCheck(head);
}

void headNullCheck(Node *head) {
    if (head) {
        printf("null check error.");
    }
}

//normal case
//with circle
void test() {
    //
    int *array1 = nullptr;
    int *array2 = nullptr;
    int *array3 = nullptr;
    Node *head = nullptr;
    //test with nullptr
    createNullCheck();

    srand((unsigned) time(nullptr));

//    int randomLength =
}

//野指针
int main() {
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    const int ARRAY_LENGTH = sizeof(array) / sizeof(int);
    Node *head = createLinkedList(array, ARRAY_LENGTH);
    print(head);
    head = reverseLinkedList(head);
    print(head);
    destroyLinkedList(head);
    print(head);

    return 0;
}
