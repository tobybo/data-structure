#include "min_heap.h"
#include "time.h"
#include "stdlib.h"

#include <iostream>

int main()
{
	CMinHeap<int> heap;
	time_t t;
	int rand_num;
	srand((unsigned)time(&t));
	for(int i = 0; i < 10; i++){
		rand_num = rand()%100000;
		std::cout<<rand_num<<std::endl;
		heap.pushNode(rand_num);
	}
	heap.showTree();
	std::cout<<heap.getRoot()<<std::endl;
	heap.dropNode();
	heap.showTree();
	//heap.pushNode(1);
	//heap.showTree();
	//heap.pushNode(2);
	//heap.showTree();
	//heap.pushNode(3);
	/*heap.showTree();*/
	return 0;
}
