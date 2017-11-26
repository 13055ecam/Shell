#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stats.h"


//void shrink();
//void sortn();
//void cnlup();

/* terminal*/
int main(void)
{
    char test[15];
    while(1){
        scanf("%s", test);
        int ret = strcmp("shrink", test);
        int ret1 = strcmp("sortn", test);
        int ret2 = strcmp("stats", test);
        int ret3 = strcmp("cnlup", test);

        if (ret == 0){
            //shrink();
        }
        else if(ret1 == 0){
            //sortn();
        }
        else if(ret2 == 0){
            stats();
        }
        else if(ret3 == 0){
            //cnlup();
        }
    }
}

