#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

int main()
{
    int iteration = 0;

    while(1) {
        printf("While loop iteration %d\n", iteration);
        
        sleep(3);
        
        iteration++;
    }
}