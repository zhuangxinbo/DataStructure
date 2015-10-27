#ifndef __Btree_H__
#define __Btree_H__


typedef struct Btree{
    int key;
    struct Btree* left;
    struct Btree* right;
}BtreeNode,*BiTree;


enum RetrunStatus{
    MALLOC_BITREE_NODE_OK,
    BITREE_HAS_NODE,
    BITREE_HAS_NOT_NODE,
    BITREE_DEL_NODE_OK,
    BITREE_INSERT_OK
};
extern int Btree_Insert(int key,BtreeNode** root);
extern void Btree_InorderWalk(BtreeNode* root);





#endif
