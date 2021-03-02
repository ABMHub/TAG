#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

#include "grafo.h"

using namespace std;

int main () {
  // Cria objeto de arquivo
  ifstream file("soc-dolphins.mtx ");
  string str;
  bool flag = true;

  // Itera no arquivo ate os dados do grafo
  while (flag) {
    getline(file, str);
    if (str.at(0) != '%')
      flag = false;
  }

  // Extrai informacao da primeira linha de dados
  string delimiter = " ";
  size_t pos = 0;
  vector<int> dados; // v[0] = 62, v[1] = 62, v[2] = 159
  while ((pos = str.find(delimiter)) != string::npos) {
    dados.push_back(stoi(str.substr(0, pos)));
    str.erase(0, pos + delimiter.length());
  }
  dados.push_back(stoi(str));
  
  // Instancia grafo e cria vertices
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


  cout << "Coeficiente de aglomeracao medio do grafo: " << g.aglomeracaoMedia() << '\n';

  vector<set<Vertice>> vec = g.bronKerbosch(false); // chamada sem pivoteamento
  cout << "\nBron-Kerbosch sem pivoteamento:\n";
  printCliques(vec);

  vec = g.bronKerbosch(true);  // chamada com pivoteamento
  cout << "\nBron-Kerbosch com pivoteamento:\n";
  printCliques(vec);

  return 0;
}