#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <list>
#include <set>

using namespace std;

/* Classe Vertice:
Guarda nome, lista de adjacencia e grau de cada vertice
Usa metodo proprio para adicionar aresta entre vertices
*/

class Vertice;

class Aresta {
  public:
    Vertice* destino;
    int peso;

    Aresta(Vertice* destino, int peso) {
      this->destino = destino;
      this->peso = peso;
    }

    bool operator==(const Aresta a) const {
      if (destino == a.destino) 
        if (peso == a.peso)
          return true;

      return false;
      
    }

    bool operator!=(const Aresta a) const {
      if (destino != a.destino) 
        if (peso != a.peso)
          return true;

      return false;
      
    }
};

class Vertice {
  public:
    string nome;
    list<Aresta> lista;
    int grau;

    // Construtor
    Vertice(string nome) {
      this->nome = nome;
      this->grau = 0;
    }

    /* 
      Metodo para adicionar aresta
      a flag 'bidirecional' indica se a aresta sera adicionada nas duas direcoes:
      a->b e b->a ou apenas a->b
    */
    void addAresta (Vertice* b, int peso) {
      // cout << "Adicionando aresta entre " << nome << " e " << b->nome << "\n";
      Aresta a(b, peso);
      lista.push_back(a);
      grau++;
    }

    void removeAresta(Vertice a) {
      for (auto it = lista.begin(); it != lista.end(); ++it) {
        if (*(it->destino) == a) {
          lista.remove(*it);
          grau--;
          return;
        }
      }
    }

    // Funcao para calcular o coeficiente de aglomeracao do vertice
    float coefAglomeracao() {
      int triangulos = 0;
      for (list<Aresta>::iterator it = lista.begin(); it != lista.end(); ++it) {
        for (list<Aresta>::iterator it2 = it; it2 != lista.end(); ++it2) {
          // Checa se existe conexao entre dois vertices diferentes da lista de adjacencia do vertice analisado
          if (it->destino->listHas(*(it->destino))) 
            triangulos++;             // caso haja conexao, encontramos um triangulo
        }
      }

      float res;
      if (grau <= 1) 
        res = 0;        // Caso algum vertice tenha grau 1, encontraremos uma div/0, portanto e o programa fechara com erro
      else
        res = ((float) (2*triangulos)) / (grau*(grau - 1));

      return res;
    }

    // Metodo simples para printar informacoes sobre um vertice
    void printV () {
      cout << nome << " " << lista.size() << " " << grau << "\n";
    }

    // Operador para comparacoes. Implementado pelo uso de std::set no programa
    bool operator==(Vertice v) {
      if (v.nome.compare(nome) != 0)
        return false;
      
      if (v.lista != lista)
        return false;
      
      return true;
    }

    bool operator!=(Vertice v) {
      if (v.nome.compare(nome) == 0)
        return false;
      
      if (v.lista == lista)
        return false;
      
      return true;
    }

    // Operador para comparacoes. Implementado pelo uso de std::set no programa
    bool operator<(Vertice v) const {
      if (nome < v.nome) {
        return true;
      }
      return false;
    }

    // Funcao privada para checar se ha vertice v na lista de adjacentes do vertice
    bool listHas (Vertice v) {
      for (list<Aresta>::iterator it = lista.begin(); it != lista.end(); ++it) {
        if (*(it->destino) == v) {  
          return true;    // Caso o vertice v esteja na lista de adjacencia, retorna true
        }
      }
      return false;       // Caso contrario, retorna false 
    }
};

/* 
  Classe Digrafo
  Guarda uma lista de vertices presente no Digrafo,
  assim como o numero de vertices adicionados

  Contem varios algoritmos classicos de pesquisa e exploracao de um Digrafo
*/
class Digrafo {
  public:
    list<Vertice> vertices;
    int numVertices;

    // Construtor que inicia a lista de vertices vazia
    Digrafo() {
      vertices = {};
      numVertices = 0;
    }

