/* 
 * File:   stdcompare.cpp
 * Author: ilson.buss
 *
 * Created on 28 de Março de 2011, 14:21
 */

#include "SparseMatrix.h"
#include "_common.h"
#include <string.h>

using namespace std;

//Comparador genérico, compara como se fosse inteiros
int _generic_compare(int a, int b) { return a - b; }

//Compara matrizes esparsas
int _sparseMatrix_compare(_SparseMatrixColumn<int>* a, _SparseMatrixColumn<int>* b) {
    return a->j - b->j;
}
 
