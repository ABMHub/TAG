// Codigo utilizado na atividade 5

#include <iostream>
#include <list>
#include <vector>
#include <set>

using namespace std;

class Vertice {
  public:
    string nome;
    list<Vertice*> lista;
    int grau;
    Vertice(string nome) {
      this->nome = nome;
      this->grau = 0;
      this->lista = {};
    }

    void addAresta (Vertice* b, bool bidirecional) {
      // cout << "Adicionando aresta entre " << nome << " e " << b->nome << "\n";
      lista.push_back(b);
      grau++;
      if (bidirecional)
        b->addAresta(this, false);
    }

    void printV () {
      std::cout << nome << " " << lista.size() << " " << grau << "\n";
    }
};

class Grafo {
  public:
    list<Vertice> vertices;
    int numVertices;
    Grafo() {
      vertices = {};
      numVertices = 0;
    }
    Grafo(vector<string> s) {
      for (unsigned int i = 0; i < s.size(); i++) {
        addVertice(s[i]);
      }
    }

    // TODO checar a existencia de um vertice com dado nome
    // TODO erro caso já exista vertice com dado nome
    bool addVertice (string nome) {
      Vertice v(nome);
      vertices.push_back(v);
      numVertices++;
      return true;
    }

    bool addAresta(string v1, string v2) {
      std::list<Vertice>::iterator it1;
      std::list<Vertice>::iterator it2;
      bool f1 = false, f2 = false;
      for (std::list<Vertice>::iterator it = vertices.begin(); it != vertices.end(); ++it){
        if (v1.compare(it->nome) == 0) {
          f1 = true;
          it1 = it;
        }
        if (v2.compare(it->nome) == 0) {
          f2 = true;
          it2 = it;
        }
      }
      if (!f1 || !f2) {
        cout << "Erro ao tentar montar aresta entre " << v1 << " e " << v2 << "\n"; 
        return false;
      }
      it1->addAresta(&(*it2), true);
      return true;
    }

    // ! nao funciona com grafos desconectados
    set<string> buscaProfundidade(set<string> visitados, Vertice vertice) {
      visitados.insert(vertice.nome);
      cout << "Iteracao numero " << visitados.size() << ": " << vertice.nome << "\n";
      for (std::list<Vertice*>::iterator it=vertice.lista.begin(); it != vertice.lista.end(); ++it){
        string nome = (*it)->nome;
        if (visitados.count(nome) == 0) {
          visitados = buscaProfundidade(visitados, **it);
        }
      }
      return visitados;
    }

    void buscaLargura(Vertice vertice) {
      set<string> set;
      set.insert(vertice.nome);
      list<Vertice> fila;
      fila.push_back(vertice);
      int i = 1;
      while(!(fila.empty())) {
        Vertice v = fila.front();
        cout << "Iteracao numero " << i << ": " << v.nome << "\n";
        for (std::list<Vertice*>::iterator it=v.lista.begin(); it != v.lista.end(); ++it){ 
          if (set.count((*it)->nome) == 0) {
            set.insert((*it)->nome);
            fila.push_back(**it);
          }
        }
        fila.pop_front();
        i++;
      }   
    }

    void printGrafo() {
      for (std::list<Vertice>::iterator it = vertices.begin(); it != vertices.end(); ++it){
        cout << "Vertice: " << it->nome << "\n";
        // cout << "Grau: " << it->grau << "\n";
        cout << "Adjacente a: ";
        for (std::list<Vertice*>::iterator it2 = it->lista.begin(); it2 != it->lista.end(); ++it2){
          cout << (*it2)->nome << " ";
        }
        cout << "\n";
      }
    }
};

int main () {
  vector<string> v = {"v", "d", "b", "c", "e"};
  Grafo g1(v);
  g1.addAresta("b", "v");
  g1.addAresta("b", "c");
  g1.addAresta("b", "d");
  g1.addAresta("b", "e");
  g1.addAresta("v", "d");
  g1.addAresta("v", "c");
  g1.addAresta("v", "e");
  g1.addAresta("c", "e");
  g1.addAresta("e", "d");

  v = {"v", "a", "b", "c", "d", "e"};
  Grafo g2(v);  
  g2.addAresta("e", "d");
  g2.addAresta("e", "a");
  g2.addAresta("v", "d");
  g2.addAresta("v", "a");
  g2.addAresta("d", "b");
  g2.addAresta("a", "b");
  g2.addAresta("c", "b");

  v = {"v", "a", "b", "c", "d", "e", "f", "g"};
  Grafo g3(v);  
  g3.addAresta("v", "b");
  g3.addAresta("v", "a");
  g3.addAresta("v", "c");
  g3.addAresta("c", "e");
  g3.addAresta("c", "d");
  g3.addAresta("d", "f");
  g3.addAresta("d", "g");

  set<string> set;

  cout << "Grafo numero 1: \n";
  g1.printGrafo();
  cout << "\n";
  // g1.buscaProfundidade(set, g1.vertices.front());
  g1.buscaLargura(g1.vertices.front());

  cout << "\nGrafo numero 2: \n";
  g2.printGrafo();
  cout << "\n";
  // g2.buscaProfundidade(set, g2.vertices.front());
  g2.buscaLargura(g2.vertices.front());

  cout << "\nGrafo numero 3: \n";
  g3.printGrafo();
  cout << "\n";
  // g3.buscaProfundidade(set, g3.vertices.front());
  g3.buscaLargura(g3.vertices.front());

  return 0;
}