#include "btree.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define N 6
#define ORDEM 4


BTree* inicializar_arvore(FILE* pf, int* ordem) {
  BTree* a;
  int i;
  int elemento;
  fscanf(pf, "%d", ordem);

  printf("Ordem %d\n", (*ordem));
  a = bt_create((*ordem));

  while(fscanf(pf, "%d, ", &elemento) != EOF) {
    a = bt_insert(a, elemento);
  }

  return a;
}


void opcao_imprimir(BTree* a) {
  printf("\n\n");
  bt_print(a, 0);
  printf("0 1 2 3 4 5 6 7 8 9\n");
}

void opcao_inserir(BTree* a) {

}

void entrar_modo_operacoes(BTree* a) {
  int opcao;

  do {
    printf("Menu de Operacoes\n===================\n\n1. Inserir elemento\n2. Remover elemento\n3. Imprimir\n4. Sair\n=>");
    scanf("%d", &opcao);

    switch(opcao) {
      case 1:
        opcao_inserir(a);
        break;
      case 2:
        printf("Nao implementado.\n");
        break;
      case 3:
        opcao_imprimir(a);
      case 4:
        return;
    }
  } while(opcao != 4);

}


int main (int argc, char** argv) {
  int ordem;
  FILE* pf;

  if(argc != 2) {
    printf("Erro. Arquivo de entrada nao expecificado nos parametros.\n");
    return -1;
  }
  pf = fopen(argv[1], "r");


  BTree* a = inicializar_arvore(pf, &ordem);

  entrar_modo_operacoes(a);

  bt_destroy(a);
  return 0;
}
