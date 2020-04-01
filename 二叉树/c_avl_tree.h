#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

#include <stdlib.h>
#include <time.h>
#include <iostream>

using std::cout;
using std::endl;

template<class T>
class CAvltree
{
	public:
		explicit CAvltree(T& key);
		~CAvltree();
	private:
		CAvltree(){};
	public:
		struct avlnode
		{
			T key;
			int hight;
			struct avlnode* left;
			struct avlnode* right;

			avlnode(T& _key):key(_key),hight(-1){}

		};
	private:
		void freeInerNode(avlnode *);
		avlnode* findInerNode(avlnode*,T&);
		int getHight(avlnode*);
		avlnode* addInerNode(avlnode*, T&);
		avlnode* leftRotate(avlnode* pare_node,avlnode* chil_node);
		avlnode* rightRotate(avlnode* pare_node,avlnode* chil_node);
		void dropInerNode(avlnode*, T&);
		avlnode* findMinNode(avlnode*);
		avlnode* findMaxNode(avlnode*);

	public:
		avlnode* findNode(T &key);
		int updateNode(T &key, T &val); //更新节点值 成功返回 0
		avlnode* addNode(T &key);
		void dropNode(T &key);

	public:
		//先序遍历
		void showFront(avlnode*);
		//中序遍历
		void showMiddle(avlnode*);
		//后序遍历
		void showBack(avlnode*);

	private:
		avlnode* m_root;

};

template<typename T>
CAvltree<T>::CAvltree(T &key){
	m_root = new avlnode(key);
}

template<typename T>
CAvltree<T>::~CAvltree(){
	if(m_root)
		freeInerNode(m_root);
}

template<typename T>
void CAvltree<T>::freeInerNode(avlnode* pnode){
	if(pnode==nullptr)
	{
		return;
	}
	freeInerNode(pnode->left);
	freeInerNode(pnode->right);
	delete pnode;
	pnode = nullptr;
}

template<typename T>
typename CAvltree<T>::avlnode* CAvltree<T>::CAvltree::findNode(T &key){
	return findInerNode(m_root,key);
}

template<typename T>
typename CAvltree<T>::avlnode* CAvltree<T>::findInerNode(avlnode* node,T& _key){
	if(node == nullptr) //没有匹配的节点
		return node;
	if(node->key == _key)
	{
		return node;
	}
	else if(node->key > _key)
	{
		return findInderNode(node->left);
	}
	else if(node->key < _key)
	{
		return findInderNode(node->right);
	}
}

template<typename T>
int CAvltree<T>::updateNode(T &key, T &val){
	avlnode* node = findNode(key);
	if(node != nullptr)
	{
		node->key = val;
		return 0;
	}
	return 1;
}

template<typename T>
typename CAvltree<T>::avlnode* CAvltree<T>::addNode(T &_key){
	avlnode* new_node = addInerNode(m_root, _key);
	cout<<"front show: "<<endl;
	showFront(nullptr);
	return new_node;
}

template<typename T>
void CAvltree<T>::dropNode(T &key){
	if(m_root == nullptr)
		return;
	dropInerNode(m_root,key);
}

template<typename T>
int CAvltree<T>::getHight(avlnode* node){
	if(node == nullptr)
		return -1;
	int left_hight = getHight(node->left);
	int right_hight = getHight(node->right);
	int hight = left_hight>right_hight?left_hight:right_hight;
	return hight+1;
}

template<typename T>
typename CAvltree<T>::avlnode* CAvltree<T>::addInerNode(avlnode* node, T& _key){
	if(node == nullptr)
	{
		avlnode* new_node = new avlnode(_key);
		return new_node;
	}
	if(node->key > _key){
		node->left = addInerNode(node->left,_key);
		if(getHight(node->left) - getHight(node->right) == 2) //因为每次只执行一次插入 所以高度最大增长1
		{
			if(_key < node->left->key){ //左左 只需要单右旋 下降父节点 提升左子节点
				rightRotate(node,node->left);
			}
			else if(_key > node->left->key) //左右 先子节点和孙子节点单左旋 然后父节点和新子节点单右旋
			{
				leftRotate(node->left,node->left->right);
				rightRotate(node,node->left);
			}
		}
	}
	else if(node->key < _key)
	{
		node->right = addInerNode(node->right,_key);
		if(getHight(node->right) - getHight(node->left) == 2) //因为每次只执行一次插入 所以高度最大增长1
		{
			if(_key > node->right->key){ //右右 只需要单左旋 下降父节点 提升右子节点
				leftRotate(node,node->right);
			}
			else if(_key < node->right->key) //右左 先子节点和孙子节点单右旋 然后父节点和新子节点单左旋
			{
				rightRotate(node->right,node->right->right);
				leftRotate(node,node->right);
			}
		}
	}

	return node;
}

