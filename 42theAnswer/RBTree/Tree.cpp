#include "main.h"
#include "Tree.h"

TreeNode *rb_new_node(ValueType val, ElementType num)
{
    TreeNode *node = (TreeNode *)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->num = num;
    return node;
}

/**
 * ������ʾ����ӡ��
 *
 * @param T ��
 */
void ConcaveTablePrint(TreeNode* T, int m) {
    int i;
    for (i = 1; i < m; i++) {
        printf("    ");
    }
    printf("%5d", T->val);
    if (T->lchild != NULL) {
        printf("\n");
        ConcaveTablePrint(T->lchild, m + 1);
    }
    if (T->rchild != NULL) {
        printf("\n");
        ConcaveTablePrint(T->rchild, m + 1);
    }
}

/**
 * ���ű�ʾ����ӡ��
 *
 * @param T ��
 */
void ParenthesisPrint(TreeNode* T) {
    if (NULL == T) {
        return;
    }
    printf("%d", T->val);
    if (T->lchild != NULL || T->rchild != NULL) {
        printf("(");
        if (T->lchild != NULL) {
            ParenthesisPrint(T->lchild);
        } else if (T->rchild != NULL) {
            printf("#");
        }
        printf(",");
        if (T->rchild != NULL) {
            ParenthesisPrint(T->rchild);
        } else if (T->lchild != NULL){
            printf("#");
        }
        printf(")");
    }
}

/*--------------------------------------------------------------------------------------------------------------------*/

/**
 * ���ƽ��������ؼ���
 * @param key �ؼ���
 */
void visit(TreeNode* T) 
{
    printf("node number: %d      node value: %d\n", T->num,T->val);
}

/**
 * ǰ�����ƽ�������
 *
 * @param T ƽ�������
 * @param visit ����ָ��
 */
void PreOrderTraverse(TreeNode* T) 
{
    if (NULL == T) {
        return;
    }
  	visit(T);
    PreOrderTraverse(T->lchild);
    PreOrderTraverse(T->rchild);
}

/**
 * �������ƽ�������
 *
 * @param T ƽ�������
 * @param visit ����ָ��
 */
void InOrderTraverse(TreeNode* T) 
{
    if (NULL == T) {
        return;
    }
    InOrderTraverse(T->lchild);
    visit(T);
    InOrderTraverse(T->rchild);
}

/**
 * �������ƽ�������
 *
 * @param T ƽ�������
 * @param visit ����ָ��
 */
void PostOrderTraverse(TreeNode* T) 
{
    if (NULL == T) {
      	return;
    }
    PostOrderTraverse(T->lchild);
    PostOrderTraverse(T->rchild);
    visit(T);
}

/*--------------------------------------------------------------------------------------------------------------------*/

/*  create*/
void rb_create(TreeNode *&root)
{
	root=NULL;
}

/* destory*/
void rb_destroy(TreeNode *&root)
{
	if (root==NULL) return;
	rb_destroy(root->lchild);
	rb_destroy(root->rchild);
	free(root);
}

/*--------------------------------------------------------------------------------------------------------------------*/

/* lchild-rotation */
void L_Rotate(TreeNode *node, TreeNode *&root)
{

    TreeNode *rchild = node->rchild; //ָ��ָ��ָ��right

    if ((node->rchild = rchild->lchild)) //��right�����ӽڵ� �ҽ� ��node���Һ���
    {
        rchild->lchild->parent = node; //node��Ϊright���ӵĸ�ĸ�ڵ�
    }

    rchild->lchild = node; //node��Ϊright������

    if ((rchild->parent = node->parent)) //�ж�node��Ϊ���ڵ�
    {
        if (node == node->parent->rchild) //nodeΪ���׽ڵ���Һ���
        {
            node->parent->rchild = rchild;
        }
        else //nodeΪ���׽ڵ������
        {
            node->parent->lchild = rchild;
        }
    }
    else
    {
        root = rchild; //���nodeΪ���ڵ�
    }
    node->parent = rchild; //right��Ϊnode�ĸ�ĸ

}

