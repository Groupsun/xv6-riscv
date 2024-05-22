#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    if (argc < 2){
        fprintf(2, "usage: sleep must contain ticks, such as sleep 10\n");
    } else if (argc > 2){
        fprintf(2, "usage: sleep must only contain one argument\n");
    } else{
        int tick = atoi(argv[1]);
        sleep(tick);
    }
    exit(0);
}
