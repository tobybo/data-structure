#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#include <stdlib.h>
#include <time.h>
#include <iostream>
using std::cout;
using std::endl;

template <class T>
class CBinaryTree
{
	public:
		struct node{
			T key;
			struct node* left;
			struct node* right;
			node(T& _key){
				key = _key;
				left = nullptr;
				right = nullptr;
			};
		};
	private:
		node* m_root;
	public:
		explicit CBinaryTree(T& key);
		~CBinaryTree();
		//增加节点
		void insertNode(T& key,node*);
		//删除节点
		void dropNode(T& key,node*&);
		//查找节点
		node* findNode(T& key, node*);
		//查找最小节点
		node* findMinNode(node*);
		//查找最大节点
		node* findMaxNode(node*);
		//释放所有节点的内存
		void freeNodes(node*);
		//打印所有节点的值
		void showNodes(node*);
};

template <typename T>
CBinaryTree<T>::CBinaryTree(T& key){
	m_root = new node(key);
	cout<<"insert first: "<<key<<", rootkey: "<<m_root->key<<endl;
	time_t t;
	srand((unsigned)time(&t));
}

template <typename T>
CBinaryTree<T>::~CBinaryTree(){
	freeNodes(m_root);
}

template <typename T>
void CBinaryTree<T>::freeNodes(node* root){
	if(!root)
		return;
	if(root->left)
	{
		freeNodes(root->left);
	}
	else
	if(root->right){
		freeNodes(root->left);
	}
	else{
		delete root;
		root = nullptr;
	}
}

template <typename T>
void CBinaryTree<T>::insertNode(T& key,node* root){
	if(!m_root)
	{
		m_root = new node(key);
		cout<<"insert first: "<<key<<", rootkey: "<<m_root->key<<endl;
	}
	else{
		if(!root)
			root = m_root;
		if(root->key > key){
			if(!root->left){
				root->left = new node(key);
			}
			else{
				insertNode(key,root->left);
			}
		}
		else
		if(root->key < key){
			if(!root->right){
				root->right = new node(key);
			}
			else{
				insertNode(key,root->right);
			}
		}
	}
}

template <typename T>
void CBinaryTree<T>::dropNode(T& key,node*& root){
	node* temp = nullptr;
	if(!m_root)
		return;
	if(!root)
		root = m_root;
	if(root->key > key){
		if(!root->left) return;
		dropNode(key,root->left);
	}
	else
	if(root->key < key){
		if(!root->right) return;
		dropNode(key,root->right);
	}
	else
	if(root->left&&root->right)
	{
		int i = rand()%2;
		if(i)
			temp = findMinNode(root->right);
		else
			temp = findMaxNode(root->left);
		root->key = temp->key;
		if(i)
			dropNode(temp->key,root->right);
		else
			dropNode(temp->key,root->left);
	}
	else
	{
		if(root->left)
			temp = root->left;
			*root = *root->left;
		else
		{
			temp = root->left;
			*root = *root->right;
		}
		delete temp;
	}
}

template <typename T>
typename CBinaryTree<T>::node* CBinaryTree<T>::findNode(T& key,node* root){
	if(!m_root)
		return m_root;
	if(!root)
		root = m_root;
	if(root->key == key)
		return root;
	else
	if(root->key > key){
		if(!root->left){
			return root->left;
		}
		else
			return findNode(key,root->left);
	}
	else
	if(root->key < key){
		if(!root->right){
			return root->right;
		}
		else
			return findNode(key,root->right);
	}
	return nullptr;
}

template <typename T>
typename CBinaryTree<T>::node* CBinaryTree<T>::findMinNode(node* root){
	if(!root)
		root = m_root;
	if(!root||!root->left){
		return root;
	}
	return findMinNode(root->left);
}

template <typename T>
typename CBinaryTree<T>::node* CBinaryTree<T>::findMaxNode(node* root){
	if(!root)
		root = m_root;
	if(!root||!root->right){
		return root;
	}
	return findMinNode(root->right);
}

template <typename T>
void CBinaryTree<T>::showNodes(node* root){
	if(!root)
		root = m_root;
	if(!root)
	{
		cout<<"no node"<<endl;
		return;
	}
	cout<<root->key<<endl;
	if(root->left)
	{
		showNodes(root->left);
	}
	if(root->right)
	{
		showNodes(root->right);
	}
}

#endif