    // Construtor que inicializa a lista de vertices atraves de um vetor
    Digrafo(vector<string> s) {
      numVertices = 0;
      for (unsigned int i = 0; i < s.size(); i++) {
        addVertice(s[i]);
      }
    }

    Digrafo(list<Vertice> l) {
      numVertices = 0;
      for (auto it = l.begin(); it != l.end(); ++it) {
        addVertice(it->nome);
      }
    }

    // TODO checar a existencia de um vertice com dado nome
    // TODO erro caso já exista vertice com dado nome
    // Metodo para adicionar vertice no Digrafo. 
    bool addVertice (string nome) {
      Vertice v(nome);
      vertices.push_back(v);
      numVertices++;
      return true;
    }

    Vertice getVertice (string nome) {
      for (auto it = vertices.begin(); it != vertices.end(); ++it) {
        if (it->nome.compare(nome) == 0) {
          return *it;
        }
      }
    }

    bool addAresta(string origem, string destino) {
      return addAresta(origem, destino, 0);
    }

    // Metodo para adicionar aresta entre dois vertices determinados pelo nome
    bool addAresta(string origem, string destino, int peso) {
      std::list<Vertice>::iterator it1;
      std::list<Vertice>::iterator it2;
      bool f1 = false, f2 = false;
      // Loop para pegar a referencia dos dois vertices escolhidos
      for (std::list<Vertice>::iterator it = vertices.begin(); it != vertices.end(); ++it){
        if (origem.compare(it->nome) == 0) {
          f1 = true;
          it1 = it;
        }
        if (destino.compare(it->nome) == 0) {
          f2 = true;
          it2 = it;
        }
      }
      // Caso algum vertice nao tenha sido encontrado, retorna com uma mensagem de erro
      if (!f1 || !f2) {
        cout << "Erro ao tentar montar aresta entre " << origem << " e " << destino << "\n"; 
        return false;
      }
      // Adiciona aresta entre os dois vertices, com 'true' para 'bidirecional'
      it1->addAresta(&(*it2), peso);
      return true;
    }

    void removeVertice(string vertice) {
      bool f1 = false;
      list<Vertice>::iterator it;
      for (it = vertices.begin(); it != vertices.end() && !f1; ++it)
        if (vertice.compare(it->nome) == 0) 
          f1 = true;

      Vertice v = *it;

      for (it = vertices.begin(); it != vertices.end(); ++it) {
        if (*it != v){
          it->removeAresta(v);
        }
      }

    }

    bool removeAresta(string origem, string destino) {
      std::list<Vertice>::iterator it1;
      std::list<Vertice>::iterator it2;
      bool f1 = false, f2 = false;
      // Loop para pegar a referencia dos dois vertices escolhidos
      for (std::list<Vertice>::iterator it = vertices.begin(); it != vertices.end(); ++it){
        if (origem.compare(it->nome) == 0) {
          f1 = true;
          it1 = it;
        }
        if (destino.compare(it->nome) == 0) {
          f2 = true;
          it2 = it;
        }
      }
      if (!f1 || !f2) {
        cout << "Erro ao tentar remover aresta entre " << origem << " e " << destino << "\n"; 
        return false;
      }
      it1->removeAresta(*it2);
      return true;
    }

    // Metodo do algoritmo de Bron-Kerbosch. Passar 'true' como parametro para pivoteamento, 'false' para sem pivoteamento
    vector<set<Vertice>> bronKerbosch(bool pivoteamento) {
      vector<set<Vertice>> cliquesMaximais;

      // P sera o conjunto de todos os vertices do grafo
      // Converte a lista de vertices para um conjunto de vertices, para o uso de funcoes de uniao, iterseccao e subtracao de conjuntos
      set<Vertice> P = listToSet(vertices);
      set<Vertice> R;
      set<Vertice> X;

      // Determina qual metodo privado sera chamado: com ou sem pivoteamento
      if (pivoteamento)
        bKPivo(R, P, X, &cliquesMaximais);
      
      else
        bK(R, P, X, &cliquesMaximais);

      // Retorna um vetor com todos os conjuntos de cliques maximais
      return cliquesMaximais;
    }

