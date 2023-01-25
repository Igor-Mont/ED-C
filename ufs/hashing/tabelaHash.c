#include <stdio.h>
#include <string.h>

// 2 * 15 (qtd. elementos) = primo mais proximo da soma
// usar lista para guardar colisões  

#define TAM 31

void inicializarTabela(int t[]) {
  for(int i = 0; i < TAM; i++)
    t[i] = 0;
} 

int hash(int chave) {
  return chave % TAM;
}

void inserir(int valor, int t[]) {
  int id = hash(valor);

  while(t[id] != 0) {
    id = hash(id + 1);
  } 

  t[id] = valor;
}

int busca(int t[], int chave) {
  int id = hash(chave);

  printf("Chave gerada> %d\n", id);

  while(t[id] != 0) {
    if(t[id] == chave) return t[id];

    id = hash(id + 1);
  }

  return 0;
}

void imprimir (int t[]) {
  for(int i = 0; i < TAM; i++) {
    printf("%d = %d\n", i, t[i]);
  }
}

int main() {
  int opcao = 0;
  int valor;
  int tabela[TAM];

  inicializarTabela(tabela);

  do {
    printf("\n\t0 - Sair");
    printf("\n\t1 - Inserir");
    printf("\n\t2 - Buscar");
    printf("\n\t3 - Imprimir");

    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      printf("\t Qual valor deseja inserir? ");
      scanf("%d", &valor);
      inserir(valor, tabela);
      break;
    case 2:
      printf("\t Qual valor deseja buscar? ");
      scanf("%d", &valor);
      int retorno = busca(tabela, valor);
      if(retorno != 0) {
        printf("Valor encontrado: %d\n", retorno);
      } else {
        printf("Valor não encontrado\n");
      }
      break;
    case 3:
      imprimir(tabela);
      break;
    
    default:
      printf("Opcao invalida");
    }
  } while(opcao != 0);

  return 0;
}