#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

#include "grafo.h"

using namespace std;

int main () {
  // Cria objeto de arquivo
  ifstream file("soc-dolphins.mtx");
  string str;
  bool flag = true;

  // Itera no arquivo ate a parte de dados do grafo
  while (flag) {
    getline(file, str);
    if (str.at(0) != '%')
      flag = false;
  }

  // Extrai informacao da primeira linha de dados
  string delimiter = " ";
  size_t pos = 0;
  vector<int> dados; // ao final do while: v[0] = 62, v[1] = 62, v[2] = 159
  while ((pos = str.find(delimiter)) != string::npos) {
    dados.push_back(stoi(str.substr(0, pos)));
    str.erase(0, pos + delimiter.length());
  }
  dados.push_back(stoi(str));
  
  // Instancia grafo e cria vertices de 1 ate 62
  Grafo g;
  for (int i = 1; i <= dados[0]; i++) {
    g.addVertice(to_string(i));
  }

  // Adiciona arestas aos vertices a partir do arquivo
  for (int i = 0; i < dados[2]; i++) {
    string vert1, vert2;
    getline(file, vert1);
    size_t pos = vert1.find(delimiter);
    vert2 = vert1.substr(0, pos);
    vert1.erase(0, pos + delimiter.length());

    g.addAresta(vert1, vert2);
  }

  // Imprime o retorno do metodo de aglomeracao media do grafo.
  cout << "Coeficiente de aglomeracao medio do grafo: " << g.aglomeracaoMedia() << '\n';

  /* 
    O algoritmo de bron-kerbosch retorna um vetor de cliques maximais
    Cada clique maximal esta numa estrutura de conjunto (set)
    Ou seja, vector<set<Vertice>> eh um vetor de conjuntos de vertices, cada conjunto sendo um clique maximal

    Apos o metodo ser executado, chamaremos uma funcao aparte para printar no console todos os cliques
  */

  vector<set<Vertice>> vec;
  
  vec = g.bronKerbosch(false); // chamada sem pivoteamento
  cout << "\nBron-Kerbosch sem pivoteamento:\n";
  printCliques(vec);

  vec = g.bronKerbosch(true);  // chamada com pivoteamento
  cout << "\nBron-Kerbosch com pivoteamento:\n";
  printCliques(vec);

  return 0;
}