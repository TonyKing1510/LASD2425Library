
#include <iostream>
#include "test.hpp"

#include "../zlasdtest/container/container.hpp"
#include "../zlasdtest/container/testable.hpp"
#include "../zlasdtest/container/dictionary.hpp"
#include "../zlasdtest/container/traversable.hpp"
#include "../zlasdtest/container/mappable.hpp"
#include "../zlasdtest/container/linear.hpp"

#include "../zlasdtest/vector/vector.hpp"
#include "../zlasdtest/list/list.hpp"
#include "../zlasdtest/set/set.hpp"
#include "../zlasdtest/heap/heap.hpp"
#include "../zlasdtest/pq/pq.hpp"


#include <string>
#include <random>
#include <ctime>


/* ************************************************************************** */

#include <iostream>
#include "../heap/vec/heapvec.hpp"
#include "../pq/heap/pqheap.hpp"
#include "../zmytest/test.hpp"

using namespace lasd;
using namespace std;

namespace mytestlasd
{

 // Funzione per generare un numero intero casuale tra 1 e 20
int generateRandomInt() {
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<> distribution(1, 20); // Intervallo: 1 - 20 inclusi

  return distribution(generator);
}

// funzione per generare un numero double casuale tra 1 e 20
double generateRandomDouble() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> distribution(1.0, 20.0); // Intervallo: 1.0 - 20.0 inclusi
    return distribution(generator);
}

// Funzione per generare una stringa casuale
std::string generateRandomString(size_t length) {
    const std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::random_device rd; // Ottiene un numero casuale da un dispositivo hardware
    std::mt19937 generator(rd()); // Inizializza il generatore con il dispositivo hardware
    std::uniform_int_distribution<size_t> distribution(0, characters.size() - 1);

    std::string randomString;
    for (size_t i = 0; i < length; ++i) {
        randomString += characters[distribution(generator)];
    }

    return randomString;
};
// Funzione per generare un numero intero casuale unico tra 1 e 20
int generateUniqueRandomInt() {
    static lasd::SetVec<int> generatedNumbers;
    static std::random_device rd; // Seed casuale
    static std::mt19937 generator(rd()); // Motore Mersenne Twister
    static std::uniform_int_distribution<> distribution(1, 20); // Distribuzione uniforme tra 1 e 20

    const int MIN = 1;
    const int MAX = 20;
    const unsigned long MAX_UNIQUE_NUMBERS = static_cast<unsigned long>(MAX - MIN + 1);

    // Se il set contiene tutti i numeri unici possibili (20 in questo caso),
    // svuotalo per permettere di generare nuovamente l'intero range.
    if (generatedNumbers.Size() >= MAX_UNIQUE_NUMBERS) {
        generatedNumbers.Clear();
       
    }

    int number;
    bool insertedSuccessfully;
    do {
        number = distribution(generator);
      
        insertedSuccessfully = generatedNumbers.Insert(number);
    } while (!insertedSuccessfully); // Loop finché l'inserimento non ha successo

    return number;
}

double generateUniqueRandomDouble(){
    static lasd::SetVec<double> generatedNumbers; 
    static std::random_device rd;
    static std::mt19937 generator(rd());
    static std::uniform_int_distribution<> distribution(1.0, 20.0); 
    
    const int MIN = 1;
    const int MAX = 20;
    const unsigned long MAX_UNIQUE_NUMBERS = static_cast<unsigned long>(MAX - MIN + 1);

    // Se il set contiene tutti i numeri unici possibili (20 in questo caso),
    // svuotalo per permettere di generare nuovamente l'intero range.
    if (generatedNumbers.Size() >= MAX_UNIQUE_NUMBERS) {
        generatedNumbers.Clear();
       
    }

    int number;
    bool insertedSuccessfully;
    do {
        number = distribution(generator);
      
        insertedSuccessfully = generatedNumbers.Insert(number);
    } while (!insertedSuccessfully); // Loop finché l'inserimento non ha successo

    return number;
}



