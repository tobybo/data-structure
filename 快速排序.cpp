#include<cassert>
#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<stack>

#include"global_fun.h"

//extern const int MAX_RAND_NUM;
//const int size = 10*1000*1000;
const int size = MAX_RAND_NUM;

void sort_fask_sentry_front(int *arr, int size); //前面的哨兵先走
void sort_fask_sentry_back(int *arr, int size);   //后面的哨兵先走
void sort_fask_wakeng(int *arr, int size);
void sort_fast_pointer(int *arr, int size);
void sort_fast_lua(int *arr, int low, int upper);

void swap(int* arr, int i, int j);
int get_max_k(int *arr,int size, int k);
bool sort_cmp(int *arr, int i, int j);

void test_find_k();
void test_sentry_front();
void test_sentry_back();
void test_wakeng();
void test_pointer();
void test_lua();

int main()
{
	test_lua();
	test_pointer();
	test_wakeng();
	//test_find_k();
	test_sentry_back();
	test_sentry_front();
	return 0;
}

/*哨兵法: 给定一个左端或右端的参照值,根据两头哨兵行军后相遇的点可以确定参照值的顺序位置; nlogn
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
 *	       front先走,由于 1,2,3 都小于5,所以 front = 4 = back, 这时候就需要把 front - 1 位置的值 和 look交换了;
 *6.当两个哨兵相遇，检查是否还有新的哨兵，检查条件为当前两个哨兵与各自出发点之间距离间隔是否 > 1;
 *7.如果条件为真,则将新的两个哨兵压栈;
*/
void sort_fask_sentry_front(int *arr, int size)
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
				if(sentry_front == k)
					return look_val;
				else if(sentry_front < k)
				{
					find_stack.push(sentry_front + 1);
					find_stack.push(now_right);
				}
				else
				{
					find_stack.push(now_left);
					find_stack.push(sentry_front - 1);
				}
				//printf("%d,%d,%d,%d\n",now_left,sentry_front - 1,sentry_front + 1,now_right);
			}
			else if(sentry_front - 1 > now_left)
			{
				arr[now_left] = arr[sentry_front - 1];
				arr[sentry_front - 1] = look_val;
				if(sentry_front - 1 == k)
					return look_val;
				else if(sentry_front - 1 < k)
				{
					find_stack.push(sentry_front);
					find_stack.push(now_right);
				}
				else
				{
					find_stack.push(now_left);
					find_stack.push(sentry_front - 2);
				}
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

void sort_fask_sentry_back(int *arr, int size)
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
		while(arr[sentry_back] > look_val && sentry_back > sentry_front)
		{
			sentry_back--;
		}
		while(arr[sentry_front] <= look_val && sentry_front < sentry_back)
		{
			sentry_front++;
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
			else
			{
				find_stack.push(sentry_front + 1);
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

/*挖坑法
 *
 * */
void sort_fask_wakeng(int *arr, int size)
{
	assert(size > 1);
	int front(0),now_left(0);
	int back,now_right;
	back = now_right = size - 1;
	int look_idx = now_left;
	std::stack<int> find_stack;
	while(front < back || find_stack.size() > 0)
	{
		while(front >= back)
		{
			if(find_stack.size() <= 1)
				return;
			back = now_right = find_stack.top();
			find_stack.pop();
			front = now_left = find_stack.top();
			find_stack.pop();
			look_idx = now_left;
		}
		while(front < back && arr[back] > arr[look_idx])
		{
			back--;
		}
		if(front == back)
		{
			find_stack.push(now_left);
			find_stack.push(front - 1);
			find_stack.push(front + 1);
			find_stack.push(now_right);
			continue;
		}
		else
		{
			swap(arr,back,look_idx);
			look_idx = back;
		}
		while(front < back && arr[front] <= arr[look_idx])
		{
			front++;
		}
		if(front == back)
		{
			find_stack.push(now_left);
			find_stack.push(front - 1);
			find_stack.push(front + 1);
			find_stack.push(now_right);
			continue;
		}
		else
		{
			swap(arr,front,look_idx);
			look_idx = front;
		}
	}
}

/*快慢指针法: 两个指针都从0出发,参照值为0位的元素
 * 1.后指针遇到 <= 参照值 则两个指针都右移,
 * 2.遇到 > 参照值, 右指针右移, 左指针不动,
 * 3.再次遇到 <= 参照值的时候,
 * 4.左指针右移后交换两个指针指向的值,
 * 5.重复234直到右指针走到边界,
 * 这样就完成了一趟排序,
 * 因为前指针永远指向的是<=参照值的值,
 * 交换参照值和前指针指向的位置的值,
 * 再继续以前指针会分割线开始排序
 *
 * */
void sort_fast_pointer(int *arr, int size)
{
	assert(size > 1);
	int front = 0;
	int back = 0;
	int now_left = 0;
	int now_right = size - 1;
	std::stack<int> find_stack;
	while(back < now_right || find_stack.size() > 0)
	{
		while(back >= now_right)
		{
			if(find_stack.size() < 1)
				return;
			now_right = find_stack.top();
			find_stack.pop();
			now_left = find_stack.top();
			find_stack.pop();
			front = now_left;
			back = now_left;
		}
		while(back++ < now_right)
		{
			if(arr[back] <= arr[now_left])
			{
				front++;
			}
			else
			{
				break;
			}
		}
		while(back++ < now_right)
		{
			if(arr[back] <= arr[now_left])
			{
				front++;
				swap(arr,front,back);
			}
		}
		swap(arr,now_left,front);
		find_stack.push(now_left);
		find_stack.push(front - 1);
		find_stack.push(front + 1);
		find_stack.push(now_right);
	}
}

void sort_fast_lua(int* arr, int low, int upper)
{
	while(low < upper)
	{
		int i,j;
		if(sort_cmp(arr,upper,low))
		{
			swap(arr,low,upper);
		}
		if(upper - low == 1) return; //only tow elems
		i = (low + upper)/2;
		if(sort_cmp(arr,i,low)) //cmp with first
		{
			swap(arr,low,i);
		}
		else if(sort_cmp(arr,upper,i)) //cmp with last
		{
			swap(arr,i,upper);
		}
		if(upper - low == 2) return; //only three elems
		swap(arr,i,upper-1);
		i = low;
		j = upper - 1;
		int pivot = j;
		for(;;)
		{
			while(sort_cmp(arr,++i,pivot)); //find pos from low + 1 to upper - 1 which val is bigger than arr[pivot]
			while(sort_cmp(arr,pivot,--j)); //find pos from upper - 2 to low which val is smaller than arr[pivot]
			if(i > j) //not found
				break;
			swap(arr,i,j); //change tow sentrys
		}
		swap(arr,i,pivot); //mv pivot to a pos, which pos's left vals are all less than arr[pivot] and the right vals are all bigger than arr[pivot]
		if(i - low < upper - i)
		{
			j = i - 1;
			i = low;
			low = j + 2; //means old_i + 1
		}
		else
		{
			i = i + 1;
			j = upper;
			upper = i - 2;
		}
		sort_fast_lua(arr,i,j);
	}
}

bool sort_cmp(int *arr, int i, int j)
{
	return arr[i] < arr[j];
}

void swap(int* arr, int i, int j)
{
	if(i == j)
		return;
	arr[i] = arr[i]^arr[j];
	arr[j] = arr[i]^arr[j];
	arr[i] = arr[i]^arr[j];
	/*std::cout<<"-----------------"<<std::endl;*/
	//for(i = 0; i < size; i++)
	//{
		//std::cout<<arr[i]<<" ";
	//}
	/*std::cout<<std::endl;*/
}

//-------------------------test func-------------------
void test_sentry_front()
{
	int *arr = get_rand_arr(size);
	int i;
	for(i = 0; i < size; i++)
	{
		//std::cout<<arr[i]<<" ";
	}
	//std::cout<<std::endl;
	std::cout<<"arr已经装填完毕，装填数量为: "<<size<<std::endl;
	time_t start = clock();
	sort_fask_sentry_front(arr,size);
	std::cout<<"cost time: "<<clock() - start<<std::endl;
	for(i = 0; i < size; i++)
	{
		//std::cout<<arr[i]<<" ";
	}
	//std::cout<<std::endl;
}

void test_sentry_back()
{
	int *arr = get_rand_arr(size);
	int i;
	for(i = 0; i < size; i++)
	{
		//std::cout<<arr[i]<<" ";
	}
	//std::cout<<std::endl;
	std::cout<<"arr已经装填完毕，装填数量为: "<<size<<std::endl;
	time_t start = clock();
	sort_fask_sentry_back(arr,size);
	std::cout<<"cost time: "<<clock() - start<<std::endl;
	for(i = 0; i < size; i++)
	{
		//std::cout<<arr[i]<<" ";
	}
	//std::cout<<std::endl;
}

void test_wakeng()
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
	sort_fask_wakeng(arr,size);
	std::cout<<"cost time: "<<clock() - start<<std::endl;
	/*for(i = 0; i < size; i++)*/
	//{
		//std::cout<<arr[i]<<" ";
	//}
	/*std::cout<<std::endl;*/
}

void test_pointer()
{
	int *arr = get_rand_arr(size);
	/*int i;*/
	//for(i = 0; i < size; i++)
	//{
		//std::cout<<arr[i]<<" ";
	//}
	/*std::cout<<std::endl;*/
	std::cout<<"arr已经装填完毕，装填数量为: "<<size<<std::endl;
	time_t start = clock();
	sort_fast_pointer(arr,size);
	std::cout<<"cost time: "<<clock() - start<<std::endl;
	/*for(i = 0; i < size; i++)*/
	//{
		//std::cout<<arr[i]<<" ";
	//}
	/*std::cout<<std::endl;*/
}

void test_lua()
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
	sort_fast_lua(arr,0,size - 1);
	std::cout<<"cost time: "<<clock() - start<<std::endl;
	//for(i = 0; i < size; i++)
	//{
		//std::cout<<arr[i]<<" ";
	//}
	/*std::cout<<std::endl;*/
}

void test_find_k()
{
	int *arr = get_rand_arr(size);
	int i;
	std::cout<<"arr已经装填完毕，装填数量为: "<<size<<std::endl;
	time_t start = clock();
	int val = get_max_k(arr,size, size/3);
	std::cout<<"val: "<<val<<std::endl;
	time_t cost_clock = clock() - start;
	double sec = (double)cost_clock/CLOCKS_PER_SEC;
	std::cout<<"clock: "<<cost_clock<<"; cost time: "<<sec<<std::endl;
}
