/* 
 * File:   BinaryTree.h
 * Author: ilson.buss
 *
 * Created on 12 de Abril de 2011, 09:08
 */

#ifndef BINARYTREE_H
#define	BINARYTREE_H

#include <iostream>
#include <iomanip>
#include "Branch.h"

using namespace std;


//Comparador genérico
int _generic_compare(int a, int b);

//Classe que contém uma arvore binária
template <class T>
class BinaryTree {
    //Raiz da arvore
    Branch<T>* root;
    //Função comparadora
    int (*cmp)(T, T);

    //Imprime uma arvore
    void printTree(Branch<T>* b, int curd) {
        if(b != null) {
            Branch<T>* parent = b->parent;

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

    //Coração da impressao inordem
    void printInOrdem(Branch<T>* b) {
        if(b) {
            printInOrdem(b->left);
            cout << b->data << " ";
            printInOrdem(b->right);
        }
    }

    //Obtém o ramo do dado ou nulo se nao achar
    Branch<T>* getBranch(T data) {
        if(root == null) return null;

        //Inicia varredura com a raiz
        Branch<T>* b = root;
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

public:
    //Cria uma arvore binaria
    BinaryTree() {
        root = null;
        cmp = (int (*)(T, T)) _generic_compare;
    }

    //Cria uma arvore binaria, informando a funcao comparadora
    BinaryTree(int (*compareFunction)(T, T)) {
        root = null;
        cmp = compareFunction;
    }

    //Insere um elemento na arvore
    void insert(T data) {
        //Se a raiz é nula, atribui ela
        if(root == null) {
            root = new Branch<T>(data);
            return;
        }

        //Inicia varredura com a raiz
        Branch<T>* parent = null;
        Branch<T>* b = root;
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
    }

    //Remove um elemento da arvore
    bool remove(T data) {
        Branch<T>* b = getBranch(data);
        if(b == null) return false;
        bool isRoot = b == root;

        //Remove e retorna quem ficou no lugar
        Branch<T>* replace = b->removeMe();
        //Se for root altera o root
        if(isRoot) root = replace;
        //Retorna sucesso
        return true;
    }

    //Checa se o elemento existe
    bool contains(T data) {
        return getBranch(data) != null;
    }

    //Retorna um valor a partir de uma chave
    //NOTA: O tipo do valor é generico, deve ser informado e também informar a funcao
    //      que extrai o valor a partir de uma chave
    template <class V>
    V search(T key, V(*valFunc)(T) ) {
        Branch<T>* b = getBranch(key);
        if(b == null) return null;
        else return valFunc(b->data);
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
                cout << "-- Arvore_Binaria(altura=" << getHeight() << ") -- " << endl;
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

};

#endif	/* BINARYTREE_H */