template <typename Data>
void InsertAtFrontMove(uint & testnum, uint & testerr, lasd::List<Data> & lst, bool chk, Data&& val) {
  bool tst;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") Insert at the front of the list the value \"" << val << "\": ";
    lst.InsertAtFront(std::move(val));
    std::cout << ((tst = chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  catch (std::exception & exc) {
    std::cout << "\"" << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  testerr += (1 - (uint) tst);
}

template <typename Data>
void EqualHeapVec(uint& testnum, uint& testerr, const lasd::HeapVec<Data>& heap1, const lasd::HeapVec<Data>& heap2, bool chk) {
  bool tst;
  testnum++;
  try {
    std::cout << " " << testnum << " (" << testerr << ") The two heaps are " << ((tst = (heap1 == heap2)) ? "" : "not ") << "equal: ";
    std::cout << ((tst = (tst == chk)) ? "Correct" : "Error") << "!" << std::endl;
  } catch (std::exception& exc) {
    std::cout << "\"" << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
  }
  testerr += (1 - static_cast<uint>(tst));
}
template <typename Data>
void NonEqualHeapVec(uint& testnum, uint& testerr, const lasd::HeapVec<Data>& heap1, const lasd::HeapVec<Data>& heap2, bool chk) {
    bool tst;
    testnum++;
    try {
        std::cout << " " << testnum << " (" << testerr << ") The two heaps are " << ((tst = (heap1 != heap2)) ? "not " : "") << "equal: ";
        std::cout << ((tst = (tst == chk)) ? "Correct" : "Error") << "!" << std::endl;
    } catch (std::exception& exc) {
        std::cout << "\"" << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
    }
    testerr += (1 - static_cast<uint>(tst));
}

template <typename Data>
void ChangeMovePQ(uint& testnum, uint& testerr, lasd::PQ<Data>& pq, ulong idx, Data&& val, bool expectedSuccess) {
  testnum++;
  bool succeeded = true;
  try {
    std::cout << " " << testnum << " Change the value \"" << pq[idx] << "\" at index \"" << idx 
              << "\" to the value \"" << val << "\" in the priority queue: ";
    pq.Change(idx, std::move(val));
    std::cout << "Operation completed. ";
  } catch (const std::exception& exc) {
    std::cout << "\"" << exc.what() << "\" Exception thrown. ";
    succeeded = false;
  }

  if (succeeded == expectedSuccess) {
    std::cout << "Correct!" << std::endl;
  } else {
    std::cout << "Error!" << std::endl;
    testerr++;
  }
}


template <typename Data>
void ChangeCopyPQ(uint& testnum, uint& testerr, lasd::PQ<Data>& pq, ulong idx, const Data& val, bool expectedSuccess) {
  testnum++;
  bool succeeded = true;
  try {
    std::cout << " " << testnum << " Change the value \"" << pq[idx] << "\" at index \"" << idx 
              << "\" to the value \"" << val << "\" in the priority queue: ";
    pq.Change(idx, val);
    std::cout << "Operation completed. ";
  } catch (const std::exception& exc) {
    std::cout << "\"" << exc.what() << "\" Exception thrown. ";
    succeeded = false;
  }

  if (succeeded == expectedSuccess) {
    std::cout << "Correct!" << std::endl;
  } else {
    std::cout << "Error!" << std::endl;
    testerr++;
  }
}






template <typename Data>
void InsertMovePQ(uint & testnum, uint & testerr, lasd::PQ<Data> & pq, Data && val) {
  testnum++;
  bool tst = true;
  try {
    std::cout << " " << testnum << " Insert on the priority queue of the value \"" << val << "\": ";
    pq.Insert(std::move(val));
    std::cout << "Correct!" << std::endl;
  }
  catch (std::exception & exc) {
    std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
    tst = false;
  }
  testerr += (1 - (uint) tst);
}






    /* ************************************************************************** */

    void testHeapInt(unsigned &testnum, unsigned &testerr){
        unsigned loctestnum = 0, loctesterr = 0;
        cout << endl
                << "Begin of Heap<int> Test:" << endl;
            try
            {

                lasd::HeapVec<int> h1;
                Empty(loctestnum, loctesterr, h1, true);
                Size(loctestnum, loctesterr, h1, true, 0);
                IsHeap(loctestnum, loctesterr, h1, true);

                h1.Sort();

                IsHeap(loctestnum, loctesterr, h1, true);


                lasd::List<int> lst1;
                InsertAtBack(loctestnum, loctesterr, lst1, true, 1);
                InsertAtBack(loctestnum, loctesterr, lst1, true, 1000);
                InsertAtBack(loctestnum, loctesterr, lst1, true, 23);
                InsertAtBack(loctestnum, loctesterr, lst1, true, 11);

                h1 = lst1;
                Empty(loctestnum, loctesterr, h1, false);
                Size(loctestnum, loctesterr, h1, false, 0);

                IsHeap(loctestnum, loctesterr, h1, true);

                Traverse(loctestnum, loctesterr, h1, true, &TraversePrint<int>);

                h1.Sort();

                Traverse(loctestnum, loctesterr, h1, true, &TraversePrint<int>);

                IsHeap(loctestnum, loctesterr, h1, false);

                EqualLinear(loctestnum, loctesterr, h1, lst1, false);

                InsertAtBack(loctestnum, loctesterr, lst1, true, 9002);

                h1 = std::move(lst1);
                Empty(loctestnum, loctesterr, lst1, false);

                IsHeap(loctestnum, loctesterr, h1, true);

                Traverse(loctestnum, loctesterr, h1, true, &TraversePrint<int>);

                NonEqualLinear(loctestnum, loctesterr, h1, lst1, true);

                h1.Clear();
                Empty(loctestnum, loctesterr, h1, true);
                Size(loctestnum, loctesterr, h1, true, 0);

                lasd::SetVec<int> v1;
                InsertC(loctestnum, loctesterr, v1, true, 10);
                InsertC(loctestnum, loctesterr, v1, true, 1);
                InsertC(loctestnum, loctesterr, v1, true, 90);

                Traverse(loctestnum, loctesterr, v1, true, &TraversePrint<int>);
                

                lasd::HeapVec<int> h2(v1);
                Empty(loctestnum, loctesterr, v1, false);
                Size(loctestnum, loctesterr, v1, false, 0);
                IsHeap(loctestnum, loctesterr, h2, true);
                Traverse(loctestnum, loctesterr, h2, true, &TraversePrint<int>);
                EqualHeapVec(loctestnum, loctesterr, h2, h1, false);
                NonEqualHeapVec(loctestnum, loctesterr, h2, h1, true);

                v1.Clear();
                h2.Clear();

                lasd::SetLst<int> lst2;

                InsertAtBack(loctestnum, loctesterr, lst2, true, 1);
                InsertAtBack(loctestnum, loctesterr, lst2, true, 1000);
                InsertAtBack(loctestnum, loctesterr, lst2, true, 23);
                InsertAtBack(loctestnum, loctesterr, lst2, true, 11);

                lasd::HeapVec<int> h3(std::move(lst2));

                Empty(loctestnum, loctesterr, lst2, false);
                Size(loctestnum, loctesterr, lst2, false, 0);
                IsHeap(loctestnum, loctesterr, h3, true);
                Traverse(loctestnum, loctesterr, h3, true, &TraversePrint<int>);
                EqualHeapVec(loctestnum, loctesterr, h3, h1, false);
                NonEqualHeapVec(loctestnum, loctesterr, h3, h1, true);
                Empty(loctestnum, loctesterr, h3, false);
                Size(loctestnum, loctesterr, h3, true, 4);

                h3.Clear();
                lst2.Clear();

                InsertAtBack(loctestnum, loctesterr, lst2, true, 1);

                h2 = lst2;

                lasd::HeapVec<int> h4(h2);

                Empty(loctestnum, loctesterr,h4, false);
                Size(loctestnum, loctesterr,h4, true, 1);
                IsHeap(loctestnum, loctesterr,h4, true);
                Traverse(loctestnum, loctesterr,h4, true, &TraversePrint<int>);
                EqualHeapVec(loctestnum, loctesterr,h4, h2, true);
                NonEqualHeapVec(loctestnum, loctesterr,h4, h2, false);
                h4.Clear();
                Empty(loctestnum, loctesterr,h4, true);
                Size(loctestnum, loctesterr,h4, true, 0);

                lst2.Clear();

                InsertAtBack(loctestnum, loctesterr, lst2, true, 1000);

                h2.Clear();

                h2 = std::move(lst2);

                lasd::HeapVec<int> h5(std::move(h2));
                Empty(loctestnum, loctesterr,h5, false);
                Size(loctestnum, loctesterr,h5, true,1);
                IsHeap(loctestnum, loctesterr,h5, true);
                Traverse(loctestnum, loctesterr,h5, true, &TraversePrint<int>);
                EqualHeapVec(loctestnum, loctesterr,h5, h1, false);
                NonEqualHeapVec(loctestnum, loctesterr,h5, h1, true);
                h5.Clear();
                Empty(loctestnum, loctesterr,h5, true);
                Size(loctestnum, loctesterr,h5, true, 0);


                h1 = h5;
                EqualHeapVec(loctestnum, loctesterr,h1, h5, true);
                NonEqualHeapVec(loctestnum, loctesterr,h1, h5, false);

                h2 = std::move(h5);
                EqualHeapVec(loctestnum, loctesterr,h2, h5, true);
                EqualHeapVec(loctestnum, loctesterr,h1, h2, true);

                h5.Clear();

                lasd::Vector<int> vec1(5);
                SetAt(loctestnum, loctesterr, vec1, true, 0, 411);
                SetAt(loctestnum, loctesterr, vec1, true, 1, 141);
                SetAt(loctestnum, loctesterr, vec1, true, 2, 129);
                SetAt(loctestnum, loctesterr, vec1, true, 3, 2115);

                h5 = std::move(vec1);

                h5.Sort();
                IsHeap(loctestnum, loctesterr, h5, false);

                h5.Clear();
                vec1.Clear();

                lasd::HeapVec<int> h6;
                Empty(loctestnum, loctesterr, h6, true);
                Size(loctestnum, loctesterr, h6, true, 0);

                lasd::List<int> lst3;

                for(int i = 0; i < 10; i++){
                    InsertAtBack(loctestnum, loctesterr, lst3, true, generateRandomInt());
                }

                h6 = std::move(lst3);
                IsHeap(loctestnum, loctesterr, h6, true);
                Traverse(loctestnum, loctesterr, h6, true, &TraversePrint<int>);
                h6.Sort();
                IsHeap(loctestnum, loctesterr, h6, false);

                lasd::HeapVec<int> h7(std::move(h6));
                Empty(loctestnum, loctesterr, h7, false);
                Size(loctestnum, loctesterr, h7, true, 10);

                IsHeap(loctestnum, loctesterr, h7, false);

                h7.Clear();
                Empty(loctestnum, loctesterr, h7, true);

                lasd::List<int> lst4;
                for(int i = 0; i < 10; i++){
                    InsertAtBack(loctestnum, loctesterr, lst4, true, generateRandomInt());
                }
                h7 = std::move(lst4);
                Map(loctestnum, loctesterr, h7, true, &MyMapPrint<int>);
                MapPreOrder(loctestnum, loctesterr, h7, true, &MyMapPrint<int>);
                MapPostOrder(loctestnum, loctesterr, h7, true, &MyMapPrint<int>);
                Map(loctestnum, loctesterr, h7, true, &MapIncrement<int>);
                Map(loctestnum, loctesterr, h7, true, &MapDecrement<int>);
                Map(loctestnum, loctesterr, h7, true, &MapDouble<int>);
                Map(loctestnum, loctesterr, h7, true, &MapDoubleNPrint<int>);
                Map(loctestnum, loctesterr, h7, true, &MapIncrementNPrint<int>);
                Map(loctestnum, loctesterr, h7, true, &MapInvertNPrint<int>);
                Map(loctestnum, loctesterr, h7, true, &MapInvert<int>);
                Map(loctestnum, loctesterr, h7, true, &MapHalf<int>);
                Map(loctestnum, loctesterr, h7, true, &MapParityInvert<int>);

                h7.Clear();



                lst4.Clear();

                InsertAtBack(loctestnum, loctesterr, lst4, true, 1);
                InsertAtBack(loctestnum, loctesterr, lst4, true, 2);
                InsertAtBack(loctestnum, loctesterr, lst4, true, 3);
                InsertAtBack(loctestnum, loctesterr, lst4, true, 4);
                InsertAtBack(loctestnum, loctesterr, lst4, true, 5);

                h7 = std::move(lst4);


                Fold(loctestnum, loctesterr, h7, true, &FoldAdd<int>, 0, 15);
                FoldPreOrder(loctestnum, loctesterr, h7, true, &FoldAdd<int>, 0, 15);
                FoldPostOrder(loctestnum, loctesterr, h7, true, &FoldAdd<int>, 0, 15);
                Fold(loctestnum, loctesterr, h7, true, &FoldMultiply<int>, 1, 120);
                FoldPreOrder(loctestnum, loctesterr, h7, true, &FoldMultiply<int>, 1, 120);
                FoldPostOrder(loctestnum, loctesterr, h7, true, &FoldMultiply<int>, 1, 120);
                Fold(loctestnum, loctesterr, h7, true, &FoldParity, 0, 1);


                h7.Clear();

                //1.Heap da container ordinato
                lasd::HeapVec<int> h8(4);
                Empty(loctestnum, loctesterr, h8, false);
                Traverse(loctestnum, loctesterr, h8, true, &TraversePrint<int>);
                Size(loctestnum, loctesterr, h8, true, 4);
                IsHeap(loctestnum, loctesterr, h8, true);

                lasd::Vector<int> vec2(4);
                SetAt(loctestnum, loctesterr, vec2, true, 0, 1);
                SetAt(loctestnum, loctesterr, vec2, true, 1, 2);
                SetAt(loctestnum, loctesterr, vec2, true, 2, 3);
                SetAt(loctestnum, loctesterr, vec2, true, 3, 4);

                h8 = std::move(vec2);

                Empty(loctestnum, loctesterr, vec2, false);
                Traverse(loctestnum, loctesterr, h8, true, &TraversePrint<int>);
                IsHeap(loctestnum, loctesterr, h8, true);

                h8.Clear();

                lasd::SortableVector<int> sv1(4);
                for(int i = 0; i < 4; i++) {
                    SetAt(loctestnum, loctesterr, sv1, true, i, generateRandomInt());
                }
                Traverse(loctestnum, loctesterr, sv1, true, &TraversePrint<int>);
                sv1.Sort();
                Traverse(loctestnum, loctesterr, sv1, true, &TraversePrint<int>);
                h8 = std::move(sv1);
                IsHeap(loctestnum, loctesterr, h8, true);
                Traverse(loctestnum, loctesterr, h8, true, &TraversePrint<int>);

                h8.Sort();
                IsHeap(loctestnum, loctesterr, h8, false);
                EqualLinear(loctestnum, loctesterr, h8, sv1, true);

                

                //2.Heap da container non ordinato e operatore []
                  lasd::HeapVec<int> h9(5);
                  Empty(loctestnum, loctesterr, h9, false);
                  Size(loctestnum, loctesterr, h9, true, 5);
                    IsHeap(loctestnum, loctesterr, h9, true);

                lasd::List<int> lst5;
                for(int i = 0; i < 5; i++) {
                    InsertAtBack(loctestnum, loctesterr, lst5, true, i + 1);
                }
                h9 = std::move(lst5);
                Empty(loctestnum, loctesterr, lst5, false);
                Size(loctestnum, loctesterr, h9, true, 5);
                IsHeap(loctestnum, loctesterr, h9, true);
                Traverse(loctestnum, loctesterr, h9, true, &TraversePrint<int>);
                EqualLinear(loctestnum, loctesterr, h9, lst5, false);
                h9.Sort();
                IsHeap(loctestnum, loctesterr, h9, false);

                GetFront(loctestnum, loctesterr, h9, true, 1);
               GetBack(loctestnum, loctesterr, h9, true, 5);

               

              

                h9.Clear();
                Empty(loctestnum, loctesterr, h9, true);
                Size(loctestnum, loctesterr, h9, true, 0);
                IsHeap(loctestnum, loctesterr, h9, true);

                //Heap vuoto
                lasd::HeapVec<int> h10;
                Empty(loctestnum, loctesterr, h10, true);
                Size(loctestnum, loctesterr, h10, true, 0);
                IsHeap(loctestnum, loctesterr, h10, true);
                h10.Sort();
                IsHeap(loctestnum, loctesterr, h10, true);
                EqualHeapVec(loctestnum, loctesterr, h10, h1, true);
                NonEqualHeapVec(loctestnum, loctesterr, h10, h1, false);
                h10.Clear();
                Empty(loctestnum, loctesterr, h10, true);
                Size(loctestnum, loctesterr, h10, true, 0);

                IsHeap(loctestnum, loctesterr, h10, true);

                lasd::Vector<int> vec3;
                lasd::HeapVec<int> h11(std::move(vec3));
                Empty(loctestnum, loctesterr, h11, true);
                Size(loctestnum, loctesterr, h11, true, 0);
                IsHeap(loctestnum, loctesterr, h11, true);

                //heap con un solo elemento
                lasd::HeapVec<int> h12(1);
                Empty(loctestnum, loctesterr, h12, false);
                Size(loctestnum, loctesterr, h12, true, 1);
                IsHeap(loctestnum, loctesterr, h12, true);

                lasd::SetVec<int> v2;
                InsertC(loctestnum, loctesterr, v2, true, 1001);
                Traverse(loctestnum, loctesterr, v2, true, &TraversePrint<int>);
                h12 = std::move(v2);
                Empty(loctestnum, loctesterr, v2, false);
                Size(loctestnum, loctesterr, v2, true, 1);
                IsHeap(loctestnum, loctesterr, h12, true);
                Traverse(loctestnum, loctesterr, h12, true, &TraversePrint<int>);
                EqualHeapVec(loctestnum, loctesterr, h12, h1, false);
                NonEqualHeapVec(loctestnum, loctesterr, h12, h1, true);
                h12.Clear();

                //heap con elementi tutti uguali
                lasd::HeapVec<int> h13(5);
                Empty(loctestnum, loctesterr, h13, false);
                Size(loctestnum, loctesterr, h13, true, 5);
                IsHeap(loctestnum, loctesterr, h13, true);

                lasd::Vector<int> vec4(5);
                SetAt(loctestnum, loctesterr, vec4, true, 0, 1);
                SetAt(loctestnum, loctesterr, vec4, true, 1, 1);
                SetAt(loctestnum, loctesterr, vec4, true, 2, 1);
                SetAt(loctestnum, loctesterr, vec4, true, 3, 1);
                SetAt(loctestnum, loctesterr, vec4, true, 4, 1);
                h13 = vec4;
                IsHeap(loctestnum, loctesterr, h13, true);
                h13.Sort();
                IsHeap(loctestnum, loctesterr, h13, true);

                // Test operator[] non-const
                    lasd::HeapVec<int> hp(2);

                    // Test operator[] const
                    const lasd::HeapVec<int>& const_hp = hp;
                    std::cout << "Accesso const (index 1): " << const_hp[1] << std::endl;
                
                
            }catch(...)
            {
                loctestnum++;
                loctesterr++;
                cout << endl
                    << "Unmanaged error! " << endl;
            }
        cout << "End of Heap<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
        testnum += loctestnum;
        testerr += loctesterr;
    }
    
    /* ************************************************************************** */



        void testHeapDouble(unsigned &testnum, unsigned &testerr){
                unsigned loctestnum = 0, loctesterr = 0;
                cout << endl
                        << "Begin of Heap<double> Test:" << endl;
                    try
                    {
                            lasd::HeapVec<double> h1;
                            Empty(loctestnum, loctesterr, h1, true);
                            Size(loctestnum, loctesterr, h1, true, 0);
                            IsHeap(loctestnum, loctesterr, h1, true);

                            h1.Sort();

                            IsHeap(loctestnum, loctesterr, h1, true);

                            lasd::List<double> lst1;
                            InsertAtBack(loctestnum, loctesterr, lst1, true, 1.0);
                            InsertAtBack(loctestnum, loctesterr, lst1, true, 1000.0);
                            InsertAtBack(loctestnum, loctesterr, lst1, true, 23.0);
                            InsertAtBack(loctestnum, loctesterr, lst1, true, 11.0);

                            h1 = lst1;
                            Empty(loctestnum, loctesterr, h1, false);
                            Size(loctestnum, loctesterr, h1, false, 0);

                            IsHeap(loctestnum, loctesterr, h1, true);

                            Traverse(loctestnum, loctesterr, h1, true, &TraversePrint<double>);

                            h1.Sort();

                            Traverse(loctestnum, loctesterr, h1, true, &TraversePrint<double>);

                            IsHeap(loctestnum, loctesterr, h1, false);

                            EqualLinear(loctestnum, loctesterr, h1, lst1, false);

                            InsertAtBack(loctestnum, loctesterr, lst1, true, 9002.0);

                            h1 = std::move(lst1);
                            Empty(loctestnum, loctesterr, lst1, false);

                            IsHeap(loctestnum, loctesterr, h1, true);

                            Traverse(loctestnum, loctesterr, h1, true, &TraversePrint<double>);

                            NonEqualLinear(loctestnum, loctesterr, h1, lst1, true);

                            h1.Clear();
                            Empty(loctestnum, loctesterr, h1, true);
                            Size(loctestnum, loctesterr, h1, true, 0);

                            lasd::SetVec<double> v1;
                            InsertC(loctestnum, loctesterr, v1, true, 10.0);
                            InsertC(loctestnum, loctesterr, v1, true, 1.0);
                            InsertC(loctestnum, loctesterr, v1, true, 90.0);

                            Traverse(loctestnum, loctesterr, v1, true, &TraversePrint<double>);

                            lasd::HeapVec<double> h2(v1);
                            Empty(loctestnum, loctesterr, v1, false);
                            Size(loctestnum, loctesterr, v1, false, 0);
                            IsHeap(loctestnum, loctesterr, h2, true);
                            Traverse(loctestnum, loctesterr, h2, true, &TraversePrint<double>);
                            EqualHeapVec(loctestnum, loctesterr, h2, h1, false);
                            NonEqualHeapVec(loctestnum, loctesterr, h2, h1, true);

                            v1.Clear();
                            h2.Clear();

                            lasd::SetLst<double> lst2;

                            InsertAtBack(loctestnum, loctesterr, lst2, true, 1.0);
                            InsertAtBack(loctestnum, loctesterr, lst2, true, 1000.0);
                            InsertAtBack(loctestnum, loctesterr, lst2, true, 23.0);
                            InsertAtBack(loctestnum, loctesterr, lst2, true, 11.0);

                            lasd::HeapVec<double> h3(std::move(lst2));

                            Empty(loctestnum, loctesterr, lst2, false);
                            Size(loctestnum, loctesterr, lst2, false, 0);
                            IsHeap(loctestnum, loctesterr, h3, true);
                            Traverse(loctestnum, loctesterr, h3, true, &TraversePrint<double>);
                            EqualHeapVec(loctestnum, loctesterr, h3, h1, false);
                            NonEqualHeapVec(loctestnum, loctesterr, h3, h1, true);
                            Empty(loctestnum, loctesterr, h3, false);
                            Size(loctestnum, loctesterr, h3, true, 4);

                            h3.Clear();
                            lst2.Clear();

                            InsertAtBack(loctestnum, loctesterr, lst2, true, 1.0);

                            h2 = lst2;

                            lasd::HeapVec<double> h4(h2);

                            Empty(loctestnum, loctesterr, h4, false);
                            Size(loctestnum, loctesterr, h4, true, 1);
                            IsHeap(loctestnum, loctesterr, h4, true);
                            Traverse(loctestnum, loctesterr, h4, true, &TraversePrint<double>);
                            EqualHeapVec(loctestnum, loctesterr, h4, h2, true);
                            NonEqualHeapVec(loctestnum, loctesterr, h4, h2, false);
                            h4.Clear();
                            Empty(loctestnum, loctesterr, h4, true);
                            Size(loctestnum, loctesterr, h4, true, 0);

                            lst2.Clear();

                            InsertAtBack(loctestnum, loctesterr, lst2, true, 1000.0);

                            h2.Clear();

                            h2 = std::move(lst2);

                            lasd::HeapVec<double> h5(std::move(h2));
                            Empty(loctestnum, loctesterr, h5, false);
                            Size(loctestnum, loctesterr, h5, true, 1);
                            IsHeap(loctestnum, loctesterr, h5, true);
                            Traverse(loctestnum, loctesterr, h5, true, &TraversePrint<double>);
                            EqualHeapVec(loctestnum, loctesterr, h5, h1, false);
                            NonEqualHeapVec(loctestnum, loctesterr, h5, h1, true);
                            h5.Clear();
                            Empty(loctestnum, loctesterr, h5, true);
                            Size(loctestnum, loctesterr, h5, true, 0);

                            h1 = h5;
                            EqualHeapVec(loctestnum, loctesterr, h1, h5, true);
                            NonEqualHeapVec(loctestnum, loctesterr, h1, h5, false);

                            h2 = std::move(h5);
                            EqualHeapVec(loctestnum, loctesterr, h2, h5, true);
                            EqualHeapVec(loctestnum, loctesterr, h1, h2, true);

                            h5.Clear();

                            lasd::Vector<double> vec1(5);
                            SetAt(loctestnum, loctesterr, vec1, true, 0, 411.0);
                            SetAt(loctestnum, loctesterr, vec1, true, 1, 141.0);
                            SetAt(loctestnum, loctesterr, vec1, true, 2, 129.0);
                            SetAt(loctestnum, loctesterr, vec1, true, 3, 2115.0);

                            h5 = std::move(vec1);

                            h5.Sort();
                            IsHeap(loctestnum, loctesterr, h5, false);

                            lasd::HeapVec<double> h6;
                            Empty(loctestnum, loctesterr, h6, true);
                            Size(loctestnum, loctesterr, h6, true, 0);

                            lasd::List<double> lst3;

                            for(int i = 0; i < 10; i++){
                                InsertAtBack(loctestnum, loctesterr, lst3, true, generateRandomDouble());
                            }

                            h6 = std::move(lst3);
                            IsHeap(loctestnum, loctesterr, h6, true);
                            Traverse(loctestnum, loctesterr, h6, true, &TraversePrint<double>);
                            h6.Sort();
                            IsHeap(loctestnum, loctesterr, h6, false);


                            lasd::List<double> lst4;
                            for(int i = 0; i < 10; i++){
                                InsertAtBack(loctestnum, loctesterr, lst4, true, generateRandomDouble());
                            };
                            
                            h6 = std::move(lst4);
                            Map(loctestnum, loctesterr, h6, true, &MyMapPrint<double>);
                            MapPreOrder(loctestnum, loctesterr, h6, true, &MyMapPrint<double>);
                            MapPostOrder(loctestnum, loctesterr, h6, true, &MyMapPrint<double>);
                            Map(loctestnum, loctesterr, h6, true, &MapIncrement<double>);
                            Map(loctestnum, loctesterr, h6, true, &MapDecrement<double>);
                            Map(loctestnum, loctesterr, h6, true, &MapDouble<double>);
                            Map(loctestnum, loctesterr, h6, true, &MapDoubleNPrint<double>);


                            h6.Clear();

                            lst4.Clear();

                            InsertAtBack(loctestnum, loctesterr, lst4, true, 1.0);
                            InsertAtBack(loctestnum, loctesterr, lst4, true, 2.0);
                            InsertAtBack(loctestnum, loctesterr, lst4, true, 3.0);
                            InsertAtBack(loctestnum, loctesterr, lst4, true, 4.0);
                            InsertAtBack(loctestnum, loctesterr, lst4, true, 5.0);

                            h6 = std::move(lst4);

                            Fold(loctestnum, loctesterr, h6, true, &FoldAdd<double>, 0.0, 15.0);
                            FoldPreOrder(loctestnum, loctesterr, h6, true, &FoldAdd<double>, 0.0, 15.0);
                            FoldPostOrder(loctestnum, loctesterr, h6, true, &FoldAdd<double>, 0.0, 15.0);
                            Fold(loctestnum, loctesterr, h6, true, &FoldMultiply<double>, 1.0, 120.0);
                            FoldPreOrder(loctestnum, loctesterr, h6, true, &FoldMultiply<double>, 1.0, 120.0);
                            FoldPostOrder(loctestnum, loctesterr, h6, true, &FoldMultiply<double>, 1.0, 120.0);

                            h6.Clear();


                            Map(loctestnum, loctesterr, h6, true, &MyMapPrint<double>);
                            MapPreOrder(loctestnum, loctesterr, h6, true, &MyMapPrint<double>);
                            MapPostOrder(loctestnum, loctesterr, h6, true, &MyMapPrint<double>);
                            Map(loctestnum, loctesterr, h6, true, &MapIncrement<double>);
                            Map(loctestnum, loctesterr, h6, true, &MapDecrement<double>);
                            Map(loctestnum, loctesterr, h6, true, &MapDouble<double>);
                            Map(loctestnum, loctesterr, h6, true, &MapDoubleNPrint<double>);

                            //1.Heap da container ordinato
                            lasd::HeapVec<double> h8(4);
                            Empty(loctestnum, loctesterr, h8, false);
                            Traverse(loctestnum, loctesterr, h8, true, &TraversePrint<double>);
                            Size(loctestnum, loctesterr, h8, true, 4);
                            IsHeap(loctestnum, loctesterr, h8, true);

                            lasd::Vector<double> vec2(4);
                            SetAt(loctestnum, loctesterr, vec2, true, 0, 1.0);
                            SetAt(loctestnum, loctesterr, vec2, true, 1, 2.0);
                            SetAt(loctestnum, loctesterr, vec2, true, 2, 3.0);
                            SetAt(loctestnum, loctesterr, vec2, true, 3, 4.0);

                            h8 = std::move(vec2);

                            Empty(loctestnum, loctesterr, vec2, false);
                            Traverse(loctestnum, loctesterr, h8, true, &TraversePrint<double>);
                            IsHeap(loctestnum, loctesterr, h8, true);

                            h8.Clear();

                            lasd::SortableVector<double> sv1(4);
                            for (int i = 0; i < 4; i++) {
                                SetAt(loctestnum, loctesterr, sv1, true, i, generateUniqueRandomDouble());
                            }
                            Traverse(loctestnum, loctesterr, sv1, true, &TraversePrint<double>);
                            sv1.Sort();
                            Traverse(loctestnum, loctesterr, sv1, true, &TraversePrint<double>);
                            h8 = std::move(sv1);
                            IsHeap(loctestnum, loctesterr, h8, true);
                            Traverse(loctestnum, loctesterr, h8, true, &TraversePrint<double>);

                            h8.Sort();
                            IsHeap(loctestnum, loctesterr, h8, false);
                            EqualLinear(loctestnum, loctesterr, h8, sv1, true);
 

                            //2.Heap da container non ordinato e operatore []
                            lasd::HeapVec<double> h9(5);
                            Empty(loctestnum, loctesterr, h9, false);
                            Size(loctestnum, loctesterr, h9, true, 5);
                            IsHeap(loctestnum, loctesterr, h9, true);

                            lasd::List<double> lst5;
                            for (int i = 0; i < 5; i++) {
                                InsertAtBack(loctestnum, loctesterr, lst5, true, i + 1.0);
                            }
                            h9 = std::move(lst5);
                            Empty(loctestnum, loctesterr, lst5, false);
                            Size(loctestnum, loctesterr, h9, true, 5);
                            IsHeap(loctestnum, loctesterr, h9, true);
                            Traverse(loctestnum, loctesterr, h9, true, &TraversePrint<double>);
                            EqualLinear(loctestnum, loctesterr, h9, lst5, false);
                            h9.Sort();
                            IsHeap(loctestnum, loctesterr, h9, false);

                            GetFront(loctestnum, loctesterr, h9, true, 1.0);
                            GetBack(loctestnum, loctesterr, h9, true, 5.0);


                            h9.Clear();
                            Empty(loctestnum, loctesterr, h9, true);
                            Size(loctestnum, loctesterr, h9, true, 0);
                            IsHeap(loctestnum, loctesterr, h9, true);

                            //Heap vuoto
                            lasd::HeapVec<double> h10;
                            Empty(loctestnum, loctesterr, h10, true);
                            Size(loctestnum, loctesterr, h10, true, 0);
                            IsHeap(loctestnum, loctesterr, h10, true);
                            h10.Sort();
                            IsHeap(loctestnum, loctesterr, h10, true);
                            EqualHeapVec(loctestnum, loctesterr, h10, h1, true);
                            NonEqualHeapVec(loctestnum, loctesterr, h10, h1, false);
                            h10.Clear();
                            Empty(loctestnum, loctesterr, h10, true);
                            Size(loctestnum, loctesterr, h10, true, 0);
                            IsHeap(loctestnum, loctesterr, h10, true);

                            lasd::Vector<double> vec3;
                            lasd::HeapVec<double> h11(std::move(vec3));
                            Empty(loctestnum, loctesterr, h11, true);
                            Size(loctestnum, loctesterr, h11, true, 0);
                            IsHeap(loctestnum, loctesterr, h11, true);

                            //heap con un solo elemento
                            lasd::HeapVec<double> h12(1);
                            Empty(loctestnum, loctesterr, h12, false);
                            Size(loctestnum, loctesterr, h12, true, 1);
                            IsHeap(loctestnum, loctesterr, h12, true);

                            lasd::SetVec<double> v2;
                            InsertC(loctestnum, loctesterr, v2, true, 1001.0);
                            Traverse(loctestnum, loctesterr, v2, true, &TraversePrint<double>);
                            h12 = std::move(v2);
                            Empty(loctestnum, loctesterr, v2, false);
                            Size(loctestnum, loctesterr, v2, true, 1);
                            IsHeap(loctestnum, loctesterr, h12, true);
                            Traverse(loctestnum, loctesterr, h12, true, &TraversePrint<double>);
                            EqualHeapVec(loctestnum, loctesterr, h12, h1, false);
                            NonEqualHeapVec(loctestnum, loctesterr, h12, h1, true);
                            h12.Clear();

                            //heap con elementi tutti uguali
                            lasd::HeapVec<double> h13(5);
                            Empty(loctestnum, loctesterr, h13, false);
                            Size(loctestnum, loctesterr, h13, true, 5);
                            IsHeap(loctestnum, loctesterr, h13, true);

                            lasd::Vector<double> vec4(5);
                            SetAt(loctestnum, loctesterr, vec4, true, 0, 1.0);
                            SetAt(loctestnum, loctesterr, vec4, true, 1, 1.0);
                            SetAt(loctestnum, loctesterr, vec4, true, 2, 1.0);
                            SetAt(loctestnum, loctesterr, vec4, true, 3, 1.0);
                            SetAt(loctestnum, loctesterr, vec4, true, 4, 1.0);
                            h13 = vec4;
                            IsHeap(loctestnum, loctesterr, h13, true);
                            h13.Sort();
                            IsHeap(loctestnum, loctesterr, h13, true);

                            // Test operator[] non-const
                            lasd::HeapVec<double> hp(2);

                            // Test operator[] const
                            const lasd::HeapVec<double>& const_hp = hp;
                            std::cout << "Accesso const (index 1): " << const_hp[1] << std::endl;


                    }catch(...)
                    {
                        loctestnum++;
                        loctesterr++;
                        cout << endl
                            << "Unmanaged error! " << endl;
                    }
                cout << "End of Heap<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
                testnum += loctestnum;
                testerr += loctesterr;
            }

    /* ************************************************************************** */

    void testHeapString(unsigned &testnum, unsigned &testerr){
                unsigned loctestnum = 0, loctesterr = 0;
                cout << endl
                        << "Begin of Heap<string> Test:" << endl;
                    try
                    {

                        lasd::HeapVec<string> h1;
                        Empty(loctestnum, loctesterr, h1, true);
                        Size(loctestnum, loctesterr, h1, true, 0);
                        IsHeap(loctestnum, loctesterr, h1, true);

                        h1.Sort();

                        IsHeap(loctestnum, loctesterr, h1, true);

                        lasd::List<string> lst1;
                        InsertAtBack(loctestnum, loctesterr, lst1, true, string("a"));
                        InsertAtBack(loctestnum, loctesterr, lst1, true, string("z"));
                        InsertAtBack(loctestnum, loctesterr, lst1, true, string("b"));
                        InsertAtBack(loctestnum, loctesterr, lst1, true, string("m"));

                        h1 = lst1;
                        Empty(loctestnum, loctesterr, h1, false);
                        Size(loctestnum, loctesterr, h1, false, 0);

                        IsHeap(loctestnum, loctesterr, h1, true);

                        Traverse(loctestnum, loctesterr, h1, true, &TraversePrint<string>);

                        h1.Sort();

                        Traverse(loctestnum, loctesterr, h1, true, &TraversePrint<string>);

                        IsHeap(loctestnum, loctesterr, h1, false);

                        EqualLinear(loctestnum, loctesterr, h1, lst1, false);

                        InsertAtBack(loctestnum, loctesterr, lst1, true, string("x"));

                        h1 = std::move(lst1);
                        Empty(loctestnum, loctesterr, lst1, false);

                        IsHeap(loctestnum, loctesterr, h1, true);

                        Traverse(loctestnum, loctesterr, h1, true, &TraversePrint<string>);

                        NonEqualLinear(loctestnum, loctesterr, h1, lst1, true);

                        h1.Clear();
                        Empty(loctestnum, loctesterr, h1, true);
                        Size(loctestnum, loctesterr, h1, true, 0);

                        lasd::SetVec<string> v1;
                        InsertC(loctestnum, loctesterr, v1, true, string("uno"));
                        InsertC(loctestnum, loctesterr, v1, true, string("due"));
                        InsertC(loctestnum, loctesterr, v1, true, string("tre"));

                        Traverse(loctestnum, loctesterr, v1, true, &TraversePrint<string>);

                        lasd::HeapVec<string> h2(v1);
                        Empty(loctestnum, loctesterr, v1, false);
                        Size(loctestnum, loctesterr, v1, false, 0);
                        IsHeap(loctestnum, loctesterr, h2, true);
                        Traverse(loctestnum, loctesterr, h2, true, &TraversePrint<string>);
                        EqualHeapVec(loctestnum, loctesterr, h2, h1, false);
                        NonEqualHeapVec(loctestnum, loctesterr, h2, h1, true);

                        v1.Clear();
                        h2.Clear();

                        lasd::SetLst<string> lst2;

                        InsertAtBack(loctestnum, loctesterr, lst2, true, string("gatto"));
                        InsertAtBack(loctestnum, loctesterr, lst2, true, string("cane"));
                        InsertAtBack(loctestnum, loctesterr, lst2, true, string("lupo"));
                        InsertAtBack(loctestnum, loctesterr, lst2, true, string("orso"));

                        lasd::HeapVec<string> h3(std::move(lst2));

                        Empty(loctestnum, loctesterr, lst2, false);
                        Size(loctestnum, loctesterr, lst2, false, 0);
                        IsHeap(loctestnum, loctesterr, h3, true);
                        Traverse(loctestnum, loctesterr, h3, true, &TraversePrint<string>);
                        EqualHeapVec(loctestnum, loctesterr, h3, h1, false);
                        NonEqualHeapVec(loctestnum, loctesterr, h3, h1, true);
                        Empty(loctestnum, loctesterr, h3, false);
                        Size(loctestnum, loctesterr, h3, true, 4);

                        h3.Clear();
                        lst2.Clear();

                        InsertAtBack(loctestnum, loctesterr, lst2, true, string("koala"));

                        h2 = lst2;

                        lasd::HeapVec<string> h4(h2);

                        Empty(loctestnum, loctesterr, h4, false);
                        Size(loctestnum, loctesterr, h4, true, 1);
                        IsHeap(loctestnum, loctesterr, h4, true);
                        Traverse(loctestnum, loctesterr, h4, true, &TraversePrint<string>);
                        EqualHeapVec(loctestnum, loctesterr, h4, h2, true);
                        NonEqualHeapVec(loctestnum, loctesterr, h4, h2, false);
                        h4.Clear();
                        Empty(loctestnum, loctesterr, h4, true);
                        Size(loctestnum, loctesterr, h4, true, 0);

                        lst2.Clear();

                        InsertAtBack(loctestnum, loctesterr, lst2, true, string("zebra"));

                        h2.Clear();

                        h2 = std::move(lst2);

                        lasd::HeapVec<string> h5(std::move(h2));
                        Empty(loctestnum, loctesterr, h5, false);
                        Size(loctestnum, loctesterr, h5, true, 1);
                        IsHeap(loctestnum, loctesterr, h5, true);
                        Traverse(loctestnum, loctesterr, h5, true, &TraversePrint<string>);
                        EqualHeapVec(loctestnum, loctesterr, h5, h1, false);
                        NonEqualHeapVec(loctestnum, loctesterr, h5, h1, true);
                        h5.Clear();
                        Empty(loctestnum, loctesterr, h5, true);
                        Size(loctestnum, loctesterr, h5, true, 0);

                        h1 = h5;
                        EqualHeapVec(loctestnum, loctesterr, h1, h5, true);
                        NonEqualHeapVec(loctestnum, loctesterr, h1, h5, false);

                        h2 = std::move(h5);
                        EqualHeapVec(loctestnum, loctesterr, h2, h5, true);
                        EqualHeapVec(loctestnum, loctesterr, h1, h2, true);

                        h5.Clear();

                        lasd::Vector<string> vec1(5);
                        SetAt(loctestnum, loctesterr, vec1, true, 0, string("rosso"));
                        SetAt(loctestnum, loctesterr, vec1, true, 1, string("verde"));
                        SetAt(loctestnum, loctesterr, vec1, true, 2, string("blu"));
                        SetAt(loctestnum, loctesterr, vec1, true, 3, string("giallo"));

                        h5 = std::move(vec1);

                        h5.Sort();
                        IsHeap(loctestnum, loctesterr, h5, false);

                        h5.Clear();

                        vec1.Clear();


                        lasd::HeapVec<string> h6;
                        Empty(loctestnum, loctesterr, h6, true);
                        Size(loctestnum, loctesterr, h6, true, 0);

                        lasd::List<string> lst3;

                        for(int i = 0; i < 10; i++){
                            InsertAtBack(loctestnum, loctesterr, lst3, true, generateRandomString(10));
                        }

                        h6 = std::move(lst3);
                        IsHeap(loctestnum, loctesterr, h6, true);
                        Traverse(loctestnum, loctesterr, h6, true, &TraversePrint<string>);
                        h6.Sort();
                        IsHeap(loctestnum, loctesterr, h6, false);

                          lasd::List<string> lst4;
                            for(int i = 0; i < 10; i++){
                                InsertAtBack(loctestnum, loctesterr, lst4, true, generateRandomString(10));
                            };
                            
                            h6 = std::move(lst4);
                            Map(loctestnum, loctesterr, h6, true, &MyMapPrint<string>);
                            MapPreOrder(loctestnum, loctesterr, h6, true, &MyMapPrint<string>);
                            MapPostOrder(loctestnum, loctesterr, h6, true, &MyMapPrint<string>);
                            Map(loctestnum, loctesterr, h6, true,[](string &str) { MapStringAppend(str, "<--Hello"); });




                            // 1. Heap da container ordinato
                            lasd::HeapVec<string> h8(4);
                            Empty(loctestnum, loctesterr, h8, false);
                            Traverse(loctestnum, loctesterr, h8, true, &TraversePrint<string>);
                            Size(loctestnum, loctesterr, h8, true, 4);
                            IsHeap(loctestnum, loctesterr, h8, true);

                            lasd::Vector<string> vec2(4);
                            SetAt(loctestnum, loctesterr, vec2, true, 0, string("apple"));
                            SetAt(loctestnum, loctesterr, vec2, true, 1, string("banana"));
                            SetAt(loctestnum, loctesterr, vec2, true, 2, string("cherry"));
                            SetAt(loctestnum, loctesterr, vec2, true, 3, string("date"));

                            h8 = std::move(vec2);

                            Empty(loctestnum, loctesterr, vec2, false);
                            Traverse(loctestnum, loctesterr, h8, true, &TraversePrint<string>);
                            IsHeap(loctestnum, loctesterr, h8, true);

                            h8.Clear();

                            lasd::SortableVector<string> sv1(4);
                            for (int i = 0; i < 4; i++) {
                                SetAt(loctestnum, loctesterr, sv1, true, i, generateRandomString(6));
                            }
                            Traverse(loctestnum, loctesterr, sv1, true, &TraversePrint<string>);
                            sv1.Sort();
                            Traverse(loctestnum, loctesterr, sv1, true, &TraversePrint<string>);
                            h8 = std::move(sv1);
                            IsHeap(loctestnum, loctesterr, h8, true);
                            Traverse(loctestnum, loctesterr, h8, true, &TraversePrint<string>);

                            h8.Sort();
                            IsHeap(loctestnum, loctesterr, h8, false);
                            Traverse(loctestnum, loctesterr, h8, true, &TraversePrint<string>);
                            Traverse(loctestnum, loctesterr, sv1, true, &TraversePrint<string>);
                            EqualLinear(loctestnum, loctesterr, h8, sv1, false);

                            GetFront(loctestnum, loctesterr, h8, false, string("apple"));
                            GetBack(loctestnum, loctesterr, h8, false, string("date"));

                            // 2. Heap da container non ordinato e operatore []
                            lasd::HeapVec<string> h9(5);
                            Empty(loctestnum, loctesterr, h9, false);
                            Size(loctestnum, loctesterr, h9, true, 5);
                            IsHeap(loctestnum, loctesterr, h9, true);

                            cout<<"mammffsfsfsadadsad"<<endl;

                            lasd::List<string> lst5;
                            for (int i = 0; i < 5; i++) {
                                InsertAtBack(loctestnum, loctesterr, lst5, true, generateRandomString(10));
                            }
                            h9 = std::move(lst5);
                            Empty(loctestnum, loctesterr, lst5, false);
                            Size(loctestnum, loctesterr, h9, true, 5);
                            IsHeap(loctestnum, loctesterr, h9, true);
                                                        cout<<"mammffsfsfsawqeewe123324332324dadsad"<<endl;

                            Traverse(loctestnum, loctesterr, h9, true, &TraversePrint<string>);
                            EqualLinear(loctestnum, loctesterr, h9, lst5, false);
                            h9.Sort();
                            IsHeap(loctestnum, loctesterr, h9, false);

                            GetFront(loctestnum, loctesterr, h9, false, string("a"));
                            GetBack(loctestnum, loctesterr, h9, false, string("z"));
                            

                            h9.Clear();
                            Empty(loctestnum, loctesterr, h9, true);
                            Size(loctestnum, loctesterr, h9, true, 0);
                            IsHeap(loctestnum, loctesterr, h9, true);

                            // Heap vuoto
                            lasd::HeapVec<string> h10;
                            Empty(loctestnum, loctesterr, h10, true);
                            Size(loctestnum, loctesterr, h10, true, 0);
                            IsHeap(loctestnum, loctesterr, h10, true);
                            h10.Sort();
                            IsHeap(loctestnum, loctesterr, h10, true);
                            EqualHeapVec(loctestnum, loctesterr, h10, h1, true);
                            NonEqualHeapVec(loctestnum, loctesterr, h10, h1, false);
                            h10.Clear();
                            Empty(loctestnum, loctesterr, h10, true);
                            Size(loctestnum, loctesterr, h10, true, 0);
                            IsHeap(loctestnum, loctesterr, h10, true);

                            lasd::Vector<string> vec3;
                            lasd::HeapVec<string> h11(std::move(vec3));
                            Empty(loctestnum, loctesterr, h11, true);
                            Size(loctestnum, loctesterr, h11, true, 0);
                            IsHeap(loctestnum, loctesterr, h11, true);

                            // Heap con un solo elemento
                            lasd::HeapVec<string> h12(1);
                            Empty(loctestnum, loctesterr, h12, false);
                            Size(loctestnum, loctesterr, h12, true, 1);
                            IsHeap(loctestnum, loctesterr, h12, true);

                            lasd::SetVec<string> v2;
                            InsertC(loctestnum, loctesterr, v2, true, string("single"));
                            Traverse(loctestnum, loctesterr, v2, true, &TraversePrint<string>);
                            h12 = std::move(v2);
                            Empty(loctestnum, loctesterr, v2, false);
                            Size(loctestnum, loctesterr, v2, true, 1);
                            IsHeap(loctestnum, loctesterr, h12, true);
                            Traverse(loctestnum, loctesterr, h12, true, &TraversePrint<string>);
                            EqualHeapVec(loctestnum, loctesterr, h12, h1, false);
                            NonEqualHeapVec(loctestnum, loctesterr, h12, h1, true);
                            h12.Clear();

                            // Heap con elementi tutti uguali
                            lasd::HeapVec<string> h13(5);
                            Empty(loctestnum, loctesterr, h13, false);
                            Size(loctestnum, loctesterr, h13, true, 5);
                            IsHeap(loctestnum, loctesterr, h13, true);

                            lasd::Vector<string> vec4(5);
                            for (int i = 0; i < 5; i++) {
                                SetAt(loctestnum, loctesterr, vec4, true, i, string("same"));
                            }
                            h13 = vec4;
                            IsHeap(loctestnum, loctesterr, h13, true);
                            h13.Sort();
                            IsHeap(loctestnum, loctesterr, h13, true);

                            
                            

                            
                    }catch(...)
                    {
                        loctestnum++;
                        loctesterr++;
                        cout << endl
                            << "Unmanaged error! " << endl;
                    }
                cout << "End of Heap<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
                testnum += loctestnum;
                testerr += loctesterr;
            }

    
    /* ************************************************************************** */

            void testPQHeapInt(unsigned &testnum, unsigned &testerr){
                unsigned loctestnum = 0, loctesterr = 0;
                cout << endl
                        << "Begin of PQHeap<int> Test:" << endl;
                    try
                    {
                        lasd::PQHeap<int> pqh1;
                        Empty(loctestnum, loctesterr, pqh1, true);
                        Size(loctestnum, loctesterr, pqh1, true, 0);

                        for(int i = 0; i < 10; i++){
                            Insert(loctestnum, loctesterr, pqh1, generateRandomInt());
                        }


                        Traverse(loctestnum, loctesterr, pqh1, true, &TraversePrint<int>);
                        Change(loctestnum, loctesterr, pqh1,true, 0, 1000);
                        Change(loctestnum, loctesterr, pqh1,true, 1, 500);
                        Traverse(loctestnum, loctesterr, pqh1, true, &TraversePrint<int>);


                        pqh1.Clear();

                        Empty(loctestnum, loctesterr, pqh1, true);
                        Size(loctestnum, loctesterr, pqh1, true, 0);
                        Tip(loctestnum,loctesterr, pqh1, false, 0);
                        RemoveTip(loctestnum, loctesterr, pqh1, false);


                        lasd::HeapVec<int> h1;
                        Empty(loctestnum, loctesterr, h1, true);
                        Size(loctestnum, loctesterr, h1, true, 0);

                        lasd::List<int> lst1;
                        for(int i=0; i < 10; i++){
                            InsertAtBack(loctestnum, loctesterr, lst1, true, generateRandomInt());
                        } 

                        pqh1 = lst1;
                        Empty(loctestnum, loctesterr, pqh1, false);
                        Size(loctestnum, loctesterr, pqh1, false, 0);

                        Traverse(loctestnum, loctesterr, pqh1, true, &TraversePrint<int>);

                        pqh1.Clear();

                        pqh1 = std::move(lst1);

                        Empty(loctestnum, loctesterr, pqh1, false);

                        Traverse(loctestnum, loctesterr, pqh1, true, &TraversePrint<int>);


                        pqh1.Clear();  
                        
                        cout<<"Insert"<<endl;


                        InsertMovePQ(loctestnum, loctesterr, pqh1, 1);
                        InsertMovePQ(loctestnum, loctesterr, pqh1, 90);
                        Traverse(loctestnum, loctesterr, pqh1, true, &TraversePrint<int>);

                        Tip(loctestnum,loctesterr, pqh1, true, 90);
                        RemoveTip(loctestnum, loctesterr, pqh1, true);
                        TipNRemove(loctestnum, loctesterr, pqh1, true, 1);
                        
                        cout<<"Mammto"<<endl;
                        InsertMovePQ(loctestnum, loctesterr, pqh1, 1000);

                        ChangeMovePQ(loctestnum, loctesterr, pqh1, 0, std::move(92327897),true);
                        Traverse(loctestnum, loctesterr, pqh1, true, &TraversePrint<int>);

                        lasd::PQHeap<int> pqh2(pqh1);
                        Empty(loctestnum, loctesterr, pqh2, false);

                        Traverse(loctestnum, loctesterr, pqh2, true, &TraversePrint<int>);

                        lasd::PQHeap<int> pqh3(std::move(pqh2));
                        Empty(loctestnum, loctesterr, pqh2, true);
                        Size(loctestnum, loctesterr, pqh2, true, 0);

                        Traverse(loctestnum, loctesterr, pqh3, true, &TraversePrint<int>);

                        Change(loctestnum, loctesterr, pqh3,true, 0, 100);

                        ChangeMovePQ(loctestnum, loctesterr, pqh3, 0, std::move(1),true);
                        cout<<"Mammtowqeqw"<<endl;

                        Insert(loctestnum, loctesterr, pqh3, 1000);

                        Traverse(loctestnum, loctesterr, pqh3, true, &TraversePrint<int>);

                        ChangeCopyPQ(loctestnum, loctesterr, pqh3, 1000, 500, false);

                        pqh3.Clear();

                        ChangeCopyPQ(loctestnum, loctesterr, pqh3, 0, 500, false);
                        ChangeMovePQ(loctestnum, loctesterr, pqh3, 0, std::move(500), false);


                        lasd::List<int> lst2;
                        for(int i = 0; i < 10; i++){
                            InsertAtBack(loctestnum, loctesterr, lst2, true, generateRandomInt());
                        }


                        lasd::PQHeap<int> pqh4(std::move(lst2));

                        pqh3 = pqh4;
                        Empty(loctestnum, loctesterr, pqh4, false);
                        Size(loctestnum, loctesterr, pqh4, false, 0);

                        Traverse(loctestnum, loctesterr, pqh3, true, &TraversePrint<int>);
                        RemoveTip(loctestnum, loctesterr, pqh3, true);
                        Traverse(loctestnum, loctesterr, pqh3, true, &TraversePrint<int>);

                        pqh3.Clear();

                        pqh3 = std::move(pqh4);


                        pqh3.Clear();
                        pqh4.Clear();

                        lst2.Clear();

                        InsertAtBack(loctestnum, loctesterr, lst2, true, 1);

                        pqh4 = std::move(lst2);

                        Traverse(loctestnum, loctesterr, pqh4, true, &TraversePrint<int>);
                        Tip(loctestnum,loctesterr, pqh4, true, 1);
                        TipNRemove(loctestnum, loctesterr, pqh4, true, 1);
                        Empty(loctestnum, loctesterr, pqh4, true);
                        Size(loctestnum, loctesterr, pqh4, true, 0);

                        pqh4.Clear();
                        Exists(loctestnum, loctesterr, pqh4, false, 0);

                        //PQHeap con contenitore ordinato
                        lasd::SetLst<int> sl1;
                        for(int i = 0; i < 10; i++){
                            InsertAtBack(loctestnum, loctesterr, sl1, true, generateUniqueRandomInt());
                        }
                        lasd::PQHeap<int> pqh5(10);
                        Empty(loctestnum, loctesterr, sl1, false);
                        Size(loctestnum, loctesterr, sl1, true, 10);

                        pqh5 = sl1;

                        Tip(loctestnum, loctesterr, pqh5, true, pqh5.Tip());
                        RemoveTip(loctestnum, loctesterr, pqh5, true);
                        Traverse(loctestnum, loctesterr, pqh5, true, &TraversePrint<int>);
                        EqualLinear(loctestnum, loctesterr, pqh5, sl1, false);
                        NonEqualLinear(loctestnum, loctesterr, pqh5, sl1, true);

                        Empty(loctestnum, loctesterr, sl1, false);
                        Traverse(loctestnum, loctesterr, pqh5, true, &TraversePrint<int>);
                        
                        InsertMovePQ(loctestnum, loctesterr, pqh5, 1000);
                        Traverse(loctestnum, loctesterr, pqh5, true, &TraversePrint<int>);
                        ChangeMovePQ(loctestnum, loctesterr, pqh5, 0, std::move(500), true);
                        Traverse(loctestnum, loctesterr, pqh5, true, &TraversePrint<int>);
                        ChangeCopyPQ(loctestnum, loctesterr, pqh5, 1000, 500, false);
                        Exists(loctestnum, loctesterr, pqh5, true, 500);

                        //PQHeap con contenitore non ordinato
                        lasd::HeapVec<int> h90(sl1);
                        Empty(loctestnum, loctesterr, h90, false);
                        Size(loctestnum, loctesterr, h90, true, 10);
                        IsHeap(loctestnum, loctesterr, h90, true);

                        lasd::PQHeap<int> pqh6(std::move(h90));
                        Tip(loctestnum,loctesterr, pqh6, true, pqh6.Tip()); 
                        RemoveTip(loctestnum, loctesterr, pqh6, true);
                        Traverse(loctestnum, loctesterr, pqh6, true, &TraversePrint<int>);
                        
                        Empty(loctestnum, loctesterr, pqh6, false);
                        Size(loctestnum, loctesterr, pqh6, true, 9);
                        Exists(loctestnum, loctesterr, pqh6, false, 500);
                        Traverse(loctestnum, loctesterr, pqh6, true, &TraversePrint<int>);

                        //Test operator[] non-const
                        const lasd::PQHeap<int>& const_pqh = pqh6;
                        std::cout << "Accesso const (index 1): " << const_pqh[1] << std::endl;

                        //PQHeap con un solo elemento
                        lasd::PQHeap<int> pqh7;
                        lasd::Vector<int> vec1(1);
                        SetAt(loctestnum, loctesterr, vec1, true, 0, 42);
                        pqh7 = std::move(vec1);
                        Empty(loctestnum, loctesterr, pqh7, false);
                        Size(loctestnum, loctesterr, pqh7, true, 1);
                        
                        Exists(loctestnum, loctesterr, pqh7, true, 42);
                        Tip(loctestnum,loctesterr, pqh7, true, 42);
                        RemoveTip(loctestnum, loctesterr, pqh7, true);
                        Empty(loctestnum, loctesterr, pqh7, true);
                        Size(loctestnum, loctesterr, pqh7, true, 0);
                        Exists(loctestnum, loctesterr, pqh7, false, 42);
                        InsertMovePQ(loctestnum, loctesterr, pqh7, 100);
                        ChangeMovePQ(loctestnum, loctesterr, pqh7, 0, std::move(200), true);
                        Traverse(loctestnum, loctesterr, pqh7, true, &TraversePrint<int>);
                        ChangeCopyPQ(loctestnum, loctesterr, pqh7, 200, 300, false);
                        Exists(loctestnum, loctesterr, pqh7, false, 300);
                        pqh7.Clear();
                        

                        //PQHeap con elementi tutti uguali
                        lasd::PQHeap<int> pqh8(5);
                        Empty(loctestnum, loctesterr, pqh8, false);
                        Size(loctestnum, loctesterr, pqh8, true, 5);

                        lasd::Vector<int> vec2(5);
                        for (int i = 0; i < 5; i++) {
                            SetAt(loctestnum, loctesterr, vec2, true, i, 42);
                        }
                        pqh8 = vec2;
                        Exists(loctestnum, loctesterr, pqh8, true, 42);
                        Traverse(loctestnum, loctesterr, pqh8, true, &TraversePrint<int>);
                        Tip(loctestnum,loctesterr, pqh8, true, 42);
                        RemoveTip(loctestnum, loctesterr, pqh8, true);
                        Traverse(loctestnum, loctesterr, pqh8, true, &TraversePrint<int>);
                        TipNRemove(loctestnum, loctesterr, pqh8, true, 42);
                        InsertMovePQ(loctestnum, loctesterr, pqh8, 1000);
                        Traverse(loctestnum, loctesterr, pqh8, true, &TraversePrint<int>);

                        
                        
                        RemoveTip(loctestnum, loctesterr, pqh8, true);
                        RemoveTip(loctestnum, loctesterr, pqh8, true);
                        RemoveTip(loctestnum, loctesterr, pqh8, true);
                        Empty(loctestnum, loctesterr, pqh8, false);
                        Size(loctestnum, loctesterr, pqh8, true, 1);
                        Traverse(loctestnum, loctesterr, pqh8, true, &TraversePrint<int>);
                        InsertMovePQ(loctestnum, loctesterr, pqh8, 1000);
                        
                       
                        
                    
                        lasd::List<int> lst3;
                        for(int i = 0; i < 10; i++){
                            InsertAtBack(loctestnum, loctesterr, lst3, true, i);
                        }
                        
                        HeapVec<int> heap600(lst3);
                        GetFront(loctestnum, loctesterr, heap600, true, 9);
                        GetBack(loctestnum, loctesterr, heap600, true, 1);
                        Traverse(loctestnum, loctesterr, heap600, true, &TraversePrint<int>);

                        PQHeap<int> pqh9(std::move(heap600));
                        GetFront(loctestnum, loctesterr, pqh9, true, 9);
                        GetBack(loctestnum, loctesterr, pqh9, true, 1);

                        Vector<int> vec400(2);
                        SetAt(loctestnum, loctesterr, vec400, true, 0, 1);
                        SetAt(loctestnum, loctesterr, vec400, true, 1, 2);

                        HeapVec<int> heap700(std::move(vec400));
                        GetFront(loctestnum, loctesterr, heap700, true, 2);
                        GetBack(loctestnum, loctesterr, heap700, true, 1);
                       

                        Traverse(loctestnum, loctesterr, heap700, true, &TraversePrint<int>);

                        PQHeap<int> pqh10(std::move(heap700));
                        pqh10.Resize(5);
                        Traverse(loctestnum, loctesterr, pqh10, true, &TraversePrint<int>);
                        Size(loctestnum, loctesterr, pqh10, true, 5);
                        for(int i = 2; i < 5; i++){
                            Change(loctestnum, loctesterr, pqh10, true, i, 1000 + i);
                        }

                        Traverse(loctestnum, loctesterr, pqh10, true, &TraversePrint<int>);

                        try{
                            pqh10.Resize(1);
                            Traverse(loctestnum, loctesterr, pqh10, true, &TraversePrint<int>);
                            Size(loctestnum, loctesterr, pqh10, true, 2);
                            loctestnum++;

                            loctesterr++;
                        }catch(...){
                            loctestnum++;
                            cout << "Resize failed as expected!  --> check Passed" << endl;

                        }

                        //pq vuoto
                        lasd::PQHeap<int> pqh11;
                        Empty(loctestnum, loctesterr, pqh11, true);
                        Size(loctestnum, loctesterr, pqh11, true, 0);
                        Tip(loctestnum, loctesterr, pqh11, false, 0);
                        RemoveTip(loctestnum, loctesterr, pqh11, false);
                        Exists(loctestnum, loctesterr, pqh11, false, 0);
                        Traverse(loctestnum, loctesterr, pqh11, true, &TraversePrint<int>);
                        TraversePreOrder(loctestnum, loctesterr, pqh11, true, &TraversePrint<int>);
                        TraversePostOrder(loctestnum, loctesterr, pqh11, true, &TraversePrint<int>);
                        GetFront(loctestnum, loctesterr, pqh11, false, 0);
                        GetBack(loctestnum, loctesterr, pqh11, false, 0);
                        Change(loctestnum, loctesterr, pqh11, false, 0, 100);
                        ChangeMovePQ(loctestnum, loctesterr, pqh11, 0, std::move(100), false);
                        ChangeCopyPQ(loctestnum, loctesterr, pqh11, 0, 100, false);
                        InsertMovePQ(loctestnum, loctesterr, pqh11, 1);
                        TipNRemove(loctestnum, loctesterr, pqh11, true, 1);
                        RemoveTip(loctestnum, loctesterr, pqh11, false);
                        pqh11.Resize(5);
                        Empty(loctestnum, loctesterr, pqh11, false);
                        Size(loctestnum, loctesterr, pqh11, true, 5);

                        

                    }catch(...)
                    {
                        loctestnum++;
                        loctesterr++;
                        cout << endl
                            << "Unmanaged error! " << endl;
                    }
                cout << "End of PQHeap<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
                testnum += loctestnum;
                testerr += loctesterr;
            }
    /* ************************************************************************** */


            void testPQHeapDouble(unsigned &testnum, unsigned &testerr){
                unsigned loctestnum = 0, loctesterr = 0;
                cout << endl
                        << "Begin of PQHeap<double> Test:" << endl;
                    try
                    {
                        lasd::PQHeap<double> pqh1;
                        Empty(loctestnum, loctesterr, pqh1, true);
                        Size(loctestnum, loctesterr, pqh1, true, 0);

                        for(int i = 0; i < 10; i++){
                            Insert(loctestnum, loctesterr, pqh1, generateRandomDouble());
                        }

                        Traverse(loctestnum, loctesterr, pqh1, true, &TraversePrint<double>);
                        Change(loctestnum, loctesterr, pqh1,true, 0, 1000.0);
                        Change(loctestnum, loctesterr, pqh1,true, 1, 500.0);
                        Traverse(loctestnum, loctesterr, pqh1, true, &TraversePrint<double>);

                        pqh1.Clear();

                        Empty(loctestnum, loctesterr, pqh1, true);
                        Size(loctestnum, loctesterr, pqh1, true, 0);
                        Tip(loctestnum, loctesterr, pqh1, false, 0.0);
                        RemoveTip(loctestnum, loctesterr, pqh1, false);

                        lasd::HeapVec<double> h1;
                        Empty(loctestnum, loctesterr, h1, true);
                        Size(loctestnum, loctesterr, h1, true, 0);

                        lasd::List<double> lst1;
                        for(int i = 0; i < 10; i++){
                            InsertAtBack(loctestnum, loctesterr, lst1, true, generateRandomDouble());
                        } 

                        pqh1 = lst1;
                        Empty(loctestnum, loctesterr, pqh1, false);
                        Size(loctestnum, loctesterr, pqh1, false, 0);
                        Traverse(loctestnum, loctesterr, pqh1, true, &TraversePrint<double>);

                        pqh1.Clear();
                        pqh1 = std::move(lst1);
                        Empty(loctestnum, loctesterr, pqh1, false);
                        Traverse(loctestnum, loctesterr, pqh1, true, &TraversePrint<double>);

                        pqh1.Clear();  

                        InsertMovePQ(loctestnum, loctesterr, pqh1, 1.0);
                        InsertMovePQ(loctestnum, loctesterr, pqh1, 90.0);
                        Traverse(loctestnum, loctesterr, pqh1, true, &TraversePrint<double>);

                        Tip(loctestnum, loctesterr, pqh1, true, 90.0);
                        RemoveTip(loctestnum, loctesterr, pqh1, true);
                        TipNRemove(loctestnum, loctesterr, pqh1, true, 1.0);

                        InsertMovePQ(loctestnum, loctesterr, pqh1, 1000.0);
                        ChangeMovePQ(loctestnum, loctesterr, pqh1, 0, std::move(92327897.0), true);
                        Traverse(loctestnum, loctesterr, pqh1, true, &TraversePrint<double>);

                        lasd::PQHeap<double> pqh2(pqh1);
                        Empty(loctestnum, loctesterr, pqh2, false);
                        Traverse(loctestnum, loctesterr, pqh2, true, &TraversePrint<double>);

                        lasd::PQHeap<double> pqh3(std::move(pqh2));
                        Empty(loctestnum, loctesterr, pqh2, true);
                        Size(loctestnum, loctesterr, pqh2, true, 0);
                        Traverse(loctestnum, loctesterr, pqh3, true, &TraversePrint<double>);

                        Change(loctestnum, loctesterr, pqh3,true, 0, 100.0);
                        ChangeMovePQ(loctestnum, loctesterr, pqh3, 0, std::move(1.0), true);
                        Insert(loctestnum, loctesterr, pqh3, 1000.0);
                        Traverse(loctestnum, loctesterr, pqh3, true, &TraversePrint<double>);

                        ChangeCopyPQ(loctestnum, loctesterr, pqh3, 1000.0, 500.0, false);

                        pqh3.Clear();

                        ChangeCopyPQ(loctestnum, loctesterr, pqh3, 0.0, 500.0, false);
                        ChangeMovePQ(loctestnum, loctesterr, pqh3, 0, std::move(500.0), false);

                        lasd::List<double> lst2;
                        for(int i = 0; i < 10; i++){
                            InsertAtBack(loctestnum, loctesterr, lst2, true, generateRandomDouble());
                        }

                        lasd::PQHeap<double> pqh4(std::move(lst2));

                        pqh3 = pqh4;
                        Empty(loctestnum, loctesterr, pqh4, false);
                        Size(loctestnum, loctesterr, pqh4, false, 0);
                        Traverse(loctestnum, loctesterr, pqh3, true, &TraversePrint<double>);

                        RemoveTip(loctestnum, loctesterr, pqh3, true);
                        Traverse(loctestnum, loctesterr, pqh3, true, &TraversePrint<double>);

                        pqh3.Clear();
                        pqh3 = std::move(pqh4);

                        pqh3.Clear();
                        pqh4.Clear();

                        lst2.Clear();

                        InsertAtBack(loctestnum, loctesterr, lst2, true, 1.0);

                        pqh4 = std::move(lst2);

                        Traverse(loctestnum, loctesterr, pqh4, true, &TraversePrint<double>);
                        Tip(loctestnum, loctesterr, pqh4, true, 1.0);
                        TipNRemove(loctestnum, loctesterr, pqh4, true, 1.0);
                        Empty(loctestnum, loctesterr, pqh4, true);
                        Size(loctestnum, loctesterr, pqh4, true, 0);



                        //PQHeap con contenitore ordinato
                        lasd::SetLst<double> sl1;
                        for(int i = 0; i < 10; i++){
                            InsertAtBack(loctestnum, loctesterr, sl1, true, generateUniqueRandomDouble());
                        }
                        lasd::PQHeap<double> pqh5(10);
                        Empty(loctestnum, loctesterr, sl1, false);
                        Size(loctestnum, loctesterr, sl1, true, 10);

                        pqh5 = sl1;

                        Tip(loctestnum, loctesterr, pqh5, true, pqh5.Tip());
                        RemoveTip(loctestnum, loctesterr, pqh5, true);
                        Traverse(loctestnum, loctesterr, pqh5, true, &TraversePrint<double>);
                        EqualLinear(loctestnum, loctesterr, pqh5, sl1, false);
                        NonEqualLinear(loctestnum, loctesterr, pqh5, sl1, true);

                        Empty(loctestnum, loctesterr, sl1, false);
                        Traverse(loctestnum, loctesterr, pqh5, true, &TraversePrint<double>);

                        InsertMovePQ(loctestnum, loctesterr, pqh5, 1000.0);
                        Traverse(loctestnum, loctesterr, pqh5, true, &TraversePrint<double>);
                        ChangeMovePQ(loctestnum, loctesterr, pqh5, 0, std::move(500.0), true);
                        Traverse(loctestnum, loctesterr, pqh5, true, &TraversePrint<double>);
                        ChangeCopyPQ(loctestnum, loctesterr, pqh5, 1000.0, 500.0, false);
                        Exists(loctestnum, loctesterr, pqh5, true, 500.0);

                        //PQHeap con contenitore non ordinato
                        lasd::HeapVec<double> h90(sl1);
                        Empty(loctestnum, loctesterr, h90, false);
                        Size(loctestnum, loctesterr, h90, true, 10);
                        IsHeap(loctestnum, loctesterr, h90, true);

                        lasd::PQHeap<double> pqh6(std::move(h90));
                        Tip(loctestnum, loctesterr, pqh6, true, pqh6.Tip()); 
                        RemoveTip(loctestnum, loctesterr, pqh6, true);
                        Traverse(loctestnum, loctesterr, pqh6, true, &TraversePrint<double>);

                        Empty(loctestnum, loctesterr, pqh6, false);
                        Size(loctestnum, loctesterr, pqh6, true, 9);
                        Exists(loctestnum, loctesterr, pqh6, false, 500.0);
                        Traverse(loctestnum, loctesterr, pqh6, true, &TraversePrint<double>);

                        //Test operator[] non-const
                        const lasd::PQHeap<double>& const_pqh = pqh6;
                        std::cout << "Accesso const (index 1): " << const_pqh[1] << std::endl;

                        //PQHeap con un solo elemento
                        lasd::PQHeap<double> pqh7;
                        lasd::Vector<double> vec1(1);
                        SetAt(loctestnum, loctesterr, vec1, true, 0, 42.0);
                        pqh7 = std::move(vec1);
                        Empty(loctestnum, loctesterr, pqh7, false);
                        Size(loctestnum, loctesterr, pqh7, true, 1);

                        Exists(loctestnum, loctesterr, pqh7, true, 42.0);
                        Tip(loctestnum, loctesterr, pqh7, true, 42.0);
                        RemoveTip(loctestnum, loctesterr, pqh7, true);
                        Empty(loctestnum, loctesterr, pqh7, true);
                        Size(loctestnum, loctesterr, pqh7, true, 0);
                        Exists(loctestnum, loctesterr, pqh7, false, 42.0);
                        InsertMovePQ(loctestnum, loctesterr, pqh7, 100.0);
                        ChangeMovePQ(loctestnum, loctesterr, pqh7, 0, std::move(200.0), true);
                        Traverse(loctestnum, loctesterr, pqh7, true, &TraversePrint<double>);
                        ChangeCopyPQ(loctestnum, loctesterr, pqh7, 200.0, 300.0, false);
                        Exists(loctestnum, loctesterr, pqh7, false, 300.0);
                        pqh7.Clear();

                        //PQHeap con elementi tutti uguali
                        lasd::PQHeap<double> pqh8(5);
                        Empty(loctestnum, loctesterr, pqh8, false);
                        Size(loctestnum, loctesterr, pqh8, true, 5);

                        lasd::Vector<double> vec2(5);
                        for (int i = 0; i < 5; i++) {
                            SetAt(loctestnum, loctesterr, vec2, true, i, 42.0);
                        }
                        pqh8 = vec2;
                        Exists(loctestnum, loctesterr, pqh8, true, 42.0);
                        Traverse(loctestnum, loctesterr, pqh8, true, &TraversePrint<double>);
                        Tip(loctestnum, loctesterr, pqh8, true, 42.0);
                        RemoveTip(loctestnum, loctesterr, pqh8, true);
                        Traverse(loctestnum, loctesterr, pqh8, true, &TraversePrint<double>);
                        TipNRemove(loctestnum, loctesterr, pqh8, true, 42.0);
                        InsertMovePQ(loctestnum, loctesterr, pqh8, 1000.0);
                        Traverse(loctestnum, loctesterr, pqh8, true, &TraversePrint<double>);

                        RemoveTip(loctestnum, loctesterr, pqh8, true);
                        RemoveTip(loctestnum, loctesterr, pqh8, true);
                        RemoveTip(loctestnum, loctesterr, pqh8, true);
                        Empty(loctestnum, loctesterr, pqh8, false);
                        Size(loctestnum, loctesterr, pqh8, true, 1);
                        Traverse(loctestnum, loctesterr, pqh8, true, &TraversePrint<double>);
                        InsertMovePQ(loctestnum, loctesterr, pqh8, 1000.0);

                        lasd::List<double> lst3;
                        for(int i = 0; i < 10; i++){
                            InsertAtBack(loctestnum, loctesterr, lst3, true, static_cast<double>(i));
                        }

                        HeapVec<double> heap600(lst3);
                        GetFront(loctestnum, loctesterr, heap600, true, 9.0);
                        GetBack(loctestnum, loctesterr, heap600, true, 1.0);
                        
                        Traverse(loctestnum, loctesterr, heap600, true, &TraversePrint<double>);

                        PQHeap<double> pqh9(std::move(heap600));
                        GetFront(loctestnum, loctesterr, pqh9, true, 9.0);
                        GetBack(loctestnum, loctesterr, pqh9, true, 1.0);

                        Vector<double> vec400(2);
                        SetAt(loctestnum, loctesterr, vec400, true, 0, 1.0);
                        SetAt(loctestnum, loctesterr, vec400, true, 1, 2.0);

                        HeapVec<double> heap700(std::move(vec400));
                        GetFront(loctestnum, loctesterr, heap700, true, 2.0);
                        GetBack(loctestnum, loctesterr, heap700, true, 1.0);

                        Traverse(loctestnum, loctesterr, heap700, true, &TraversePrint<double>);

                        PQHeap<double> pqh10(std::move(heap700));
                        pqh10.Resize(5);
                        Traverse(loctestnum, loctesterr, pqh10, true, &TraversePrint<double>);
                        Size(loctestnum, loctesterr, pqh10, true, 5);
                        for(int i = 2; i < 5; i++){
                            Change(loctestnum, loctesterr, pqh10, true, i, 1000.0 + i);
                        }

                        Traverse(loctestnum, loctesterr, pqh10, true, &TraversePrint<double>);

                        try {
                            pqh10.Resize(1);
                            Traverse(loctestnum, loctesterr, pqh10, true, &TraversePrint<double>);
                            Size(loctestnum, loctesterr, pqh10, true, 2);
                            loctestnum++;
                            loctesterr++;
                        } catch (...) {
                            loctestnum++;
                            cout << "Resize failed as expected!  --> check Passed" << endl;
                        }

                        //pq vuoto
                        lasd::PQHeap<double> pqh11;
                        Empty(loctestnum, loctesterr, pqh11, true);
                        Size(loctestnum, loctesterr, pqh11, true, 0);
                        Tip(loctestnum, loctesterr, pqh11, false, 0.0);
                        RemoveTip(loctestnum, loctesterr, pqh11, false);
                        Exists(loctestnum, loctesterr, pqh11, false, 0.0);
                        Traverse(loctestnum, loctesterr, pqh11, true, &TraversePrint<double>);
                        TraversePreOrder(loctestnum, loctesterr, pqh11, true, &TraversePrint<double>);
                        TraversePostOrder(loctestnum, loctesterr, pqh11, true, &TraversePrint<double>);
                        GetFront(loctestnum, loctesterr, pqh11, false, 0.0);
                        GetBack(loctestnum, loctesterr, pqh11, false, 0.0);
                        Change(loctestnum, loctesterr, pqh11, false, 0, 100.0);
                        ChangeMovePQ(loctestnum, loctesterr, pqh11, 0, std::move(100.0), false);
                        ChangeCopyPQ(loctestnum, loctesterr, pqh11, 0, 100.0, false);
                        InsertMovePQ(loctestnum, loctesterr, pqh11, 1.0);
                        TipNRemove(loctestnum, loctesterr, pqh11, true, 1.0);
                        RemoveTip(loctestnum, loctesterr, pqh11, false);
                        pqh11.Resize(5);
                        Empty(loctestnum, loctesterr, pqh11, false);
                        Size(loctestnum, loctesterr, pqh11, true, 5);




                    }catch(...)
                    {
                        loctestnum++;
                        loctesterr++;
                        cout << endl
                            << "Unmanaged error! " << endl;
                    }
                cout << "End of PQHeap<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
                testnum += loctestnum;
                testerr += loctesterr;
            }

    /* ************************************************************************** */

            void testPQHeapString(unsigned &testnum, unsigned &testerr){
                unsigned loctestnum = 0, loctesterr = 0;
                cout << endl
                        << "Begin of PQHeap<string> Test:" << endl;
                    try
                    {
                        lasd::PQHeap<string> pqh1;
                        Empty(loctestnum, loctesterr, pqh1, true);
                        Size(loctestnum, loctesterr, pqh1, true, 0);

                        for(int i = 0; i < 10; i++){
                            Insert(loctestnum, loctesterr, pqh1, generateRandomString(10));
                        }

                        Traverse(loctestnum, loctesterr, pqh1, true, &TraversePrint<string>);
                        Change(loctestnum, loctesterr, pqh1,true, 0, string("Cambiato0"));
                        Change(loctestnum, loctesterr, pqh1,true, 1, string("Cambiato1"));
                        Traverse(loctestnum, loctesterr, pqh1, true, &TraversePrint<string>);

                        pqh1.Clear();

                        Empty(loctestnum, loctesterr, pqh1, true);
                        Size(loctestnum, loctesterr, pqh1, true, 0);
                        Tip(loctestnum, loctesterr, pqh1, false, string(""));
                        RemoveTip(loctestnum, loctesterr, pqh1, false);

                        lasd::HeapVec<string> h1;
                        Empty(loctestnum, loctesterr, h1, true);
                        Size(loctestnum, loctesterr, h1, true, 0);

                        lasd::List<string> lst1;
                        for(int i = 0; i < 10; i++){
                            InsertAtBack(loctestnum, loctesterr, lst1, true, generateRandomString(10));
                        }

                        pqh1 = lst1;
                        Empty(loctestnum, loctesterr, pqh1, false);
                        Size(loctestnum, loctesterr, pqh1, false, 0);
                        Traverse(loctestnum, loctesterr, pqh1, true, &TraversePrint<string>);

                        pqh1.Clear();
                        pqh1 = move(lst1);

                        Empty(loctestnum, loctesterr, pqh1, false);
                        Traverse(loctestnum, loctesterr, pqh1, true, &TraversePrint<string>);

                        pqh1.Clear();

                        InsertMovePQ(loctestnum, loctesterr, pqh1, string("uno"));
                        InsertMovePQ(loctestnum, loctesterr, pqh1, string("novanta"));
                        Traverse(loctestnum, loctesterr, pqh1, true, &TraversePrint<string>);

                        Tip(loctestnum, loctesterr, pqh1, true, string("uno"));
                        RemoveTip(loctestnum, loctesterr, pqh1, true);
                        TipNRemove(loctestnum, loctesterr, pqh1, true, string("novanta"));

                        InsertMovePQ(loctestnum, loctesterr, pqh1, string("mille"));
                        ChangeMovePQ(loctestnum, loctesterr, pqh1, 0, move(string("cambiato_finale")), true);
                        Traverse(loctestnum, loctesterr, pqh1, true, &TraversePrint<string>);

                        lasd::PQHeap<string> pqh2(pqh1);
                        Empty(loctestnum, loctesterr, pqh2, false);
                        Traverse(loctestnum, loctesterr, pqh2, true, &TraversePrint<string>);

                        lasd::PQHeap<string> pqh3(move(pqh2));
                        Empty(loctestnum, loctesterr, pqh2, true);
                        Size(loctestnum, loctesterr, pqh2, true, 0);
                        Traverse(loctestnum, loctesterr, pqh3, true, &TraversePrint<string>);

                        Change(loctestnum, loctesterr, pqh3,true, 0, string("cento"));
                        ChangeMovePQ(loctestnum, loctesterr, pqh3, 0, move(string("uno")), true);
                        Insert(loctestnum, loctesterr, pqh3, string("mille"));
                        Traverse(loctestnum, loctesterr, pqh3, true, &TraversePrint<string>);

                        ChangeCopyPQ(loctestnum, loctesterr, pqh3, 0, string("cinquecento"), true);
                        pqh3.Clear();
                        ChangeCopyPQ(loctestnum, loctesterr, pqh3, 0, string("cinquecento"), false);
                        ChangeMovePQ(loctestnum, loctesterr, pqh3, 0, move(string("cinquecento")), false);

                        lasd::List<string> lst2;
                        for(int i = 0; i < 10; i++){
                            InsertAtBack(loctestnum, loctesterr, lst2, true, generateRandomString(10));
                        }

                        lasd::PQHeap<string> pqh4(move(lst2));
                        pqh3 = pqh4;
                        Empty(loctestnum, loctesterr, pqh4, false);
                        Size(loctestnum, loctesterr, pqh4, false, 0);

                        Traverse(loctestnum, loctesterr, pqh3, true, &TraversePrint<string>);
                        RemoveTip(loctestnum, loctesterr, pqh3, true);
                        Traverse(loctestnum, loctesterr, pqh3, true, &TraversePrint<string>);

                        pqh3.Clear();
                        pqh3 = move(pqh4);
                        pqh3.Clear();
                        pqh4.Clear();
                        lst2.Clear();

                        InsertAtBack(loctestnum, loctesterr, lst2, true, string("uno"));
                        pqh4 = move(lst2);

                        Traverse(loctestnum, loctesterr, pqh4, true, &TraversePrint<string>);
                        Tip(loctestnum, loctesterr, pqh4, true, string("uno"));
                        TipNRemove(loctestnum, loctesterr, pqh4, true, string("uno"));
                        Empty(loctestnum, loctesterr, pqh4, true);
                        Size(loctestnum, loctesterr, pqh4, true, 0);

                        

                        // PQHeap con contenitore ordinato
                        lasd::SetLst<string> sl1;
                        for(int i = 0; i < 10; i++){
                            InsertAtBack(loctestnum, loctesterr, sl1, true, generateRandomString(10));
                        }
                        lasd::PQHeap<string> pqh5(10);
                        Empty(loctestnum, loctesterr, sl1, false);
                        Size(loctestnum, loctesterr, sl1, true, 10);

                        pqh5 = sl1;

                        Tip(loctestnum, loctesterr, pqh5, true, pqh5.Tip());
                        RemoveTip(loctestnum, loctesterr, pqh5, true);
                        Traverse(loctestnum, loctesterr, pqh5, true, &TraversePrint<string>);
                        EqualLinear(loctestnum, loctesterr, pqh5, sl1, false);
                        NonEqualLinear(loctestnum, loctesterr, pqh5, sl1, true);

                        Empty(loctestnum, loctesterr, sl1, false);
                        Traverse(loctestnum, loctesterr, pqh5, true, &TraversePrint<string>);

                        InsertMovePQ(loctestnum, loctesterr, pqh5, string("uno"));
                        Traverse(loctestnum, loctesterr, pqh5, true, &TraversePrint<string>);
                        ChangeMovePQ(loctestnum, loctesterr, pqh5, 0, std::move(string("due")), true);
                        Traverse(loctestnum, loctesterr, pqh5, true, &TraversePrint<string>);
                        Exists(loctestnum, loctesterr, pqh5, true, string("due"));

                        // PQHeap con contenitore non ordinato
                        lasd::HeapVec<string> h90(sl1);
                        Empty(loctestnum, loctesterr, h90, false);
                        Size(loctestnum, loctesterr, h90, true, 10);
                        IsHeap(loctestnum, loctesterr, h90, true);

                        lasd::PQHeap<string> pqh6(std::move(h90));
                        Tip(loctestnum, loctesterr, pqh6, true, pqh6.Tip()); 
                        RemoveTip(loctestnum, loctesterr, pqh6, true);
                        Traverse(loctestnum, loctesterr, pqh6, true, &TraversePrint<string>);

                        Empty(loctestnum, loctesterr, pqh6, false);
                        Size(loctestnum, loctesterr, pqh6, true, 9);
                        Exists(loctestnum, loctesterr, pqh6, false, string("due"));
                        Traverse(loctestnum, loctesterr, pqh6, true, &TraversePrint<string>);

                        // Test operator[] non-const
                        const lasd::PQHeap<string>& const_pqh = pqh6;
                        cout << "Accesso const (index 1): " << const_pqh[1] << endl;

                        // PQHeap con un solo elemento
                        lasd::PQHeap<string> pqh7;
                        lasd::Vector<string> vec1(1);
                        SetAt(loctestnum, loctesterr, vec1, true, 0, string("ciao"));
                        pqh7 = std::move(vec1);
                        Empty(loctestnum, loctesterr, pqh7, false);
                        Size(loctestnum, loctesterr, pqh7, true, 1);

                        Exists(loctestnum, loctesterr, pqh7, true, string("ciao"));
                        Tip(loctestnum, loctesterr, pqh7, true, string("ciao"));
                        RemoveTip(loctestnum, loctesterr, pqh7, true);
                        Empty(loctestnum, loctesterr, pqh7, true);
                        Size(loctestnum, loctesterr, pqh7, true, 0);
                        Exists(loctestnum, loctesterr, pqh7, false, string("ciao"));
                        InsertMovePQ(loctestnum, loctesterr, pqh7, string("gatto"));
                        ChangeMovePQ(loctestnum, loctesterr, pqh7, 0, std::move(string("cane")), true);
                        Traverse(loctestnum, loctesterr, pqh7, true, &TraversePrint<string>);
                        Exists(loctestnum, loctesterr, pqh7, false, string("cavallo"));
                        pqh7.Clear();

                        // PQHeap con elementi tutti uguali
                        lasd::PQHeap<string> pqh8(5);
                        Empty(loctestnum, loctesterr, pqh8, false);
                        Size(loctestnum, loctesterr, pqh8, true, 5);

                        lasd::Vector<string> vec2(5);
                        for (int i = 0; i < 5; i++) {
                            SetAt(loctestnum, loctesterr, vec2, true, i, string("ripeti"));
                        }
                        pqh8 = vec2;
                        Exists(loctestnum, loctesterr, pqh8, true, string("ripeti"));
                        Traverse(loctestnum, loctesterr, pqh8, true, &TraversePrint<string>);
                        Tip(loctestnum, loctesterr, pqh8, true, string("ripeti"));
                        RemoveTip(loctestnum, loctesterr, pqh8, true);
                        Traverse(loctestnum, loctesterr, pqh8, true, &TraversePrint<string>);
                        TipNRemove(loctestnum, loctesterr, pqh8, true, string("ripeti"));
                        InsertMovePQ(loctestnum, loctesterr, pqh8, string("nuovo"));
                        Traverse(loctestnum, loctesterr, pqh8, true, &TraversePrint<string>);

                        RemoveTip(loctestnum, loctesterr, pqh8, true);
                        RemoveTip(loctestnum, loctesterr, pqh8, true);
                        RemoveTip(loctestnum, loctesterr, pqh8, true);
                        Empty(loctestnum, loctesterr, pqh8, false);
                        Size(loctestnum, loctesterr, pqh8, true, 1);
                        Traverse(loctestnum, loctesterr, pqh8, true, &TraversePrint<string>);
                        InsertMovePQ(loctestnum, loctesterr, pqh8, string("altro"));

                        lasd::List<string> lst3;
                        for(int i = 0; i < 10; i++){
                            InsertAtBack(loctestnum, loctesterr, lst3, true, string("valore") + to_string(i));
                        }

                        HeapVec<string> heap600(lst3);
                        GetFront(loctestnum, loctesterr, heap600, true, string("valore9"));
                        GetBack(loctestnum, loctesterr, heap600, true, string("valore1"));
                        Traverse(loctestnum, loctesterr, heap600, true, &TraversePrint<string>);

                        PQHeap<string> pqh9(std::move(heap600));
                        GetFront(loctestnum, loctesterr, pqh9, true, string("valore9"));
                        GetBack(loctestnum, loctesterr, pqh9, true, string("valore1"));

                        Vector<string> vec400(2);
                        SetAt(loctestnum, loctesterr, vec400, true, 0, string("alfa"));
                        SetAt(loctestnum, loctesterr, vec400, true, 1, string("beta"));

                        HeapVec<string> heap700(std::move(vec400));
                        GetFront(loctestnum, loctesterr, heap700, true, string("beta"));
                        GetBack(loctestnum, loctesterr, heap700, true, string("alfa"));

                        Traverse(loctestnum, loctesterr, heap700, true, &TraversePrint<string>);

                        PQHeap<string> pqh10(std::move(heap700));
                        pqh10.Resize(5);
                        Traverse(loctestnum, loctesterr, pqh10, true, &TraversePrint<string>);
                        Size(loctestnum, loctesterr, pqh10, true, 5);
                        for(int i = 2; i < 5; i++){
                            Change(loctestnum, loctesterr, pqh10, true, i, string("extra") + to_string(i));
                        }

                        Traverse(loctestnum, loctesterr, pqh10, true, &TraversePrint<string>);

                        try {
                            pqh10.Resize(1);
                            Traverse(loctestnum, loctesterr, pqh10, true, &TraversePrint<string>);
                            Size(loctestnum, loctesterr, pqh10, true, 2);
                            loctestnum++;
                            loctesterr++;
                        } catch (...) {
                            loctestnum++;
                            cout << "Resize failed as expected!  --> check Passed" << endl;
                        }

                        // pq vuoto
                        lasd::PQHeap<string> pqh11;
                        Empty(loctestnum, loctesterr, pqh11, true);
                        Size(loctestnum, loctesterr, pqh11, true, 0);
                        Tip(loctestnum, loctesterr, pqh11, false, string(""));
                        RemoveTip(loctestnum, loctesterr, pqh11, false);
                        Exists(loctestnum, loctesterr, pqh11, false, string(""));
                        Traverse(loctestnum, loctesterr, pqh11, true, &TraversePrint<string>);
                        TraversePreOrder(loctestnum, loctesterr, pqh11, true, &TraversePrint<string>);
                        TraversePostOrder(loctestnum, loctesterr, pqh11, true, &TraversePrint<string>);
                        GetFront(loctestnum, loctesterr, pqh11, false, string(""));
                        GetBack(loctestnum, loctesterr, pqh11, false, string(""));
                        Change(loctestnum, loctesterr, pqh11, false, 0, string("start"));
                        ChangeMovePQ(loctestnum, loctesterr, pqh11, 0, std::move(string("start")), false);
                        ChangeCopyPQ(loctestnum, loctesterr, pqh11, 0, string("start"), false);
                        InsertMovePQ(loctestnum, loctesterr, pqh11, string("inizio"));
                        TipNRemove(loctestnum, loctesterr, pqh11, true, string("inizio"));
                        RemoveTip(loctestnum, loctesterr, pqh11, false);
                        pqh11.Resize(5);
                        Empty(loctestnum, loctesterr, pqh11, false);
                        Size(loctestnum, loctesterr, pqh11, true, 5);


                        






                    }catch(...)
                    {
                        loctestnum++;
                        loctesterr++;
                        cout << endl
                            << "Unmanaged error! " << endl;
                    }
                cout << "End of PQHeap<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
                testnum += loctestnum;
                testerr += loctesterr;
            }



    /* ************************************************************************** */

    void testHeap(unsigned &testnum, unsigned &testerr){
        unsigned loctestnum = 0, loctesterr = 0;
        testHeapInt(loctestnum, loctesterr);
        testHeapDouble(loctestnum, loctesterr);
       testHeapString(loctestnum, loctesterr);
        testnum += loctestnum;
        testerr += loctesterr;
        cout << endl
             << "Exercise 2 - Heap (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;

    }
    
    /* ************************************************************************** */


    void testPQHeap(unsigned &testnum, unsigned &testerr){
         unsigned loctestnum = 0, loctesterr = 0;
          testPQHeapInt(loctestnum, loctesterr);
          testPQHeapDouble(loctestnum, loctesterr);
        testPQHeapString(loctestnum, loctesterr);
        testnum += loctestnum;
        testerr += loctesterr;
        cout << endl
             << "Exercise 2 - PQheap (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
      }

    /* ************************************************************************** */
void mytest()
{
    cout << endl << "~*~#~*~ Welcome to the LASD MyTest Suite ~*~#~*~ " << endl;

    uint loctestnum, loctesterr;
    uint stestnum = 0, stesterr = 0;

    loctestnum = 0; loctesterr = 0;
    testHeap(loctestnum, loctesterr);
    stestnum += loctestnum; stesterr += loctesterr;

    loctestnum = 0; loctesterr = 0;
    testPQHeap(loctestnum, loctesterr);
    stestnum += loctestnum; stesterr += loctesterr;


    cout << endl << "Exercise 2 (MyTest) (Errors/Tests: " << stesterr << "/" << stestnum << ")";

    cout << endl << "Goodbye!" << endl;
}

    /* ************************************************************************** */

} // namespace mytest
