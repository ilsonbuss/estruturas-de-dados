#ifndef STACK_H
#define	STACK_H

#include <_common.h>
#include <string>
#include <iostream>
#include <Windows.h>
using namespace std;

template <class T>
class Stack {
private:
    int growthFactor;

    int vetSize;
    int top;
    T* list;
public:

    // Construtor
    Stack(int tam = 20) {
        vetSize = tam;
        list = new T[vetSize];
        top = -1;
        growthFactor = 75;
    }

    // Construtor de copia
    Stack(Stack<T> &stackBase) {
        vetSize = stackBase.vetSize;
        top = stackBase.top;
        list = new T[vetSize];
        for (int i = 0; i <= top; i++) {
            list[i] = stackBase.list[i];
        }
    }

    //Destrutor da pilha
    ~Stack() {
        delete [] list;
    }

    // Checa se esta vazia
    bool isEmpty() {
        return top == -1;
    }

    // Retorna a quantidade de elementos na pilha
    int size() {
        return top + 1;
    }

    // Checa se esta vazia
    bool isFull() {
        return top == vetSize - 1;
    }

    //Empilha
    //retorna verdadeiro se empilhou
    bool push(T val) {
        //Se ta cheio, temos que aumentar o vetor
        if (isFull()) {
            //Caso nao conseguir aumentar o vetor, retorna falso
            if(! _vector_ensure(&list, &vetSize, growthFactor) ) return false;
        }
        //Empilha
        list[++top] = val;
        return true;
    }

    //Desempilha
    T pop() {
        if (isEmpty()) {
            return 0;
        } else {
            return list[top--];
        }


    }

    //Imprime a pilha
    void print() {
        cout << "-------- Stack --------";
        if (top < 0) cout << "- VAZIA ";
        for (int i = top; i >= 0; i--) {
            cout << endl << (top - i + 1) << ": " << list[i];
            if (i == top) cout << " <--- TOPO";
        }
        cout << endl << "-----------------------" << endl;
    }

    // Obtém o topo
    T peek() {
        if (isEmpty()) return null;
        else return list[top];
    }

    // Obtém o elementos com indice offset deslocado a partir do topo
    T peek(int offset) {
        if (offset >= vetSize) return null;
        else return list[top - offset];
    }

    // Debug interativo da pilha
    void shell() {
        int choose;
        T val;
        do {
            cout << "-- PILHA(topo=" << top << ") -- " << endl;
            cout << "1: Empilhar (push)" << endl;
            cout << "2: Desempilhar (pop)" << endl;
            cout << "3: Topo (peek)" << endl;
            cout << "4: Mostrar (print)" << endl;
            cout << "5: Sair" << endl;

            cout << "Escolha: ";
            cin >> choose;

            switch (choose) {
                case 1: //Empilha
                    cout << "digite: ";
                    cin >> val;
                    if (push(val)) cout << "Empilhou." << endl;
                    else cout << "Pilha cheia" << endl;

                    Sleep(500);
                    system("cls");
                    break;
                case 2: //Desempilha
                    if (isEmpty() == false) {
                        val = pop();
                        cout << "Desempilhou: " << val << endl;
                    } else {
                        cout << "Pilha vazia" << endl;
                    }

                    system("pause");
                    system("cls");
                    break;
                case 3: //Topo
                    val = peek();
                    cout << "Desempilhou: " << val << endl;

                    system("pause");
                    system("cls");
                    break;
                case 4: //Mostra
                    print();

                    system("pause");
                    system("cls");
                    break;
                case 5:
                    break;
                default:
                    cout << "Opcao invalida!" << endl;

                    Sleep(500);
                    system("cls");
            }

        } while (choose != 5);
    }
};

#endif	/* STACK_H */
