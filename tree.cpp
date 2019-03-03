#include <iostream>

using namespace std;


#define MAX_TREE_SIZE 100
typedef int TElemType;

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
}BiTNode, *BiTNode; 


//	树结构 
typedef struct{
	PTNode nodes[MAX_TREE_SIZE];
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


int main(){
	
	return 0;
}
