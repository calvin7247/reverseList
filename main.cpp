#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

struct Node {
    Node *next;
    int val;
};

const int NODE_LENGTH = sizeof(Node);
const int BITS_TO_BYTE = 8;
bool DEBUG = true;

Node *createLinkedList(int *array, int length);

Node *reverseLinkedList(Node *node);

void destroyLinkedList(Node *node);

void appendNode(Node *p, int val);

void print(Node *head);

void headNullCheck(Node *head);

void createNullCheck();

unsigned long long getTotalSystemMemory();

bool checkSame(int *arr, int length, Node *head, bool reverse);

// free package function
void Free(void *p);

//bad case
//1. array points to a null pointer
//2. an illegal length for array, may be a negative number, zero, or a large number
//3. index across its actual length (cannot process this exception)
Node *createLinkedList(int *array, int length) {
    if (array == nullptr) {
        return nullptr;
    }
    if (length <= 0) {
        return nullptr;
    }

    long long totalMemory = getTotalSystemMemory();
    // 0.9 is a experienced value, we can't allocate all memory for process
    // Assume that you have 2GB RAM on 64-bit operation system
    // the total node length is about 1.6^30, and size is 1.6GB
    // the total array length is same as node, and size is 0.4GB
    // the calculation course:
    // 2GB/(16+4)B=0.1*2^30, 0.1*2^30*16B=1.6GB
    // 0.1*2^30*4B=0.4GB
    int NODE_MAX = totalMemory / (BITS_TO_BYTE / (float)NODE_LENGTH * 0.9);
    if (length > NODE_MAX) {
        printf("Too large memory for allocation");
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
        Free(node);
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

bool checkSame(int *arr, int length, Node *head, bool reverse) {
    if(arr && head && length > 0) {
        int i = 0;
        if(reverse) {
            i = length - 1;
            while(head) {
                if(i < 0) {
                    return false;
                }
                if(arr[i] == head->val) {
                    i--;
                    head = head->next;
                } else {
                    return false;
                }
            }
        } else {
            while(head) {
                if(i > length) {
                    return false;
                }
                if(arr[i] == head->val) {
                    i++;
                    head = head->next;
                } else {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
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

//if normal, it should not have any results
void createNullCheck() {
    int *array = nullptr;
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

//2^31*8bit=2^31Byte=2GB
void createBigArrayCheck() {
    srand((unsigned) time(NULL));
    int length = INT32_MAX;
//    int length = 100;
    int *array = (int *) malloc(length * sizeof(int));
    for (int i = 0; i < length; i++) {
        array[i] = rand();
    }
    Node *head = createLinkedList(array, length);
    Free(array);
    createNullCheck();
    destroyLinkedList(head);
}

void createLinkedListCheck() {
    createNullCheck();
    createBigArrayCheck();
}


void Free(void *p) {
    free(p);
    p = nullptr;
}

//get all available memory on Mac(unix)
// 17179869184(2GB) bits on my Mac
// 17179869184 >> 2^31-1
unsigned long long getTotalSystemMemory() {
    long pages = sysconf(_SC_PHYS_PAGES);
    long page_size = sysconf(_SC_PAGE_SIZE);
    return pages * page_size;
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

//环路检测与避免
//野指针
int main() {
//    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
//    const int ARRAY_LENGTH = sizeof(array) / sizeof(int);
//    Node *head = createLinkedList(array, ARRAY_LENGTH);
//    print(head);
//    head = reverseLinkedList(head);
//    print(head);
//    destroyLinkedList(head);
//    print(head);

    return 0;
}
