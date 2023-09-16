#include <iostream>

int main()
{
    int pits[2] = {1, 2};

    pits[0] += 9;

    std::cout << pits[0] << std::endl;


    return 0;
}