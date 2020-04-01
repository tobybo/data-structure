#include <iostream>
#include "c_avl_tree.h"

using std::cout;
using std::endl;

int main(){
	int a[] = {10,1,11,3,7,50,4,5};
	CAvltree<int> *avl_tree = new CAvltree<int>(a[0]);
	avl_tree->addNode(a[1]);
	avl_tree->addNode(a[2]);
	avl_tree->addNode(a[3]);
	avl_tree->addNode(a[4]);
	avl_tree->addNode(a[5]);
	avl_tree->addNode(a[6]);
	avl_tree->addNode(a[7]);
	return 0;
}
