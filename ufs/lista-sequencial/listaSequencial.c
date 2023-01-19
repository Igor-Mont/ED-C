#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 50

typedef int KeyType;

typedef struct {
  KeyType key;
} Record;

typedef struct {
  Record A[MAX];
  int nElem;
} List;

void initializeList(List* l) {
  l->nElem = 0;
}

void restartList(List* l) {
  l->nElem = 0;
}

int length(List* l) {
  return l->nElem;
}

void printList(List* l) {
  printf("List: \" ");
  for(int i = 0; i < l->nElem; i++) {
    printf("%i ", l->A[i].key);
  }
  printf("\"\n");
}

int sequentialSearch(List* l, KeyType key) {
  int i = 0;
  while(i < l->nElem) {
    if(key == l->A[i].key) return i;
    i++;
  }

  return -1;
}

bool insertElem(List* l, Record record, int pos) {
  if((l->nElem == MAX) || (pos < 0) || (pos > l->nElem)) return false;
  
  for(int i = l->nElem; i > pos; i--) {
    l->A[i] = l->A[i-1];
  }

  l->A[pos] = record;
  l->nElem++;

  return true;
}

bool deleteElem(List* l, KeyType key) {
  int pos = sequentialSearch(l, key);

  if(pos == -1) return false;

  for(int i = pos; i <l->nElem; i++) {
    l->A[i] = l->A[i+1];
  }

  l->nElem--;

  return true;
}

int main() {

  return 0;
}