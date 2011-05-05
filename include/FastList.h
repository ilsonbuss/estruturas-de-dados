/* 
 * File:   FastList.h
 * Author: Ilson Buss
 *         Jeferson Brustolin
 *
 * Created on 31 de Março de 2011, 19:39
 *
 * Implementação de uma Lista Circular Duplamente Encadeada
 */

#ifndef FASTLIST_H
#define	FASTLIST_H


#include <string>
#include <iostream>
#include <Windows.h>
using namespace std;
#define null 0

//
// Implementação de um nó duplamente encadeado
//
template <class T>
class FastNode {
public:
    FastNode* next;
    FastNode* prev;
    T data;

    //Inicia um no, nota que neste construtor o campo next não é iniciado
    FastNode(T data) {
        this->data = data;
        //Nota: Ta faltando iniciar!
    }

    //Altera o proximo
    void setNext(FastNode* next) {
        //Indica quem será o proximo deste
        this->next = next;
        //Indica que o anterior do proximo irá ser este
        next->prev = this;
    }

    //Função auxiliar para inserir um nó depois deste
    FastNode *insertAfter(T data) {
        //Cria um novo nó indicando o dado
        FastNode<T> *p = new FastNode<T>(data);
        //O proximo dele é o proximo do atual
        p->setNext(next);
        //Indica que o proximo nó deste é o que foi criado
        next = p;
        //Indica que o anterior do que foi criado irá ser este
        p->prev = this;
        //Retorna o nó criado
        return p;
    }

    //Função auxiliar para remover um nó depois deste
    T removeAfter() {
        //Obtém o next antigo
        FastNode<T> *oldNext = next;
        //Atualiza next com o next do oldNext
        next = oldNext->next;
        //Obtém o dado do nó removido
        T tmpData = oldNext->data;
        //Deleta da memorio o no
        delete oldNext;
        //Retorna o dado do nó removido
        return tmpData;
    }

    //Remove o nó atual
    T removeMe() {
        prev->next = next;
        next->prev = prev;
        T tmpData = data;
        delete this;
        return tmpData;
    }
};

//Comparador genérico
int _generic_compare(int a, int b);

//
// Implementação da lista
//
template <class T>
class FastList {
    int curSize;
    FastNode<T> *last;
    #define first last->next
    int (*cmp)(T, T);

    //Obtém um no baseando no seu indice
    //Se for melhor começar pelo fim, o faz
    FastNode<T>* getNode(int index) {
        FastNode<T> *p;
        if(index > curSize / 2) {
            p = last;
            index = curSize - index;
            while(--index) p = p->prev;
        } else {
            p = first;
            while(index--) p = p->next;
        }
        return p;
    }
public:

    //Inicia uma lista encadeada
    FastList() {
        //Tamanho vazio
        curSize = 0;
        //Inicia os no nulo
        last = null;
        //Inicia comparador
        cmp = (int (*)(T, T)) _generic_compare;
    }

    //Inicia uma lista encadeada
    FastList(int (*compareFunction)(T, T)) {
        //Tamanho vazio
        curSize = 0;
        //Inicia os no nulo
        last = null;
        //Inicia comparador
        cmp = compareFunction;
    }

    //Destroi a lista
    ~FastList() {
        clear();
    }

    //Checa se a lista está vazia
    bool isEmpty() {
        return curSize == 0;
    }

    //Insere no primeiro elemento da lista
    void addFirst(T data) {
        //Novo nó de primeiro
        FastNode<T> *p = new FastNode<T>(data);
        //Se é vazia, o primeiro também é o ultimo
        if(isEmpty()) {
            last = p;
            //Caracteristica da lista circular, nao tem ponteiro nulo
            p->next = p; //O proximo do primeiro é ele mesmo quando curSize == 1
            p->prev = p; //O anterior do primeiro é o ultimo, que é ele menos quando curSize == 1
        }
        //Aloca No com dado e o next = first
        p->setNext(first);
        //Altera o primeiro (proximo do ultimo)
        last->setNext(p);
        //Adicionou, incrementa o contador de tamanho
        curSize++;
    }

    //Insere no ultimo elemento da lista
    void addLast(T data) {
        //Checa se o ultimo é nulo
        if(isEmpty()) {
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
            FastNode<T> *p = first;
            while( cmp(data, p->data) >= 0) {
                p = p->next;
            }
            //Adiciona depois do anterior do ponteiro onde parou
            p->prev->insertAfter(data);
            //Adicionou, então incrementa o contador de tamanho
            curSize++;
        }
    }

    //Imprime a lista na tela
    void print() {
        cout << "-------- Lista Circular Duplamente Encadeada --------";
        if(isEmpty()) {
            cout << "- VAZIA ";
        } else {
            FastNode<T> *p = first;
            int i = 1;
            do {
                //Mostre dado                                                                                                                                                                                                                                                 ra
                cout << endl << (i++) << ": " << p->data;
            } while( (p = p->next) != first);
        }
        cout << endl << "---------------------------------------------" << endl;
    }

    //Obtém o tamanho atual da lista
    int size() {
        return curSize;
    }

//    //Remove o elemento de indice i
//    T remove(int i) {
//        //Checa bounds
//        if(i < 0 || i >= curSize) return null;
//        //Checa se remove o primeiro
//        if(i == 0) return removeFirst();
//
//        //Varre a lista até achar a posição correta
//        FastNode<T> *current = first;
//        FastNode<T> *before = null;
//        for(int tmp = 0; tmp < i; tmp++) {
//            before = current;
//            current = current->next;
//        }
//        //Obtém o dado
//        T ret = current->data;
//        //Remove o current
//        before->removeAfter();
//        //Diminui tamanho
//        curSize--;
//        //Checa se era o ultimo
//        if(curSize == i) last = before;
//        //Retorna o dado que foi removido
//        return ret;
//    }

    //Remove o primeiro elemento
    T removeFirst() {
        //Reduz tamanho
        curSize--;
        //Remove primeiro e retorna seu dado
        return first->removeMe();
    }

    //Remove o primeiro elemento
    T removeLast() {
        //Reduz tamanho
        curSize--;
        //Obtem novo ultimo (anterior do atual)
        FastNode<T> *newLast = last->prev;
        //Remove o atual ultimo e obtém seu dado
        T data = last->removeMe();
        //Atualiza ultimo
        last = newLast;
        //Retorna dado
        return data;
    }

    //Remove o elemento de indice i
    T remove(int i) {
        //Checa bounds
        if(i < 0 || i >= curSize) return null;
        //Checa se remove o primeiro
        if(i == 0) return removeFirst();
        //Checa se remove o ultimo
        if(i == curSize - 1) return removeLast();
        //Reduz tamanho
        curSize--;
        //Obtém o nó do indice e o remove
        return getNode(i).removeMe();
    }

    //Obtém o elemento do indice i
    T get(int i) {
        //Checa bounds
        if(i < 0 || i >= curSize)
            return null;
        //Retorna
        return getNode(i)->data;
    }


    //Retorna o ultimo elemento da lista
    T peek() {
        if(!isEmpty()) return last->data;
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
                cout << "-- LISTA_C.D.E.(tam=" << size() << ") -- " << endl;
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

#undef first


#endif	/* FASTLIST_H */

