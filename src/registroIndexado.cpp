/* 
 * File:   registroIndexado.cpp
 * Author: ilson.buss
 *
 * Created on 3 de Maio de 2011, 08:52
 */

/*


 Registro!
 *
 * Escolhe quais indices serao indexados
 *
 * Cria uma arvore com o dado desta tabela MAIS uma lista encadeada contendo
 * os indices que contem aquele dado
 *
 * TABELA: Uma lista de uma estrutura, lê ela de um arquivo
 * {ID, NOME, IDADE, SALARIO, ANOS}
 *
 * CONSULTA:
 *
 * Selecione registro com:
 * idade >= 48 E Salário >= 2200
 *
 * idade    atributo
 * >=       operador
 * 48       valor
 * E        conjuncao
 *
 *

 */

#include <cstdlib>

#include "FastList.h"
#include "AVLTree.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <Windows.h>

using namespace std;

/**
 * Estrutura da tabela empregado
 */
typedef struct {
    int codEmp;
    string nome;
    int idade;
    float salario;
} tbEmpregado;

/**
 * Onde as instancias da tabela serao armazenadas
 */
FastList<tbEmpregado*> lista;

class Consulta;
//Lista de consultadas, para depois juntar as consultas
FastList<Consulta*> consultas;
//Consulta atual sendo executada
Consulta* consultaAtual;

//Chamado quando encontra algo relacionado a consulta atual
void encontrar(FastList<tbEmpregado*>* val);

/**
 * Sistema de consulta
 */
class Consulta {
    //Busca usada quando nao está indexado
    void linearSearch() {
        FastList<tbEmpregado*> f;
        tbEmpregado* emp;
        
        for(int i = 0; i < lista.size(); i++) {
            int (*cmp)(FastList<tbEmpregado*>*, FastList<tbEmpregado*>*) = treeIndex->getCmpFunc();
            emp = lista.get(i);
            
            f.addFirst(emp);
            int dif = cmp(key, &f);
            f.removeFirst();
            if(relationalMatch(rop, dif)) {
                achados->addLast(emp);
            }
        }
    }
public:
    //Arvore de indexacao
    AVLTree<FastList<tbEmpregado*>*> *treeIndex;
    //Chave
    FastList<tbEmpregado*>* key;
    //Operadores relacionais
    RelationalOperator rop;
    //Lista de todos os achados
    FastList<tbEmpregado*>* achados;
    //Tempo de execucao
    double executionTime;

    //Construtor da consulta
    Consulta(AVLTree<FastList<tbEmpregado*>*> *tree, RelationalOperator rop) {
        this->treeIndex = tree;
        this->rop = rop;
        achados = new FastList<tbEmpregado*>();
        key = new FastList<tbEmpregado*>();
        key->addFirst(new tbEmpregado());
    }
    
    //Executa a consulta
    void execute() {
        if(achados->isEmpty() == false) {
            cout << "Consulta ja foi executada!" << endl;
            return;
        }
        //Informa que a consulta atual é essa
        consultaAtual = this;
        //Tempos para contar duração
        DWORD start, end;
        start = GetTickCount();
        //Se for indexado, executa uma busca indexada
        if(isIndexed()) {
            treeIndex->search(key, rop, encontrar);
        } else {
            //Caso contrario, uma busca linear
            linearSearch();
        }
        //Pega o tempo de duração da execucao
        end = GetTickCount();
        executionTime = ((end - start) / 1000.0);
    }

    //Checa se a consulta está indexada
    bool isIndexed() {
        return treeIndex->isEmpty() == false;
    }

    //Faz a interseção desta consulta com a outra
    void intersection(Consulta* c) {
        //Soma os tempos de execucao
        executionTime+= c->executionTime;
        //Faz a intersecao
        tbEmpregado* emp;
        for(achados->ibegin(); emp = achados->inext(); ) {
            //Se nao encontrou no outro, remove deste
            if(c->achados->contains(emp) == false) {
                achados->iremove();
            }
        }
    }

    ~Consulta() {
        delete key;
        delete achados;
    }
};

//Chamado quando encontra algo relacionado a consulta atual
void encontrar(FastList<tbEmpregado*>* val) {
    tbEmpregado* emp;
    for(val->ibegin(); emp = val->inext(); ) {
        consultaAtual->achados->addLast(emp);
    }
}

//
// Sistema de indexação
//

//Indexacao da idade
int cmp_idade(FastList<tbEmpregado*>* a, FastList<tbEmpregado*>* b) {
    return b->peek()->idade - a->peek()->idade;
}
AVLTree<FastList<tbEmpregado*>*> idade(cmp_idade);

//Indexacao da idade
int cmp_salario(FastList<tbEmpregado*>* a, FastList<tbEmpregado*>* b) {
    return (int) (b->peek()->salario - a->peek()->salario);
}
AVLTree<FastList<tbEmpregado*>*> salario(cmp_salario);


