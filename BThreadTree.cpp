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
#include <stack>

using namespace std;

typedef char TElemType;
typedef enum{link, thread} PointTag;

typedef struct BThrNode{
	TElemType val;
	PointTag ltag, rtag;
	struct BThrNode *lchild, *rchild;
}BThrNode, *BThrTree;

// 上一结点 
BThrTree pre;
 

// 前序遍历线索化：递归线索化 
// 由于前序遍历是从根结点开始，而线索化主要出现在两层以后，
//  
void PreThrTraverse(BThrTree T){
	if (T){
		if (!T->lchild){
			T->ltag = thread;
			T->lchild = pre;
		}
		if (!pre->rchild){
			pre->rtag = thread;
			pre->rchild = T;
		}
		pre = T;
		if (T->ltag == link)	// 防止叶子结点的前驱被当成子树 
			PreThrTraverse(T->lchild);
		if (T->rtag == link)
			PreThrTraverse(T->rchild);
	}
} 

void PreThreading(BThrTree *t, BThrTree T){
	*t = (BThrTree)malloc(sizeof(BThrNode));		// 创建一个头结点
	(*t)->ltag = link;
	(*t)->rtag = thread;
	(*t)->rchild = *t;	// 后继暂时指向自己 
	if (T == NULL){
		(*t)->lchild = *t;
	}
	else{
		pre = *t;
		(*t)->lchild = T;
		PreThrTraverse(T);
		pre->rtag = thread;		// 最后一个结点后继为头结点，遍历时可作判断条件**** 
		pre->rchild = *t;
		(*t)->rchild = pre;		// 头结点的后继为最后一个结点（它的左子树为根结点） 
	} 

}

/*
二叉树前序遍历输出 
思路：由于前序二叉树的遍历顺序为  顶点-->左子树-->右子树，则直接开始输出，
先找左子树，左子树找不到后直接找其右子树（包含后继） 
*/ 
void PreThrOrderTraverse(BThrTree T){
	BThrTree p = T->lchild;	// p指向根结点
	while (p != T){
		printf ("%c", p->val);
		if (p->ltag == link)
			p = p->lchild;
		else
			p = p->rchild;		
	}	
}

// 中序遍历线索化：递归线索化 
void InThrTraverse(BThrTree T){		//  
	if (T){
		InThrTraverse(T->lchild);	// 到叶子结点尽头 
		if (!T->lchild){	// 判断是否有左子树，若无则设置前驱 
			T->ltag = thread;
			T->lchild = pre;
		}
		if (!pre->rchild){	
			pre->rtag = thread;
			pre->rchild = T;
		}
		pre = T;
		InThrTraverse(T->rchild);
	}
}
/*
中序遍历线索化
需设立一个头结点（左子树指向根结点，右子树为后继，指向树遍历的最后一个结点） 
*/
void InThreading(BThrTree *t, BThrTree T){
	*t = (BThrTree)malloc(sizeof(BThrNode));		// 创建一个头结点
	(*t)->ltag = link;
	(*t)->rtag = thread;
	(*t)->rchild = *t;	// 后继暂时指向自己 
	if (T == NULL){
		(*t)->lchild = *t;
	}
	else{
		pre = *t;
		(*t)->lchild = T;
		InThrTraverse(T);
		pre->rtag = thread;		// 最后一个结点后继为头结点，遍历时可作判断条件**** 
		pre->rchild = *t;
		(*t)->rchild = pre;		// 头结点的后继为最后一个结点（它的左子树为根结点） 
	} 

}

/*
二叉树中序遍历输出 
思路：由于中序二叉树的遍历顺序为  左子树-->顶点-->右子树，则先找到尽头的左子树，
输出，若 rtag = link，则存在右子树，输出右子树（此时左子树看作顶点）。若 rtag =
thread，由于该二叉树线索化了，则右子树指向后继，指针往后进即可。 
*/ 
void InThrOrderTraverse(BThrTree T){
	BThrTree p = T->lchild;	// p指向根结点
	while (p != T){
		while (p->ltag == link){
			p = p->lchild;
		} 
		printf ("%c", p->val);
		while ((p->rtag == thread) && (p->rchild != T)){	// 当p有后继且后继不是头结点 
			 p = p->rchild;
			 printf ("%c", p->val);
		}
		p = p->rchild;		
	}	
}



