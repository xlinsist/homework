#include <iostream>
#include "main.h"
#include "Tree.h"

using namespace std;

int flag = NOT_CREATED; // 全局变量，用来判断平衡二叉树是否已经创建
int number;//自动分配的节点编号，每次新建树都从1开始，往上累加 

/**
 * 平衡二叉树演示功能菜单
 */
void Menu() {
    system("color 0D");
    printf("**************************************************************************\n");
    printf("*                                                                        *\n");
    printf("************************红黑树演示功能选择菜单****************************\n");
    printf("*                                                                        *\n");
    printf("*****to improve is to change, to be perfect is to change often************\n");
    printf("*                                                                        *\n");
    printf("*                         1. 创建一棵平衡二叉树                          *\n");
    printf("*                         2. 插入结点                                    *\n");
    printf("*                         3. 删除结点                                    *\n");
    printf("*                         4. 查找结点                                    *\n");
    printf("*                         0. 退出                                        *\n");
    printf("*                                                                        *\n");
    printf("**************************************************************************\n");
}


/**
 * 创建平衡二叉树操作
 *
 * @param T 平衡二叉树
 */
void InitOperation(TreeNode* &T) {
    if (flag == HAVE_BEEN_CREATED) {
        printf("您之前已经创建了一颗平衡二叉树，是否销毁之前创建的重新创建？（Y/y：是, 其他任意键为否）");
        char choice = getchar();
        fflush(stdin);
        if (toupper(choice) == 'Y') {
            rb_destroy(T);
            //printf("the tree has been destroyed。");
        } else {
            return;
        }
    }    
    
    rb_create(T);
    number=0;
    
    //printf("new tree initialize succeed.\n");
    printf("创建成功！\n");
    flag = HAVE_BEEN_CREATED;      
}

/**
 * 插入结点操作
 *
 * @param T 平衡二叉树
 */
void rb_insertOperation(TreeNode* &T) {
    if (flag == NOT_CREATED) {
        // 平衡二叉树还未创建
        printf("您还未创建平衡二叉树，无法插入结点，请先创建。");
        return;
    } else if (flag == HAVE_BEEN_CREATED) {
        if (NULL == T) {
            printf("您的平衡二叉树是空的，快为它插入结点吧！\n");
        } else {
           printf("\n----------------------------------------------------");
            printf("\n您的平衡二叉树为：");
            ParenthesisPrint(T);
            printf("\n\n");
            ConcaveTablePrint(T, 1);
            printf("\n----------------------------------------------------\n\n");
 
        }
        while (1) {
            printf("请输入要插入结点的关键字: ");
            ValueType value;
            while (1 != scanf("%d", &value)) {//prevent illegal input
                getchar();
                fflush(stdin);
                printf("请输入正确的值!\n");
                //printf("intput invalid! please try again\n");
                printf("请输入要插入结点的关键字: ");
            }          
            if (value==-1)
            {
            	return;
			}
            if (rb_search(value,T) != NULL) {                
				printf("插入失败了，因为您输入的关键字已经存在了。\n\n");                
            } else {
            	number++;
                rb_insert(value,number,T);
	            printf("\n----------------------------------------------------");
	            printf("\n您的平衡二叉树为：");
	            ParenthesisPrint(T);
	            printf("\n\n");
	            ConcaveTablePrint(T, 1);
	            printf("\n----------------------------------------------------\n\n");
 
            }
            printf("请继续输入要插入结点的关键字；如果你已经插入完毕，输出数字 -1 可回到主菜单\n");            
        }
    }
}

/**
 * 删除结点操作
 *
 * @param T 平衡二叉树
 */
