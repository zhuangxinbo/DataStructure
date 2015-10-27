#include <stdio.h>
#include <stdlib.h>
#include "Btree.h"

int Btree_Insert(int key,BtreeNode** root)
{
    if(*root==NULL)
    {
        BiTree node = (BiTree)malloc(sizeof(BtreeNode));
        node->right = node->left = NULL;
        node->key = key;
        *root = node;
        return MALLOC_BITREE_NODE_OK;
    }

    if((*root)->key < key)
        Btree_Insert(key,&((*root)->right));
    else if ((*root)->key > key)
        Btree_Insert(key,&((*root)->left));
    else if ((*root)->key  == key)
    {
        return BITREE_HAS_NODE;
    }
}

int Btree_InsertQ(int key,BtreeNode** link)
{
    BtreeNode * current ;

    while((current = *link)!= NULL)
    {
        if(key > current->key)
            link = &current->right;
        else if(key < current->key)
            link = &current->left;
        else if(key == current->key)
            return BITREE_HAS_NODE;
        
    }

    current = malloc(sizeof(BtreeNode));
    current->left = current->right = NULL;
    current->key =key;
    *link = current;
    return BITREE_INSERT_OK;
}

int Btree_SearchNode(int key,BtreeNode *root)
{
    while(root!=NULL)
    {
        if(key>root->key)
            root = root->right;
        else if(key < root->key)
            root = root->left;
        else if(key == root->key)
            return BITREE_HAS_NODE;
    }

    return BITREE_HAS_NOT_NODE;

}

static int __DelNode(BtreeNode** node)
{
    BtreeNode* p;
    BtreeNode* precursor;
    
    if((*node)->right == NULL)
    {
        p = *node;
        *node = (*node)->left;
        free(p);
    }
    else if((*node)->left ==NULL)
    {
        p = *node;
        *node = (*node)->right;
        free(p);
    }
    else{
        p = *node;
        precursor =(*node)->left;

        while(precursor->right){
            p = precursor;
            precursor = precursor->right;

        }

        (*node)->key=precursor->key;
        if(*node != p)
           p->right =precursor->left;
        else
           p->left =precursor->left;
        free(precursor);
    }

    return BITREE_DEL_NODE_OK;

}

int Btree_DelNode(int key,BtreeNode** root)
{
    while(*root!=NULL)
    {
        if(key > (*root)->key)
            root = &((*root)->right);
        else if(key < (*root)->key)
            root = &((*root)->left);
        else if( key == (*root)->key)
        {
           return  __DelNode(root); 
        }
    
    }
    return BITREE_HAS_NOT_NODE;

}

int Del(int key,BtreeNode** root)
{
    if(!*root)
        return -1;
    else{
        if(key==(*root)->key)
            return __DelNode(root);
        else if(key >(*root)->key)
            return Del(key,&(*root)->right);
        else 
            return Del(key,&(*root)->left);
    
    }


}




void Btree_InorderWalk(BtreeNode* root)
{
    if(root)
    {
        Btree_InorderWalk(root->left);
        printf("key=%d ",root->key);
        Btree_InorderWalk(root->right);
    }
        
}


int main()
{
    BtreeNode* root=NULL;
    int a[]={6,8,1,3,2,0,5,4,9,-5};
    int i;
    #if 0
    Btree_InsertQ(6,&root);
    Btree_InsertQ(8,&root);
    Btree_InsertQ(3,&root);
    Btree_InsertQ(1,&root);
    #endif
    for(i=0;i<10;i++)
    {
        Btree_InsertQ(a[i],&root);
    }
    Btree_InorderWalk(root);
    Btree_DelNode(8,&root);
    Btree_DelNode(-5,&root);
    Btree_DelNode(6,&root);


    Btree_InorderWalk(root);
}
