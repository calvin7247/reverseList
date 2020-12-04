#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

struct Node {
    Node *next;
    int val;
};

const int NODE_LENGTH = sizeof(Node);
const int INT_NODE_LENGTH = sizeof(Node) + sizeof(int);
const int BITS_TO_BYTE = 8;
bool DEBUG = true;

Node *createLinkedList(int *array, int length);

Node *reverseLinkedList(Node *node);

void destroyLinkedList(Node *node);

void appendNode(Node *p, int val);

void printLinkedList(Node *head);

void headNullCheck(Node *head);

void createNullCheck();

unsigned long long getTotalSystemMemory();

bool checkSame(int *arr, int length, Node *head, bool reverse);

Node* loopTest(Node *head);

int loopLength(Node *);

Node* loopEntrance(Node *);

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
//    printf("%d", length);
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

//append a new node to p
//p is not null
void appendNode(Node *p, int val) {
    Node *q = (Node *) malloc(NODE_LENGTH);
    q->val = val;
    p->next = q;
}

void destroyLinkedList(Node *node) {
    //loop test, break the chain and release the node
    Node *res = loopTest(node);
    if(res != nullptr) {
        return;
    }

    if (node == nullptr) {
        printf("DestroyLinkedList method, null pointer error.\n");
        return;
    }
    Node *p;
    while (node) {
        p = node->next;
        free(node);
        node = nullptr;
        node = p;
    }
}

Node *reverseLinkedList(Node *head) {
    //loop test, if loop found, do nothing
    Node *res = loopTest(head);
    if(res != nullptr) {
        printf("Loop founded, do not reverse\n");
        return nullptr;
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

void printLinkedList(Node *head) {
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

void printArray(int *array, int length) {
    if (!DEBUG) {
        return;
    }
    for (int i = 0; i < length; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
}


//if normal, it should not have any results
void createNullCheck() {
    int *array = nullptr;
    int anotherArr[] = {1, 2, 3};
    Node *head = nullptr;
    printf("**Test for CreateLinkedList start.**\n");
    //these case should return nullptr
    head = createLinkedList(array, -1);
    headNullCheck(head);
    head = createLinkedList(array, 0);
    headNullCheck(head);
    head = createLinkedList(array, 10);
    headNullCheck(head);
    head = createLinkedList(anotherArr, -1);
    headNullCheck(head);
    head = createLinkedList(anotherArr, 0);
    headNullCheck(head);
    //normal case should return an existing pointer
    head = createLinkedList(anotherArr, sizeof(anotherArr) / sizeof(int));
    headNullCheck(head);
    destroyLinkedList(head);
    head = nullptr;
    printf("**Test for CreateLinkedList parameter finished.**\n\n");
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
    printf("**Test for CreateLinkedList with big array finished.**\n");
}

void createLinkedListCheck() {
    createNullCheck();
    createBigArrayCheck();
}

//get all available memory on Mac(unix)
// 17179869184(2GB) bits on my Mac
unsigned long long getTotalSystemMemory() {
    long pages = sysconf(_SC_PHYS_PAGES);
    long page_size = sysconf(_SC_PAGE_SIZE);
    return pages * page_size / BITS_TO_BYTE;
}

void normalCaseTest() {
    printf("**Test for CreateLinkedList with normal array start.**\n");
    int NORMAL_LENGTH = 5;
    srand((unsigned) time(nullptr));
    int *normalArray = (int *) malloc(NORMAL_LENGTH * sizeof(int));
    for (int i = 0; i < NORMAL_LENGTH; i++) {
        normalArray[i] = rand();
    }
    Node *head = createLinkedList(normalArray, NORMAL_LENGTH);
    bool checkRes = checkSame(normalArray, NORMAL_LENGTH, head, false);
//    printArray(normalArray, NORMAL_LENGTH);
//    printLinkedList(head);
    if (!checkRes) {
        printf("Got some error\n");
    } else {
        printf("Arrays are same as LinkListNodes.\n");
    }
    head = reverseLinkedList(head);
    checkRes = checkSame(normalArray, NORMAL_LENGTH, head, true);
//    printArray(normalArray, NORMAL_LENGTH);
//    printLinkedList(head);
    if (!checkRes) {
        printf("Got some error\n");
    } else {
        printf("Arrays are same as ReverseLinkListNodes.\n");
    }
    free(normalArray);
    normalArray = nullptr;
    destroyLinkedList(head);
    printf("**Test for CreateLinkedList with normal array end.**\n");
}

Node* loopTest(Node *head) {
    if(!head) {
        printf("LoopTest method with null pointer error.");
        return nullptr;
    }
    Node *slow = head->next;
    if(slow == nullptr) {
        return nullptr;
    }
    Node *fast = slow->next;
    while(fast && slow) {
        if(slow == fast) {
            return slow;
        }
        slow = slow->next;
        fast = fast->next;
        if(fast != nullptr) {
            fast = fast->next;
        }
    }
    return nullptr;
}

int loopLength(Node *head) {
    Node *loopEntrance = loopTest(head);
    if(!loopEntrance) {
        return 0;
    }
    int length = 1;
    Node *p = loopEntrance->next;
    while(p != loopEntrance) {
        ++length;
        p = p->next;
    }
    return length;
}

Node* loopEntrance(Node *head) {
    int length = loopLength(head);
    if(length > 0) {
        Node *entrance = head;
        for(int i = 0; i < length; i++) {
            entrance = entrance->next;
        }
        while(head != entrance) {
            head = head->next;
            entrance = entrance->next;
        }
        return entrance;
    } else {
        return nullptr;
    }
}

void generateLoop(Node *head, int length) {
    int randPos = rand() % length;
    Node *tail = head;
    Node *loopPos = head;
    while(tail->next) {
        tail = tail->next;
    }
    for(int i = 0; i < randPos; ++i) {
        loopPos = loopPos->next;
    }

    tail->next = loopPos;
}


void loopCaseTest() {
    int NORMAL_LENGTH = 5;
    srand((unsigned) time(nullptr));
    int *normalArray = (int *) malloc(NORMAL_LENGTH * sizeof(int));
    for (int i = 0; i < NORMAL_LENGTH; i++) {
        normalArray[i] = rand();
    }
    Node *head = createLinkedList(normalArray, NORMAL_LENGTH);
    bool checkRes = checkSame(normalArray, NORMAL_LENGTH, head, false);
    printArray(normalArray, NORMAL_LENGTH);
    printLinkedList(head);
    if (!checkRes) {
        printf("Got some error\n");
    } else {
        printf("Arrays are same as LinkListNodes.\n");
    }

    //generate loop for
    generateLoop(head, NORMAL_LENGTH);

    head = reverseLinkedList(head);
    //reverse = false, do nothing
    checkRes = checkSame(normalArray, NORMAL_LENGTH, head, false);
//    printArray(normalArray, NORMAL_LENGTH);
//    printLinkedList(head);
    if (checkRes) {
        printf("Got some error\n");
    } else {
        printf("Reverse do nothing\n");
    }
//    free(normalArray);
//    normalArray = nullptr;
//    destroyLinkedList(head);
}


//normal case
//with circle
void test() {

    //bad case test
//    createLinkedListCheck();

    //normal case
//    normalCaseTest();

    //loop case
    loopCaseTest();
}

int main() {
//    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
//    const int ARRAY_LENGTH = sizeof(array) / sizeof(int);
//    Node *head = createLinkedList(array, ARRAY_LENGTH);
//    printLinkedList(head);
//    head = reverseLinkedList(head);
//    printLinkedList(head);
//    destroyLinkedList(head);
//    printLinkedList(head);
    test();

    return 0;
}
