#include <iostream>
#include "main.h"
#include "Tree.h"

using namespace std;

int flag = NOT_CREATED; // ȫ�ֱ����������ж�ƽ��������Ƿ��Ѿ�����
int number;//�Զ�����Ľڵ��ţ�ÿ���½�������1��ʼ�������ۼ� 

/**
 * ƽ���������ʾ���ܲ˵�
 */
void Menu() {
    system("color 0D");
    printf("**************************************************************************\n");
    printf("*                                                                        *\n");
    printf("************************�������ʾ����ѡ��˵�****************************\n");
    printf("*                                                                        *\n");
    printf("*****to improve is to change, to be perfect is to change often************\n");
    printf("*                                                                        *\n");
    printf("*                         1. ����һ��ƽ�������                          *\n");
    printf("*                         2. ������                                    *\n");
    printf("*                         3. ɾ�����                                    *\n");
    printf("*                         4. ���ҽ��                                    *\n");
    printf("*                         0. �˳�                                        *\n");
    printf("*                                                                        *\n");
    printf("**************************************************************************\n");
}


/**
 * ����ƽ�����������
 *
 * @param T ƽ�������
 */
void InitOperation(TreeNode* &T) {
    if (flag == HAVE_BEEN_CREATED) {
        printf("��֮ǰ�Ѿ�������һ��ƽ����������Ƿ�����֮ǰ���������´�������Y/y����, ���������Ϊ��");
        char choice = getchar();
        fflush(stdin);
        if (toupper(choice) == 'Y') {
            rb_destroy(T);
            //printf("the tree has been destroyed��");
        } else {
            return;
        }
    }    
    
    rb_create(T);
    number=0;
    
    //printf("new tree initialize succeed.\n");
    printf("�����ɹ���\n");
    flag = HAVE_BEEN_CREATED;      
}

/**
 * ���������
 *
 * @param T ƽ�������
 */
void rb_insertOperation(TreeNode* &T) {
    if (flag == NOT_CREATED) {
        // ƽ���������δ����
        printf("����δ����ƽ����������޷������㣬���ȴ�����");
        return;
    } else if (flag == HAVE_BEEN_CREATED) {
        if (NULL == T) {
            printf("����ƽ��������ǿյģ���Ϊ��������ɣ�\n");
        } else {
           printf("\n----------------------------------------------------");
            printf("\n����ƽ�������Ϊ��");
            ParenthesisPrint(T);
            printf("\n\n");
            ConcaveTablePrint(T, 1);
            printf("\n----------------------------------------------------\n\n");
 
        }
        while (1) {
            printf("������Ҫ������Ĺؼ���: ");
            ValueType value;
            while (1 != scanf("%d", &value)) {//prevent illegal input
                getchar();
                fflush(stdin);
                printf("��������ȷ��ֵ!\n");
                //printf("intput invalid! please try again\n");
                printf("������Ҫ������Ĺؼ���: ");
            }          
            if (value==-1)
            {
            	return;
			}
            if (rb_search(value,T) != NULL) {                
				printf("����ʧ���ˣ���Ϊ������Ĺؼ����Ѿ������ˡ�\n\n");                
            } else {
            	number++;
                rb_insert(value,number,T);
	            printf("\n----------------------------------------------------");
	            printf("\n����ƽ�������Ϊ��");
	            ParenthesisPrint(T);
	            printf("\n\n");
	            ConcaveTablePrint(T, 1);
	            printf("\n----------------------------------------------------\n\n");
 
            }
            printf("���������Ҫ������Ĺؼ��֣�������Ѿ�������ϣ�������� -1 �ɻص����˵�\n");            
        }
    }
}

/**
 * ɾ��������
 *
 * @param T ƽ�������
 */
