#include<stdlib.h>
#include<time.h>
#include<iostream>

#include "global_fun.h"

using namespace std;

//const int test_extend_const;

void insert_sort(int*,int);

int main(int argn, char* const* argv){
    int len = 1000000;
    int *arr = get_rand_arr(len);

    time_t start = clock();

    //insert_sort(arr,len);
    cout<<test_extend_const<<endl;

    cout<<"costtime: "<<clock() - start<<endl;
    //for(int i = 0;i<len;i++)
    //    cout<<arr[i]<<endl;
    return 0;
}

void insert_sort(int* arr, int len){
    int temp;
    int swap;
    for (int i = 0;i<len;i++){
        temp = arr[i];
        for(int pos = i+1;pos < len;pos++){
            if (arr[pos] < temp){
                swap = temp;
                temp = arr[pos];
                arr[pos] = swap;
            }
        }
        arr[i] = temp;
    }
}

