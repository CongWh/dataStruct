#include <iostream>

using namespace std;
typedef int TElemType; 

typedef struct BiTNode{
	TElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree; 


/*
二叉排序树原理： 一个空树遇到第一个树时，将它作为根 root。再次插入数值 key 后，与根结点进行比较，
若 key > root ，则向根的右子树比较，反之向根的左子树比较。依次与路上的各个结点比较。最终的排序树
的顺序为二叉树中序遍历。 
*/


// 查找 
int BST(BiTree T, BiTree parent, int key, BiTree *p){
	if (!T){
		*p = parent;  // 主要用来作其他操作的使用条件，*p 只是一个结点，非一个树结构 
		return 0;
	}
	else if (key < T->data){
		BST(T->lchild,T,key,&(*p));
	}
	else if (key > T->data){
		BST(T->rchild,T,key,&(*p));
	}
	else if (key == T->data){
		*p = T;
		return 1;
	}
}

// 查找，非递归 
int BST2(BiTree T, BiTree f, int key, BiTree *p){

	BiTree s;	// 指向上一结点 
	if(!T){	
		*p = f;		
		return 0;	
	}
	while(T){
		if(key == T->data){	
			*p = T;		
			return 1;	
		}
		if(key > T->data){	
			s = T;	
			T = T->rchild;		
		}
		else{	
			s = T;	
			T = T->lchild;		
		}
	}
	*p = s;
	return 0;

}

int InsertBST(BiTree *T,int key){
	BiTree p = NULL, s = NULL;

	if (!BST(*T,NULL,key,&p)){		// 若没有，此时 p 指向的是最后一个结点 

		s = (BiTree)malloc(sizeof(BiTNode));
		s->data = key;	// 创建结点 key
		s->lchild = s->rchild = nullptr;	// 不是递归，需要手动初始化左右子树 
		if (!p){	// 先判断是否为空 
			*T = s;
		} 		
		else if (key > p->data){
			p->rchild = s;
		} 
		else{
			p->lchild = s;
		}

		return 1;
	}
	return 0;	
}

int Delete(BiTree *p){	// 删除某结点 （需要嫁接其左右子树） 
	if (!(*p))
		return 0;
	BiTree s = *p;
	if (!(*p)->lchild){		// 删除结点简单情况：只有左子树或右子树 
		(*p) = (*p)->rchild;
		free(s);
	}
	else if (!(*p)->rchild){
		(*p) = (*p)->lchild;
		free(s);
	}	
	else{		// 左右子树都存在，找其前驱（得到最相近的数，这样深度不会增加） 
		s = (*p)->lchild;	// 中序遍历的特点 前驱为该结点，否则在其右子树中
		BiTree tmp = *p;
		if (!s->rchild){	// 判断斜树:若左斜则lchild为前驱 
			*p = s;
			free(tmp);
			return 1;
		}
		while (s->rchild){	// 否则，再找最右端的结点，该点为前驱 
			tmp = s;
			s = s->rchild;
		} 
		(*p)->data = s->data;
		if (s->lchild){
			tmp->lchild = s->lchild;
			free(s);
		}
	} 
	return 1;
}

int DeleteBST(BiTree *T, int key)
{
	if(!(*T))
		return 0;	// 不存在关键字等于key的数据元素 
	else{
		if( key == (*T)->data )
			Delete(T);
		else if( key < (*T)->data)
			DeleteBST(&(*T)->lchild, key);
		else
			DeleteBST(&(*T)->rchild, key);
	}
}

// 中序遍历： 简化为三角形，遍历顺序 左子树-->顶点-->右子树
void InOrderTraverse(BiTree T){
	if (T == NULL)
		return ;
	InOrderTraverse(T->lchild);
	printf("%d ", T->data);
	InOrderTraverse(T->rchild);
} 

int main(){
	BiTree p = NULL,T = NULL;
	int key = 51, n = 10;
	int i;
	int a[10] = {62,88,58,47,35,73,51,99,37,93};
	for( i = 0; i < n; i++ )
		InsertBST(&T, a[i]);

	printf("中序遍历二叉排序树：\n");
	InOrderTraverse(T);
	printf("\n");
	printf("删除51后，中序遍历二叉排序树：\n");
	DeleteBST(&T,key);
	InOrderTraverse(T);
	return 0;
}

