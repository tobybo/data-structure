#include<iostream>

using namespace std;

const int max_rand = 42342342;

int main(int argn,char*const*argv)
{

    return 0;
}

void build_rand_arr(int* arr,int len){
    while(len > 0){
        len--;
        arr[len] = rand()%max_rand;
    }
}

int find_k(int* arr,int len,int k){
    int most_min_num;
    for(int i = 0; i<len; i++){
        if (i+1 <= k){
            most_min_num = most_min_num <= arr[i];most_min_num:arr[i];
        }
        else{

        }
    }

}