/* rchild-rotation */

void R_Rotate(TreeNode *node, TreeNode *&root)

{

    TreeNode *lchild = node->lchild; //ָ��ָ��ָ��left

    if ((node->lchild = lchild->rchild)) //��left���Һ��Ӹ�ֵ��node�����ӣ���left���Һ��Ӳ�Ϊ��
    {
        lchild->rchild->parent = node; //node��Ϊleft�Һ��ӵĸ��׽ڵ�
    }

    lchild->rchild = node; //node��Ϊleft���Һ���

    if ((lchild->parent = node->parent)) //��left�ĸ��ڵ�ָ��node�ĸ��ڵ㣬���Ҵ�ʱ��node��Ϊ���ڵ�
    {
        if (node == node->parent->rchild) //nodeΪ�丸�ڵ���Һ���
        {
            node->parent->rchild = lchild;
        }
        else //nodeΪ�丸�ڵ������
        {

            node->parent->lchild = lchild;
        }
    }
    else //nodeΪ���ڵ�
    {
        root = lchild;
    }

    node->parent = lchild; //left��Ϊnode�ĸ��ڵ�

}

/*--------------------------------------------------------------------------------------------------------------------*/

/*����ĳֵ�������Ƿ��Ѿ����ڣ����񣬴��ݳ��������λ��*/
TreeNode *rb_search_auxiliary(ValueType val, TreeNode *&root, TreeNode **save) //save�Ƕ���ָ�룬Ϊ���ں����д��ݳ�һ��ָ���������

{

    TreeNode *node = root, *parent = NULL;
    //node��ʾ��ǰ�ڵ㣨����while�ǵݹ飩��
    //parent��ʾ����λ�ã�����Ҷ�ӽڵ��parent����Ҷ�ӽڵ���Ǳ�ʾ���������ڵ㡣ע���ں�������龰��Ҷ�ӽڵ��ǿսڵ㣩

    int del;

    while (node)
    {
        parent = node;
        del = node->val - val;
        if (0 < del) //val С�ڵ�ǰ�ڵ㣬���ԣ���������������
        {
            node = node->lchild;
        }
        else if (0 > del) //val ���ڵ�ǰ�ڵ㣬���ԣ���������������
        {
            node = node->rchild;
        }
        else
        {
            return node; //���ҳɹ�������
        }
    }

    if (save) //���ز���λ��
    {
        *save = parent;
    }

    return NULL;
}

/*���Ҳ���*/
TreeNode *rb_search(ValueType val, TreeNode *&root)

{
    return rb_search_auxiliary(val, root, NULL);
    //����ǲ����йؽڵ㣬���Ҳ����ڵ�ʱֻ��Ҫ����NULL�����ˣ��Ͳ���Ҫ��¼����λ��
}

/*--------------------------------------------------------------------------------------------------------------------*/