    // Sobrecarga: se nao forem passados parametros, faz algoritmo sem pivoteamento
    vector<set<Vertice>> bronKerbosch() {
      vector<set<Vertice>> cliquesMaximais;

      set<Vertice> R;
      set<Vertice> P = listToSet(vertices);
      set<Vertice> X;
    
      bK(R, P, X, &cliquesMaximais);

      return cliquesMaximais;
    }

    // Funcao para retornar aglomeracao media do grafo
    float aglomeracaoMedia() {
      float coef = 0;
      // Calcularemos o coeficiente de aglomeracao para cada vertice e somaremos na variavel coef
      for (list<Vertice>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
        coef += it->coefAglomeracao();  
      }
      // Retorna media dos coeficientes de aglomeracao
      return coef/numVertices;
    }

    void kosajaruSharir() {
      list<Vertice> ordem;
      Digrafo inverso = inverteArestas();
      set<string> visitados;
      while (visitados.size() != inverso.numVertices){
        bool flag = false;
        for (auto it = inverso.vertices.begin(); it != inverso.vertices.end() && !flag; ++it) {
          if (visitados.count(it->nome) == 0) {
            ordem = uniteList(inverso.buscaProfundidade(&visitados, *it), ordem);
            flag = true;
          }
        }
      }
      visitados.clear();
      while (visitados.size() != numVertices){
        bool flag = false;
        for (auto it = ordem.begin(); it != ordem.end() && !flag; ++it) {
          if (visitados.count(it->nome) == 0) {
            list<Vertice> aux = buscaProfundidade(&visitados, getVertice(it->nome));
            for (auto it = aux.begin(); it != aux.end(); ++it) {
              cout << it->nome << " ";
            }
            cout << '\n';
            flag = true;
          }
        }
      }
    }

    // ! nao funciona com grafos desconectados
    // Realiza busca em profundidade recursivamente e printa na tela os detalhes de cada iteracao
    list<Vertice> buscaProfundidade(set<string>* visitados, Vertice vertice) {
      list<Vertice> ret;
      visitados->insert(vertice.nome);
      // cout << "Iteracao numero " << visitados->size() << ": " << vertice.nome << "\n";
      for (std::list<Aresta>::iterator it=vertice.lista.begin(); it != vertice.lista.end(); ++it){
        string nome = it->destino->nome;
        if (visitados->count(nome) == 0) {
          ret = uniteList(buscaProfundidade(visitados, *(it->destino)), ret);
        }
      }
      ret.push_front(vertice);
      return ret;
    }

    // Realiza busca em largura e printa na tela os detalhes de cada iteracao
    void buscaLargura(Vertice vertice) {
      set<string> set;
      set.insert(vertice.nome);
      list<Vertice> fila;
      fila.push_back(vertice);
      int i = 1;
      while(!(fila.empty())) {
        Vertice v = fila.front();
        cout << "Iteracao numero " << i << ": " << v.nome << "\n";
        for (std::list<Aresta>::iterator it=v.lista.begin(); it != v.lista.end(); ++it){ 
          if (set.count(it->destino->nome) == 0) {
            set.insert(it->destino->nome);
            fila.push_back(*(it->destino));
          }
        }
        fila.pop_front();
        i++;
      }   
    }

