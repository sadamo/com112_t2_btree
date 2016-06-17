#ifndef BTREEH
#define BTREEH

typedef struct btree BTree;

BTree∗ bt create (void);
void bt destroy (BTree∗ a);
BTree∗ bt search (BTree∗ a, int x, int∗ pos);
int bt key (BTree∗ a, int pos);
BTree∗ bt insert (BTree∗ a, int x);
BTree∗ bt remove (BTree∗ a, int x);
void bt print (BTree∗ a, int indent);

#endif
