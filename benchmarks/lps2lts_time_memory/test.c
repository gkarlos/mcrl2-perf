#include <stdio.h>

int f() {
    int x = 2;
    return x;
}

int main(void)
{
    int x = f();
    printf("%d\n", f());
}
