/* 
 * File:   AVLTree.h
 * Author: ilson.buss
 *
 * Created on 5 de Abril de 2011, 08:59
 */

#ifndef AVLTREE_H
#define	AVLTREE_H


#include <iostream>
#include <iomanip>
#include "AVLBranch.h"
#include "operators.h"

using namespace std;


//Comparador genérico
int _generic_compare(int a, int b);

//Classe que contém uma arvore binária
template <class T>
class AVLTree {
    //Raiz da arvore
    AVLBranch<T>* root;
    //Função comparadora
    int (*cmp)(T, T);

    //Imprime uma arvore
    void printTree(AVLBranch<T>* b, int curd) {
        if(b != null) {
            AVLBranch<T>* parent = b->parent;

            cout << setw(2 * curd) << "" << b->data << " (";
            if(parent) {
                if(b == parent->left) cout << "LEFT";
                else if(b == parent->right) cout << "RIGHT";
                else cout << "ERROR";
            } else cout << "ROOT";
            cout << ")" << endl;

            printTree(b->left, curd + 1);
            printTree(b->right, curd + 1);
        }
    }

    //Busca
    void search(AVLBranch<T>* b, T key, int dif, RelationalOperator rop, void(*findFunc)(T)) {
        int ldif = b->left ? cmp(key, b->left->data) : 0;
        int rdif = b->right ? cmp(key, b->right->data) : 0;
        //Checa se a diferenca esta de acordo com o operador relacional
        bool found = relationalMatch(rop, dif);
        //Vai para os filhos procurar
        if(b->left) search(b->left, key, ldif, rop, findFunc);
        if(b->right) search(b->right, key, rdif, rop, findFunc);
        //Se achou, acha a funcao de encontrar
        if(found) findFunc(b->data);
    }
    
    //Coração da impressao inordem
    void inOrdem(AVLBranch<T>* b, void(*func)(T)) {
        if(b) {
            inOrdem(b->left, func);
            func(b->data);
            inOrdem(b->right, func);
        }
    }

    //Coração da impressao inordem
    void printInOrdem(AVLBranch<T>* b) {
        if(b) {
            printInOrdem(b->left);
            cout << b->data << " ";
            printInOrdem(b->right);
        }
    }

    //Obtém o ramo do dado ou nulo se nao achar
    AVLBranch<T>* getBranch(T data) {
        if(root == null) return null;

        //Inicia varredura com a raiz
        AVLBranch<T>* b = root;
        int comp;
        //Enquanto o valor da raiz
        while(b != null) {
            //Faz a comparacao e armazena numa variavel
            comp = cmp(data, b->data);
            //Escolhe em qual ramo continuar
            if(comp > 0) b = b->right;
            else if(comp < 0) b = b->left;
            else break; //É igual, para o while
        }
        //Retorna o ramo onde parou ou nulo se nao achou
        return b;
    }

    //Rotaciona o ramo para esquerda
    void rotateToRight(AVLBranch<T> *p) {
        AVLBranch<T> *q = p->left;
        AVLBranch<T> *aux = q->right;
        q->right = p; q->parent = p->parent; p->parent = q;
        p->left = aux; if(aux) aux->parent = p;
        
        //Checa se precisa trocar a raiz
        if(root == p) root = q;
        else {
            if(q->parent->left == p) q->parent->left = q;
            else if(q->parent->right == p) q->parent->right = q;
            else cout << "Reference error in rotateLeft" << endl;
        }
    }

    //Rotaciona o ramo para direita
    void rotateToLeft(AVLBranch<T> *p) {
        AVLBranch<T> *q = p->right;
        AVLBranch<T> *aux = q->left;
        q->left = p; q->parent = p->parent; p->parent = q;
        p->right = aux; if(aux) aux->parent = p;

        //Checa se precisa trocar a raiz
        if(root == p) root = q;
        else {
            if(q->parent->left == p) q->parent->left = q;
            else if(q->parent->right == p) q->parent->right = q;
            else cout << "Reference error in rotateRight" << endl;
        }
    }

public:
    //Cria uma arvore binaria
    AVLTree() {
        root = null;
        cmp = (int (*)(T, T)) _generic_compare;
    }

    //Cria uma arvore binaria, informando a funcao comparadora
    AVLTree(int (*compareFunction)(T, T)) {
        root = null;
        cmp = compareFunction;
    }

    //Insere um elemento na arvore
    void insert(T data) {
        //Se a raiz é nula, atribui ela
        if(root == null) {
            root = new AVLBranch<T>(data);
            return;
        }

        //Inicia varredura com a raiz
        AVLBranch<T>* parent = null;
        AVLBranch<T>* b = root;
        int comp;
        //Enquanto o valor da raiz
        while(b != null) {
            //O pai será o atual
            parent = b;
            //Faz a comparacao e armazena numa variavel
            comp = cmp(data, b->data);
            //Escolhe em qual ramo continuar
            if(comp >= 0) b = b->right;
            else b = b->left;
        }

        //Escolhe onde inserir
        if(comp >= 0) parent->insertRight(data);
        else parent->insertLeft(data);

        //AVL propriamente dito
        //Obtém o pai do pai, para checar problemas de balanceamento
        b = parent->parent;
        int rbf;
        int lbf;
        while(b != null) {
            //Checa por rotacao
            switch(b->getBalanceFactor()) {
                case -2:
                    rbf = b->right->getBalanceFactor();
                    //Depuração
                    //cout << "Rotate to left" << endl;
                    if(rbf < 0) {
                        rotateToLeft(b);
                    } else {
                        rotateToRight(b->right);
                        rotateToLeft(b);
                    }
                    break;
                case 2:
                    lbf = b->left->getBalanceFactor();
                    //Depuração
                    //cout << "Rotate to right" << endl;
                    if(lbf > 0) {
                        rotateToRight(b);
                    } else {
                        rotateToLeft(b->left);
                        rotateToRight(b);
                    }
                    break;
            }
            //Proximo pai para checar balanceamento
            b = b->parent;
        }
    }