void rb_eraseOperation(TreeNode *&T) {
    if (flag == NOT_CREATED) {
        // ƽ���������δ����
        printf("����δ����ƽ����������޷�ɾ����㣬���ȴ�����");
    } else if (flag == HAVE_BEEN_CREATED) {
        if (NULL == T) {
            printf("����ƽ��������ǿյģ��޷�ɾ����㣬���Ȳ����㣡\n");
        } else {
            printf("\n----------------------------------------------------");
           	printf("\n����ƽ�������Ϊ��");
            ParenthesisPrint(T);
            printf("\n\n");
            ConcaveTablePrint(T, 1);
            printf("\n----------------------------------------------------");
            printf("\n\n");
            while (1) {
                printf("������Ҫɾ�����Ĺؼ���: ");
                ValueType value;
                while (1 != scanf("%d", &value)) {
                    getchar();
                    fflush(stdin);
                    fprintf(stderr, "��������ȷ��ֵ��\n");
                    printf("������Ҫɾ�����Ĺؼ���: ");
                }
                if (NULL == rb_search(value,T)) {
                    // �ؼ��ֲ���ƽ�����������
                    printf("������Ĺؼ��ֲ���ƽ��������С�\n\n");
                } else {                    
                    rb_erase(value,T);
                    if (NULL == T) {
                        printf("ƽ��������Ѿ�����ɾ���ɾ��ˣ����ü���ɾ����\n");
                        break;
                    } else {
                        printf("\n----------------------------------------------------");
		 	            printf("\n����ƽ�������Ϊ��");
			            ParenthesisPrint(T);
			            printf("\n\n");
			            ConcaveTablePrint(T, 1);
                        printf("\n----------------------------------------------------\n\n");
                    }
                }
                printf("�Ƿ����ɾ������Y/y����, ���������Ϊ�񣩣�");
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
 * ���ҽ�����
 *
 * @param T ƽ�������
 */
void rb_searchOperation(TreeNode *&T) {
    ElementType key;
    TreeNode *p;
    if (NOT_CREATED == flag) {
        printf("����δ����ƽ����������޷����в��ң����ȴ�����\n");
        return;
    }
    if (NULL == T) {
        printf("����ƽ��������ǿյģ�\n");
        return;
    } else {        
        printf("��������Ҫ���ҵĹؼ��֣�");
        ValueType value;
        while (scanf("%d", &value) != 1) {
            printf("��������ȷ��ֵ!\n");
            printf("��������Ҫ���ҵĹؼ��֣�");
        }
        p = rb_search(value,T);
        if (NULL == p) {
            printf("û���ҵ��ùؼ��֡�\n");
        } else {
            printf("�Թؼ������ڽ����������£�\n");
            printf("------------------------------------------------------\n");
			ParenthesisPrint(p);
            printf("\n\n");
            ConcaveTablePrint(p, 1);
            printf("\n----------------------------------------------------\n\n");
        }
    }
}


/**
 * ����������
 */
int main()
{
    system("color 0F");
    int selectNum; //get command in form of number
    TreeNode *T;//new treeNode
    while (1) {
        Menu();//show menu in screen
        printf("������������еĲ�����");
        scanf("%d", &selectNum);
        getchar();
        fflush(stdin);//a contradictory discussion compasses, leave it alone
        if (0 == selectNum) {
            printf("\n�Ƿ��˳�����Y/y����, ���������Ϊ��");
            char option;
            option = getchar();
            fflush(stdin);
            if (toupper(option) == 'Y') {//detail
                if (flag == HAVE_BEEN_CREATED) {
                    rb_destroy(T);
                }
                // ѡ���˳�����Сд�Կ�
                exit(EXIT_SUCCESS);
            }
        } else {
        	
            switch (selectNum) {
                case 1: InitOperation(T); break; // ��ʼ������ƽ�������
                case 2: rb_insertOperation(T); break; // ����
                case 3: rb_eraseOperation(T); break; // ɾ��
                case 4: rb_searchOperation(T); break; // ����               
                default: fprintf(stderr, "��������ȷ��ֵ��\n"); break;//print diectly to the screen
            }
        }
        system("PAUSE");
        system("CLS"); // ��������
    }
    system("PAUSE");
    getch();
    return 0;
}