void rb_eraseOperation(TreeNode *&T) {
    if (flag == NOT_CREATED) {
        // 平衡二叉树还未创建
        printf("您还未创建平衡二叉树，无法删除结点，请先创建。");
    } else if (flag == HAVE_BEEN_CREATED) {
        if (NULL == T) {
            printf("您的平衡二叉树是空的，无法删除结点，请先插入结点！\n");
        } else {
            printf("\n----------------------------------------------------");
           	printf("\n您的平衡二叉树为：");
            ParenthesisPrint(T);
            printf("\n\n");
            ConcaveTablePrint(T, 1);
            printf("\n----------------------------------------------------");
            printf("\n\n");
            while (1) {
                printf("请输入要删除结点的关键字: ");
                ValueType value;
                while (1 != scanf("%d", &value)) {
                    getchar();
                    fflush(stdin);
                    fprintf(stderr, "请输入正确的值！\n");
                    printf("请输入要删除结点的关键字: ");
                }
                if (NULL == rb_search(value,T)) {
                    // 关键字不在平衡二叉树里面
                    printf("您输入的关键字不在平衡二叉树中。\n\n");
                } else {                    
                    rb_erase(value,T);
                    if (NULL == T) {
                        printf("平衡二叉树已经被您删除干净了，不用继续删除了\n");
                        break;
                    } else {
                        printf("\n----------------------------------------------------");
		 	            printf("\n您的平衡二叉树为：");
			            ParenthesisPrint(T);
			            printf("\n\n");
			            ConcaveTablePrint(T, 1);
                        printf("\n----------------------------------------------------\n\n");
                    }
                }
                printf("是否继续删除？（Y/y：是, 其他任意键为否）：");
                char c;
                getchar();
                scanf("%c", &c);
                fflush(stdin);
                if (toupper(c) != 'Y') {
                    break;
                }
                printf("\n");
            }
        }
    }
}

/**
 * 查找结点操作
 *
 * @param T 平衡二叉树
 */
void rb_searchOperation(TreeNode *&T) {
    ElementType key;
    TreeNode *p;
    if (NOT_CREATED == flag) {
        printf("您还未创建平衡二叉树，无法进行查找，请先创建。\n");
        return;
    }
    if (NULL == T) {
        printf("您的平衡二叉树是空的！\n");
        return;
    } else {        
        printf("请输入您要查找的关键字：");
        ValueType value;
        while (scanf("%d", &value) != 1) {
            printf("请输入正确的值!\n");
            printf("请输入您要查找的关键字：");
        }
        p = rb_search(value,T);
        if (NULL == p) {
            printf("没有找到该关键字。\n");
        } else {
            printf("以关键字所在结点的子树如下：\n");
            printf("------------------------------------------------------\n");
			ParenthesisPrint(p);
            printf("\n\n");
            ConcaveTablePrint(p, 1);
            printf("\n----------------------------------------------------\n\n");
        }
    }
}


/**
 * 测试主函数
 */
int main()
{
    system("color 0F");
    int selectNum; //get command in form of number
    TreeNode *T;//new treeNode
    while (1) {
        Menu();//show menu in screen
        printf("请输入您想进行的操作：");
        scanf("%d", &selectNum);
        getchar();
        fflush(stdin);//a contradictory discussion compasses, leave it alone
        if (0 == selectNum) {
            printf("\n是否退出？（Y/y：是, 其他任意键为否）");
            char option;
            option = getchar();
            fflush(stdin);
            if (toupper(option) == 'Y') {//detail
                if (flag == HAVE_BEEN_CREATED) {
                    rb_destroy(T);
                }
                // 选择退出，大小写皆可
                exit(EXIT_SUCCESS);
            }
        } else {
        	
            switch (selectNum) {
                case 1: InitOperation(T); break; // 初始化创建平衡二叉树
                case 2: rb_insertOperation(T); break; // 插入
                case 3: rb_eraseOperation(T); break; // 删除
                case 4: rb_searchOperation(T); break; // 查找               
                default: fprintf(stderr, "请输入正确的值！\n"); break;//print diectly to the screen
            }
        }
        system("PAUSE");
        system("CLS"); // 清屏操作
    }
    system("PAUSE");
    getch();
    return 0;
}