template<typename T>
typename CAvltree<T>::avlnode* CAvltree<T>::leftRotate(avlnode* pare_node,avlnode* chil_node){
	int temp = 0;
	avlnode* old_parent_cont = new avlnode(temp);
	*old_parent_cont = *pare_node;
	*pare_node = *chil_node;
	*chil_node = *old_parent_cont;
	chil_node->right = pare_node->left;
	pare_node->left = chil_node;
	return pare_node;
}

template<typename T>
typename CAvltree<T>::avlnode* CAvltree<T>::rightRotate(avlnode* pare_node,avlnode* chil_node){
	avlnode* old_parent_cont;
	*old_parent_cont = *pare_node;
	*pare_node = *chil_node;
	*chil_node = *old_parent_cont;
	chil_node->left = pare_node->right;
	pare_node->right = chil_node;
	return pare_node;
}

template<typename T>
void CAvltree<T>::dropInerNode(avlnode* node, T& _key){
	if(node->key < _key)
	{
		if(node->left == nullptr)
		{
			return;
		}
		dropInerNode(node->left,_key);
		if(getHight(node->right) - getHight(node->left) == 2) //因为每次只执行一次插入 所以高度最大增长1
		{
			if(node->right->left != nullptr)
			{
				//右左旋转
				rightRotate(node->right,node->right->left);
				leftRotate(node,node->right);
			}
			else
			{
				//右右旋转
				rightRotate(node,node->right);
			}
		}
	}
	else if(node->key > _key)
	{
		if(node->right == nullptr)
		{
			return;
		}
		dropInerNode(node->right,_key);
		if(getHight(node->left) - getHight(node->right) == 2) //因为每次只执行一次插入 所以高度最大增长1
		{
			if(node->left->right != nullptr)
			{
				//左右旋转
				leftRotate(node->left,node->left->right);
				rightRotate(node,node->left);
			}
			else
			{
				//左左旋转
				leftRotate(node,node->left);
			}
		}
	}
	else if(node->left && node->right)
	{
		avlnode* temp = findMaxNode(node->left);
		node->key = temp->key;
		dropInerNode(node->left,temp->key);
	}
	else{
		avlnode* temp;
		if(node->left)
		{
			temp = node->left;
			*node = *node->left;
		}
		else
		{
			temp = node->right;
			*node = *node->right;
		}
		delete temp;
	}
}

template<typename T>
typename CAvltree<T>::avlnode* CAvltree<T>::findMinNode(avlnode* node){
	if(node->left == nullptr)
		return node;
	else
		return findMinNode(node->left);
}

template<typename T>
typename CAvltree<T>::avlnode* CAvltree<T>::findMaxNode(avlnode* node){
	if(node->right == nullptr)
		return node;
	else
		return findMinNode(node->right);
}

template<typename T>
void CAvltree<T>::showFront(avlnode* node){
	//cout<<"<---------- begin show front ------------>"<<endl;
	if(m_root == nullptr)
		return;
	if(node == nullptr)
		node = m_root;
	cout<<node->key<<endl;
	if(node->left)
		showFront(node->left);
	if(node->right)
		showFront(node->right);
}

template<typename T>
void CAvltree<T>::showMiddle(avlnode* node){
	cout<<"<---------- begin show middle ------------>"<<endl;
	if(m_root == nullptr)
		return;
}

template<typename T>
void CAvltree<T>::showBack(avlnode* node){
	cout<<"<---------- begin show back ------------>"<<endl;
	if(m_root == nullptr)
		return;
}

#endif
