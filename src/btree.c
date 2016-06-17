#define N 5 /* order (an odd number) */
struct btree {
  int n; /* number of keys */
  int k[N];
  BTree *p[N+1];
};


static int isleaf (BTree* a) {
  return (a−>p[0] == NULL);
}
static int findpos (BTree* a, int x, int* pos) {
  for ((*pos)=0; (*pos)<a−>n; ++(*pos))
    if (x==a−>k[*pos])
      return 1;
      else if (x<a−>k[*pos])
        break ;
  return 0;
}
BTree* bt_search(BTree* a, int x, int* pos) {
  int found = findpos(a,x,pos);
  if (found)
    return a;
  else if (isleaf(a))
    return NULL;
  else
    return bt_search(a−>p[*pos] ,x,pos);
}

int bt key (BTree* a, int pos) {
  return a−>k[pos];
}
