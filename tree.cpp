/*
Tree: 	
						A
				B				C
			D				E		F		
		 G	  H			  I	


前序遍历：ABDGHCEIF
前序输入：ABDG##H###CEI###F## 

*/
#include <iostream>
#include <queue>
using namespace std;


#define MAX_TREE_SIZE 100
typedef char TElemType;

// 双亲表示法 
struct PTNode{
	TElemType data;
	int parent;		// root's parent: -1
}PTNode;

// 双亲表示法扩展：增加长子域
typedef struct PTNode1{
	TElemType data;
	int parent;		
	int lchild;   // Not exist: -1 
}PTNode1; 

// 孩子表示法
typedef struct CLinkedList{
	TElemType data;
	TElemType *next;
}CLinkedList;

typedef struct CTNode{
	TElemType data;
	CLinkedList *firstChild;
}CTNode; 

// 兄弟表示法： 将复杂的树变成了二叉树
typedef struct BTNode{
	TElemType data;
	struct BTNode *firstChild, *rightBro;
}BTNode; 


// 二叉树的二叉链表
typedef struct BiTNode{
	TElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree; 


//	树结构 
typedef struct Tree{
	struct PTNode nodes[MAX_TREE_SIZE];
	int r, n;
};


// 先序遍历： 简化为三角形，遍历顺序 顶点-->左子树-->右子树
void PreOrderTraverse(BiTree T){
	if (T == NULL)
		return ;
	printf("%c",T->data);
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);
} 


// 中序遍历： 简化为三角形，遍历顺序 左子树-->顶点-->右子树
void InOrderTraverse(BiTree T){
	if (T == NULL)
		return ;
	InOrderTraverse(T->lchild);
	printf("%c", T->data);
	InOrderTraverse(T->rchild);
} 

// 后序遍历： 简化为三角形，遍历顺序 左子树-->右子树-->顶点
void PostOrderTraverse(BiTree T){
	if (T == NULL)
		return ;
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	printf("%c", T->data);
} 

// 层序遍历： 整个二叉树，从上到下、从左到右依次遍历。 
// 思路：建立一个队列，某一结点 A 先入队，A出队时则将它的孩子入队，反复进行。 
void LevelOrderTraverse(BiTree T){
	if (T == NULL)
		return;
	queue<BiTree> q;
	BiTree front; 
	q.push(T); 
	while (!q.empty()){
		front = q.front();
		q.pop();
		if (front->lchild)
			q.push(front->lchild);
		if (front->rchild)
			q.push(front->rchild);
		printf("%c", front->data);
	}
	
} 

// 前序遍历创建树 
void CreateBiTree_Pre(BiTree *T){
	char c;
	scanf("%c",&c);
	
	if (c == '#'){
		*T = NULL;
		return;
	}
	
	*T = (BiTree)malloc(sizeof(BiTNode));
	(*T)->data = c;
	
	CreateBiTree_Pre(&(*T)->lchild);
	CreateBiTree_Pre(&(*T)->rchild);
	return;	
}

// 释放二叉树的占用内存 
void delNode(BiTree *T) 
{
  if (*T == NULL) 
  	return;
  delNode(&(*T)->lchild);
  delNode(&(*T)->rchild);
  free(*T);
  *T = NULL; 
  return;
}

int main(int argc, char *argv[])
{
	BiTree T = NULL;
	printf("请前序遍历输入结点：");
	CreateBiTree_Pre(&T);
	printf("前序遍历：");
	PreOrderTraverse(T);
	printf("\n中序遍历：");
	InOrderTraverse(T);
	printf("\n后序遍历：");
	PostOrderTraverse(T);
	printf("\n层序遍历：");
	LevelOrderTraverse(T);
	delNode(&T);
	
	
	return 0;
}