/* ����ڵ�֮�����µ���������Ľṹ */
void rb_insert_rebalance(TreeNode *node, TreeNode *&root)
{
    TreeNode *parent, *gparent, *uncle, *tmp; //gparent=grand parent������������������˼
    //ѭ��������parentΪnode�ĸ��ڵ��Ҳ�Ϊ�գ����⣬node�ĸ��ڵ����ɫΪ��ɫʱ�������������������Ҫ���и��ӵĵ�����������Ҫrebalance
    //ʹ��while����ʹ��if��ԭ���ǣ���uncleΪ��ɫʱ��ǣ�浽�ݹ�
    while ((parent = node->parent) && (parent->col == RED))
    {
        gparent = parent->parent;
        if (parent == gparent->lchild) //���1�����游������Ϊ���ڵ�ʱ
        {
            uncle = gparent->rchild; //��ʱ������Ǹ�ĸ���Һ���

            if (uncle && uncle->col == RED) //���1.1�����岻ΪNULL���Ǻ�ɫ��
            {
                uncle->col = BLACK;
                parent->col = BLACK;

                gparent->col = RED;
                node = gparent; //node�ġ��ݹ顱
            }
            else //���1.2������ڵ��Ǻ�ɫ��
            {
                if (parent->rchild == node) //���1.2.1: LR�ͣ������ΪLL��
                {
                    L_Rotate(parent, root);
                    tmp = parent;
                    parent = node;
                    node = tmp;
                }
                //���1.2.2: LL��
                parent->col = BLACK;
                gparent->col = RED;
                R_Rotate(gparent, root);
            }
        }
        else //if(parent == gparent->rchild)���������ڵ�Ϊ�游�ڵ���Һ���ʱ
        {
            uncle = gparent->lchild; //�游�ڵ��������Ϊ����ڵ�

            if (uncle && uncle->col == RED) //���2.1�����岻ΪNULL���Ǻ�ɫ��
            {
                uncle->col = BLACK;

                parent->col = BLACK;
                gparent->col = RED;
                node = gparent;
            }
            else //���2.2������ڵ��Ǻ�ɫ��
            {
                if (parent->lchild == node) //���2.2.1: RL�ͣ������ΪRR��
                {
                    R_Rotate(parent, root);
                    tmp = parent;
                    parent = node;
                    node = tmp;
                }
                //���2.2.2: RR��
                parent->col = BLACK;

                gparent->col = RED;
                L_Rotate(gparent, root);
            }
        }
    }

    root->col = BLACK; //���ڵ㣬������ô����������Ϊ��ɫ
}

/*����ڵ�*/
void rb_insert(ValueType val, ElementType num, TreeNode *&root)
{
    TreeNode *parent = NULL, *node; //parent��ʾ����λ�ã�node��ʾ�½ڵ�
    parent = NULL;

    if ((node = rb_search_auxiliary(val, root, &parent))) //����ýڵ㲻���ڣ���᷵��nodeһ��NULLֵ��ͬʱͨ������ַ���ðѲ���λ�ø�ֵ��parent
    {
        return;// root; 
        //����ýڵ��Ѵ��ڣ������������
    }

    node = rb_new_node(val, num);    //�����½ڵ�
    node->parent = parent;           //��ʼ��
    node->lchild = node->rchild = NULL; //��ʼ��
    node->col = RED;                 //��ʼ������Ĭ�ϲ���Ľڵ�Ϊ��ɫ�ڵ�

    if (parent)
    {
        if (parent->val > val) //��ѭƽ����������򣬾������½ڵ���뵽����λ�ýڵ����߻��ұ�
        {
            parent->lchild = node;
        }
        else
        {
            parent->rchild = node;
        }
    }
    else //parentΪ�գ�˵������ĸýڵ���ǵ�һ���ڵ㣬�����ڵ�
    {
        root = node;
    }
    rb_insert_rebalance(node, root); 
    return;// rb_insert_rebalance(node, root); //����ڵ�󣬵���rb_search_rebalance�޸������
}

/*--------------------------------------------------------------------------------------------------------------------*/

//�������4��ɾ�����

/* ɾ���ڵ�֮�����µ���������Ľṹ */

//x��ʾҪɾ���Ľڵ㣬*other��w��ʾ�ֵܽڵ�

void rb_erase_rebalance(TreeNode *node, TreeNode *parent, TreeNode *&root)