// 后序遍历线索化：递归线索化 
void PostThrTraverse(BThrTree T){		//  
	if (T){
		InThrTraverse(T->lchild);	// 到叶子结点尽头
		InThrTraverse(T->rchild);
		if (!T->lchild){	// 判断是否有左子树，若无则设置前驱 
			T->ltag = thread;
			T->lchild = pre;
		}
		if (!pre->rchild){	
			pre->rtag = thread;
			pre->rchild = T;
		}
		pre = T;
	}
}
/*
后序遍历线索化
需设立一个头结点（左子树指向根结点，右子树为后继，指向树遍历的最后一个结点） 

*/
void PostThreading(BThrTree *t, BThrTree T){
	*t = (BThrTree)malloc(sizeof(BThrNode));		// 创建一个头结点
	(*t)->ltag = link;
	(*t)->rtag = thread;
	(*t)->rchild = *t;	// 后继暂时指向自己 
	if (T == NULL){
		(*t)->lchild = *t;
	}
	else{
		pre = *t;
		(*t)->lchild = T;
		PostThrTraverse(T);
		pre->rtag = thread;		// 最后一个结点后继为头结点，遍历时可作判断条件**** 
		pre->rchild = *t;
		(*t)->rchild = pre;		// 头结点的后继为最后一个结点（它的左子树为根结点） 
	} 

}

/*
二叉树后序遍历输出 
思路：由于中序二叉树的遍历顺序为  左子树-->右子树-->顶点，则先找到尽头的左子树，
输出，若 rtag = link，则存在右子树，输出右子树（此时左子树看作顶点）。若 rtag =
thread，由于该二叉树线索化了，则右子树指向后继，指针往后进即可。 
*/ 
void PostThrOrderTraverse(BThrTree T){
	BThrTree p = T->lchild;	// p指向根结点
	while (p != T){
		while (p->ltag == link && p->lchild != pre) {
			p = p->lchild;
		} 
		while (p->rtag == link && p->rchild != pre){
			p = p->rchild;
		} 
		if ((p->rtag == thread) && (p->rchild != T)){	// 当p有后继且后继不是头结点 
			 printf ("%c", p->val);
			 pre = p;
			 p = p->rchild;
			 
		}

//		p = p->rchild;
//		printf ("%c", p->val);
				
	}	
}






// 前序遍历创建线索树 
void CreateBiTree(BThrTree *T){

	char c;
	scanf("%c", &c);
	if (c == '#'){
		*T = NULL;
		return;
	}	
	else{
		*T = (BThrTree)malloc(sizeof(BThrNode));
		(*T)->val = c;
		(*T)->ltag = link;
		(*T)->rtag = link;
	} 
	CreateBiTree(&(*T)->lchild);
	CreateBiTree(&(*T)->rchild);
}

void delBiTree(BThrTree *T){
	if (*T){
		delBiTree(&(*T)->lchild);
		delBiTree(&(*T)->rchild);
		free(*T);
		*T = nullptr;		
	}
}


int main(int argc, char *argv[])
{
	BThrTree T = NULL,t = NULL;
	printf("请前序遍历输入结点：");
	CreateBiTree(&T);
	printf("中序遍历线索化后输入结点：");
	InThreading(&t,T);
	InThrOrderTraverse(t);
	delBiTree(&T);
	delBiTree(&t);
/*
	printf("前序遍历线索化后输入结点：");
	PreThreading(&t,T);
	PreThrOrderTraverse(t);
	delBiTree(&T);
	delBiTree(&t); */
/*	
	printf("后序遍历线索化后输入结点：");
	PostThreading(&t,T);
	PostThrOrderTraverse(t);
	delBiTree(&T);
	delBiTree(&t); */
	return 0;
}

