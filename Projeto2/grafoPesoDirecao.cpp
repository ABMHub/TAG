#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <list>
#include <set>

using namespace std;

/*
  Struct prioridade serve para guardar o nome e a prioridade de uma escola
  Eh usada junto com a classe professor, para montar sua lista de prioridades
  Essencial para guardar o rank prioridade mesmo se a estrutura da lista for alterada
*/
typedef struct prioridade {
  string nome;
  int rank;
} prioridade;

class Vertice;

/*
  Classe Aresta serve para guardar informacoes associadas a uma aresta de um grafo
  Para este projeto, a aresta guarda o numero da vaga ocupada pela associacao escola-professor,
  assim como o grau de prioridade que o professor da a essa escola, alem do endereco oridem e destino dos vertices terminais
*/
class Aresta {
  public:
    Vertice* origem;
    Vertice* destino;
    int prioridade;
    int vaga;

    // Construtor de uma aresta
    Aresta(Vertice* origem, Vertice* destino, int prioridade, int vaga) {
      this->origem = origem;
      this->destino = destino;
      this->prioridade = prioridade;
      this->vaga = vaga;
    }

    // Operador para comparacoes
    bool operator==(const Aresta a) const {
      if (destino == a.destino) 
        if (prioridade == a.prioridade)
          return true;

      return false;
      
    }

    // Operador para comparacoes
    bool operator!=(const Aresta a) const {
      if (destino != a.destino) 
        if (prioridade != a.prioridade)
          return true;

      return false;
      
    }
};

/* Classe Vertice:
Guarda nome, lista de adjacencia e grau de cada vertice
Usa metodo proprio para adicionar aresta entre vertices
*/
class Vertice {
  public:
    string nome;
    list<Aresta> lista;
    int grau;

    // Construtor para retornos vazios;
    Vertice() {
      this->nome = "Vazio";
      this->grau = 0;
    }

    // Construtor
    Vertice(string nome) {
      this->nome = nome;
      this->grau = 0;
    }

    /*
      Metodo para adicionar aresta entre vertice 'this' e 'b',
      passando os parametros necessarios para o construtor da aresta
    */
    Aresta addAresta (Vertice* b, int prioridade, int vaga) {
      // cout << "Adicionando aresta entre " << nome << " e " << b->nome << "\n";
      Aresta a(this, b, prioridade, vaga);
      if (vaga == 0)
        lista.push_front(a);
      else 
        lista.push_back(a);
      grau++;
      return a;
    }
    
    // Metodo que remove aresta entre vertice 'this' e vertice 'a'
    void removeAresta(Vertice a) {
      for (auto it = lista.begin(); it != lista.end(); ++it) {
        if (*(it->destino) == a) {
          lista.remove(*it);
          grau--;
          return;
        }
      }
    }

    // Operador para comparacoes
    bool operator==(Vertice v) {
      if (v.nome.compare(nome) != 0)
        return false;
      
      if (v.lista != lista)
        return false;
      
      return true;
    }

    // Operador para comparacoes
    bool operator!=(Vertice v) {
      if (v.nome.compare(nome) == 0)
        return false;
      
      if (v.lista == lista)
        return false;
      
      return true;
    }
    /* 
      Funcao para checar se ha vertice v na lista de adjacentes do vertice
      Usado pelo metodo Grafo::hasIncoming
    */
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
  Classe escola, usada para guardas os dados de cada escola individualmente,
  assim como um construtor especializado para ler os dados dirato do arquivo.
*/
class Escola {
  public:
    string nome;
    vector<int> habilitacao;

    // Construtor da escola, para retornos vazios de funcao
    Escola() {
      nome = "vazio";
    }

