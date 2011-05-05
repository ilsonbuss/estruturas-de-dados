/* 
 * File:   LinkedList.h
 * Author: ilson.buss
 *
 * Created on 15 de Março de 2011, 09:12
 */

#include <string>
#include <vector>
#include <iostream>
#include <Windows.h>
#include "List.h"


using namespace std;

#ifndef LINKEDLIST_H
#define	LINKEDLIST_H

#define null 0

template <class T>
struct No {
    T data;
    No* next;

    //Inicia um no, nota que neste construtor o campo next não é iniciado
    No(T data) {
        this->data = data;
    }

    //Inicia um no
    No(T data, No* next) {
        this->data = data;
        this->next = next;
    }

    //Função auxiliar para inserir um nó depois deste
    No *insertAfter(T dado) {
        //Cria um novo nó indicando o dado e que o proximo
        No<T> *p = new No<T>(dado, next);
        //Indica que o proximo nó deste é o que foi criado agora
        next = p;
        //Retorna o nó criado
        return p;
    }

    //Função auxiliar para remover um nó depois deste
    T removeAfter() {
        //Proximo deve ser diferente de nulo
        if(next != null) {
            //Obtém o next antigo
            No<T> *oldNext = next;
            //Atualiza next com o next do oldNext
            next = oldNext->next;
            //Obtém o dado do nó removido
            T tmpData = oldNext->data;
            //Deleta da memorio o no
            delete oldNext;
            //Retorna o dado do nó removido
            return tmpData;
        } else {
            return null;
        }
    }
};

//Comparador genérico
int _generic_compare(int a, int b);

template <class T>
class LinkedList {
    int curSize;
    No<T> *first;
    No<T> *last;
    int (*cmp)(T, T);
public:

    //Inicia uma lista encadeada
    LinkedList() {
        //Tamanho vazio
        curSize = 0;
        //Inicia os no nulo
        first = null;
        last = null;
        //Inicia comparador
        cmp = (int (*)(T, T)) _generic_compare;
    }

    //Inicia uma lista encadeada
    LinkedList(int (*compareFunction)(T, T)) {
        //Tamanho vazio
        curSize = 0;
        //Inicia os no nulo
        first = null;
        last = null;
        //Inicia comparador
        cmp = compareFunction;
    }

    //Destroi a lista
    ~LinkedList() {
        clear();
    }

    //Checa se a lista está vazia
    bool isEmpty() {
        return curSize < 1;
    }

    //Insere no primeiro elemento da lista
    void addFirst(T data) {
        //Aloca No com dado e o next = first
        No<T> *p = new No<T>(data, first);
        //Indica que o novo no sera o primeiro da lista
        first = p;

        //Se o last for nulo, o primeiro também sera o ultimo
        if(last == null) last = p;

        //Adicionou, incrementa o contador de tamanho
        curSize++;
    }
    
    //Insere no ultimo elemento da lista
    void addLast(T data) {
        //Checa se o ultimo é nulo
        if(last == null) {
            //É a mesma coisa que inserir no primeiro neste caso
            addFirst(data);
        } else {
            //Insere um novo nó depois do ultimo e atualiza o ultimo com o criado
            last = last->insertAfter(data);
            //Adicionou, então incrementa o contador de tamanho
            curSize++;
        }
    }

    //Insere um elemento de forma ordenada (deve
    int addSorted(T data) {
        //Se a lista está vazia ou o dado é menor que o primeiro, insere no inicio
        if(isEmpty() || cmp(data, first->data) < 0) {
            addFirst(data);
        //Se o dado é maior que o ultimo, insere no ultimo
        } else if( cmp(data, last->data) > 0) {
            addLast(data);
        //Se não é o começo nem o fim
        } else {
            //Varre a lista até achar a posição correta
            No<T> *current = first;
            No<T> *before;
            while( cmp(data, current->data) >= 0) {
                before = current;
                current = current->next;
            }
            //Adiciona depois de sua posição anterior
            before->insertAfter(data);
            //Adicionou, então incrementa o contador de tamanho
            curSize++;
        }
    }

