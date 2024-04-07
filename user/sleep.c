#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
 
int main(int argc, char *argv[]) {
    if (argc < 2){
        printf("the number of agrments is valid");
        exit(0);
    }
    int click = atoi(argv[1]);
    sleep (click);
    exit(1);
}