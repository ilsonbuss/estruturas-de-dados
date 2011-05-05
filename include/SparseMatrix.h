/* 
 * File:   SparseMatrix.h
 * Author: ilson.buss
 *
 * Created on 22 de Março de 2011, 08:53
 */

#ifndef SPARSEMATRIX_H
#define	SPARSEMATRIX_H

#include <stdio.h>

#include "LinkedList.h"

//Coluna da matriz
template <class T>
struct _SparseMatrixColumn {
    T data;
    int j;

    int operator>=(const _SparseMatrixColumn& op) {
        return j >= op.j;
    }

    int operator<(const _SparseMatrixColumn& op) {
        return j < op.j;
    }

    int operator>(const _SparseMatrixColumn& op) {
        return j > op.j;
    }

    _SparseMatrixColumn() {
        
    }

    _SparseMatrixColumn(T data, int j) {
        this->data = data;
        this->j = j;
    }
};

//Funcao para comparar, ordenando as colunas da matriz
int _sparseMatrix_compare(_SparseMatrixColumn<int>* a, _SparseMatrixColumn<int>* b);

//Matriz esparsa
template <class T>
class SparseMatrix {
    LinkedList< _SparseMatrixColumn<T>* > **lines;
    int N;
    int M;

    //Aloca linhas na
    void allocLines() {
        lines = (LinkedList< _SparseMatrixColumn<T>*>**) malloc(N * sizeof(LinkedList< _SparseMatrixColumn<T>*>*));
        for(int i = 0; i < N; i++) {
            lines[i] = new LinkedList< _SparseMatrixColumn<T>* >( 
                    (int (*)(_SparseMatrixColumn<T>*, _SparseMatrixColumn<T>*))
                    _sparseMatrix_compare);
        }
    }

    //
    _SparseMatrixColumn<T>* getColuna(int i, int j) {
        //Obtém linha i
        LinkedList< _SparseMatrixColumn<T>* > *l = lines[i];
        //Procura pela coluna
        for(int c = 0; c < l->size(); c++) {
            int curJ = l->get(c)->j;
            //Checa se achou
            if(curJ == j) return l->get(c);
            //Checa se passou
            if(curJ > j) return null;
        }
        //Nao achou, retorna null
        return null;
    }
public:

    //Cria uma matrix esparsa de N linhas
    SparseMatrix(int N) {
        this->N = N;
        this->M = 5;
        allocLines();
    }

    //Cria uma matrix esparsa de N linhas
    SparseMatrix(int N, int M) {
        this->N = N;
        this->M = M;
        allocLines();
    }

    //Destroi a matriz
    ~SparseMatrix() {
        for(int i = 0; i < N; i++) delete lines[i];
        free(lines);
    }
    
    
    //Obtém o valor que esta no indice i, j da matriz
    T get(int i, int j) {
        //Checa indice invalido
        if(i >= N || i < 0 || j < 0) return null;

        //Tenta obtér a coluna
        _SparseMatrixColumn<T>* mdata = getColuna(i, j);
        //Conseguiu obter? Retorna seu dado
        if(mdata != null) return mdata->data;
        else return null; //Se não, retorna nulo
    }

    //Altera o valor que está no indice i, j da matriz
    bool set(int i, int j, T val) {
        //Checa indice invalido
        if(i>= N || i < 0 || j < 0) return false;
        //Se o valor for nulo, chama a funcao certa
        if(val == null) {
            return setNull(i, j);
        }

        //Checa se ja existe dado naquela coluna
        _SparseMatrixColumn<T> *mdata = getColuna(i, j);
        if(mdata != null) {
            //Altera o dado atual
            mdata->data = val;
        } else {
            //Adiciona um novo dado na lista
            LinkedList< _SparseMatrixColumn<T>* > *l = lines[i];
            mdata = new _SparseMatrixColumn<T>(val, j);
            l->addSorted(mdata);
        }
        //Retorna verdadeiro, modificou
        return true;
    }

    //Altera para o nulo o indice
    bool setNull(int i, int j) {
        //Checa indice invalido
        if(i>= N || i < 0 || j < 0) return false;

        //Obtém linha i
        LinkedList< _SparseMatrixColumn<T>* > *l = lines[i];
        //Procura pela coluna
        for(int c = 0; c < l->size(); c++) {
            int curJ = l->get(c)->j;
            //Checa se achou
            if(curJ == j) {
                //Remove e retorna verdadeiro
                l->remove(c);
                return true;
            }
            //Checa se passou
            if(curJ > j) return false;
        }

        //Retorna false, pois não achou
        return false;
    }

    //Imprime matriz na tela, especificando quantos digitos de espacamento
    void print(int digits) {
        char spacing[digits + 5];
        sprintf(spacing, "%%-%dd", digits); //Fazer %-Xd

        printf("--- Matriz Esparsa %dx%d ---", N, M);
        for(int i = 0; i < N; i++) {
            printf("\n");

            LinkedList< _SparseMatrixColumn<T>* > *l = lines[i];
            int j = 0;
            for(int c = 0; c < l->size(); c++) {
                _SparseMatrixColumn<T>* aux = l->get(c);
                while(j < aux->j) {
                    printf(spacing, 0);
                    j++;
                }
                printf(spacing, aux->data);
                j++;
            }
            while(j < M) {
                printf(spacing, 0);
                j++;
            }
        }
        printf("\n     %d elementos", count());
        printf("\n------------------------\n");
    }

    //Imprime matriz na tela, com 4 digitos de espacamento
    void print() {
        print(4);
    }

    //Conta o numero de elementos validos na matriz
    int count() {
        int soma = 0;
        //Conta total de elementos em cada lista
        for(int i = 0; i < N; i++) {
            LinkedList< _SparseMatrixColumn<T>* > *l = lines[i];
            soma+= l->size();
        }
        //Retorna a soma do tamanho das linhas
        return soma;
    }



    void shell() {
        int choose, i, j;
        T val;
        do {
                cout << "-- MATRIZ ESPARSA(elem=" << count() << ") -- " << endl;
                cout << "1: Setar valor" << endl;
                cout << "2: Obter valor" << endl;
                cout << "3: Setar nulo" << endl;
                cout << "4: Imprimir" << endl;
                cout << "5: Sair" << endl;

                cout << "Escolha: ";
                cin >> choose;

                switch(choose) {
                case 1: //set
                        cout << "digite (i j val): ";
                        fflush(stdin);
                        scanf("%d %d %d", &i, &j, &val);
                        if(set(i, j, val)) cout << "Setado." << endl;
                        else cout << "Linha invalida" << endl;
                        Sleep(500);
                        system("cls");
                        break;
                case 2: //get
                        cout << "digite (i j): ";
                        scanf("%d %d", &i, &j);
                        val = get(i, j);
                        cout << "mat[" << i << "][" << j << "] = " << val << endl;
                        system("pause");
                        
                        system("cls");
                        break;
                case 3: //setNull
                        cout << "digite (i j): ";
                        fflush(stdin);
                        scanf("%d %d", &i, &j);
                        if(setNull(i, j)) cout << "Setado nulo." << endl;
                        else cout << "Ja esta nulo" << endl;
                        Sleep(500);
                        system("cls");
                        break;
                case 4: //print
                        print();

                        system("pause");
                        system("cls");
                        break;
                case 5:
                        break;
                default:
                        cout << "Opcao invalida!" << endl;
                        fflush(stdin);
                        Sleep(500);
                        system("cls");
                }

        } while(choose != 5);
    }

};


#endif	/* SPARSEMATRIX_H */