    // Construtor que recebe uma linha inteira do arquivo de input, processa os dados e instancia o objeto
    Escola(string dados) {
      unsigned int i = 0;
      bool flag = false;

      // Encontra o final do nome da escola
      while (!flag) {
        if (dados.at(i) == ')') {
          flag = true;
          i--;
        }
        i++;
      }

      // Nome da escola eh igual ao char 1 ate o char i, encontrado anteriormente
      this->nome = dados.substr(1, i - 1);
      i++;
      flag = false;

      // Analisa as habililitacoes necessarias da escola e coloca em um vetor
      while (!flag){
        if (dados.size() > i+2) {
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
      for(unsigned int i = 0; i < habilitacao.size(); i++) {
        if (h >= habilitacao[i]) {
          return true;
        }
      }
      return false;
    }
};

/* 
  Classe professor, usada para guardas os dados de cada professor individualmente,
  assim como um construtor especializado para ler os dados dirato do arquivo.
*/
class Professor {
  public:
    string nome;
    int habilitacao;
    vector<prioridade> escolas;

    Professor() {
      nome = "Vazio";
      habilitacao = 0;
    }

    // Construtor que recebe uma linha inteira do arquivo de input, processa os dados e instancia o objeto
    Professor(string dados) {
      int i = 0;
      bool flag = false;

      // Encontra o final do nome do professor
      while (!flag) {
        if (dados.at(i) == ',') {
          flag = true;
          i--;
        }
        i++;
      }
      
      // Salva nome do professor
      this->nome = dados.substr(1, i - 1);

      // Salva habilitacao do professor
      i += 2;
      this->habilitacao = stoi(dados.substr(i, 1));

      // Encontra lista de preferencia de escolas
      i += 5;
      int j = i - 1;  // j eh um contador de chars auxiliar, que sempre marcara o inicio de um nome de escola
      flag = false;   // Flag para sinalizar o final do loop
      int rank = 1;   // Rank sera um contador, sendo que a primeira posicao da lista sera o rank 1
      while (!flag) {
        // Se encontrarmos ')' ou ',', chegamos ao final de algum nome de escola
        if (dados.at(i) == ')' || dados.at(i) == ',') {
          j++;
          prioridade pri;
          pri.nome = dados.substr(j, i - j);
          pri.rank = rank;
          // Salva struct na lista de prioridades
          this->escolas.push_back(pri);
          // Se encontramos um ')', chegamos ao final. A flag sera ativada e o loop encerrado
          if (dados.at(i) == ')') {
            flag = true;
          }
          rank ++;
        }
        // Sempre que encontrarmos um espaco em branco, moveremos j para essa posicao, marcando o inicio de um nome de escola
        else if (dados.at(i) == ' ') {
          j = i;
        }
        i++;
      }
    }

    // Comparador implementado para a funcao sort, usada na funcao 'emparelhamento'
    bool operator<(Professor b) {
      if (this->habilitacao > b.habilitacao)
        return false;

      if (this->habilitacao < b.habilitacao)
        return true;

      if (this->nome < b.nome)
        return true;

      return false;
          
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
    int numVertices;

    // Metodo para adicionar no grafo um vertice de professor
    bool addVertice (Professor p) {
      Vertice v(p.nome);
      vertices.push_back(v);
      numVertices++;
      return true;
    }

    // Metodo para adicionar no grafo um vertice de escola
    bool addVertice (Escola e) {
      Vertice v(e.nome);
      vertices.push_back(v);
      numVertices++;
      return true;
    }

    // Metodo para encontrar no grafo um vertice, baseado no seu nome
    Vertice getVertice (string nome) {
      for (auto it = vertices.begin(); it != vertices.end(); ++it) {
        if (it->nome.compare(nome) == 0) {
          return *it;
        }
      }
      return Vertice();
    }

    // Metodo para adicionar aresta entre dois vertices determinados pelo nome
    bool addAresta(string origem, string destino, int prioridade, int vaga) {
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
      // Adiciona aresta entre os dois vertices, bidirecionalmente
      it1->addAresta(&(*it2), prioridade, vaga);
      it2->addAresta(&(*it1), prioridade, vaga);

      return true;
    }

    // Metodo para remover aresta, baseado no nome dos dois vertices terminais
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

    // Metodo para descobrir quantas arestas estao apontando para determinado vertice.
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
        if (it->nome == "E1") cout << "\n";
        cout << it->nome;
        cout << " associado a: ";
        for (std::list<Aresta>::iterator it2 = it->lista.begin(); it2 != it->lista.end(); ++it2){
          cout << "(nome = " << it2->destino->nome << ", preferencia = " << it2->prioridade << ", vaga = " << it2->vaga + 1 << ") ";
        }
        cout << "\n";
      }
    }
};

/*
  Funcao que le o arquivo de entrada e salva os dados em dois vetores,
  um contendo a lista de escolas, e o outro contendo a lista de professores
*/
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

