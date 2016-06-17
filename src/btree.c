static BTPage* btree_page_create_empty(BTree* bt, BTPage* pgParent)
{
  int i;
  /* allocate memory for page structure */
  BTPage* pgCurrent = (BTPage*)malloc(sizeof(BTreePage));
  /* initialize empty page (with 0 elements) */
  pgCurrent->numkeys = 0;
  /* set page parent */
  pgCurrent->parent = pgParent;
  /* allocate memory for nodes (key + info) and children
  (allocate additional node and pointer to rchild to hold temporary overflow) */
  pgCurrent->node = (BTNode**) malloc(bt->order * sizeof(BTNode*));
  pgCurrent->rchild = (BTPage**) malloc((bt->order) * sizeof(BTPage*));
  /* initialize nodes and children pointers */
  pgCurrent->lchild = NULL;
  for (i=0; i < bt->order; ++i)
  {
    pgCurrent->node[i] = NULL;
    pgCurrent->rchild[i] = NULL;
  }
  return pgCurrent;
}


static BTPage* btree_insert_aux(BTree* bt, BTPage* pgCurrent, BTNode* btNode) {
  int i;
  if (pgCurrent == NULL) { /* create new page */
    BTPage* pgNew = btree_page_create(bt, NULL, btNode);
    return pgNew;
  }
  /* find out where info should be inserted
  (if order is large, a binary search should be used) */
  for (i=0; i < pgCurrent->numkeys; ++i)
  if (btNode->key == pgCurrent->node[i]->key) /* if key exists, update info */
  {
    pgCurrent->node[i]->info = btNode->info;
    return pgCurrent;
  }
  else if (btNode->key < pgCurrent->node[i]->key)
  break;
  if (pgCurrent->lchild == NULL)  /* if leaf, insert here */
  btree_page_insert_node_at(pgCurrent, btNode, NULL, i);
  else if (i == 0)
  pgCurrent = btree_insert_aux(bt,  pgCurrent->lchild, btNode);
  else
  pgCurrent = btree_insert_aux(bt,  pgCurrent->rchild[i-1], btNode);
  if (btree_page_overflowed(bt, pgCurrent)) {
    pgCurrent = btree_page_split(bt, pgCurrent);
  }
  return pgCurrent;
}
void btree_insert(BTree* bt, int key, void* info)
{
  BTNode* btNode = btree_node_create(key, info);
  BTPage* pgCurrent = btree_insert_aux(bt, bt->root, btNode);
  if (bt->root != pgCurrent)
  bt->root = pgCurrent;
}





static BTPage* btree_page_split(BTree* bt, BTPage* pgCurrent) {
  BTPage* pgParent = pgCurrent->parent;
  BTPage* pgNew = btree_page_create_empty(bt, pgParent);
  int i, j;
  int idxMedian = (bt->order+1)/2 - 1;
  BTNode* nodeMedian = pgCurrent->node[median];
  pgNew->lchild = pgCurrent->rchild[median];
  pgNew->parent = pgParent;
  if (pgNew->lchild) pgNew->lchild->parent = pgNew;
  if (pgParent == NULL) { /* create new root */
    pgParent = btree_page_create(bt, NULL, nodeMedian);
    pgParent->lchild = pgCurrent;
    pgParent->rchild[0] = pgNew;
    pgCurrent->parent = pgParent;
    bt->root = pgParent;
    pgNew->parent = pgParent;
  }
  else { /* insert median node into parent */
    btree_page_insert_node_at(pgParent, nodeMedian, pgNew,
      btree_page_find_insertion_point(pgParent, nodeMedian));
    }
    /* move nodes right of median to new page */
    for (j=0, i = idxMedian + 1; i < pgCurrent->numkeys; ++i, ++j)    {
      pgNew->node[j] = pgCurrent->node[i];
      pgNew->rchild[j] = pgCurrent->rchild[i];
      if (pgNew->rchild[j]) pgNew->rchild[j]->parent = pgNew;
      ++(pgNew->numkeys);
      pgCurrent->node[i] = NULL;
      pgCurrent->rchild[i] = NULL;
    }
    /* remove median node and insert it in parent page */
    pgCurrent->node[median] = NULL;
    pgCurrent->rchild[median] = NULL;
    pgCurrent->numkeys = idxMedian;
    return pgParent;
  }