    //Remove um elemento da arvore
    bool remove(T data) {
        AVLBranch<T>* b = getBranch(data);
        if(b == null) return false;
        bool isRoot = b == root;

        //Remove e retorna quem ficou no lugar
        AVLBranch<T>* replace = b->removeMe();
        //Se for root altera o root
        if(isRoot) root = replace;
        //Retorna sucesso
        return true;
    }

    //Checa se o elemento existe
    bool contains(T data) {
        return getBranch(data) != null;
    }

    //Obtém o elemento a partir de uma chave (nota usado para funcoes cmp exclusiva)
    T get(T key) {
        AVLBranch<T>* b = getBranch(key);
        return b ? b->data : null;
    }

    //Retorna um valor a partir de uma chave
    //NOTA: O tipo do valor é generico, deve ser informado e também informar a funcao
    //      que extrai o valor a partir de uma chave
    template <class V>
    V search(T key, V(*valFunc)(T) ) {
        AVLBranch<T>* b = getBranch(key);
        if(b == null) return null;
        else return valFunc(b->data);
    }

    void search(int(*searchFunc)(T) ) {
        if(root == null) return null;

        //Inicia varredura com a raiz
        AVLBranch<T>* b = root;
        int comp;
        //Enquanto o valor da raiz
        while(b != null) {
            //Faz a comparacao e armazena numa variavel
            comp = searchFunc(b->data);
            //Escolhe em qual ramo continuar
            if(comp > 0) b = b->right;
            else if(comp < 0) b = b->left;
            else break; //É igual, para o while
        }
    }

    //Forma de buscar algo a partir de um operador relacional e uma funcao para encontrar dados achados
    void search(T key, RelationalOperator rop, void(*findFunc)(T)) {
        if(root) search(root, key, cmp(key, root->data), rop, findFunc);
    }

    // Varre a arvore em inOrdem, passando um funcao para realizar algo
    void inOrder(void(*func)(T)) {
        inOrder(root, func);
    }

    //Imprime arvore na sequencia in-ordem
    void printInOrder() {
        printInOrdem(root);
        cout << " " << endl;
    }

    //Imprime arvore na sequencia pre-ordem
    void printPreOrder() {
        //TODO
    }

    //Imprime arvore na sequencia pos-ordem
    void printPostOrder() {
        //TODO
    }

    //Obtém a altura da arvore
    int getHeight() {
        if(root == null) return -1;
        else return root->getHeight();
    }

    //Checa se arvore está vazia
    bool isEmpty() {
        return getHeight() == -1;
    }

    //Imprime arvore
    void print() {
        cout << "--" << endl;
        if(root) {
            printTree(root, 0);
        } else {
            cout << "<vazio>" << endl;
        }
        cout << "--" << endl;
    }

    // Console interativo para arvore binaria
    void shell() {
        int choose;
        T val;
        do {
                cout << "-- Arvore_AVL(altura=" << getHeight() << ") -- " << endl;
                cout << "1: Inserir" << endl;
                cout << "2: Remover" << endl;
                cout << "3: Existe?" << endl;
                cout << "4: Mostrar (profundidade)" << endl;
                cout << "5: Mostrar (pre ordem)" << endl;
                cout << "6: Mostrar (in ordem)" << endl;
                cout << "7: Mostrar (pos ordem)" << endl;
                cout << "8: Sair" << endl;

                cout << "Escolha: ";
                cin >> choose;

                switch(choose) {
                case 1: //Inserir
                        cout << "digite: ";
                        cin >> val;
                        insert(val);
                        cout << "Add." << endl;
                        Sleep(500);
                        system("cls");
                        break;
                case 2: //Remover
                        cout << "digite: ";
                        cin >> val;
                        if(remove(val)) cout << "Removido." << endl;
                        else cout << "Nao encontrou." << endl;
                        Sleep(500);
                        system("cls");
                        break;
                case 3: //Existe?
                        cout << "digite: ";
                        cin >> val;
                        if(contains(val)) cout << "Existe." << endl;
                        else cout << "Nao existe." << endl;
                        Sleep(500);
                        system("cls");
                        break;
                case 4: //Mostra (profundindade)
                        print();
                        system("pause");
                        system("cls");
                        break;
                case 5: //Mostra (pre ordem)
                        printPreOrder();
                        system("pause");
                        system("cls");
                        break;
                case 6: //Mostra (in ordem)
                        printInOrder();
                        system("pause");
                        system("cls");
                        break;
                case 7: //Mostra (pos ordem)
                        printPostOrder();
                        system("pause");
                        system("cls");
                        break;
                case 8:
                        break;
                default:
                        cout << "Opcao invalida!" << endl;

                        Sleep(500);
                        system("cls");
                }

        } while(choose != 8);
    }

    //Retorna o ponteiro da funcao comparadora
    int (*getCmpFunc())(T, T) {
        return cmp;
    }

};

#endif	/* AVLTREE_H */

