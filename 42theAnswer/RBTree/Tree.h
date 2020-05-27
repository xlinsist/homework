
/**************************************************************
*	Include File Section
**************************************************************/

#include "main.h"

/**************************************************************
*	Macro Define Section
**************************************************************/
#define HAVE_BEEN_CREATED 1    // 平衡二叉树已经创建
#define NOT_CREATED 0         // 平衡二叉树未创建

/**************************************************************
*	Struct Define Section
**************************************************************/
typedef int ValueType;
typedef int ElementType;

typedef enum ColorSet
{
    RED = 0,
    BLACK = 1
} ColorSet;

typedef struct TreeNode
{
    struct TreeNode *lchild, *rchild; 
    ValueType val;   //value of node
    ElementType num; //number of node
    
    struct TreeNode *parent;
    ColorSet col;    //col of node(back or red)

} TreeNode;

/**************************************************************
*	Prototype Declare Section
**************************************************************/

//打印整棵树 
void ConcaveTablePrint(TreeNode *T, int m);

void ParenthesisPrint(TreeNode *T);

/*------------------------------------------------------------*/

void visit(TreeNode* T) ;//打印单个节点信息 

//遍历，前中后 
void PreOrderTraverse(TreeNode* T) ;

void InOrderTraverse(TreeNode* T) ;

void PostOrderTraverse(TreeNode* T) ;

/*------------------------------------------------------------*/

void rb_create(TreeNode *&root);//创建平衡树 

void rb_destroy(TreeNode *&root);//销毁平衡树 

void rb_insert(ValueType val, ElementType num, TreeNode* &root);//若给定权值不存在，插入权值 

TreeNode *rb_search(ValueType val, TreeNode* &root);//返回指向给定权值的指针，或返回NULL若权值不存在 

void rb_erase(ValueType val, TreeNode* &root);//若给定权值存在，删除该权值 


