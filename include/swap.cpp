#include <iostream>
#include "swap.h"

void swap(int &a, int &b) {
    int temp = b;
    b = a;
    a = temp;
}