{

    TreeNode *other, *o_left, *o_right; //x���ֵ�*other, �ֵ�����*o_left, �Һ���*o_right

    while ((!node || node->col == BLACK) && node != root) //�����ɾ�ڵ�Ϊ�գ����߽ڵ�Ϊ��ɫ�����߸ýڵ��Ǹ��ڵ㣬���ùܻ�ֱ��ɾ����������ά��ƽ��
    {
        if (parent->lchild == node)
        {
            other = parent->rchild;

            if (other->col == RED)  //���1��x���ֵܽڵ�w�Ǻ�ɫ��
            {                       //�Բ�����
                other->col = BLACK; //a. ���ֵܽڵ�Ⱦ�ɺ�ɫ

                parent->col = RED;                   //b. �Ѹ��ڵ�Ⱦ�ɺ�ɫ
                L_Rotate(parent, root); //��p[x]��������
                other = parent->rchild;               //x�����ֵܽڵ�new w ����ת֮ǰw��ĳ�����ӡ���ʵ���������Ч��
                //��������ʵ��Ȼ������ƽ�����ṹ���������ǰ��������������������
            }

            //���2��x���ֵܽڵ�w�Ǻ�ɫ����w����������ȫΪ��ɫ
            if ((!other->lchild || other->lchild->col == BLACK) && (!other->rchild || other->rchild->col == BLACK))
            {
                //�Բߣ��ѵ�ǰ�ڵ���ֵܽڵ��г�ȡ��һ�غ�ɫ׷�ӵ����ڵ��ϣ��Ѹ��ڵ㵱���µĵ�ǰ�ڵ�
                other->col = RED; //a. �ֵܽڵ�Ϊ��ɫ
                node = parent;    //b. �Ѹ��ڵ㵱���µĵ�ǰ�ڵ�

                parent = node->parent;
            }
            else
            {
                //���3��x���ֵܽڵ�w�Ǻ�ɫ�ģ���w�������Ǻ�ɫ���Һ���Ϊ��ɫ
                if (!other->rchild || other->rchild->col == BLACK)
                {
                    if ((o_left = other->lchild)) //w��������left[w]����ɫ����
                    {
                        o_left->col = BLACK; //w��������ɫ�ɺ�->��
                    }

                    other->col = RED;                    //�ֵܽڵ�w�ɺ�->��
                    R_Rotate(other, root); //��w�����������Ӷ�������ʻָ�

                    other = parent->rchild; //�仯�󣬸��ڵ���Һ��ӣ���Ϊ�µ��ֵܽڵ�
                }

                //���4��x���ֵܽڵ�w�Ǻ�ɫ�ģ��ֵܽڵ���Һ����Ǻ�ɫ
                other->col = parent->col; //a. ���ֵܽڵ�Ⱦ�ɵ�ǰ�ڵ㸸�ڵ����ɫ

                parent->col = BLACK; //b. �ѵ�ǰ�ڵ�ĸ��ڵ�Ⱦ�ɺ�ɫ
                if (other->rchild)
                {
                    other->rchild->col = BLACK; //c. �ֵܽڵ���Һ���Ⱦ�ɺ�ɫ
                }

                L_Rotate(parent, root); //d. �Ե�ǰ�ڵ�ĸ��ڵ�Ϊ֧���������
                node = root;                         //e. �ѵ�ǰ�ڵ�x��Ϊ��root
                                                     //��ʱ�㷨������������������ʵ�ת��ȷ

                break;
            }
        }
        else //������������������ԭ��һ�£�ֻ�����ҶԳ�
        {

            other = parent->lchild;
            if (other->col == RED)
            {
                other->col = BLACK;

                parent->col = RED;

                R_Rotate(parent, root);
                other = parent->lchild;
            }
            if ((!other->lchild || other->lchild->col == BLACK) && (!other->rchild || other->rchild->col == BLACK))
            {
                other->col = RED;
                node = parent;
                parent = node->parent;
            }
            else
            {
                if (!other->lchild || other->lchild->col == BLACK)
                {
                    if ((o_right = other->rchild))
                    {
                        o_right->col = BLACK;
                    }
                    other->col = RED;

                    L_Rotate(other, root);
                    other = parent->lchild;
                }

                other->col = parent->col;
                parent->col = BLACK;

                if (other->lchild)
                {

                    other->lchild->col = BLACK;
                }
                R_Rotate(parent, root);

                node = root;
                break;
            }
        }
    }

    if (node)
    {
        node->col = BLACK;
    }

    return;
}

