#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define SIZE 1024
int tree[SIZE];     

void init_tree() 
{
    for (int i = 0; i < SIZE; i++) 
    {
        tree[i] = -1;
    }
}

void insert(int key)
{
    int idx = 1;
    while(idx < SIZE)
    {
        if (tree[idx] == -1)
        {
            tree[idx] = key;
            return;
        }
        if (key == tree[idx])
        {
            printf("중복 키 %d: 삽입되지 않음\n", key);
            return; // 중복이면 삽입 안함
        }
        else
        {
            if (key < tree[idx])
            {
                idx *= 2;
            }
            else
            {
                idx = 2*idx+1;
            }
        }
    }
    printf("트리 공간 부족\n");
    return;
}

int find_min_index(int idx)
{
    while(tree[idx] != -1)
    {
        idx *= 2;
    }
    idx = idx/2;
    return idx;
}

void delete_key(int key)
{
    int idx = 1;
    while (idx < SIZE && tree[idx] != -1 && tree[idx] != key) 
    {
        if (key < tree[idx])
        {
            idx = 2 * idx;
        }
        else
        {
            idx = 2 * idx + 1;
        }
    }
    if (idx >= SIZE || tree[idx] == -1) 
    {
        printf("키 %d 없음\n", key);
        return;
    }

    int left = 2 * idx;
    int right = 2 * idx + 1;

    if (tree[left] == -1 && tree[right] == -1)
    {
        tree[idx] = -1;
        return;
    }
    if (tree[left] != -1 && tree[right] == -1)
    {
        int tmp = tree[left];
        if(tree[2*left] != -1 || tree[2*left+1] != -1)    delete_key(tree[left]);
        else tree[left] = -1;
        tree[idx] = tmp;
        return;
    }
    if (tree[left] == -1 && tree[right] != -1)
    {
        int tmp = tree[right];
        if(tree[2*right] != -1 || tree[2*right+1] != -1)    delete_key(tree[right]);
        else tree[right] = -1;
        tree[idx] = tmp;
        return;
    }
    else
    {
        int minidx = find_min_index(right);
        if(right == minidx)
        {
            int tmp = tree[right];
            delete_key(tree[right]);
            tree[idx] = tmp;
        }
        else
        {
            tree[idx] = tree[minidx];
            tree[minidx] = -1;
        }
        return;
    }    
}

void makeBST() 
{
    int key;
    printf("BST 생성: 음수 입력 시 종료\n");
    while (1) 
    {
        printf("삽입할 값 입력: ");
        if (scanf("%d", &key) != 1 || key < 0) break;
        insert(key);
    }
}

void insert_loop() 
{
    int key;
    printf("삽입 반복: 음수 입력 시 종료\n");
    while (1) 
    {
        printf("삽입할 값 입력: ");
        if (scanf("%d", &key) != 1 || key < 0) break;
        insert(key);
    }
}

void delete_loop() 
{
    int key;
    printf("삭제 반복: 음수 입력 시 종료\n");
    while (1) 
    {
        printf("삭제할 값 입력: ");
        if (scanf("%d", &key) != 1 || key < 0) break;
        delete_key(key);
    }
}

int get_tree_size() 
{
    int max_idx = 0;
    for (int i = 1; i < SIZE; i++) 
    {
        if (tree[i] != -1) 
        {
            max_idx = i;
        }
    }
    printf("\n");
    printf("max_idx is % d", max_idx);
    return max_idx;
}

int TreeHei(int idx, int arr[])
{
    if (arr[idx]==-1 || idx > SIZE)     return 0;
    int left = TreeHei(2*idx, arr);
    int right = TreeHei(2*idx+1, arr);

    return 1 + ((right > left) ? right : left);
}

void RL(int idx)
{
    int A_idx = 2*idx;
    int C_idx = idx;

}

void AVL(int idx)
{
    int right = TreeHei(2*idx+1, tree);
    int left = TreeHei(2*idx, tree);

    if(right - left < -1)
    {
        if(TreeHei(2*right, tree) > TreeHei(2*right+1, tree))
        {
            
        }
    }   
    if(right - left > 1)
    {

    }
    else return;
}


void inorder_with_array() 
{
    int stack[SIZE];
    int top = -1;
    int idx = 1;
    printf("\n[중위 순회 결과]: ");
    while (idx < SIZE || top != -1) 
    {
        while (idx < SIZE && tree[idx] != -1) 
        {
            stack[++top] = idx;
            idx = 2 * idx;
        }
        if (top == -1) break;
        idx = stack[top--];
        printf("%d ", tree[idx]);
        idx = 2 * idx + 1;
    }

    int size = get_tree_size();
    printf("\n[트리 배열 상태]:\n");
    for (int i = 1; i <= size; i++) 
    {
        if (tree[i] == -1)
        {
            printf("tree[%d] = -1\n", i);
        }
        else
        {
            printf("tree[%d] = %d \t hei = %d \t left_hei = %d \t right_hei = %d \n", i, tree[i], TreeHei(i, tree), TreeHei(2*i, tree), TreeHei(2*i+1, tree));
        }
    }
}



int main() 
{
    int choice;
    init_tree();
    while (1) 
    {
        printf("\n=== 이진탐색트리 메뉴 ===\n");
        printf("1. 트리 생성\n");
        printf("2. 삽입\n");
        printf("3. 삭제\n");
        printf("4. 종료\n");
        printf("선택: ");

    if (scanf("%d", &choice) != 1)  break;

    switch (choice) 
    {

        case 1:
                init_tree();
                makeBST();
                inorder_with_array();
                break;
        case 2:
                insert_loop();
                inorder_with_array();
                break;
        case 3:
                delete_loop();
                inorder_with_array();
                break;
        case 4:
                printf("프로그램 종료.\n");
                return 0;
        default:
                printf("잘못된 입력입니다.\n");
    }
    }

    return 0;
}