#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    if (argc != 1){
        fprintf(2, "usage: pingpong don't need any arguments\n");
    } else{
        int p[2];        // file descriptor for pipe
        pipe(p);         // create pipe
        if(fork() == 0){ // child
            read(p[0], 0, 8);
            int pid = getpid();
            fprintf(1, "%d: received ping\n", pid);
            write(p[1], "pong\n", 8);
            close(p[1]);
            close(p[0]);
            exit(0);
        } else{
            write(p[1], "ping\n", 8);
            wait(0);
            read(p[0], 0, 8);
            int pid = getpid();
            fprintf(1, "%d: received pong\n", pid);
            close(p[1]);
            close(p[0]);
        }
    }
    exit(0);
}

