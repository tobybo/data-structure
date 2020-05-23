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
	delete []arr;
    return 0;
}

void insert_sort(int* arr, int len){
    int temp;
    for (int use_pos = 1;use_pos<len;use_pos++){
        temp = arr[use_pos]; //待插入的数
        for(int move_pos = use_pos;move_pos > 0 && arr[move_pos - 1] ;move_pos++){
			arr[move_pos] = arr[move_pos - 1]; //将比待插入数大的数都向后移动一位
			                                   //不用担心覆盖值 因为最后一位保存的是待插入的数 已经被存到temp里
        arr[move_pos] = temp; //move_pos永远指向的是可以存放temp的位置
		                      //因为比temp大的值已经往后面移动一位
							  //比temp小的值的位置在 move_pos - 1处
    }
}