//�������ɾ���ڵ�

void rb_erase(ValueType key, TreeNode *&root)

{

    TreeNode *child, *parent, *old, *lchild, *node;
    ColorSet col;

    if (!(node = rb_search_auxiliary(key, root, NULL))) //����rb_search_auxiliary����Ҫɾ���Ľڵ�
    {
        printf("key %d is not exist!\\n");
        return;// root;
    }

    old = node;

    //ɾ���ڵ����������ӽڵ�
    //���ԣ�����ѡ��ѵ�ǰɾ���ڵ��������е����Ԫ�ػ������������е���СԪ�طŵ��ŵ���ɾ���ڵ��λ�ã������ǰ��������е���СԪ�طŵ��ŵ���ɾ���ڵ��λ��
    if (node->lchild && node->rchild)
    {
        node = node->rchild;

        while ((lchild = node->lchild) != NULL) //�ҵ�����������СԪ�ؽڵ㣬���浽node��
        {
            node = lchild;
        }
        child = node->rchild;   //childΪnode���Ҷ��ӣ���node����ӵ��ֵܽڵ㡣��ʱnodeһ��û���������
        parent = node->parent; //parentΪnode�ڵ�ĸ��ڵ�
        col = node->col;       //color�������node�ڵ��color

        if (child) //node���Ҷ��Ӳ�Ϊ�գ���������Ҷ��ӣ������游�ڵ���Ϊ���ڵ�
        {
            child->parent = parent;
        }

        if (parent) //���node�ڵ�ĸ��ڵ㲻Ϊ�գ�����Ϊ���ڵ�
        {
            if (parent->lchild == node) //���нڵ���ƶ�������node��Ψһ�Ķ��ӣ��Ҷ��ӣ��ڵ�ҽӵ�node�ĸ��ڵ���
            {
                parent->lchild = child;
            }
            else
            {
                parent->rchild = child;
            }
        }
        else //node�ĸ��ڵ�Ϊ���ڵ�
        {
            root = child;
        }

        if (node->parent == old) //node�ĸ��ڵ����Ҫɾ���Ľڵ�
        {

            parent = node;
        }

        node->parent = old->parent; //���а���������СԪ�ؽڵ�ŵ���ǰɾ���ڵ㴦�Ĳ���

        node->col = old->col;

        node->rchild = old->rchild;
        node->lchild = old->lchild;

        if (old->parent) //�����ǰɾ���ڵ�ĸ��ڵ���ڣ���old��Ϊ���ڵ�
        {
            if (old->parent->lchild == old) //��ǰɾ���ڵ����丸�ڵ������
            {
                old->parent->lchild = node;
            }
            else
            {
                old->parent->rchild = node; //��ǰɾ���ڵ����丸�ڵ���Һ���
            }
        }
        else
        {
            root = node; //��ǰɾ���ڵ�Ϊ���ڵ�
        }

        old->lchild->parent = node;
        if (old->rchild)
        {
            old->rchild->parent = node;
        }
    } //if(node->lchild && node->rchild)

    else //��else��䴦����ǣ�ɾ���ڵ�û�ж��ӡ�ֻ��һ������ʱ�����
    {
        if (!node->lchild) //ɾ���ڵ�
        {

            child = node->rchild;
        }
        else if (!node->rchild)
        {
            child = node->lchild;
        }
        parent = node->parent;
        col = node->col;

        if (child)
        {
            child->parent = parent;
        }
        if (parent)
        {

            if (parent->lchild == node)
            {
                parent->lchild = child;
            }
            else
            {
                parent->rchild = child;
            }
        }
        else
        {

            root = child;
        }
    }

    free(old);
    if (col == BLACK)
    {
        rb_erase_rebalance(child, parent, root); //����rb_erase_rebalance���ָ����������
    }

    return;// root;
}