  // Salva o conteudo processado nos ponteiros passados
  *pptr = p;
  *eptr = e;
}

// Funcao para encontrar determinado professor em determinado vetor, retornando a posicao dele
int getProfessor(vector<Professor> v, string nome) {
  for (unsigned int i = 0; i < v.size(); i++) {
    if (v[i].nome == nome)
      return i;
  }
  return -1;
}

// Funcao para encontrar determinada escola em determinado vetor, retornando o proprio objeto
Escola getEscola(vector<Escola> e, string nome) {
  for (unsigned int i = 0; i < e.size(); i++) {
    if (e[i].nome == nome)
      return e[i];
  }
  return Escola();
}

// Funcao que indica se determinada vaga, de determinada escola, esta ocupada ou nao
bool isVagaOcupada (Vertice v, int vaga) {
  for (auto i = v.lista.begin(); i != v.lista.end(); i++) {
    if (i->vaga == vaga) {
      return true;
    }
  }
  return false;
}

// Funcao que diz se determinado professor tem uma outra escola com vagas em sua lista de prioridades
bool temEscolaDisponivel(Professor profAntigo, vector<Escola> e, Grafo g) {
  Vertice p = g.getVertice(profAntigo.nome);
  string escAssociada = p.lista.begin()->destino->nome;

  for (unsigned int i = 0; i < profAntigo.escolas.size(); i++) {
    string nomeEscola = profAntigo.escolas[i].nome;

    // Pula a escola em que o professor ja esta associado
    // ? eh necessario pular ?
    if (nomeEscola != escAssociada) {
      Escola esc = getEscola(e, nomeEscola);
      Vertice v = g.getVertice(nomeEscola);
      
      for (unsigned int j = 0; j < esc.habilitacao.size(); j++) {
        // Se o professor tiver habilitacao suficiente, e a vaga estiver desocupada, retorna true
        if (esc.habilitacao[j] <= profAntigo.habilitacao && !isVagaOcupada(v, j)) {
          return true;
        }
      }
    }
  }
  // Caso nao encontre vaga, retorna false
  return false;
}

/*
  Funcao para decidir o 'vencedor' em uma disputa de vagas
  O vencedor sera sempre o que mais quer a escola, se tiver a habilitacao necessaria
  Em caso de empate, sera escolhido o com menor habilitacao (mas no minimo a necessaria)
  Em caso de novo empate, veremos se o professor atualmente alocado (profAntigo) pode ir para outra escola com vaga vazia
  Retorna true caso o professor desalocado ganhe o 'duelo'. Caso contrario, retorna false
*/
bool disputaDeVagas(Professor prof, Professor profAntigo, Escola esc, Vertice v, int vaga, int rank, vector<Escola> e, Grafo g) {
  // Se o professor desalocado nao tiver habiltiacao o suficiente, ele eh eliminado
  if (esc.habilitacao[vaga] > prof.habilitacao)
    return false;

  else {
    // Instancia aresta
    list<Aresta>::iterator disputada;
    // Primeira vaga (vaga 0)
    if (vaga == 0) {
      disputada = v.lista.begin();
    }
    // Segunda vaga (vaga 1)
    else {
      disputada = v.lista.end();
      disputada--;
    }

    // Caso o professor alocado queira menos a escola que o professor desalocado
    // ou, em caso de empate, o professor desalocado tenha menos habilitacao, havera a substituicao
    if (rank < disputada->prioridade || (rank == disputada->prioridade && prof.habilitacao < profAntigo.habilitacao)) {
      return true;
    }

    // Segundo desempate: caso o professor alocado consiga ir para outra escola vazia
    else if (rank == disputada->prioridade && prof.habilitacao == profAntigo.habilitacao && temEscolaDisponivel(profAntigo, e, g)) {
      return true;
    }

    return false;
  }
}

// Descobre qual professor esta alocado em determinada vaga
string getVagaOcupada(Vertice v, int vaga) {
  for (auto i = v.lista.begin(); i != v.lista.end(); i++)  {
    if (i->vaga == vaga) {
      return i->destino->nome;
    }
  }
  return "";
}

// Ve se a escola esta com todos as vagas desocupadas
bool escolaVazia (Vertice v, Grafo g) {
  if(g.hasIncoming(v) == 0) {
    return true;
  }
  return false;
}

// Funcao faz emparelhamento maximo, alocando professores apenas para suas escolas desejadas
vector<Professor> emparelhamento(vector<Professor> * professores, vector<Escola> e, Grafo *g) {
  vector<Professor> desalocados = *professores;

  // Ordena vetor de professores na ordem crescente de habilitacao
  sort(desalocados.begin(), desalocados.end());
  vector<Professor> alocados;
  bool flag = false;

  // For loop pelos professores desalocados
  for (unsigned int i = 0; i < desalocados.size(); i++) {

    // pedaco de codigo para printar o estado do grafo a cada 40 professores analisados.
    // como o codigo repete o 'i' varias vezes, quando professores sao substituidos,
    // essa logica e necessaria para evitar um desnecessario numero de prints
    if (alocados.size() % 25 == 0 && alocados.size() != 0) {
      flag = true;
    }
    else if (flag == true) {
      cout << "\n -----------------" << alocados.size() << " professores alocados. -------------------- \n";
      g->printGrafo();
      flag = false;
    }

    Professor prof = desalocados[i];
    bool alocado = false;

    // For loop pela lista de prioridade de cada professor
    for (unsigned int j = 0; j < prof.escolas.size() && !alocado; j++) {
      prioridade pri = prof.escolas[j];
      Escola esc = getEscola(e, pri.nome);
      Vertice v = g->getVertice(esc.nome);


      bool inv = false;
      // Caso a segunda vaga da escola seja apropriada para o professor, inverteremos o proximo loop
      if (esc.habilitacao.size() == 2 && esc.habilitacao[0] < esc.habilitacao[1]) {
        inv = true;
      }

      // For loop pela vaga de cada escola
      for (unsigned int l = 0; l < esc.habilitacao.size() && !alocado; l++) {
        int k;                          // Variavel auxiliar para inverter o loop
        if (inv && l == 0) k = 1;       // Caso inv esteja true, inverteremos o loop
        else if (inv && l == 1) k = 0;  
        else k = l;                     // Caso contrario, o loop ocorrera normalmente
        
        // Se o professor tiver o minimo de habilitacao, veremos se ele tera concorrencia para a vaga
        // Se o professor for de habilitacao 3, ele entrara apenas em escolas que requerem habilitacao 3
        if (esc.habilitacao[k] <= prof.habilitacao && !(prof.habilitacao == 3 && esc.habilitacao[k] < 3)) {
          // Caso a vaga esteja vazia, o professor ocupara a vaga
          if (!isVagaOcupada(v, k)) {
            desalocados.erase(desalocados.begin() + i);
            alocados.push_back(prof);
            g->addAresta(prof.nome, esc.nome, pri.rank, k);

            i--;
            alocado = true;
          }
          // Caso a vaga nao esteja vazia, veremos qual professor permanecera nela
          else {
            int pos = getProfessor(alocados, getVagaOcupada(v, k));
            Professor profAntigo = alocados[pos];
            // Se o professor desalocado for mais apropriado para a vaga que o alocado, havera uma troca
            if (disputaDeVagas(prof, profAntigo, esc, v, k, pri.rank, e, *g)) {
              prof.escolas.erase(prof.escolas.begin() + j);
              alocados.erase(alocados.begin() + pos);
              // O professor recem-desalocado sera o proximo a ser avaliado
              desalocados[i] = profAntigo;
              g->removeAresta(esc.nome, profAntigo.nome);

              alocados.push_back(prof);
              g->addAresta(prof.nome, esc.nome, pri.rank, k);
              i--;
              // Encerra loops k e j
              alocado = true;
            }
          }
        }
      }
    }
  }
  
  *professores = desalocados;
  return alocados;
}
/* 
  Funcao para alocar todos os professores que sobraram.
  Alocara todos com prioridade 5, ou seja, prioridade menor que a menor prioridade da lista de prioridade
*/
vector<Professor> alocaSobras(vector<Professor> * professores, vector<Professor> alocados, vector<Escola> e, Grafo *g) {
  vector<Professor> desalocados = *professores;

  // Ordena vetor de professores na ordem crescente de habilitacao
  sort(desalocados.begin(), desalocados.end());

  // Faz 2 loops. O primeiro preenchera todas as escolas vazias, o segundo alocara os professores que sobrarem
  for (unsigned int l = 0; l < 2; l++) {
    // For loop pelos professores desalocados
    for (unsigned int i = 0; i < desalocados.size(); i++) {
      Professor prof = desalocados[i];
      bool alocado = false;

      // For loop por todas as escolas
      for (unsigned int j = 0; j < e.size() && !alocado; j++) {
        Escola esc = e[j];
        Vertice v = g->getVertice(esc.nome);
        
        // For loop por todas as vagas da escola
        for (unsigned int k = 0; k < esc.habilitacao.size() && !alocado; k++) {
          // Se estivermos no primeiro loop, apenas avaliaremos as escolas vazias
          // Caso for o segundo loop, avaliaremos todas as vagas
          if (!(l == 0 && !escolaVazia(v, *g)) && esc.habilitacao[k] <= prof.habilitacao) {
            // Caso a vaga esteja vazia, o professor ocupara a vaga
            if (!isVagaOcupada(v, k)) {
              desalocados.erase(desalocados.begin() + i);
              alocados.push_back(prof);
              g->addAresta(prof.nome, esc.nome, 5, k);

              i--;
              alocado = true;
            }
            // Caso a vaga nao esteja vazia, veremos qual professor permanecera nela
            else {
              int pos = getProfessor(alocados, getVagaOcupada(v, k));
              Professor profAntigo = alocados[pos];
              if (disputaDeVagas(prof, profAntigo, esc, v, k, 5, e, *g)) {
                alocados.erase(alocados.begin() + pos);
                // O professor recem-desalocado sera o proximo a ser avaliado
                desalocados[i] = profAntigo;

                g->removeAresta(esc.nome, profAntigo.nome);
                alocados.push_back(prof);
                g->addAresta(prof.nome, esc.nome, 5, k);
                i--;
                // Encerra loops k e j
                alocado = true;
              }
            }
          }
        }
      }
    }
  }
  *professores = desalocados;
  return alocados;
}

int main () {
  vector<Professor> p;
  vector<Escola> e;

  // Chama funcao de ler arquivo, passando como parametros os ponteiros dos vetores de prof e escola
  leArquivo("entradaProjTag2.txt", &p, &e);

  // Inicializa vertices do grafo. 100 para professores, 50 para escolas
  Grafo g;
  for (int i = 0; i < 100; i++) {
    g.addVertice(p[i]);
  }

  for (int i = 0; i < 50; i++) {
    g.addVertice(e[i]);
  }

  // Variaveis para salvar os dois estados do programa
  vector<Professor> p1;
  vector<Professor> p2;
  Grafo g1;

  // Salva estado antes de alocar os professores sobrando
  p1 = emparelhamento(&p, e, &g);
  // Salva grafo antes de alocar os professores que sobraram
  g1 = g;
  // Salva estado pos-termino do programa
  p2 = alocaSobras(&p, p1, e, &g);

  cout << "\n----------- FIM DO PRIMEIRO LOOP. RESULTADO: -----------\n";
  cout << "\n----------- Emparelhamento utilizando apenas a lista de preferencia -----------\n\n";
  g1.printGrafo();

  cout << "\n";
  cout << "Professores satisfeitos: " << p1.size() << "\n";
  cout << "Professores alocados: " << p1.size() << "\n";

  cout << "\n----------- Emparelhamento alocando todos os professores que restam -----------\n\n";
  g.printGrafo();

  cout << "\n";
  cout << "Professores satisfeitos: " << p1.size() << "\n";
  cout << "Professores alocados: " << p2.size() << "\n";

  return 0;
}