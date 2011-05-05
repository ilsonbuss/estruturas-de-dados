/* 
 * File:   Branch.h
 * Author: ilson.buss
 *
 * Created on 12 de Abril de 2011, 08:39
 */

#ifndef BRANCH_H
#define	BRANCH_H

#define null 0

#include <iostream>
using namespace std;

//Implementação genérica de um ramo para uma arvore binária
template <class T>
class Branch {
    int heightTEST;

    //Aumenta tamanho deste ramo e seus sucessores
    void checkIncreaseHeight(int from) {//TODO: checa se deve mesmo aumentar
        return;
        heightTEST++;
        if(parent != null) parent->checkIncreaseHeight(from);
    }

    //Aumenta tamanho deste ramo e seus sucessores
    void checkDecreaseHeight(int from) {//TODO: checar se deve mesmo reduzir
        return;
        heightTEST--;
        if(parent != null) parent->checkDecreaseHeight(from);
    }

    //Aumenta tamanho deste ramo e seus sucessores
    //Retorna a maior altura ficada
    int decreaseHeight(int from) {
        return 0;
        int lh;
        int rh;

        heightTEST--;
        if(left != null) lh = left->decreaseHeight(from);
        else lh = -1;
        if(right != null) rh = right->decreaseHeight(from);
        else rh = -1;

        if(rh == -1 && lh == -1) return heightTEST;
        else if(rh > lh) return rh;
        else return lh;
    }

public:
    //Filho esquerdo
    Branch<T>* left;
    //Filho direito
    Branch<T>* right;
    //Pai do ramo
    Branch<T>* parent;
    //Dado deste ramo
    T data;

    //Cria um novo ramo
    Branch(T data, Branch<T>* parent = null) {
        this->data = data;
        left = null;
        right = null;
        this->parent = parent;
        heightTEST = 0;
    }

    //Se destrói este ramo, des
    ~Branch() {
        //if(left) delete left;
        //if(right) delete right;
    }

    //Insere no filho da esquerda
    void insertLeft(T data) {
        //Cria novo
        Branch<T>* newBranch = new Branch<T>(data, this);
        //Checa se deve aumentar o tamanho
        bool increase = left == null && right == null;
        //Checa se há existe um filho na posica esquerda
        if(left != null) {
            cout << "TODO: reisercao" << endl;
            //checa increase height 
            //filho.pai = newBranch
        }
        //Atribui esquerda
        left = newBranch;
        //Aumenta tamanho
        if(increase) checkIncreaseHeight(heightTEST);
    }

    //Insere no filho da direita
    void insertRight(T data) {
        //Cria novo
        Branch<T>* newBranch = new Branch<T>(data, this);
        //Checa se deve aumentar o tamanho
        bool increase = left == null && right == null;
        //Checa se há existe um filho na posicao direita
        if(right != null) {
            cout << "TODO: reisercao" << endl;
            //checa increase height 
            //filho.pai = newBranch
        }

        //Atribui direita
        right = newBranch;
        //Aumenta tamanho
        if(increase) checkIncreaseHeight(heightTEST);
    }

    //Remove o ramo
    Branch<T>* removeMe() {
        //Decrementa tamanho
        int from = heightTEST;
        decreaseHeight(from);

        //Checa
        bool rightReplace = true;

        //Obtém o menor descendente à direita (em descendent)
        Branch<T>* b = right;
        Branch<T>* bparent = null;
        while(b != null) {
            bparent = b;
            b = b->left;
        }
        Branch<T>* descendent = bparent;//Este ramo vai ficar no lugar do que será removido
        
        //Se o descendente for nulo, falhou em buscar na direita, tenha na esquerda
        if(descendent == null) {
            rightReplace = false;
            b = left;
            bparent = null;
            while(b != null) {
                bparent = b;
                b = b->right;
            }
            descendent = bparent;//Este ramo vai ficar no lugar do que será removido
        }

        //
        //Faz a transicao adequada
        //

        //Altera a referencia dos nó do pai
        if(parent) {
            if(parent->left == this) parent->left = descendent;
            else if(parent->right == this) parent->right = descendent;
            else cout << "Erro de referencia " << endl;
        }
        //Altera a referencia dos nós do descendente e seu pai
        if(descendent) {
            //Checa se precisa mudar as referencias dos descendentes da direita do nosso descendente (a esquerda nao existe ninguem, mas a direita...)
            //Se o pai do descendente nao for o que será será removido
            if(rightReplace && descendent != right) {
                descendent->parent->left = descendent->right;
                if(descendent->right) descendent->right->parent = descendent->parent;
            } else if(!rightReplace && descendent != left) {
                descendent->parent->right = descendent->left;
                if(descendent->left) descendent->left->parent = descendent->parent;
            }

            ///////////////////////////////////////////
            // Assume o papel do que será removido:  //
            ///////////////////////////////////////////

            //Pai
            descendent->parent = parent;
            //No esquerda
            if(descendent != left) {
                descendent->left = left;
                if(descendent->left) descendent->left->parent = descendent;
            }
            //No direita (tem que ter cuidado, pois pode ser o descendente!)
            if(descendent != right) {
                descendent->right = right;
                if(descendent->right) descendent->right->parent = descendent;
            }
        }

        //Apaga esta referencia
        delete this;

        //Retorna o descendente
        return descendent;
    }

    //Obtém a altura
    int getHeight() {
        int lh;
        if(left) lh = left->getHeight();
        else lh = -1;

        int rh;
        if(right) rh = right->getHeight();
        else rh = -1;

        if(lh > rh) return lh + 1;
        else return rh + 1;
    }

    //Obtém a altura otimizada (em versão de testes)
    int getHeightTEST() {
        return heightTEST;
    }

};

#endif	/* BRANCH_H */

