#include "Test.h"

//normal case
//with circle
void test() {
    //parameter check
    parameterTest();

    //illegal length for create method
    createNullCheck();

    //large array for create method
    createBigArrayCheck();

    //normal case
    normalCaseTest();

    //loop case
    loopCaseTest();
}

int main() {
    test();

    return 0;
}
