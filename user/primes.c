#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
prime(int *p)
{
    close(p[1]);
    // read first number
    int judge, n;
    read(p[0], &judge, sizeof(int));
    printf("prime %d\n", judge);
    // try to read the remaining numbers
    int ret_code = read(p[0], &n, sizeof(int));

    if (ret_code != 0) {
        int cp[2];
        pipe(cp);

        if(fork()==0){
            prime(cp);
            exit(0);
        } else{
            close(cp[0]);
            do {
                if (n % judge != 0)
                    write(cp[1], &n, sizeof(int));
                ret_code = read(p[0], &n, sizeof(int));
            } while(ret_code != 0);
            close(cp[1]);
            wait(0);
        }
    }

    close(p[0]);
}

int
main(int argc, char *argv[])
{
    if(argc != 1){
        fprintf(2, "usage: primes don't need any arguments\n");
    } else{
        int p[2];
        pipe(p);
        
        if(fork()==0){  // child
            prime(p);
            exit(0);
        } else{
            close(p[0]);
            for (int i = 2; i <= 35; i++)
                write(p[1], &i, sizeof(i));
            close(p[1]);
            wait(0);
        }
    }
    exit(0);
}