//Funcao para indexar um campo
void indexar(AVLTree<FastList<tbEmpregado*>*> &tree) {
    tbEmpregado* emp;
    FastList<tbEmpregado*> key;
    for(lista.ibegin(); emp = lista.inext(); ) {
        key.addFirst(emp);
        FastList<tbEmpregado*>* f = tree.get(&key);
        key.removeFirst();

        //Se nao foi criado, cria a lista
        if(f == null) {
            f = new FastList<tbEmpregado*>();
            f->addFirst(emp);
            tree.insert(f);
        } else {
            f->addLast(emp);
        }
    }
}

/**
 * Função usada para inserir elementos na lista e indexa-los
 */
void inserir(string nome, int idade, float salario) {
    tbEmpregado *emp = new tbEmpregado;
    emp->codEmp = lista.size();
    emp->nome = nome;
    emp->idade = idade;
    emp->salario = salario;
    lista.addLast(emp);
}

/**
 * Popula o registro
 */
void popular();




/**
 * Função principal
 */
void registro_main() {
    //Popula o registro
    popular();
    //Indexador
    bool ask = true;
    bool indexIdade = true;
    bool indexSalario = true;
    if(ask) {
        string ret;
        cout << "Deseja indexar idade? (s/n) R: ";
        cin >> ret;
        indexIdade = ret == "s";
        cout << "Deseja indexar salario? (s/n) R: ";
        cin >> ret;
        indexSalario = ret == "s";
    }
    if(indexIdade) {
        indexar(idade);
        cout << "Campo idade indexado!" << endl;
    }
    if(indexSalario) {
        indexar(salario);
        cout << "Campo salario indexado!" << endl;
    }

    //Leitor de consultas
    do {
        string ret;
        Consulta* first = null;
        cout << "***********************" << endl;
        cout << "*      CONSULTA       *" << endl;
        cout << "***********************" << endl;
        consultas.clear();
        do {
            if(consultas.isEmpty()) {
                cout << "Deseja adicionar uma restricao? (s/n) R: ";
                cin >> ret;
                if(ret == "s") {
                    cout << "Modelo: <coluna> <operador> <valor>" << endl;
                    cout << "Exemplo: idade >= 18" << endl;
                }
            } else {
                cout << "Deseja adicionar outra restricao? (s/n) R: ";
                cin >> ret;
            }
            if(ret == "s") {
                string coluna, op, val;
                cout << ">> ";
                cin >> coluna;
                cin >> op;
                cin >> val;

                RelationalOperator rop = string2relational(op);
                //Checa se o operador é invalido
                if(rop == null) {
                    cout << "operador relacional " << op << " nao encontrado!" << endl;
                } else {
                    //Checa se a consulta
                    Consulta* c = null;
                    if(coluna == "salario") {
                        c = new Consulta(&salario, rop);
                        c->key->peek()->salario = atof(val.c_str());
                    } else if(coluna == "idade") {
                        c = new Consulta(&idade, rop);
                        c->key->peek()->idade = atoi(val.c_str());
                    }
                    //Checa se gerou uma consulta
                    if(c) {
                        consultas.addLast(c);
                        //Ja faz a busca dessa expressao
                        c->execute();
                        //Checa por interseção
                        if(first == null) first = c;
                        else first->intersection(c);
                        //Numero
                        cout << first->achados->size() << " registros!" << endl;
                    } else {
                        cout << "coluna '" << coluna << "' nao encontrada!" << endl;
                    }
                }
            }
        } while(ret == "s");

        //Checa se há restricoes, realiza consultas
        if(consultas.isEmpty() == false) {
            //Mostra o que foi encontrado
            tbEmpregado* emp;
            FastList<tbEmpregado*>* achados = first->achados;
            cout << "-----------------------------------------" << endl;
            cout << setw(15) << "NOME     ";
            cout << setw(6) << "IDADE";
            cout << setw(12) << "SALARIO";
            cout << setw(5) << "ID" << endl;
            for(achados->ibegin(); emp = achados->inext() ; ) {
                cout << setw(15) << emp->nome;
                cout << setw(6) << emp->idade;
                cout.setf(ios::fixed,ios::floatfield);
                cout.precision(2);
                cout << setw(12) << emp->salario;
                cout << setw(5) << emp->codEmp << endl;
            }
            cout << "-----------------------------------------" << endl;
            cout << "Consulta encontrou " << achados->size() << " registros. (" << first->executionTime << " s)" << endl;
            system("pause");
            system("cls");
        }
    } while(consultas.isEmpty() == false);
    
    //Condicoes, adicionando condicoes...
    // Mostrar retorno, apos E merge com todas as consultas

//    consultaAtual = new Consulta(&salario, LESS);
//    //Altera valor da chave
//    consultaAtual->key->peek()->salario = 3500.0f;
//    //Executa consulta
//    consultaAtual->execute();
}



void popular() {
    char nome[50];
    int idade;
    float salario;

    FILE* f = fopen("registro.txt", "r");
    if(f != NULL) {
        while(! feof(f)) {
            fgets(nome, 50, f); int len = strlen(nome);
            if(nome[len-1] == '\n') nome[len-1] = '\0';
            fscanf(f, "%d\n%f\n", &idade, &salario);
            inserir( string(nome), idade, salario);
        }
        fclose(f);

        cout << "Sistema populado com " << lista.size() << " registros." << endl;
    } else cout << "Nao conseguir abrir registro.txt" << endl;
}
