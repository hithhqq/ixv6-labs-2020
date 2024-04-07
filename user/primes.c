#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
 
int 
main (int argc, char *argv[]){
    int parentpipe[2] ;
    int childpipe[2];
 
    //int num = 2;
    pipe(parentpipe);
    for(int i = 2;i <= 35;i++){
        write(parentpipe[1],&i,1);
    }
    
 
 
    while(1){
        if(fork()==0){
            
            int readnum = 0;
            int numcount = 0;
            
            
            close(parentpipe[1]);
            pipe(childpipe);
            int readnum_flag = -1;
            int base = 0;
            while(read(parentpipe[0],&readnum,1)){
               
                
               // printf("-------%d\n",readnum);
                if (readnum_flag == -1){
                    readnum_flag =1;
                    base = readnum;
                    printf("prime %d\n",readnum);
                } //第一次读
                else{
                   // printf("aaaaaaaaaaaaaaaaaaaaaa\n");
                    //printf("num : %d\n",readnum);
                    if(readnum%base!=0){
                        //printf("base num : %d\n",base);
                       // printf("qulifyed num : %d\n",readnum);
                        
                        write(childpipe[1],&readnum,1);
                    }
                }
                numcount++;
            }
            if(numcount==1){
                exit(0);
            }
            
            parentpipe[0] = childpipe[0];
            parentpipe[1] = childpipe[1];
        }
        else{
            close(parentpipe[0]);
            close(parentpipe[1]);
            wait(0);
            exit(0);
        }
    }
 
}