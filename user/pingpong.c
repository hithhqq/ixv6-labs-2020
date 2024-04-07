#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
 
 
 
int main(int argc, char *argv[]){
    int p[2];
    pipe(p);
    if (fork()==0){
        char send = 'a';
        char receive;
        read(p[0], &receive, 1);
        int subpid = getpid();
        printf("%d: received ping\n",subpid);
        write(p[1],&send,1);
        exit(0);
    } else{
        char send = 'b';
        char receive;
        write(p[1],&send,1);
        wait(0);
        read(p[0], &receive, 1);
        int pid = getpid();
        printf("%d: received pong\n",pid);
        exit(0);
        }    
    close(p[0]);
    close(p[0]);
    return 0;
 
 
    }