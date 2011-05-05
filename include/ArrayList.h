#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <Windows.h>
#include <List.h>
using namespace std;

template <class T>
class ArrayList {
private:
	int vetSize;
	int curSize;
	T* list;
public:

	// Construtor
	ArrayList(int tam) {
		vetSize = tam;
		list = new T[vetSize];
		curSize = 0;
	}

	// Construtor
	ArrayList() {
		vetSize = 20;
		list = new T[20];
		curSize = 0;
	}


        //Obtém o tamanho da lista
        int size() {
            return curSize;
        }

	// Checa se est� vazia
	bool isEmpty() {
		return curSize == 0;
	};

	//Adiciona
	//retorna verdadeiro se adicionou
	bool add(T val) {
		if(vetSize == curSize) {
			return false;
		} else {
			list[curSize++] = val;
			return true;
		}
	}

	//Obtem o arquivo
	T get(int index) {
		return list[index];
	}

        //Retorna o indice
        T operator[](int index) {
            return list[index];
        }

	//Imprime a pilha 
	void print() {
		cout << "-------- Lista --------";
		if(size == 0) cout << "- VAZIA ";
		for(int i = 0; i < size; i++) {
			cout << endl << (i + 1) << ": " << list[i];
		}
		cout << endl << "-----------------------" << endl;
	}

	// Debug interativo da pilha
	void shell() {
		int choose;
		T val;
		do {
			cout << "-- LISTA(tam=" << size << ") -- " << endl;
			cout << "1: Add (push)" << endl;
			cout << "2: Mostrar (print)" << endl;
			cout << "3: Sair" << endl;

			cout << "Escolha: ";
			cin >> choose;

			switch(choose) {
			case 1: //Add
				cout << "digite: ";
				cin >> val;
				if(add(val)) cout << "Add." << endl;
				else cout << "Lista cheia" << endl;

				Sleep(500);
				system("cls");
				break;
			case 2: //Mostra
				print();

				system("pause");
				system("cls");
				break;
			case 3:
				break;
			default:
				cout << "Opcao invalida!" << endl;

				Sleep(500);
				system("cls");
			}
		
		} while(choose != 3);
	}

};

