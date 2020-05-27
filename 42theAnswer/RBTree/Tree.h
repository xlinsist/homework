
/**************************************************************
*	Include File Section
**************************************************************/

#include "main.h"

/**************************************************************
*	Macro Define Section
**************************************************************/
#define HAVE_BEEN_CREATED 1    // ƽ��������Ѿ�����
#define NOT_CREATED 0         // ƽ�������δ����

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

//��ӡ������ 
void ConcaveTablePrint(TreeNode *T, int m);

void ParenthesisPrint(TreeNode *T);

/*------------------------------------------------------------*/

void visit(TreeNode* T) ;//��ӡ�����ڵ���Ϣ 

//������ǰ�к� 
void PreOrderTraverse(TreeNode* T) ;

void InOrderTraverse(TreeNode* T) ;

void PostOrderTraverse(TreeNode* T) ;

/*------------------------------------------------------------*/

void rb_create(TreeNode *&root);//����ƽ���� 

void rb_destroy(TreeNode *&root);//����ƽ���� 

void rb_insert(ValueType val, ElementType num, TreeNode* &root);//������Ȩֵ�����ڣ�����Ȩֵ 

TreeNode *rb_search(ValueType val, TreeNode* &root);//����ָ�����Ȩֵ��ָ�룬�򷵻�NULL��Ȩֵ������ 

void rb_erase(ValueType val, TreeNode* &root);//������Ȩֵ���ڣ�ɾ����Ȩֵ 