    void floydWarshall () {
      int matriz[numVertices][numVertices];
      for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
          if (i == j)
            matriz[i][j] = 0;
          else
            matriz[i][j] = 10000;
        }
      }
      for (list<Vertice>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
        for (list<Aresta>::iterator it2 = it->lista.begin(); it2 != it->lista.end(); ++it2) {
          matriz[stoi(it->nome) - 1][stoi(it2->destino->nome) - 1] = it2->peso;
        }
      }

      for (int k = 0; k < numVertices; k++) {
        for (int i = 0; i < numVertices; i++) {
          for (int j = 0; j < numVertices; j++) {
            if (matriz[i][j] > matriz[i][k] + matriz[k][j]) {
              matriz[i][j] = matriz[i][k] + matriz[k][j];
            }
          }
        }
      }

      cout << "    ";
      for (int i = 0; i < numVertices; i++) {
        cout << i+1 << "  ";
      }
      cout << "\n\n";
      for (int i = 0; i < numVertices; i++) {
        cout << i+1 << "   ";
        for (int j = 0; j < numVertices; j++) {
          if (matriz[i][j] == 10000)
            cout << "/" << "  ";
            
          else if (matriz[i][j] >= 10)
            cout << matriz[i][j] << " ";

          else 
            cout << matriz[i][j] << "  ";
        }
        cout << '\n';
      }

    }

    list<Vertice> ordenacaoTopologicaKahn() {
      list<Vertice> L;
      set<Vertice> S = listToSet(vertices);
      set<Vertice> aux;

      for(auto it = vertices.begin(); it != vertices.end(); ++it) {
        for (auto it2 = it->lista.begin(); it2 != it->lista.end(); ++it2){
          aux.insert(*(it2->destino));
        }
      }

      S = subtracao(S, aux);

      Digrafo d = *this;

      while (!S.empty()) {
        Vertice n = *(S.begin());
        cout << n.nome << ' ';
        S.erase(n);
        L.push_back(n);
        for (auto it = d.vertices.begin(); it != d.vertices.end(); ++it) {
          if (n.listHas(*it)) {
            d.removeAresta(n.nome, it->nome);
            if (!d.hasIncoming(*it)) {
              S.insert(*it);
            }
          }
        }
      }
      return L;
    }

    bool hasIncoming(Vertice v) {
      for (auto it = vertices.begin(); it != vertices.end(); ++it) {
        if (it->listHas(v)) return true;
      }
      return false;
    }

    Digrafo inverteArestas() {
      Digrafo d(vertices);

      for (auto it = vertices.begin(); it != vertices.end(); ++it) {
        for (auto it2 = it->lista.begin(); it2 != it->lista.end(); ++it2) {
          d.addAresta(it2->destino->nome, it->nome);
        }
      }

      return d;
    }

    // Printa os detalhes de cada vertice do grafo
    void printDigrafo() {
      for (std::list<Vertice>::iterator it = vertices.begin(); it != vertices.end(); ++it){
        cout << "Vertice: " << it->nome << "\n";
        // cout << "Grau: " << it->grau << "\n";
        cout << "Adjacente a: ";
        for (std::list<Aresta>::iterator it2 = it->lista.begin(); it2 != it->lista.end(); ++it2){
          cout << "(v = " << it2->destino->nome << ", p = " << it2->peso << ") ";
        }
        cout << "\n";
      }
    }

  private:
    // Funcao para printar no console um clique
    void printClique (set<Vertice> set) {
      std::set<Vertice>::iterator it;
      for (it = set.begin(); it != set.end(); ++it) {
        cout << it->nome << " ";
      }
      cout << '\n';
      return;
    }

    list<Vertice> uniteList(list<Vertice> a, list<Vertice> b) {
      for (auto it = b.begin(); it != b.end(); ++it) {
        a.push_back(*it);
      }
      return a;
    }

    // Funcao para conversao de list para set
    // Importante pois as funcoes de interseccao, uniao e subtracao de conjuntos requerem ordenacao, e list nao eh ordenada
    set<Vertice> listToSet(list<Aresta> l) {
      set<Vertice> s;
      if (l.empty())
        return s;

      for (list<Aresta>::iterator it = l.begin(); it != l.end(); ++it) {
        s.insert(*(it->destino));
      }
      return s;
    }

    set<Vertice> listToSet(list<Vertice> l) {
      set<Vertice> s;
      if (l.empty())
        return s;

      for (list<Vertice>::iterator it = l.begin(); it != l.end(); ++it) {
        s.insert(*it);
      }
      return s;
    }

    // Funcao para unir conjunto a com elemento b
    set<Vertice> uniao (set<Vertice> a, Vertice b) {
      a.insert(b);
      return a;
    }

    // Funcao para unir conjunto a com conjunto b
    set<Vertice> uniao (set<Vertice> a, set<Vertice> b) {
      set<Vertice> ret;
      set_union(a.begin(), a.end(), b.begin(), b.end(), std::inserter(ret, ret.begin()));
      return ret;
    }

    // Funcao para adquirir a interseccao entre o conjunto a e o conjunto b
    set<Vertice> interseccao (set<Vertice> a, set<Vertice> b) {
      set<Vertice> ret;
      set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::inserter(ret, ret.begin()));
      return ret;
    }

    // Funcao para executar a subtracao entre o conjunto a e o conjunto b (a / b)
    set<Vertice> subtracao (set<Vertice> a, set<Vertice> b) {
      set<Vertice> ret;
      set_difference(a.begin(), a.end(), b.begin(), b.end(), std::inserter(ret, ret.begin()));
      return ret;
    }

    // Algoritmo de Bron-Kerbosch sem pivoteamento
    void bK (set<Vertice> R, set<Vertice> P, set<Vertice> X, vector<set<Vertice>> *cliques) {
      // Caso ache um clique:
      if (P.empty() && X.empty()) {
        printClique(R);           // Printar clique no terminal
        cliques->push_back(R);    // Adicionar clique na lista de cliques
        return;                   // Encerrar recursao
      }

      set<Vertice> Paux = P;  // P auxiliar para iteracao
      for (set<Vertice>::iterator it = Paux.begin(); it != Paux.end(); ++it) {
        set<Vertice> N = listToSet(it->lista);                              // Converte a lista de adjacencia para um conjunto
        bK(uniao(R, *it), interseccao(P, N), interseccao(X, N), cliques);   // Chamada da recursao
        P.erase(*it);                                                       // Eliminar vertice analisado de P
        X.insert(*it);                                                      // Inserir Vertice analisado em X
      }
    }

    // Algoritmo de Bron-Kerbosch com pivoteamento
    void bKPivo (set<Vertice> R, set<Vertice> P, set<Vertice> X, vector<set<Vertice>> *cliques) {
      // Caso ache um clique:
      if (P.empty() && X.empty()) {
        printClique(R);           // Printar clique no terminal
        cliques->push_back(R);    // Adicionar clique na lista de cliques
        return;                   // Encerrar recursao
      }

      Vertice v = *(uniao(P, X).begin());    // Escolhe um vertice v de P uniao X
      set<Vertice> Nv = listToSet(v.lista);  // Converte a lista de adjacencia de v para um conjunto
      set<Vertice> Paux = subtracao(P, Nv);  // Iteracao ocorrera no conjunto dos elemento P / N(v)
      for (set<Vertice>::iterator it = Paux.begin(); it != Paux.end(); ++it) {
        set<Vertice> N = listToSet(it->lista);                              // Converte a lista de adjacencia para um conjunto
        bK(uniao(R, *it), interseccao(P, N), interseccao(X, N), cliques);   // Chamada da recursao
        P.erase(*it);                                                       // Eliminar vertice analisado de P
        X.insert(*it);                                                      // Inserir Vertice analisado em X
      }
    }
};

int main () {
  vector<string> v;
  v = {"A", "B", "C", "D", "E", "F", "G", "H"};
  Digrafo g1(v);

  g1.addAresta("A", "B");
  g1.addAresta("A", "C");
  g1.addAresta("A", "F");
  g1.addAresta("B", "E");
  g1.addAresta("C", "D");
  g1.addAresta("D", "A");
  g1.addAresta("D", "H");
  g1.addAresta("E", "F");
  g1.addAresta("E", "G");
  g1.addAresta("E", "H");
  g1.addAresta("F", "B");
  g1.addAresta("F", "G");
  g1.addAresta("H", "G");

  g1.kosajaruSharir();

  return 0;
}