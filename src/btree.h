#ifdef __cplusplus
extern "C" {
#endif

#ifndef BTREE_H
#define BTREE_H

typedef struct _btree BTree;
BTree* btree_create(int order);
void   btree_destroy(BTree* bt, void(*cb_destroy)(void*));
void   btree_insert(BTree* bt, int key, void* info);
void   btree_remove(BTree* bt, int key);
void   btree_print_indent(BTree* bt, void (*cb_print)(const void*));
void*  btree_find(BTree* bt, int key);

#endif

#ifdef __cplusplus
}
#endif
