#include <iostream>
#include "risc.h"

void checkPosition(Risc& risc) {
    if (risc.Get(0) > risc.Get(1)) {
        risc.Cpy(2, 1);
        risc.Move(1, 0);
        risc.Move(0, 2);
    }
}
int runEmulation(int num1, int num2) {

    Risc risc(32);
    risc.Set(0, num1);
    risc.Set(1, num2);

    checkPosition(risc);

    while (risc.Get(0) != 0 && risc.Get(1) != 0)
    {
        risc.Sub(2, 1, 0);
        risc.Move(1, 2);
        checkPosition(risc);
    }

    risc.Sum(2, 1, 0);
    return risc.Get(2);
}

int main()
{
    int result = runEmulation(34, 36);

    std::cout << result;
}
