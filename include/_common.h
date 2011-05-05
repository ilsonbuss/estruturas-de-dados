/* 
 * File:   common_.h
 * Author: ACER
 *
 * Created on 17 de Abril de 2011, 09:54
 */

#ifndef COMMON__H
#define	COMMON__H

//Constante para nulo
#define null 0

//Funcao generica para fazer comparacao
int _generic_compare(int a, int b);

//Usado para realocar um vetor
template<class T>
bool _vector_ensure(T** vetadr, int *sizeadr, int growthFactor) {
    //Obtem os valores atuais dos enderecos que guarda o dado do vetor e seu tamanho
    T* old = *vetadr;
    int curSize = *sizeadr;

    //Pega novo tamanho do vetor
    // curSize  100
    // newSize  growthFactor
    int newSize = curSize + (curSize * growthFactor / 100);
    //Cria novo vetor
    T* vet = new T[newSize];
    //Se nao conseguiu criar, cai fora
    if(vet == null) return false;

    //Copia dados do antigo para o novo
    //memcpy(vet, old, curSize * sizeof(T));
    for(int i = 0; i < curSize; i++) {
        vet[i] = old[i];
    }
    //Atualiza valores dos ponteiros
    *vetadr = vet;
    *sizeadr = newSize;

    //Apaga da memoria o vetor antigo
    delete [] old;
    //Retorna sucesso
    return true;
}

#endif	/* COMMON__H */

