#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"
 
int
main(int argc, char* argv[]){
    if(argc < 2){
        printf("the number of arguments is too small!");
        exit(1);
    }
    char* args[MAXARG];
    int status;
    memset(args,0,sizeof(args));
    for(int i = 1;i < argc; i++){
        args[i-1] = argv[i];
    }
    args[argc] = 0;
 
    while(1){
        args[argc-1] = 0;
        args[argc-1] = malloc(1024); // 为最后一个参数分配内存
        char* p = args[argc-1];
        char c;
        int n;
        while((n =read(0,&c,1))&&c!='\n'){
            *p = c;
            //printf("p:%c\n",*(p));
            ++p;
        }
       // printf("111args[argc-1]:%s \n",args[argc-1]);
 
        
        *p = '\0';
        if(n == 0){
            exit(1);
            //printf("jinru n=0\n");
            //printf("args[argc-1]:%s \n",args[argc-1]);
            if(fork()==0){
                //printf("args:\n");
                for(int i =0;i<argc;i++){
                    //printf("%s,",args[i]);
                }
            exec(argv[1],args);
            exit(1);
            }
            else{
                wait(&status);
                
            }
            exit(1);
 
        }
        else {
            //printf("jinru n=1\n");
            if(fork()==0){
            exec(argv[1],args);
            }
            else{
                wait(&status);
                
            }
            continue;
        }
 
 
    }
 
 
 
 
 
 
    return 0;
 
}