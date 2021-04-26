#include <algorithm>
#include <iostream>
#include <fstream>
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

typedef struct prioridade {
  string nome;
  int rank;
} prioridade;

class Vertice;

class Aresta {
  public:
    Vertice* origem;
    Vertice* destino;
    int prioridade;

    Aresta(Vertice* origem, Vertice* destino, int prioridade) {
      this->origem = origem;
      this->destino = destino;
      this->prioridade = prioridade;
    }

    bool operator==(const Aresta a) const {
      if (destino == a.destino) 
        if (prioridade == a.prioridade)
          return true;

      return false;
      
    }

    bool operator!=(const Aresta a) const {
      if (destino != a.destino) 
        if (prioridade != a.prioridade)
          return true;

      return false;
      
    }
    
    bool operator<(const Aresta a) const {
      if (prioridade < a.prioridade)
        return true;
      
      else if (prioridade == a.prioridade)
        if (destino < a.destino)
          return true;

      return false;
    }

    bool operator>(const Aresta a) const {
      if (prioridade > a.prioridade)
        return true;
      
      else if (prioridade == a.prioridade)
        if (destino > a.destino)
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
    Aresta addAresta (Vertice* b, int prioridade) {
      // cout << "Adicionando aresta entre " << nome << " e " << b->nome << "\n";
      Aresta a(this, b, prioridade);
      lista.push_back(a);
      grau++;
      return a;
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

    bool operator>(Vertice v) const {
      if (nome > v.nome) {
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

class Escola {
  public:
    string nome;
    vector<int> habilitacao;

    Escola() {
      nome = "vazio";
    }

    Escola(string dados) {
      int i = 0;
      bool flag = false;

      // encontra nome do professor
      while (!flag) {
        if (dados.at(i) == ')') {
          flag = true;
          i--;
        }
        i++;
      }

      this->nome = dados.substr(1, i - 1);
      i++;
      flag = false;
      while (!flag){
        if (dados.size() != i) {
          i += 2;
          habilitacao.push_back(stoi(dados.substr(i, 1)));
          i += 2;
        }
        else {
          flag = true;
        }
      }
    }

    // Metodo para saber se determinada escola aceita professor com determinada haiblitacao
    bool escolaAceitaHab(int h) {
      for(int i = 0; i < habilitacao.size(); i++) {
        if (h >= habilitacao[i]) {
          return true;
        }
      }
      return false;
    }

    void printEscola() {
      cout << "Nome: " << this->nome << ", preferencia de professores: (" << habilitacao.size() << ") ";
      for (auto i = habilitacao.begin(); i != habilitacao.end(); ++i) {
        cout << *i << " ";
      }
      cout << "\n";
    }

};

class Professor {
  public:
    string nome;
    int habilitacao;
    vector<prioridade> escolas;

    Professor() {
      nome = "Vazio";
      habilitacao = 0;
    }

    Professor(string dados) {
      int i = 0;
      bool flag = false;

      // encontra nome do professor
      while (!flag) {
        if (dados.at(i) == ',') {
          flag = true;
          i--;
        }
        i++;
      }
      // cout << dados.substr(1, i - 1) << "\n";
      this->nome = dados.substr(1, i - 1);

      // encontra numero de habilitacoes do professor
      i += 2;
      // cout << dados.substr(i, 1) << "\n";
      this->habilitacao = stoi(dados.substr(i, 1));

      // encontra escolar preferenciais
      i += 5;
      int j = i - 1;
      flag = false;
      int rank = 1;
      while (!flag) {
        if (dados.at(i) == ')' || dados.at(i) == ',') {
          j++;
          prioridade pri;
          pri.nome = dados.substr(j, i - j);
          pri.rank = rank;
          this->escolas.push_back(pri);
          if (dados.at(i) == ')') {
            flag = true;
          }
          rank ++;
        }
        else if (dados.at(i) == ' ') {
          j = i;
        }
        i++;
      }
    }

    void printProfessor() {
      cout << "Nome: " << this->nome << ", N de Habilitacoes: " << this->habilitacao << ", preferencia de escolas: (" << escolas.size() << ") ";
      for (auto i = escolas.begin(); i != escolas.end(); ++i) {
        cout << i->rank << " - " << i->nome << "; ";
      }
      cout << "\n";
    }
};

/* 
  Classe Grafo
  Guarda uma lista de vertices presente no Grafo,
  assim como o numero de vertices adicionados

  Contem varios algoritmos classicos de pesquisa e exploracao de um Grafo
*/
class Grafo {
  public:
    list<Vertice> vertices;
    list<Aresta> arestas;
    int numVertices;

    // Construtor que inicia a lista de vertices vazia
    Grafo() {
      vertices = {};
      numVertices = 0;
    }

    // Construtor que inicializa a lista de vertices atraves de um vetor
    Grafo(vector<string> s) {
      numVertices = 0;
      for (unsigned int i = 0; i < s.size(); i++) {
        addVertice(s[i]);
      }
    }

    Grafo(list<Vertice> l) {
      numVertices = 0;
      for (auto it = l.begin(); it != l.end(); ++it) {
        addVertice(it->nome);
      }
    }

    // TODO checar a existencia de um vertice com dado nome
    // TODO erro caso já exista vertice com dado nome
    // Metodo para adicionar vertice no Grafo. 
    bool addVertice (string nome) {
      Vertice v(nome);
      vertices.push_back(v);
      numVertices++;
      return true;
    }

    bool addVertice (Professor p) {
      Vertice v(p.nome);
      vertices.push_back(v);
      numVertices++;
      return true;
    }

    bool addVertice (Escola e) {
      Vertice v(e.nome);
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

    // Metodo para adicionar aresta entre dois vertices determinados pelo nome
    bool addAresta(string origem, string destino, int prioridade) {
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
      arestas.push_back(it1->addAresta(&(*it2), prioridade));
      arestas.push_back(it2->addAresta(&(*it1), prioridade));

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

    // ! nao remove aresta da lista de arestas
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
      it2->removeAresta(*it1);
      return true;
    }

    int hasIncoming(Vertice v) {
      int j = 0;
      for (auto it = vertices.begin(); it != vertices.end(); ++it) {
        if (it->listHas(v)) j++;
      }
      return j;
    }

    // Printa os detalhes de cada vertice do grafo
    void printGrafo() {
      for (std::list<Vertice>::iterator it = vertices.begin(); it != vertices.end(); ++it){
        cout << "Vertice: " << it->nome << "\n";
        // cout << "Grau: " << it->grau << "\n";
        cout << "Adjacente a: ";
        for (std::list<Aresta>::iterator it2 = it->lista.begin(); it2 != it->lista.end(); ++it2){
          cout << "(v = " << it2->destino->nome << ", p = " << it2->prioridade << ") ";
        }
        cout << "\n";
      }
    }
};

// Funcao que le o arquivo de entrada e salva os dados em dois vetores,
// um contendo a lista de escolas, e o outro contendo a lista de professores
void leArquivo (string fileStr, vector<Professor>* pptr, vector<Escola>* eptr) {
  ifstream file(fileStr);
  string str;

  // Pula tres linhas
  getline(file, str);
  getline(file, str);
  getline(file, str);

  vector<Professor> p;

  // le os dados do professor e instancia um objeto
  for(int i = 0; i < 100; i++) {
    getline(file, str);
    Professor prof(str);
    p.push_back(prof);
  }

  // Pula tres linhas
  getline(file, str);
  getline(file, str);
  getline(file, str);

  vector<Escola> e;

  // le os dados da escola e instancia um objeto
  for(int i = 0; i < 50; i++) {
    getline(file, str);
    Escola esc(str);
    e.push_back(esc);
  }

  *pptr = p;
  *eptr = e;
}

// Funcao que apaga qualquer preferencia que eh impossivel alocar estavelmente
// Exemplo: professor 1 com habilitacao 1 quer escola 2, mas escola 2 quer professores com habilitacao 3
void apagaPreferencias(vector<Professor> *p, vector<Escola> *e) {
  for (int i = 0; i < p->size(); i++) {
    Professor prof = p->at(i);
    vector<prioridade> preferencias = prof.escolas;
    for (int j = 0; j < preferencias.size(); j++) {
      string nomeEscola = preferencias[j].nome;
      int numEscola = stoi(nomeEscola.erase(0, 1));
      Escola esc = e->at(numEscola - 1); // ! testar
      if (!esc.escolaAceitaHab(prof.habilitacao)) {
        preferencias.erase(preferencias.begin() + j);
        j--;
        // cout << prof.nome << " excluido da " << esc.nome << "\n";
      }
    }
    p->at(i).escolas = preferencias;
  }
}

void printEscolas(vector<Escola> e) {
  for (int i = 0; i < e.size(); i++) {
    Escola esc = e.at(i);
    cout << esc.nome << ' ';
    for (int j = 0; j < esc.habilitacao.size(); j++) {
      cout << esc.habilitacao.at(j) << " ";
    }
    cout << '\n';
  }
}

void printProfessores(vector<Professor> p) {
  for (int i = 0; i < p.size(); i++) {
    Professor prof = p.at(i);
    prof.printProfessor();
  }
}

int converteString(string nome) {
  nome.erase(0);
  return stoi(nome);
}

int getProfessor(vector<Professor> v, string nome) {
  cout << nome << "\n";
  for (int i = 0; i < v.size(); i++) {
    if (v[i].nome == nome)
      return i;
  }
  return -1;
}

Escola getEscola(vector<Escola> e, string nome) {
  for (int i = 0; i < e.size(); i++) {
    if (e[i].nome == nome)
      return e[i];
  }
  return Escola();
}

prioridade procuraEscolaDisponivel(Professor p, vector<Escola> e, Grafo* g) {
  for (int i = 0; i < p.escolas.size(); i++) {
    Escola esc = getEscola(e, p.escolas[i].nome);
    Vertice v = g->getVertice(p.escolas[i].nome);
    if(g->hasIncoming(v) < esc.habilitacao.size() || v.lista.begin()->prioridade > p.escolas[i].rank || v.lista.end()->prioridade > p.escolas[i].rank) {
      return p.escolas[i];
    }
  }
  prioridade pri;
  pri.nome = "";
  return pri;
}

// void emparelhamento(vector<Professor> desalocados, vector<Escola> e, Grafo *g) {
//   vector<Professor> alocados;
//   bool flag = false;
//   while (!flag) {
//     flag = true;
//     for (int i = 0; i < desalocados.size(); i++) {
//       prioridade escola = procuraEscolaDisponivel(desalocados[i], e, g);
//       if (escola.nome != "") {
//         Vertice v = g->getVertice(escola.nome);
//         Escola esc = getEscola(e, escola.nome);
//         if (g->hasIncoming(v) == esc.habilitacao.size()) {
//           string antigoProf;
//           int rank = 5;
//           if (!v.lista.empty())
//             for (const auto& aresta : v.lista) {
//               if (rank > aresta.prioridade) {
//                 antigoProf = aresta.destino->nome;
//               }
//             }
//           g->removeAresta(v.nome, antigoProf);
//           int pos = getProfessor(alocados, antigoProf);
//           desalocados.push_back(alocados[pos]);
//           alocados.erase(alocados.begin() + pos);
//         }
//         alocados.push_back(desalocados[i]);
//         g->addAresta(desalocados[i].nome, escola.nome, escola.rank);
//         desalocados.erase(desalocados.begin() + i);
//         i--;
//         flag = false;
//       }
//     }
//   }
// }

bool podeAlocar(Professor prof, Escola esc, int rank, Grafo *g, vector<Professor> *alocados, vector<Professor> *desalocados) {
  Vertice v = g->getVertice(esc.nome);
  if (v.grau < esc.habilitacao.size()) {
    return true;
  }
  else {
    bool flag = false;
    string antigoProf;
    int primeiroRank;
    int primeiroHab;
    for (auto it = v.lista.begin(); it != v.lista.end(); it++) {
      auto aresta = *it;
      if (rank < aresta.prioridade) {
        if (flag == true) {
          if (aresta.prioridade > primeiroRank) {
            antigoProf = aresta.destino->nome;
          }
          else if (aresta.prioridade == primeiroRank && primeiroHab < alocados->at(getProfessor(*alocados, aresta.destino->nome)).habilitacao) {
            antigoProf = aresta.destino->nome;
          }
        }
        else {
          antigoProf = aresta.destino->nome;
          primeiroRank = aresta.prioridade;
          primeiroHab = alocados->at(getProfessor(*alocados, aresta.destino->nome)).habilitacao;
        }
        flag = true;
      }
    }
    if (flag) {
      g->removeAresta(antigoProf, esc.nome);
      int pos = getProfessor(*alocados, antigoProf);
      desalocados->push_back(alocados->at(pos));
      alocados->erase(alocados->begin() + pos);
      return true;
    }
      cout << 'c';
  }
  return false;
}

void emparelhamento(vector<Professor> desalocados, vector<Escola> e, Grafo *g) {
  vector<Professor> alocados;
  bool flag = false;
  while (!flag) {
    flag = true;
    for (int i = 0; i < desalocados.size(); i++) {
      Professor prof = desalocados[i];
      bool alocado = false;
      for (int j = 0; j < prof.escolas.size() && !alocado; j++) {
        prioridade pri = prof.escolas[j];
        if (podeAlocar(prof, getEscola(e, pri.nome), pri.rank, g, &alocados, &desalocados)){
          g->addAresta(prof.nome, pri.nome, pri.rank);
          desalocados.erase(desalocados.begin() + i);
          alocados.push_back(prof);
          i--;
          alocado = true;
          flag = false;
        }
      }
      cout << 'b';
    }
      cout << 'a';
  }
}

int main () {
  vector<Professor> p;
  vector<Escola> e;

  leArquivo("entradaProjTag2.txt", &p, &e);

  // printProfessores(p);
  // printEscolas(e);

  apagaPreferencias(&p, &e);
  
  // printProfessores(p);
  // printEscolas(e);

  Grafo g;
  for (int i = 0; i < 100; i++) {
    g.addVertice(p[i]);
  }

  for (int i = 0; i < 50; i++) {
    g.addVertice(e[i]);
  }

  emparelhamento(p, e, &g);
  g.printGrafo();



  return 0;
}