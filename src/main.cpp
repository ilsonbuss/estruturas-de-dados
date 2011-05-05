#include "LinkedList.h"
#include "SparseMatrix.h"
#include "FastList.h"
#include "AVLTree.h"
#include "BinaryTree.h"
#include "Stack.h"
#include <iostream>
#include <iomanip>

void registro_main();



int compareString(string a, string b) {
    if(a == b) return 0;
    else if (a < b) return -1;
    else return 1;
}

void btTest() {
    AVLTree<int> bt;
    bt.insert(32);
    bt.insert(16);
    bt.insert(64);
    bt.insert(30);
    bt.insert(35);
    bt.insert(96);
    bt.insert(128);
    bt.insert(94);
    bt.insert(8);
    bt.insert(2);
    bt.insert(4);
    bt.insert(10);
    bt.print();

    for(int i = 0; i <= 20; i++) {
        bt.insert(1000+i);
    }
    bt.print();

    bt.remove(64);
    bt.remove(128);
    bt.print();

    bt.remove(96);
    bt.remove(100000);
    bt.print();

    bt.remove(32);
    bt.print();

    bt.remove(94);
    bt.print();

    bt.remove(94);
    bt.print();

    bt.remove(93);
    bt.remove(95);
    bt.print();

    bt.remove(30);
    bt.print();

    bt.remove(16);
    bt.print();

    bt.remove(10);
    bt.print();

    bt.remove(35);
    bt.print();

    bt.remove(4);
    bt.print();

    bt.remove(2);
    bt.print();

    bt.remove(8);
    bt.remove(8);
    bt.remove(9);
    bt.remove(7);
    bt.print();
}

int main(int argc, char** argv) {
    //btTest();
    AVLTree<int> bt;
    bt.shell();

    //registro_main();

//    int N, M;
//    cout << "Digite o tamanho da matrix (NxM): ";
//    fflush(stdin);
//    scanf("%dx%d", &N, &M);
//    if(N < 0 || N > 200) N = 5;
//    if(M < 0 || M > 200) M = 5;
//
//    SparseMatrix<int> matrix(N, M);
//    matrix.shell();

//    matrix.get(0, 0);
//    matrix.set(0, 2, 100);
//    matrix.set(0, 0, 50);
//    matrix.set(0, 1, 1);
//    matrix.set(1, 2, 50);
//    matrix.print();
//
//    matrix.setNull(1, 2);
//    matrix.setNull(0, 6);
//    matrix.setNull(0, 0);
//    matrix.set(0, 2, 400);
//    matrix.set(0, 0, 999);
//    matrix.print();
//
//    matrix.set(0, 0, null);
//    matrix.set(4, 8, 10);
//    matrix.set(4, 4, 20);
//    matrix.set(4, 5, 30);
//    matrix.set(4, 0, 40);
//    matrix.print();
//    matrix.set(4, 5, null);
//    matrix.set(4, 8, null);
//    matrix.print();

    

        //LinkedList<int> *list = new LinkedList<int>();
//        FastList<int> *list = new FastList<int>();
//        list->addFirst(64);
//        list->addFirst(32);
//        list->addLast(128);
//        list->addSorted(256);
//        list->addSorted(16);
//        list->addSorted(80);
//        list->print();
//        list->removeFirst();
//        list->removeLast();
//        list->print();
//
//        FastList<string> *l = new FastList<string>();
//        l->addLast("hello");
//        l->addLast("great");
//        l->addLast("world");
//        l->addLast("!");
//        l->print();
//        l->remove(1);
//        l->removeLast();
//        l->print();

        //LinkedList<string> *l = new LinkedList<string>();
        //l->shell();

//        FastList<int> *l = new FastList<int>();
//        l->shell();
        
	//system("pause");
        return 0;
}
