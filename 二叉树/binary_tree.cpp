#include<iostream>

#include"binary_tree.h"

int main(){
	using std::cout;
	using std::endl;

	int a =6;
	int b =2;
	int c =8;
	int d =1;
	int e =4;
	int f =3;
	CBinaryTree<int>* my_tree = new CBinaryTree<int>(a);
	my_tree->insertNode(b,nullptr);
	my_tree->insertNode(c,nullptr);
	my_tree->insertNode(d,nullptr);
	my_tree->insertNode(e,nullptr);
	my_tree->insertNode(f,nullptr);
	my_tree->showNodes(nullptr);

	CBinaryTree<int>::node* min_node = my_tree->findMinNode(nullptr);
	CBinaryTree<int>::node* max_node = my_tree->findMaxNode(nullptr);
	if(min_node)
		cout<<"min_node: "<<min_node->key<<endl;
	if(max_node)
		cout<<"max_node: "<<max_node->key<<endl;

	return 0;
}
