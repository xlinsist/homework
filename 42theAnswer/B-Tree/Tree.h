/**************************************************************
*	Struct Define Section
**************************************************************/

typedef int ValueType;//权值类型，比如，可以是int范围，也可以是long long范围。统一用int

typedef struct TreeNode//每个节点包含的信息是一个结构体，有对应的信息。比如B树的话，就应该里面会包含一个数组，记录这个节点的权值们。
{
/*  这里写平衡树的定义方式*/
} TreeNode;


/**************************************************************
*	Function Define SectionI
**************************************************************/

/* 
    一些重要的约定：

    1. 我们在主函数里面要定义一个指向根节点的指针。这个指针表示一个B树
    举例： TreeNode* T;//此时T是指向一个节点的指针
    
    2. 我们要把函数尽可能整洁的包装起来。
    举例：现在我们需要插入x这个权值，现在的挑战是，请通过合理设计函数，让我们在主程序中只需要这样执行：

    printf("please show your number: ");
    scanf("%d",&x);
    BTree_insert(x,T);

    3. 在函数内部，我们会依次执行插入节点，分裂，在分裂等过程。最后，同样是在函数内部，root的值将已经更新。
    举例：留意下面的函数，比如：BTree_insert(ValueType val, TreeNode* &root)。  

    TreeNode*表示传进来的是个指针，如我们上面定义好的T。
    在函数里面写 &root 这是引用传递，如果你忘了可以参考这篇博客：https://www.cnblogs.com/yanlingyin/archive/2011/12/07/2278961.html


*/

/*
    我们具体需要的B树，就是成功实现下面的6个函数.这就是我们的全部任务。
*/

void BTree_create(TreeNode *&root);//初始化。（这个函数里面的代码其实就一行：root=NULL;）

void BTree_destroy(TreeNode *&root);//销毁。

void BTree_insert(ValueType val, TreeNode* &root);//插入，其中val是需要插入的权值

TreeNode *BTree_search(ValueType val, TreeNode* &root);//返回一个包含val这个权值的，指向这个节点的指针，

void BTree_erase(ValueType val, TreeNode* &root);//删除，类似插入

void PreOrderTraverse(TreeNode* T) ;//前序遍历。一行输出一个大节点。同一个节点的权值们输出在同一行。
                                    //建议先编写这个，这样写其他操作时，可以自己出数据，用这个来测试结果是否正确。

//void InOrderTraverse(TreeNode* T);//中序遍历（选做题 （2分））
//void PostOrderTraverse(TreeNode* T);//后序遍历（选做题 （2分））


/**************************************************************
  以上就是我们的作品需要的B树的所有接口，这里的任务就交给你啦，Good Luck!
**************************************************************/
