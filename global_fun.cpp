#include <stdlib.h>
#include <time.h>
#include <iostream>

#include "global_fun.h"

const int MAX_RAND_NUM = 1000*1000*10;

int* get_rand_arr(int len){
    time_t t;
    srand((unsigned)time(&t));

    int* ret = new int[len];
    for (int i = 0;i<len;i++){
        //int randnum = rand();
        //std::cout<<"rand: "<<randnum<<std::endl;
        ret[i] = rand()%MAX_RAND_NUM;

    }
    return ret;
}
