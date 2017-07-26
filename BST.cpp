// BST.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include<vector>

using namespace std;

struct node{
	int info;
	node *left;
	node *right;
	
};

//insert node in a BST
node* insert(node *root, int k){

	if(root == NULL){

		root=new node();
	    root->info=k;
	    root->left=NULL;
	    root->right=NULL;
	}
	else
	{
		if(root->info==k){
			cout<<"\nduplicate key";
		}
		else if (k < root->info)
		root->left = insert(root->left,k);
		
		else
		root->right= insert(root->right,k);

	}
	return root;
};

//find predecessor node of root
node* findPred(node *root){

    if(root->right == NULL){
		return root;
	}
	else{
		return findPred(root->right);
	}
}

//height of the BST
int height(node *root){

	if(root == NULL)return 0;

	if(root->left == NULL){
		return 1+height(root->right);
	}
	else if(root->right == NULL){
		return 1+height(root->left);
	}
	else
		return 1+ max(height(root->left), height(root->right));

}

//delete node from BST with given value k
node* deleteNode(node  *root, int k){

	if(root==NULL){
		cout<<"element does not exist\n";
		return NULL;
	}
	if(k < root->info){
		root->left = deleteNode(root->left,k);
	}
	else if(k > root->info){
		root->right = deleteNode(root->right,k);
	}
	else{

		if(root->left == NULL){
		   node *temp=root->right;
		   delete(root);
		   return temp;

		}
		else if(root->right == NULL){
		node *temp=root->left;
		delete(root);
		return temp;

		}		
		else{
			node *pred = findPred(root->left);
			root->info = pred->info;
			root->left = deleteNode(root->left,root->info);		
		}

	}

	return root;

}

//search for a node with value k in BST 
void search(node *root, int k){

	if(root==NULL){
		cout<<"key not found\n";
		return;
	}

	if(k < root->info){
	return search(root->left,k);

	}
	else if(k > root->info){
		return search(root->right,k);
	}
	else{
		cout<<"\nkey found "<<k;
	    return;	
	}
}

//find's kth smallest element in BST using inorder traversal
void findKthSmallestInorder(node *root, int k){
	static int count=1;

	if(root == NULL)return;

	findKthSmallestInorder(root->left,k);


	if(count == k){
		cout<<root->info<<" ";	
		count++;
	    return;
	}
    count++;	

	findKthSmallestInorder(root->right,k);
	
}


void findKthLargestInorder(node *root, int k){
	static int count=1;

	if(root == NULL)return;

	findKthLargestInorder(root->right,k);
	if(count == k){
		cout<<root->info<<" ";	
		count++;
	    return;
	}
    count++;	

	findKthLargestInorder(root->left,k);
	
}

//display all paths from root with the given sum
void sumFromRoot(node *root, vector<int>path, int sum){

	if(root == NULL)return;		

	if(sum >= root->info){
		sum=sum-root->info;
		path.push_back(root->info);

		if(sum == 0){
		
		for(int i=0; i<path.size(); i++)
		     cout<<" "<<path[i];		 
				
	}				
	else{
		 sumFromRoot(root->left, path, sum);
	     sumFromRoot(root->right, path, sum);
	  }	
  }				
	
}

//print all paths from any node to any node in BST that sum upto k
void printAllKSumPaths(node *root, vector<int>&path, int k){

	if(root == NULL)return;

	path.push_back(root->info);

	printAllKSumPaths(root->left, path, k);

	printAllKSumPaths(root->right, path, k);

	int sum=0;

	for(int i=path.size()-1; i>=0; i--){
		sum+=path[i];

		if(sum == k){
			cout<<"\n path found \n";
			for(int j=i; j<path.size(); j++){
				cout<<path[j]<<" ";
			}
		}		
	}

	path.pop_back();

}

//inorder traversal of BST
void inorder(node *root){

	if(root==NULL)return;
	
	else{

	   inorder(root->left);
	   cout<<root->info<<"\n";
	   inorder(root->right);
	}	
}

int _tmain(int argc, _TCHAR* argv[])
{
	node *root=NULL;
	int k,sum;

	root=insert(root,8);
	root=insert(root,3);
	root=insert(root,11);
	root=insert(root,9);
	root=insert(root,13);
	root=insert(root,1);
	root=insert(root,5);
	root=insert(root,7);

	inorder(root);

	cout<<"\n height of this BST "<<height(root);

	cout<<"\n enter sum to print all paths in a tree ";
	cin>>sum;

	vector<int>path;	
	printAllKSumPaths(root,path,sum);
	
	//sumFromRoot(root,path,sum);
	/*cout<<"\n enter k to find the kth smallest key";
	cin>>k;

	findKthSmallestInorder(root, k);

	cout<<"\n enter k to find the kth largest key";
	cin>>k;

	findKthLargestInorder(root, k);

	cout<<"\n height of this BST "<<height(root);*/


	search(root,13);
	search(root,4);	

	return 0;
}

