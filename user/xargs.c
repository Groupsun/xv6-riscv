#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

#define MAX_LINE_LEN 32
#define MAX_ARGS_LEN 32

// read line from stdin
// be careful of the malloc function
int
readline(int argc, char *argv[], char *sargv[], int max)
{
    char c, start = 1;
    char *p = "";
    int sargc = 0, cnt = 0;
    for (int i = 1; i < argc; i++){
        sargv[sargc] = malloc(MAX_ARGS_LEN);
        memcpy(sargv[sargc], argv[i], strlen(argv[i]));
        sargc++;
    }
    while(read(0, &c, 1) > 0){
        if (c == '\n'){
            *p = '\0';
            return sargc+1;
        } else{
            if(c == ' '){
                start = 1;
                sargc++;
            } else{
                if(start){
                    if (sargc >= max){
                        fprintf(2, "too many args\n");
                        exit(0);
                    }
                    start = 0;
                    sargv[sargc] = malloc(MAX_ARGS_LEN);
                    p = sargv[sargc];
                }
                *p++ = c;
            }
        }
        cnt++;
    }
    return 0;
}

int
main(int argc, char *argv[])
{
    if (argc < 2){
        fprintf(2, "usage: xargs [command]\n");
    } else{
        char *sargv[MAXARG];
        int sargc;
        while((sargc = readline(argc, argv, sargv, MAXARG)) != 0){
            if(fork() == 0){
                exec(sargv[0], sargv);
                exit(0);
            } else
                wait(0);
            for(int i=0; i<sargc; i++)
                free(sargv[i]);
        }
    }

    exit(0);
}
