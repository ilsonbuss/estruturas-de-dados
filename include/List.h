/* 
 * File:   List.h
 * Author: Buss
 *
 * Created on 31 de Março de 2011, 21:38
 */

#ifndef LIST_H
#define	LIST_H

#define null 0

template <class T>
class List {
    int curIndex;//TODO: Fazer uma pilha de iteracoes
public:
    virtual bool isEmpty()=0;

    virtual void addFirst(T data)=0;

    virtual void addLast(T data)=0;

    void add(T data) {addLast(data);}

    virtual void addSorted(T data)=0;

    virtual void print()=0;

    virtual T get(int index)=0;

    virtual T removeFirst()=0;

    virtual T removeLast()=0;

    virtual T remove(int index)=0;

    virtual T peek();

    virtual int size();

    //
    //Sistema de iteração
    ///


    T first() {
        curIndex = 0;
        return get(curIndex);
    }

    T next() {
        curIndex++;
        return get(curIndex);
    }

    int index() {
        return curIndex;
    }

    //for(T data : l) {
    //  int i = l.index();
    //  ...
    //}

    //for(T data = l.first(); data != null; data = l.next()); {
    //  int i = l.index();
    //  ...
    //}

    //for(int i = 0; i < l.size(); i++) {
    //  T data = l.get(i);
    //  ...
    //}

};


#endif	/* LIST_H */