    //Imprime a lista na tela
    void print() {
        cout << "-------- Lista Encadeada --------";
        if(isEmpty()) {
            cout << "- VAZIA ";
        } else {
            No<T> *p = first;
            int i = 1;
            do {
                //Mostre dado                                                                                                                                                                                                                                                 ra
                cout << endl << (i++) << ": " << p->data;
            } while( (p = p->next) != null);
        }
        cout << endl << "-----------------------" << endl;
    }

    //Obtém o tamanho atual da lista
    int size() {
        return curSize;
    }

    //Remove o elemento de indice i
    T remove(int i) {
        //Checa bounds
        if(i < 0 || i >= curSize) return null;
        //Checa se remove o primeiro
        if(i == 0) return removeFirst();
        
        //Varre a lista até achar a posição correta
        No<T> *current = first;
        No<T> *before = null;
        for(int tmp = 0; tmp < i; tmp++) {
            before = current;
            current = current->next;
        }
        //Obtém o dado
        T ret = current->data;
        //Remove o current
        before->removeAfter();
        //Diminui tamanho
        curSize--;
        //Checa se era o ultimo
        if(curSize == i) last = before;
        //Retorna o dado que foi removido
        return ret;
    }

    //Remove o primeiro elemento
    T removeFirst() {
        No<T> *oldFirst = first;
        first = oldFirst->next;
        T ret = oldFirst->data;
        delete oldFirst;
        curSize--;
        if(curSize == 0) last = first;
        return ret;
    }

    //Remove o primeiro elemento
    T removeLast() {
        return remove(curSize - 1);
    }

    //Obtém o elemento do indice i
    T get(int i) {
        //Checa bounds
        if(i < 0 || i >= curSize)
            return null;
        
        //Varre a lista até achar a posição correta
        No<T> *current = first;
        while(i-- > 0) current = current->next;
        //Retorna
        return current->data;
    }


    //Retorna o ultimo elemento da lista
    T peek() {
        if(last != null) return last->data;
        else return null;
    }

    //Limpa a lista
    void clear() {
        //TODO: Apagar os operadores
    }

    void shell() {
        int choose;
        T val;
        do {
                cout << "-- LISTA(tam=" << size() << ") -- " << endl;
                cout << "1: Inserir no primeiro" << endl;
                cout << "2: Inserir no ultimo" << endl;
                cout << "3: Inserir ordenado" << endl;
                cout << "4: Remover primeiro" << endl;
                cout << "5: Remover ultimo" << endl;
                cout << "6: Mostrar" << endl;
                cout << "7: Sair" << endl;

                cout << "Escolha: ";
                cin >> choose;

                switch(choose) {
                case 1: //Add first
                        cout << "digite: ";
                        cin >> val;
                        addFirst(val);
                        cout << "Add." << endl;
                        Sleep(500);
                        system("cls");
                        break;
                case 2: //Add last
                        cout << "digite: ";
                        cin >> val;
                        addLast(val);
                        cout << "Add." << endl;
                        Sleep(500);
                        system("cls");
                        break;
                case 3: //Add sorted
                        cout << "digite: ";
                        cin >> val;
                        addSorted(val);
                        cout << "Add." << endl;
                        Sleep(500);
                        system("cls");
                        break;
                case 4: //Remove first
                        if(isEmpty()) cout << "Lista vazia" << endl;
                        else {
                            cout << "Removido." << endl;
                            removeFirst();
                        }
                        Sleep(500);
                        system("cls");
                        break;
                case 5: //Remove last
                        if(isEmpty()) cout << "Lista vazia" << endl;
                        else {
                            cout << "Removido." << endl;
                            removeLast();
                        }
                        Sleep(500);
                        system("cls");
                        break;
                case 6: //Mostra
                        print();

                        system("pause");
                        system("cls");
                        break;
                case 7:
                        break;
                default:
                        cout << "Opcao invalida!" << endl;

                        Sleep(500);
                        system("cls");
                }

        } while(choose != 7);
    }

};


#endif	/* LINKEDLIST_H */

