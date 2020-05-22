#include<cassert>
#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<stack>

#include"global_fun.h"

const int size = 1000000;
void sort_fask_sentry(int *arr, int size);
int get_max_k(int *arr,int size, int k);

int main()
{
	int *arr = get_rand_arr(size);
	int i;
	/*for(i = 0; i < size; i++)*/
	//{
		//std::cout<<arr[i]<<" ";
	//}
	/*std::cout<<std::endl;*/
	std::cout<<"arr已经装填完毕，装填数量为: "<<size<<std::endl;
	time_t start = clock();
	int val = get_max_k(arr,size, size/3);
	std::cout<<"val: "<<val<<std::endl;
	//sort_fask_sentry(arr,size);
	std::cout<<"cost time: "<<clock() - start<<std::endl;
	/*for(i = 0; i < size; i++)*/
	//{
		//std::cout<<arr[i]<<" ";
	//}
	/*std::cout<<std::endl;*/
	return 0;
}

/*哨兵法:
 *1.准备前后哨兵和第一位作为参照值; 第一位为参照值和前哨兵; 最后一位为后哨兵
 *2.准备记录是否还需要继续排序的堆栈,稍后会将还需进行排序的新哨兵的值压栈
 *3.主循环进行条件：排序没有全部完成 -> 正在进行排序的哨兵还未相遇 或者 堆栈中还有未开始行进的哨兵
 *4.进入循环之前将第一次行军的哨兵和参照值初始化; 主循环中先检查当前是否有哨兵在行军,没有就从堆栈中取
 *5.当前的哨兵开始行军:
 *     sentry_back 先走, 找到第一个比参照值小的值, 停下; sentry_front 后走, 找到第一个比参照值大的值,停下;
 *     然后两个位置的值交换; 写到这里 我觉得既然是两个哨兵交换,那么谁先谁后貌似没啥区别;
 *     不是先找到一个值,然后和参照值交换(这种情况如果front先走,找到第一个值也不能交换),
 *     想到就来实验下: front 先走, back 后走;
 *     结果发现 例如 5,1,2,3,6 这种序列的时候：front = 0, back = 4, look = 5;
 *	       front先走,由于 1,2,3 都小于5,所以 front = 4 = back, 这时候;
 *6.当两个哨兵相遇，检查是否还有新的哨兵，检查条件为当前两个哨兵与各自出发点之间距离间隔是否 > 1;
 *7.如果条件为真,则将新的两个哨兵压栈;
*/
void sort_fask_sentry(int *arr, int size)
{
	assert(size > 1);
	int sentry_front(0),sentry_back(size - 1);
	int look_val(arr[0]);
	std::stack<int> find_stack;
	int now_left(0),now_right(size - 1);
	int temp;
	while(sentry_front < sentry_back || find_stack.size() > 0)
	{
		if(sentry_front >= sentry_back){
			assert(find_stack.size() >= 2);
			sentry_back  = find_stack.top();
			find_stack.pop();
			sentry_front = find_stack.top();
			find_stack.pop();
			now_left  = sentry_front;
			now_right = sentry_back;
			//std::cout<<"front: "<<sentry_front<<"; back: "<<sentry_back<<"; size: "<<find_stack.size()<<std::endl;
			if(now_left >= now_right)
				continue;
			look_val = arr[now_left];
		}
		while(arr[sentry_front] <= look_val && sentry_front < sentry_back)
		{
			sentry_front++;
		}
		while(arr[sentry_back] > look_val && sentry_back > sentry_front)
		{
			sentry_back--;
		}
		if(sentry_front == sentry_back)
		{
			if(arr[sentry_front] < look_val)
			{
				arr[now_left] = arr[sentry_front];
				arr[sentry_front] = look_val;
				find_stack.push(now_left);
				find_stack.push(sentry_front - 1);
				find_stack.push(sentry_front + 1);
				find_stack.push(now_right);
				//printf("%d,%d,%d,%d\n",now_left,sentry_front - 1,sentry_front + 1,now_right);
			}
			else if(sentry_front - 1 > now_left)
			{
				arr[now_left] = arr[sentry_front - 1];
				arr[sentry_front - 1] = look_val;
				find_stack.push(now_left);
				find_stack.push(sentry_front - 2);
				find_stack.push(sentry_front);
				find_stack.push(now_right);
				//printf("%d,%d,%d,%d\n",now_left,sentry_front - 2,sentry_front + 1,now_right);
			}
			else
			{
				find_stack.push(sentry_front);
				find_stack.push(now_right);
			}
		}
		else
		{
			temp = arr[sentry_front];
			arr[sentry_front] = arr[sentry_back];
			arr[sentry_back] = temp;
		}
	}
}

int get_max_k(int *arr,int size, int k)
{
	assert(size > 1 && k > 1 && k < size + 1);
	k--;
	int sentry_front(0),sentry_back(size - 1);
	int look_val(arr[0]);
	std::stack<int> find_stack;
	int now_left(0),now_right(size - 1);
	int temp;
	while(sentry_front < sentry_back || find_stack.size() > 0)
	{
		if(sentry_front >= sentry_back){
			assert(find_stack.size() >= 2);
			sentry_back  = find_stack.top();
			find_stack.pop();
			sentry_front = find_stack.top();
			find_stack.pop();
			now_left  = sentry_front;
			now_right = sentry_back;
			//std::cout<<"front: "<<sentry_front<<"; back: "<<sentry_back<<"; size: "<<find_stack.size()<<std::endl;
			if(now_left >= now_right)
				continue;
			look_val = arr[now_left];
		}
		while(arr[sentry_front] <= look_val && sentry_front < sentry_back)
		{
			sentry_front++;
		}
		while(arr[sentry_back] > look_val && sentry_back > sentry_front)
		{
			sentry_back--;
		}
		if(sentry_front == sentry_back)
		{
			if(arr[sentry_front] < look_val)
			{
				arr[now_left] = arr[sentry_front];
				arr[sentry_front] = look_val;
				find_stack.push(now_left);
				find_stack.push(sentry_front - 1);
				find_stack.push(sentry_front + 1);
				find_stack.push(now_right);
				if(sentry_front == k)
					return look_val;
				//printf("%d,%d,%d,%d\n",now_left,sentry_front - 1,sentry_front + 1,now_right);
			}
			else if(sentry_front - 1 > now_left)
			{
				arr[now_left] = arr[sentry_front - 1];
				arr[sentry_front - 1] = look_val;
				find_stack.push(now_left);
				find_stack.push(sentry_front - 2);
				find_stack.push(sentry_front);
				find_stack.push(now_right);
				if(sentry_front - 1 == k)
					return look_val;
				//printf("%d,%d,%d,%d\n",now_left,sentry_front - 2,sentry_front + 1,now_right);
			}
			else
			{
				find_stack.push(sentry_front);
				find_stack.push(now_right);
			}
		}
		else
		{
			temp = arr[sentry_front];
			arr[sentry_front] = arr[sentry_back];
			arr[sentry_back] = temp;
		}
	}
	return arr[k];
}

