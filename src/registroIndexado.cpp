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

/**
 * Sistema de consulta
 */
enum ConsultaOp {
    IGUAL,
    MENOR,
    MAIOR
};

/**
 * Sistema de consulta
 */
typedef struct {
    int valor;
    ConsultaOp op;
    FastList<tbEmpregado*> achados;
} Consulta;



Consulta consultaIdade;
Consulta consultaSalario;
Consulta consulta;

//
// Sistema de indexação
//

//Indexacao da idade
AVLTree<FastList<tbEmpregado*>*> idade;
int cmp_idade(FastList<tbEmpregado*>* a, FastList<tbEmpregado*>* b) {
    return b->peek()->idade - a->peek()->idade;
}
int search_idade(FastList<tbEmpregado*>* val) {
    if(consultaIdade.op == MENOR) return val->peek()->idade - consultaIdade.valor;
    else return consultaIdade.valor - val->peek()->idade;
}

//Indexacao da idade
AVLTree<FastList<tbEmpregado*>*> salario;
int cmp_salario(FastList<tbEmpregado*>* a, FastList<tbEmpregado*>* b) {
    return (int) (b->peek()->salario - a->peek()->salario);
}



/**
 * Função usada para inserir elementos na lista e indexa-los
 */
void inserir(string nome, int idade, float salario) {
    tbEmpregado *emp = (tbEmpregado*) malloc(sizeof(tbEmpregado));
    emp->codEmp = lista.size();
    emp->nome = nome;
    emp->idade = idade;
    emp->salario = salario;
    lista.addLast(emp);
}



/**
 * Função principal
 */
void registro_main() {
    
}



