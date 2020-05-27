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
 * 凹入表表示法打印树
 *
 * @param T 树
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
 * 括号表示法打印树
 *
 * @param T 树
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
 * 输出平衡二叉树关键字
 * @param key 关键字
 */
void visit(TreeNode* T) 
{
    printf("node number: %d      node value: %d\n", T->num,T->val);
}

/**
 * 前序遍历平衡二叉树
 *
 * @param T 平衡二叉树
 * @param visit 函数指针
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
 * 中序遍历平衡二叉树
 *
 * @param T 平衡二叉树
 * @param visit 函数指针
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
 * 后序遍历平衡二叉树
 *
 * @param T 平衡二叉树
 * @param visit 函数指针
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

    TreeNode *rchild = node->rchild; //指定指针指向right

    if ((node->rchild = rchild->lchild)) //将right的左孩子节点 挂接 给node的右孩子
    {
        rchild->lchild->parent = node; //node成为right左孩子的父母节点
    }

    rchild->lchild = node; //node成为right的左孩子

    if ((rchild->parent = node->parent)) //判断node不为根节点
    {
        if (node == node->parent->rchild) //node为父亲节点的右孩子
        {
            node->parent->rchild = rchild;
        }
        else //node为父亲节点的左孩子
        {
            node->parent->lchild = rchild;
        }
    }
    else
    {
        root = rchild; //如果node为根节点
    }
    node->parent = rchild; //right成为node的父母

}

/* rchild-rotation */

void R_Rotate(TreeNode *node, TreeNode *&root)

{

    TreeNode *lchild = node->lchild; //指定指针指向left

    if ((node->lchild = lchild->rchild)) //将left的右孩子赋值给node的左孩子，且left的右孩子不为空
    {
        lchild->rchild->parent = node; //node成为left右孩子的父亲节点
    }

    lchild->rchild = node; //node成为left的右孩子

    if ((lchild->parent = node->parent)) //将left的父节点指向node的父节点，并且此时，node不为根节点
    {
        if (node == node->parent->rchild) //node为其父节点的右孩子
        {
            node->parent->rchild = lchild;
        }
        else //node为其父节点的左孩子
        {

            node->parent->lchild = lchild;
        }
    }
    else //node为根节点
    {
        root = lchild;
    }

    node->parent = lchild; //left成为node的父节点

}

/*--------------------------------------------------------------------------------------------------------------------*/

/*查找某值在树中是否已经存在，若否，传递出待插入的位置*/
TreeNode *rb_search_auxiliary(ValueType val, TreeNode *&root, TreeNode **save) //save是二级指针，为了在函数中传递出一级指针给主程序

{

    TreeNode *node = root, *parent = NULL;
    //node表示当前节点（采用while非递归），
    //parent表示插入位置（即该叶子节点的parent，该叶子节点就是表示这个待插入节点。注意在红黑树的情景中叶子节点是空节点）

    int del;

    while (node)
    {
        parent = node;
        del = node->val - val;
        if (0 < del) //val 小于当前节点，所以，往其左子树查找
        {
            node = node->lchild;
        }
        else if (0 > del) //val 大于当前节点，所以，往其右子树查找
        {
            node = node->rchild;
        }
        else
        {
            return node; //查找成功，返回
        }
    }

    if (save) //返回插入位置
    {
        *save = parent;
    }

    return NULL;
}

/*查找操作*/
TreeNode *rb_search(ValueType val, TreeNode *&root)

{
    return rb_search_auxiliary(val, root, NULL);
    //如果是查找有关节点，在找不到节点时只需要返回NULL就行了，就不需要记录插入位置
}

/*--------------------------------------------------------------------------------------------------------------------*/

