#include "btree.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define N 4

int main (void) {
  int i;
  int v[N];
  srand(time(NULL));

  BTree* a = bt_create();
  for (i = 0; i<N; ++i) {
    v[i] = i;
    a = bt_insert(a,v[i]);
  }
  bt_print(a,0);


  printf("0 1 2 3 4 5 6 7 8 9\n"); /* indica o nivel das informacoeses no console */
  bt_destroy(a);
  return 0;
}
