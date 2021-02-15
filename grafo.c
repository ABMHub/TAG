#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Lista {
  char nome[50];
  struct Lista* ptr;
} Lista;

typedef struct Vertice {
  char nome[50];
  int grau;
  Lista* adjacentes;
} Vertice;

typedef struct Grafo {
  Vertice vertices[500];
  int numVertices;
} Grafo;

// Vertice* vertcpy (Vertice* destination, Vertice* origin, int n) {
//   for (int i = 0; i < n; i++){
//     destination[i] = origin[i];
//   }
//   return destination;
// }

bool addVertice (Grafo* g, char* nome) {
  if (!g) return false;

  Vertice v;
  v.grau = 0;
  v.adjacentes = NULL;
  strcpy(v.nome, nome);


  g->vertices[g->numVertices] = v;
  g->numVertices += 1;

  return 0;
}

Lista* addLista (Lista* l, char* nome) {
  if (!l) {
    Lista* l2 = malloc(sizeof(Lista));
    if (!l2) {
      printf("Malloc falhou - addLista\n");
      return NULL;
    }

    strcpy(l2->nome, nome);
    l2->ptr = NULL;
    return l2;
  }

  else {
    l->ptr = addLista(l->ptr, nome);
    return l;
  }
}

bool addAresta (Grafo* g, char* v1, char* v2) {
  int flag = 0;
  for (int i = 0; i < g->numVertices; i++) {
    char* nome = g->vertices[i].nome;
    if (!strcmp(nome, v1)) {
      g->vertices[i].adjacentes = addLista(g->vertices[i].adjacentes, v2);
      g->vertices[i].grau += 1;
      flag += 1;
    }
    if (!strcmp(nome, v2)) {
      g->vertices[i].adjacentes = addLista(g->vertices[i].adjacentes, v1);
      g->vertices[i].grau += 1;
      flag += 1;
    }
  }
  if (flag != 2)
    return false;

  return true;
}

Grafo* criaGrafo () {
  Grafo* grafo;
  grafo = malloc(sizeof(Grafo));

  grafo->numVertices = 0;
  return grafo;
}

void printGrafo(Grafo grafo) {
  for (int i = 0; i < grafo.numVertices; i++) {
    printf("%s\n", grafo.vertices[i].nome);
  }
}

void printListaArestas(Grafo grafo) {
  for (int i = 0; i < grafo.numVertices; i++) {
    Vertice v = grafo.vertices[i];
    Lista* l = v.adjacentes;
    printf("%s: ", v.nome);
    for (int j = 0; j < v.grau; j++) {
      printf("%s ", l->nome);
      l = l->ptr;
    }
    printf("\n");
  }
}

void printMatrizArestas(Grafo grafo) {
  printf("   ");
  for (int i = 0; i < grafo.numVertices; i++) {
    Vertice v = grafo.vertices[i];
    printf("%s ", v.nome);
  }
  printf("\n");
  for (int i = 0; i < grafo.numVertices; i++) {
    Vertice v = grafo.vertices[i];
    printf("%s ", v.nome);
    for (int k = 0; k < grafo.numVertices; k++) {
      Lista* l = v.adjacentes;
      bool flag = false;
      for (int j = 0; j < v.grau; j ++) {
        if (!strcmp(grafo.vertices[k].nome, l->nome)) {
          printf("1  ");
          flag = true;
        }
        l = l->ptr;
      }
      if (!flag)
        printf("0  ");
    }
    printf("\n");
  }
}

int main () {
  Grafo* grafo = criaGrafo();

  char* estados[] = {
    "AC",
    "AL",
    "AP",
    "AM",
    "BA",
    "CE",
    "DF",
    "ES",
    "GO",
    "MA",
    "MT",
    "MS",
    "MG",
    "PA",
    "PB",
    "PR",
    "PE",
    "PI",
    "RJ",
    "RN",
    "RS",
    "RO",
    "RR",
    "SC",
    "SP",
    "SE",
    "TO"
  };

  for(int i = 0; i < 27; i++) {
    addVertice(grafo, estados[i]);
  }

  addAresta(grafo, "AC", "AM");
  addAresta(grafo, "AC", "RO");
  addAresta(grafo, "AM", "RO");
  addAresta(grafo, "AM", "RR");
  addAresta(grafo, "AM", "PA");
  addAresta(grafo, "AM", "MT");
  addAresta(grafo, "RR", "PA");
  addAresta(grafo, "PA", "AP");
  addAresta(grafo, "PA", "MT");
  addAresta(grafo, "PA", "TO");
  addAresta(grafo, "PA", "MA");
  addAresta(grafo, "TO", "MT");
  addAresta(grafo, "TO", "MA");
  addAresta(grafo, "TO", "PI");
  addAresta(grafo, "TO", "BA");
  addAresta(grafo, "TO", "GO");
  addAresta(grafo, "MT", "GO");
  addAresta(grafo, "MT", "MS");
  addAresta(grafo, "MS", "GO");
  addAresta(grafo, "MS", "SP");
  addAresta(grafo, "MS", "PR");
  addAresta(grafo, "MS", "MG");
  addAresta(grafo, "GO", "MG");
  addAresta(grafo, "GO", "BA");
  addAresta(grafo, "GO", "DF");
  addAresta(grafo, "DF", "MG");
  addAresta(grafo, "RS", "SC");
  addAresta(grafo, "PR", "SC");
  addAresta(grafo, "PR", "SP");
  addAresta(grafo, "MG", "SP");
  addAresta(grafo, "RJ", "SP");
  addAresta(grafo, "RJ", "ES");
  addAresta(grafo, "BA", "ES");
  addAresta(grafo, "RJ", "MG");
  addAresta(grafo, "BA", "MG");
  addAresta(grafo, "BA", "PI");
  addAresta(grafo, "BA", "PE");
  addAresta(grafo, "BA", "AL");
  addAresta(grafo, "BA", "SE");
  addAresta(grafo, "AL", "SE");
  addAresta(grafo, "AL", "PE");
  addAresta(grafo, "PI", "PE");
  addAresta(grafo, "CE", "PE");
  addAresta(grafo, "PB", "PE");
  addAresta(grafo, "PB", "RN");
  addAresta(grafo, "PB", "CE");
  addAresta(grafo, "RN", "CE");
  addAresta(grafo, "PI", "CE");
  addAresta(grafo, "PI", "MA");

  // printGrafo(*grafo);
  printListaArestas(*grafo);
  printMatrizArestas(*grafo);

  return 0;
}