/* 插入节点之后，重新调整红黑树的结构 */
void rb_insert_rebalance(TreeNode *node, TreeNode *&root)
{
    TreeNode *parent, *gparent, *uncle, *tmp; //gparent=grand parent，其他含义如字面意思
    //循环条件：parent为node的父节点且不为空，另外，node的父节点的颜色为红色时。满足以上条件后才需要进行复杂的调整，否则不需要rebalance
    //使用while而不使用if的原因是，当uncle为红色时，牵涉到递归
    while ((parent = node->parent) && (parent->col == RED))
    {
        gparent = parent->parent;
        if (parent == gparent->lchild) //情况1：当祖父的左孩子为父节点时
        {
            uncle = gparent->rchild; //这时叔叔就是父母的右孩子

            if (uncle && uncle->col == RED) //情况1.1：叔叔不为NULL且是红色的
            {
                uncle->col = BLACK;
                parent->col = BLACK;

                gparent->col = RED;
                node = gparent; //node的“递归”
            }
            else //情况1.2：叔叔节点是黑色的
            {
                if (parent->rchild == node) //情况1.2.1: LR型，将其变为LL型
                {
                    L_Rotate(parent, root);
                    tmp = parent;
                    parent = node;
                    node = tmp;
                }
                //情况1.2.2: LL型
                parent->col = BLACK;
                gparent->col = RED;
                R_Rotate(gparent, root);
            }
        }
        else //if(parent == gparent->rchild)，即当父节点为祖父节点的右孩子时
        {
            uncle = gparent->lchild; //祖父节点的左孩子作为叔叔节点

            if (uncle && uncle->col == RED) //情况2.1：叔叔不为NULL且是红色的
            {
                uncle->col = BLACK;

                parent->col = BLACK;
                gparent->col = RED;
                node = gparent;
            }
            else //情况2.2：叔叔节点是黑色的
            {
                if (parent->lchild == node) //情况2.2.1: RL型，将其变为RR型
                {
                    R_Rotate(parent, root);
                    tmp = parent;
                    parent = node;
                    node = tmp;
                }
                //情况2.2.2: RR型
                parent->col = BLACK;

                gparent->col = RED;
                L_Rotate(gparent, root);
            }
        }
    }

    root->col = BLACK; //根节点，不论怎么样，都得置为黑色
}

/*插入节点*/
void rb_insert(ValueType val, ElementType num, TreeNode *&root)
{
    TreeNode *parent = NULL, *node; //parent表示插入位置，node表示新节点
    parent = NULL;

    if ((node = rb_search_auxiliary(val, root, &parent))) //如果该节点不存在，则会返回node一个NULL值，同时通过传地址引用把插入位置赋值给parent
    {
        return;// root; 
        //如果该节点已存在，无需另外插入
    }

    node = rb_new_node(val, num);    //分配新节点
    node->parent = parent;           //初始化
    node->lchild = node->rchild = NULL; //初始化
    node->col = RED;                 //初始化，先默认插入的节点为红色节点

    if (parent)
    {
        if (parent->val > val) //遵循平衡二叉树规则，决定将新节点加入到插入位置节点的左边或右边
        {
            parent->lchild = node;
        }
        else
        {
            parent->rchild = node;
        }
    }
    else //parent为空，说明插入的该节点就是第一个节点，即根节点
    {
        root = node;
    }
    rb_insert_rebalance(node, root); 
    return;// rb_insert_rebalance(node, root); //插入节点后，调用rb_search_rebalance修复红黑树
}

/*--------------------------------------------------------------------------------------------------------------------*/

//红黑树的4种删除情况

/* 删除节点之后，重新调整红黑树的结构 */

//x表示要删除的节点，*other、w表示兄弟节点

void rb_erase_rebalance(TreeNode *node, TreeNode *parent, TreeNode *&root)

