#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <set>

using namespace std;
/* Classe Vertice:
Guarda nome, lista de adjacencia e grau de cada vertice
Usa metodo proprio para adicionar aresta entre vertices
*/
class Vertice {
  public:
    string nome;
    list<Vertice*> lista;
    int grau;

    Vertice(string nome);

    void addAresta (Vertice* b, bool bidirecional);
    float coefAglomeracao();
    void printV ();
    bool operator==(Vertice v);
    bool operator<(Vertice v) const;

  private:
    bool listHas (Vertice v);
};

/* 
  Classe Grafo
  Guarda uma lista de vertices presente no grafo,
  assim como o numero de vertices adicionados

  Contem varios algoritmos classicos de pesquisa e exploracao de um grafo
*/
class Grafo {
  public:
    list<Vertice> vertices;
    int numVertices;

    Grafo();
    Grafo(vector<string> s);

    bool addVertice (string nome);
    bool addAresta(string v1, string v2);
    vector<set<Vertice>> bronKerbosch(bool pivoteamento);
    vector<set<Vertice>> bronKerbosch();
    float aglomeracaoMedia();
    set<string> buscaProfundidade(set<string> visitados, Vertice vertice);
    void buscaLargura(Vertice vertice);
    void printGrafo();

  private:
    void printClique (set<Vertice> set);
    set<Vertice> listToSet(list<Vertice*> l);
    set<Vertice> listToSet(list<Vertice> l);
    set<Vertice> uniao (set<Vertice> a, Vertice b);
    set<Vertice> uniao (set<Vertice> a, set<Vertice> b);
    set<Vertice> interseccao (set<Vertice> a, set<Vertice> b);
    set<Vertice> subtracao (set<Vertice> a, set<Vertice> b);
    void bK (set<Vertice> R, set<Vertice> P, set<Vertice> X, vector<set<Vertice>> *cliques);
    void bKPivo (set<Vertice> R, set<Vertice> P, set<Vertice> X, vector<set<Vertice>> *cliques);
};

void printCliques(vector<set<Vertice>> vec);