{

    TreeNode *other, *o_left, *o_right; //x的兄弟*other, 兄弟左孩子*o_left, 右孩子*o_right

    while ((!node || node->col == BLACK) && node != root) //如果待删节点为空，或者节点为红色，或者该节点是根节点，则不用管或直接删除，无需再维护平衡
    {
        if (parent->lchild == node)
        {
            other = parent->rchild;

            if (other->col == RED)  //情况1：x的兄弟节点w是红色的
            {                       //对策如下
                other->col = BLACK; //a. 把兄弟节点染成黑色

                parent->col = RED;                   //b. 把父节点染成红色
                L_Rotate(parent, root); //对p[x]进行左旋
                other = parent->rchild;               //x的新兄弟节点new w 是旋转之前w的某个孩子。其实是左旋后的效果
                //操作后，其实仍然不满足平衡树结构，但是我们把这个交给后面的情况处理
            }

            //情况2：x的兄弟节点w是黑色，且w的两个孩子全为黑色
            if ((!other->lchild || other->lchild->col == BLACK) && (!other->rchild || other->rchild->col == BLACK))
            {
                //对策：把当前节点和兄弟节点中抽取出一重黑色追加到父节点上，把父节点当成新的当前节点
                other->col = RED; //a. 兄弟节点为红色
                node = parent;    //b. 把父节点当作新的当前节点

                parent = node->parent;
            }
            else
            {
                //情况3：x的兄弟节点w是黑色的，且w的左孩子是红色，右孩子为黑色
                if (!other->rchild || other->rchild->col == BLACK)
                {
                    if ((o_left = other->lchild)) //w和其左孩子left[w]，颜色互换
                    {
                        o_left->col = BLACK; //w的左孩子颜色由红->黑
                    }

                    other->col = RED;                    //兄弟节点w由黑->红
                    R_Rotate(other, root); //对w进行右旋，从而红黑性质恢复

                    other = parent->rchild; //变化后，父节点的右孩子，作为新的兄弟节点
                }

                //情况4：x的兄弟节点w是黑色的，兄弟节点的右孩子是红色
                other->col = parent->col; //a. 把兄弟节点染成当前节点父节点的颜色

                parent->col = BLACK; //b. 把当前节点的父节点染成黑色
                if (other->rchild)
                {
                    other->rchild->col = BLACK; //c. 兄弟节点的右孩子染成黑色
                }

                L_Rotate(parent, root); //d. 以当前节点的父节点为支点进行左旋
                node = root;                         //e. 把当前节点x置为根root
                                                     //此时算法结束，红黑树所有性质调转正确

                break;
            }
        }
        else //下面情况与上述情况，原理一致，只是左右对称
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

//红黑树的删除节点

void rb_erase(ValueType key, TreeNode *&root)

{

    TreeNode *child, *parent, *old, *lchild, *node;
    ColorSet col;

    if (!(node = rb_search_auxiliary(key, root, NULL))) //调用rb_search_auxiliary查找要删除的节点
    {
        printf("key %d is not exist!\\n");
        return;// root;
    }

    old = node;

    //删除节点有两个孩子节点
    //策略：可以选择把当前删除节点左子树中的最大元素或者是右子树中的最小元素放到放到待删除节点的位置，这里是把右子树中的最小元素放到放到待删除节点的位置
    if (node->lchild && node->rchild)
    {
        node = node->rchild;

        while ((lchild = node->lchild) != NULL) //找到右子树的最小元素节点，保存到node中
        {
            node = lchild;
        }
        child = node->rchild;   //child为node的右儿子，即node左儿子的兄弟节点。这时node一定没有左儿子了
        parent = node->parent; //parent为node节点的父节点
        col = node->col;       //color保存的是node节点的color

        if (child) //node的右儿子不为空，则安置这个右儿子，把其祖父节点作为父节点
        {
            child->parent = parent;
        }

        if (parent) //如果node节点的父节点不为空，即不为根节点
        {
            if (parent->lchild == node) //进行节点的移动，即将node的唯一的儿子（右儿子）节点挂接到node的父节点上
            {
                parent->lchild = child;
            }
            else
            {
                parent->rchild = child;
            }
        }
        else //node的父节点为根节点
        {
            root = child;
        }

        if (node->parent == old) //node的父节点等于要删除的节点
        {

            parent = node;
        }

        node->parent = old->parent; //进行把右子树最小元素节点放到当前删除节点处的操作

        node->col = old->col;

        node->rchild = old->rchild;
        node->lchild = old->lchild;

        if (old->parent) //如果当前删除节点的父节点存在，即old不为根节点
        {
            if (old->parent->lchild == old) //当前删除节点是其父节点的左孩子
            {
                old->parent->lchild = node;
            }
            else
            {
                old->parent->rchild = node; //当前删除节点是其父节点的右孩子
            }
        }
        else
        {
            root = node; //当前删除节点为根节点
        }

        old->lchild->parent = node;
        if (old->rchild)
        {
            old->rchild->parent = node;
        }
    } //if(node->lchild && node->rchild)

    else //此else语句处理的是：删除节点没有儿子、只有一个儿子时的情况
    {
        if (!node->lchild) //删除节点
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
        rb_erase_rebalance(child, parent, root); //调用rb_erase_rebalance来恢复红黑树性质
    }

    return;// root;
}

