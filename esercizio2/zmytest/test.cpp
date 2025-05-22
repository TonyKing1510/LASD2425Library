
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


#include <string>
#include <random>
#include <ctime>


/* ************************************************************************** */

#include <iostream>

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



  /* ************************************************************************** */
  void testVectorInt(unsigned &testnum, unsigned &testerr)
{
    unsigned loctestnum = 0, loctesterr = 0;
    cout << endl
         << "Begin of Vector<int> Test:" << endl;
    try
    {
        lasd::Vector<int> v1(10);
        lasd::Vector<int> v2(10);

        NonEqualVector(loctestnum, loctesterr, v1, v2, false);
        SetFront(loctestnum, loctesterr, v1, true, 90000);
        SetAt(loctestnum, loctesterr, v2, true, 0, 2);
        v1.Resize(4);
        v2.Resize(4);
        EqualVector(loctestnum, loctesterr, v1, v2, false);
        v1.Clear();
        v2.Clear();
        Size(loctestnum, loctesterr, v1, true, 0);
        Size(loctestnum, loctesterr, v2, true, 0);
        v1.Resize(5);
        v2.Resize(5);
        SetAt(loctestnum, loctesterr, v1,  true, 0, 2);
        SetAt(loctestnum, loctesterr, v2,  true, 0, 2);
        EqualVector(loctestnum, loctesterr, v1, v2, true);

        v1.Clear();
        v2.Clear();
        v1.Resize(5);
        v2.Resize(5);

        for(int i = 0; i < 5; i++)
        {
            int n1 = generateRandomInt();
            SetAt(loctestnum, loctesterr, v1, true, i, n1);
            int n2 = generateRandomInt();
            SetAt(loctestnum, loctesterr, v2, true, i, n2);
        };

        cout<<"Funzionamento operator []"<<endl;
        for(int i = 0; i < 5; i++){
            cout<< v1[i] << "-";
        };
        cout<<" "<<endl;

        EqualVector(loctestnum, loctesterr, v1, v2, false);
        v1 = v2;
        EqualVector(loctestnum, loctesterr, v1, v2, true);

        


        lasd::SortableVector<int> sortv1(std::move(v1));
        int n1 = generateRandomInt();
        Empty(loctestnum, loctesterr, v1, false);
        Size(loctestnum, loctesterr, v1, false, 0);
        v1.Clear();
        Empty(loctestnum, loctesterr, v1, true);
        Size(loctestnum, loctesterr, v1, true, 0);
        n1 = generateRandomInt();
        SetBack(loctestnum, loctesterr, v1, false, n1);
        EqualVector(loctestnum, loctesterr, sortv1, v2, true);
        SetBack(loctestnum, loctesterr, sortv1, true, 2);
        n1 = generateRandomInt();
        SetAt(loctestnum, loctesterr, sortv1, true, 1, n1);
        GetBack(loctestnum, loctesterr, sortv1, true, 2);
        GetAt(loctestnum, loctesterr, sortv1, false, 7, 0);
        
  
        sortv1.Sort();
        TraversePreOrder(loctestnum, loctesterr, sortv1, true, &TraversePrint<int>);
        MapPostOrder(loctestnum, loctesterr, sortv1, true, &MapDouble<int>);
        TraversePreOrder(loctestnum, loctesterr, sortv1, true, &TraversePrint<int>);

        lasd::SortableVector<int> sortv2(sortv1);
        sortv2.Resize(7);
        SetAt(loctestnum, loctesterr, sortv2, true, 4, 145);
        SetBack(loctestnum, loctesterr, sortv2, true, -1120);

        EqualVector(loctestnum, loctesterr, v2, sortv1, false);
        v2 = sortv1;
        EqualVector(loctestnum, loctesterr, v2, sortv1, true);
        v2.Resize(10);
    
  
        Map(loctestnum, loctesterr, v2, true, &MapIncrement<int>);
        TraversePreOrder(loctestnum, loctesterr, v2, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, v2, true, &TraversePrint<int>);

        v2.Clear();
        Size(loctestnum, loctesterr, v2, true, 0);
        SetFront(loctestnum, loctesterr, v2, false, 123);
        MapPostOrder(loctestnum, loctesterr, v2, true, &MapDecrement<int>);
        v2.Resize(10);
        for(int i = 0; i < 10; i++)
        {
            SetAt(loctestnum, loctesterr, v2, true, i, generateRandomInt());
        }
      
        lasd::SortableVector<int> sv3(std::move(v2));
        sv3.Sort();
        TraversePreOrder(loctestnum, loctesterr, sv3, true, &TraversePrint<int>);
        EqualVector(loctestnum, loctesterr, sv3, sortv1, false);

        sv3.Clear();
        sv3.Sort();
        Empty(loctestnum, loctesterr, sv3, true);
        Size(loctestnum, loctesterr, sv3, true, 0);



        //test con vettore vuoto 
        lasd::SortableVector<int> stv3;
        Empty(loctestnum, loctesterr, stv3, true);
        Size(loctestnum, loctesterr, stv3, true, 0);
        stv3.Resize(0);
        Empty(loctestnum, loctesterr, stv3, true);
        Size(loctestnum, loctesterr, stv3, true, 0);
        stv3.Sort();
        TraversePreOrder(loctestnum, loctesterr, stv3, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, stv3, true, &TraversePrint<int>);
        MapPostOrder(loctestnum, loctesterr, stv3, true, &MapDouble<int>);
        TraversePreOrder(loctestnum, loctesterr, stv3, true, &TraversePrint<int>);
        stv3.Clear();
        GetAt(loctestnum, loctesterr, stv3, false, 0, 1);
        GetFront(loctestnum, loctesterr, stv3, false, 1);
        GetBack(loctestnum, loctesterr, stv3, false, 1);
        stv3.Resize(4);
        Size(loctestnum, loctesterr, stv3, true, 4);
        
        lasd::Vector<int> v4(4);
        Empty(loctestnum, loctesterr, v4, false);
        for(int i = 0; i < 4; i++)
        {
            SetAt(loctestnum, loctesterr, v4, true, i, generateRandomInt());
        }
        stv3 = v4;
        EqualVector(loctestnum, loctesterr, stv3, v4, true);
        stv3.Sort();
        TraversePreOrder(loctestnum, loctesterr, stv3, true, &TraversePrint<int>);
        MapPostOrder(loctestnum, loctesterr, stv3, true, &MapDouble<int>);
        NonEqualVector(loctestnum, loctesterr, stv3, v4, true);

        v4.Resize(7);
        stv3.Resize(7);

        for(int i = 0; i < 7; i++)
        {
            SetAt(loctestnum, loctesterr, v4, true, i, generateRandomInt());
        }

        stv3 = move(v4);
        EqualVector(loctestnum, loctesterr, stv3, v4, true);
        stv3.Sort();
        TraversePreOrder(loctestnum, loctesterr, stv3, true, &TraversePrint<int>);
        MapPostOrder(loctestnum, loctesterr, stv3, true, &MapDouble<int>);
        NonEqualVector(loctestnum, loctesterr, stv3, v4, true);
        v4.Clear();
        Size(loctestnum, loctesterr, v4, true, 0);
        Empty(loctestnum, loctesterr, v4, true);
        v4.Resize(0);
        Size(loctestnum, loctesterr, v4, true, 0);
        Empty(loctestnum, loctesterr, v4, true);


        lasd::SortableVector<int> stv1(1);
        SetAt(loctestnum, loctesterr, stv1, true, 0, 42);
        Empty(loctestnum, loctesterr, stv1, false);
        Size(loctestnum, loctesterr, stv1, true, 1);
        GetFront(loctestnum, loctesterr, stv1, true, 42);
        GetBack(loctestnum, loctesterr, stv1, true, 42);
        GetAt(loctestnum, loctesterr, stv1, true, 0, 42);

        // Traversal (dovrebbe stampare solo 42)
        TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<int>);

        // Ordinamento (non deve cambiare nulla, ma non deve crashare)
        stv1.Sort();

        // Mappatura (es. raddoppia elemento)
        MapPostOrder(loctestnum, loctesterr, stv1, true, &MapDouble<int>);
        GetAt(loctestnum, loctesterr, stv1, true, 0, 84);

        MapPostOrder(loctestnum, loctesterr, stv1, true, &MapDecrement<int>);
        GetAt(loctestnum, loctesterr, stv1, true, 0, 83);
        MapPostOrder(loctestnum, loctesterr, stv1, true, &MapIncrement<int>);
        GetAt(loctestnum, loctesterr, stv1, true, 0, 84);
        // Fold (es. somma elemento)
        int sum = 0;
        FoldPostOrder(loctestnum, loctesterr, stv1, true, &FoldAdd<int>, sum, 84);

        // Confronto con un altro vettore
        lasd::SortableVector<int> stv2(1);
        SetAt(loctestnum, loctesterr, stv2, true, 0, 84);
        EqualVector(loctestnum, loctesterr, stv1, stv2, true);
        NonEqualVector(loctestnum, loctesterr, stv1, stv2, false);
        stv2.Resize(2);
        SetAt(loctestnum, loctesterr, stv2, true, 1, 42);
        EqualVector(loctestnum, loctesterr, stv1, stv2, false);
        NonEqualVector(loctestnum, loctesterr, stv1, stv2, true);
        stv2 = std::move(stv1);
        EqualVector(loctestnum, loctesterr, stv1, stv2, false);
        NonEqualVector(loctestnum, loctesterr, stv1, stv2, true);
        stv1 = std::move(stv2);
        EqualVector(loctestnum, loctesterr, stv1, stv2, false);
        NonEqualVector(loctestnum, loctesterr, stv1, stv2, true);
        stv1.Clear();
        stv2.Clear();

        // Già ordinato
        lasd::SortableVector<int> stvSorted(5);
        SetAt(loctestnum, loctesterr, stvSorted, true, 0, 1);
        SetAt(loctestnum, loctesterr, stvSorted, true, 1, 2);
        SetAt(loctestnum, loctesterr, stvSorted, true, 2, 3);
        SetAt(loctestnum, loctesterr, stvSorted, true, 3, 4);
        SetAt(loctestnum, loctesterr, stvSorted, true, 4, 5);
        stvSorted.Sort(); // Deve restare uguale
        TraversePreOrder(loctestnum, loctesterr, stvSorted, true, &TraversePrint<int>);

        // Inversamente ordinato
        lasd::SortableVector<int> stvRev(5);
        SetAt(loctestnum, loctesterr, stvRev, true, 0, 5);
        SetAt(loctestnum, loctesterr, stvRev, true, 1, 4);
        SetAt(loctestnum, loctesterr, stvRev, true, 2, 3);
        SetAt(loctestnum, loctesterr, stvRev, true, 3, 2);
        SetAt(loctestnum, loctesterr, stvRev, true, 4, 1);
        stvRev.Sort(); // Deve diventare {1,2,3,4,5}
        TraversePreOrder(loctestnum, loctesterr, stvRev, true, &TraversePrint<int>);

        EqualVector(loctestnum, loctesterr, stvSorted, stvRev, true);

        v1 = v1;
        EqualVector(loctestnum, loctesterr, v1, v1, true);

        lasd::Vector<int> v3(5);
        SetAt(loctestnum, loctesterr, v3, true, 0, 1);
        Size(loctestnum, loctesterr, v3, true, 5);

        v3.Clear();
        Size(loctestnum, loctesterr, v3, true, 0);
        Empty(loctestnum, loctesterr, v3, true);


        lasd::List<int> lst1;
        InsertAtBack(loctestnum, loctesterr, lst1, true, 1);
        InsertAtBack(loctestnum, loctesterr, lst1, true, 2);
        InsertAtBack(loctestnum, loctesterr, lst1, true, 3);

        TraversePreOrder(loctestnum, loctesterr, lst1, true, &TraversePrint<int>);

        v3 = lst1;

        TraversePreOrder(loctestnum, loctesterr, v3, true, &TraversePrint<int>);
        EqualLinear(loctestnum, loctesterr, lst1, v3, true);
        Size(loctestnum, loctesterr, lst1, true, 3);
        Size(loctestnum, loctesterr, v3, true, 3);
        lst1.Clear();
        v3.Clear();

        InsertAtFront(loctestnum, loctesterr, lst1, true, 1);
        InsertAtFront(loctestnum, loctesterr, lst1, true, 2);
        InsertAtFront(loctestnum, loctesterr, lst1, true, 3);

        v3 = move(lst1);   
        TraversePreOrder(loctestnum, loctesterr, v3, true, &TraversePrint<int>);
        EqualLinear(loctestnum, loctesterr, lst1, v3, true);

        InsertAtBack(loctestnum, loctesterr, lst1, true, 4);
        InsertAtBack(loctestnum, loctesterr, lst1, true, 1);
        InsertAtBack(loctestnum, loctesterr, lst1, true, 10);
        InsertAtBack(loctestnum, loctesterr, lst1, true, 9);


        lasd::SortableVector<int> sv4(lst1);
        sv4.Sort();
        TraversePreOrder(loctestnum, loctesterr, sv4, true, &TraversePrint<int>);
        EqualLinear(loctestnum, loctesterr, lst1, sv4, false);
        Size(loctestnum, loctesterr, lst1, true, 7);

        sv4.Clear();
        lst1.Clear();
        v3.Clear();

        sv4.Resize(3);
        Size(loctestnum, loctesterr, sv4, true, 3);
        SetAt(loctestnum, loctesterr, sv4, true, 0, 1);
        SetAt(loctestnum, loctesterr, sv4, true, 1, 2);
        SetAt(loctestnum, loctesterr, sv4, true, 2, 3);

        MapPostOrder(loctestnum, loctesterr, sv4, true, &MapDouble<int>);
        TraversePreOrder(loctestnum, loctesterr, sv4, true, &TraversePrint<int>);
        MapPostOrder(loctestnum, loctesterr, sv4, true, &MapDecrement<int>);
        TraversePreOrder(loctestnum, loctesterr, sv4, true, &TraversePrint<int>);
        MapPostOrder(loctestnum, loctesterr, sv4, true, &MapIncrement<int>);
        TraversePreOrder(loctestnum, loctesterr, sv4, true, &TraversePrint<int>);
        MapPostOrder(loctestnum, loctesterr, sv4, true, &MapInvert<int>);
        TraversePreOrder(loctestnum, loctesterr, sv4, true, &TraversePrint<int>);
        
        MapPostOrder(loctestnum, loctesterr, sv4, true, &MapHalf<int>);
        TraversePreOrder(loctestnum, loctesterr, sv4, true, &TraversePrint<int>);
        MapPostOrder(loctestnum, loctesterr, sv4, true, &MapParityInvert<int>);   

        Traverse(loctestnum,loctesterr,sv4,true,&TraversePrint<int>);
        Fold(loctestnum,loctesterr,sv4,false,&FoldAdd<int>,-2,10);
        Traverse(loctestnum,loctesterr,sv4,true,&TraversePrint<int>);

        


    }
    catch (...)
    {
        loctestnum++;
        loctesterr++;
        cout << endl
             << "Unmanaged error! " << endl;
    }
    cout << "End of Vector<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}



  /* ************************************************************************** */
  void testVectorFloat(unsigned &testnum, unsigned &testerr)
{
    unsigned loctestnum = 0, loctesterr = 0;
    cout << endl
         << "Begin of Vector<float> Test:" << endl;
    try
    {
        double n1 = generateRandomDouble();
        double n2 = generateRandomDouble();
        lasd::Vector<double> v1(10);
        lasd::Vector<double> v2(10);

        SetFront(loctestnum, loctesterr, v1, true, 15.5);
        SetAt(loctestnum, loctesterr, v2, true, 0, 8.25);
        v1.Resize(4);
        v2.Resize(4);
        EqualVector(loctestnum, loctesterr, v1, v2, false);
        v1.Clear();
        v2.Clear();
        Size(loctestnum, loctesterr, v1, true, 0);
        Size(loctestnum, loctesterr, v2, true, 0);
        v1.Resize(5);
        v2.Resize(5);
        SetAt(loctestnum, loctesterr, v1, true, 0, 8.25);
        SetAt(loctestnum, loctesterr, v2, true, 0, 8.25);
        EqualVector(loctestnum, loctesterr, v1, v2, true);

        v1.Clear();
        v2.Clear();
        v1.Resize(5);
        v2.Resize(5);

        for(int i = 0; i < 5; i++)
        {
            n1 = generateRandomDouble();
            SetAt(loctestnum, loctesterr, v1, true, i, n1);
            n2 = generateRandomDouble();
            SetAt(loctestnum, loctesterr, v2, true, i, n2);
        }

        cout<<"Funzionamento operator []"<<endl;
        for(int i = 0; i < 5; i++){
            cout<< v1[i] << "-";
        };
        cout<<" "<<endl;

        EqualVector(loctestnum, loctesterr, v1, v2, false);
        v1 = v2;
        EqualVector(loctestnum, loctesterr, v1, v2, true);


        lasd::SortableVector<double> sortv1(std::move(v1));
        n1 = generateRandomDouble();
        Empty(loctestnum, loctesterr, v1, false);
        Size(loctestnum, loctesterr, v1, false, 0);
        v1.Clear();
        Empty(loctestnum, loctesterr, v1, true);
        Size(loctestnum, loctesterr, v1, true, 0);
        n1 = generateRandomDouble();
        SetBack(loctestnum, loctesterr, v1, false, 19.75);
        EqualVector(loctestnum, loctesterr, sortv1, v2, true);
        SetBack(loctestnum, loctesterr, sortv1, true, 8.25);
        n1 = generateRandomDouble();
        SetAt(loctestnum, loctesterr, sortv1, true, 1, n1);
        GetBack(loctestnum, loctesterr, sortv1, true, 8.25);
        GetAt(loctestnum, loctesterr, sortv1, false, 7, 0.0);

        sortv1.Sort();
        TraversePreOrder(loctestnum, loctesterr, sortv1, true, &TraversePrint<double>);
        MapPostOrder(loctestnum, loctesterr, sortv1, true, &MapDouble<double>);
        TraversePreOrder(loctestnum, loctesterr, sortv1, true, &TraversePrint<double>);

        lasd::SortableVector<double> sortv2(sortv1);
        sortv2.Resize(7);
        SetAt(loctestnum, loctesterr, sortv2, true, 4, 314.16);
        SetBack(loctestnum, loctesterr, sortv2, true, -987.65);

        EqualVector(loctestnum, loctesterr, v2, sortv1, false);
        v2 = sortv1;
        EqualVector(loctestnum, loctesterr, v2, sortv1, true);
        v2.Resize(10);

        Map(loctestnum, loctesterr, v2, true, &MapIncrement<double>);
        TraversePreOrder(loctestnum, loctesterr, v2, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, v2, true, &TraversePrint<double>);

        v2.Clear();
        Size(loctestnum, loctesterr, v2, true, 0);
        SetFront(loctestnum, loctesterr, v2, false, 456.78);
        MapPostOrder(loctestnum, loctesterr, v2, true, &MapDecrement<double>);
        v2.Resize(10);
        for(int i = 0; i < 10; i++)
        {
            SetAt(loctestnum, loctesterr, v2, true, i, generateRandomDouble());
        }

        lasd::SortableVector<double> sv3(std::move(v2));
        sv3.Sort();
        TraversePreOrder(loctestnum, loctesterr, sv3, true, &TraversePrint<double>);
        EqualVector(loctestnum, loctesterr, sv3, sortv1, false);

        sv3.Clear();
        sv3.Sort();
        Empty(loctestnum, loctesterr, sv3, true);
        Size(loctestnum, loctesterr, sv3, true, 0);

        lasd::SortableVector<double> stv3;
        Empty(loctestnum, loctesterr, stv3, true);
        Size(loctestnum, loctesterr, stv3, true, 0);
        stv3.Resize(0);
        Empty(loctestnum, loctesterr, stv3, true);
        Size(loctestnum, loctesterr, stv3, true, 0);
        stv3.Sort();
        TraversePreOrder(loctestnum, loctesterr, stv3, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, stv3, true, &TraversePrint<double>);
        MapPostOrder(loctestnum, loctesterr, stv3, true, &MapDouble<double>);
        TraversePreOrder(loctestnum, loctesterr, stv3, true, &TraversePrint<double>);
        stv3.Clear();
        GetAt(loctestnum, loctesterr, stv3, false, 0, 1.0);
        GetFront(loctestnum, loctesterr, stv3, false, 1.0);
        GetBack(loctestnum, loctesterr, stv3, false, 1.0);
        stv3.Resize(4);
        Size(loctestnum, loctesterr, stv3, true, 4);

        lasd::Vector<double> v4(4);
        Empty(loctestnum, loctesterr, v4, false);
        for(int i = 0; i < 4; i++)
        {
            SetAt(loctestnum, loctesterr, v4, true, i, generateRandomDouble());
        }
        stv3 = v4;
        EqualVector(loctestnum, loctesterr, stv3, v4, true);
        stv3.Sort();
        TraversePreOrder(loctestnum, loctesterr, stv3, true, &TraversePrint<double>);
        MapPostOrder(loctestnum, loctesterr, stv3, true, &MapDouble<double>);
        NonEqualVector(loctestnum, loctesterr, stv3, v4, true);

        v4.Resize(7);
        stv3.Resize(7);

        for(int i = 0; i < 7; i++)
        {
            SetAt(loctestnum, loctesterr, v4, true, i, generateRandomDouble());
        }

        stv3 = move(v4);
        EqualVector(loctestnum, loctesterr, stv3, v4, true);
        stv3.Sort();
        TraversePreOrder(loctestnum, loctesterr, stv3, true, &TraversePrint<double>);
        MapPostOrder(loctestnum, loctesterr, stv3, true, &MapDouble<double>);
        NonEqualVector(loctestnum, loctesterr, stv3, v4, true);
        v4.Clear();
        Size(loctestnum, loctesterr, v4, true, 0);
        Empty(loctestnum, loctesterr, v4, true);
        v4.Resize(0);
        Size(loctestnum, loctesterr, v4, true, 0);
        Empty(loctestnum, loctesterr, v4, true);

        lasd::SortableVector<double> stv1(1);
        SetAt(loctestnum, loctesterr, stv1, true, 0, 99.9);
        Empty(loctestnum, loctesterr, stv1, false);
        Size(loctestnum, loctesterr, stv1, true, 1);
        GetFront(loctestnum, loctesterr, stv1, true, 99.9);
        GetBack(loctestnum, loctesterr, stv1, true, 99.9);
        GetAt(loctestnum, loctesterr, stv1, true, 0, 99.9);

        TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<double>);

        stv1.Sort();

        MapPostOrder(loctestnum, loctesterr, stv1, true, &MapDouble<double>);
        GetAt(loctestnum, loctesterr, stv1, true, 0, 199.8);

        MapPostOrder(loctestnum, loctesterr, stv1, true, &MapDecrement<double>);
        GetAt(loctestnum, loctesterr, stv1, true, 0, 198.8);
        MapPostOrder(loctestnum, loctesterr, stv1, true, &MapIncrement<double>);
        GetAt(loctestnum, loctesterr, stv1, true, 0, 199.8);

        double sum = 0;
        FoldPostOrder(loctestnum, loctesterr, stv1, true, &FoldAdd<double>, sum, 199.8);
        

        lasd::SortableVector<double> stv2(1);
        SetAt(loctestnum, loctesterr, stv2, true, 0, 199.8);
        EqualVector(loctestnum, loctesterr, stv1, stv2, true);
        NonEqualVector(loctestnum, loctesterr, stv1, stv2, false);
        stv2.Resize(2);
        SetAt(loctestnum, loctesterr, stv2, true, 1, 99.9);
        EqualVector(loctestnum, loctesterr, stv1, stv2, false);
        NonEqualVector(loctestnum, loctesterr, stv1, stv2, true);
        stv2 = std::move(stv1);
        EqualVector(loctestnum, loctesterr, stv1, stv2, false);
        NonEqualVector(loctestnum, loctesterr, stv1, stv2, true);
        stv1 = std::move(stv2);
        EqualVector(loctestnum, loctesterr, stv1, stv2, false);
        NonEqualVector(loctestnum, loctesterr, stv1, stv2, true);
        stv1.Clear();
        stv2.Clear();

        lasd::SortableVector<double> stvSorted(5);
        SetAt(loctestnum, loctesterr, stvSorted, true, 0, 2.2);
        SetAt(loctestnum, loctesterr, stvSorted, true, 1, 4.4);
        SetAt(loctestnum, loctesterr, stvSorted, true, 2, 6.6);
        SetAt(loctestnum, loctesterr, stvSorted, true, 3, 8.8);
        SetAt(loctestnum, loctesterr, stvSorted, true, 4, 10.1);
        stvSorted.Sort();
        TraversePreOrder(loctestnum, loctesterr, stvSorted, true, &TraversePrint<double>);

        lasd::SortableVector<double> stvRev(5);
        SetAt(loctestnum, loctesterr, stvRev, true, 0, 10.1);
        SetAt(loctestnum, loctesterr, stvRev, true, 1, 8.8);
        SetAt(loctestnum, loctesterr, stvRev, true, 2, 6.6);
        SetAt(loctestnum, loctesterr, stvRev, true, 3, 4.4);
        SetAt(loctestnum, loctesterr, stvRev, true, 4, 2.2);
        stvRev.Sort();
        TraversePreOrder(loctestnum, loctesterr, stvRev, true, &TraversePrint<double>);

        EqualVector(loctestnum, loctesterr, stvSorted, stvRev, true);

        v1 = v1;
        EqualVector(loctestnum, loctesterr, v1, v1, true);
    }
    catch (...)
    {
        loctestnum++;
        loctesterr++;
        cout << endl
             << "Unmanaged error! " << endl;
    }
    cout << "End of Vector<float> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}
 /* ************************************************************************** */



void testVectorString(unsigned &testnum, unsigned &testerr)
{
    unsigned loctestnum = 0, loctesterr = 0;
    cout << endl
         << "Begin of Vector<String> Test:" << endl;
    try
    {
        // Test per Vector<string> e SortableVector<string> (copertura completa)
        lasd::Vector<string> v1(5);
        Empty(loctestnum, loctesterr, v1, false);

        SetAt(loctestnum, loctesterr, v1, true, 0,string( "Il"));
        SetAt(loctestnum, loctesterr, v1, true, 1, string("Napoli"));
        SetAt(loctestnum, loctesterr, v1, true, 2, string("campione"));
        SetAt(loctestnum, loctesterr, v1, true, 3, string("d'Italia"));
        SetAt(loctestnum, loctesterr, v1, true, 4, string("2022/23"));

        // Accesso valido e invalido
        GetAt(loctestnum, loctesterr, v1, true, 3, string("d'Italia"));
        GetAt(loctestnum, loctesterr, v1, false, 5, string(""));
        GetFront(loctestnum, loctesterr, v1, true, string("Il"));
        GetBack(loctestnum, loctesterr, v1, true, string("2022/23"));

        // Traverse e Fold
        TraversePreOrder(loctestnum, loctesterr, v1, true, &TraversePrint<string>);
        FoldPostOrder(loctestnum, loctesterr, v1, true, &FoldStringConcatenate, string(""), string("2022/23d'ItaliacampioneNapoliIl"));

        // Copy constructor e ordinamento
        lasd::SortableVector<string> v2(v1);
        EqualVector(loctestnum, loctesterr, v1, v2, true);
        v2.Sort();
        TraversePreOrder(loctestnum, loctesterr, v2, true, &TraversePrint<string>);

        // Exists su presente e assente
        Exists(loctestnum, loctesterr, v2, false, string("Milan"));
        Exists(loctestnum, loctesterr, v2, true, string("Napoli"));

        // Map clear su tutti gli elementi
        MapPreOrder(loctestnum, loctesterr, v2, true, [](string &str) { str.clear(); });
        FoldPostOrder(loctestnum, loctesterr, v2, true, &FoldStringConcatenate,string(""), string(""));

        // Confronto con altro vettore vuoto
        lasd::Vector<string> v3(5);
        EqualVector(loctestnum, loctesterr, v1, v3, false);
        Exists(loctestnum, loctesterr, v3, true, string(""));

        // Move assignment
        v3 = std::move(v1);
        Exists(loctestnum, loctesterr, v3, false, string(""));

        // Resize + Exists
        v3.Resize(9);
        Exists(loctestnum, loctesterr, v3, true, string(""));
        Exists(loctestnum, loctesterr, v3, true, string("2022/23"));

        // Resize down
        v3.Resize(3);
        Exists(loctestnum, loctesterr, v3, false, string("d'Italia"));

        // Clear e riclear
        v3.Clear();
        Empty(loctestnum, loctesterr, v3, true);
        v3.Clear(); // doppio clear
        Empty(loctestnum, loctesterr, v3, true);

        // Move su vettore vuoto
        lasd::SortableVector<string> v4(std::move(v3));
        Empty(loctestnum, loctesterr, v4, true);

        // Resize up e Map append
        v4.Resize(5);
        MapPreOrder(loctestnum, loctesterr, v4, true, [](string &str) { MapStringAppend(str, "<--Hello"); });
        SetAt(loctestnum, loctesterr, v4, true, 0, string("Hello"));
        FoldPostOrder(loctestnum, loctesterr, v4, true, &FoldStringConcatenate, string(""), string("<--Hello<--Hello<--Hello<--HelloHello"));

        Exists(loctestnum, loctesterr, v4, false, string("ciao"));
        Exists(loctestnum, loctesterr, v4, true, string("Hello"));

        // Clear finale
        v4.Clear();
        Empty(loctestnum, loctesterr, v4, true);

        // Accesso su vettore vuoto
        GetFront(loctestnum, loctesterr, v4, false, string("Hello"));
        GetBack(loctestnum, loctesterr, v4, false, string("Hello"));
        GetAt(loctestnum, loctesterr, v4, false, 0, string(""));


        lasd::List<string> lst1;
        InsertAtBack(loctestnum, loctesterr, lst1, true, string("Ti"));
        InsertAtBack(loctestnum, loctesterr, lst1, true, string("Voglio"));
        InsertAtBack(loctestnum, loctesterr, lst1, true, string("Bene"));
        InsertAtBack(loctestnum, loctesterr, lst1, true, string("Gioia"));
        TraversePreOrder(loctestnum, loctesterr, lst1, true, &TraversePrint<string>);
        v4 = lst1;
        TraversePreOrder(loctestnum, loctesterr, v4, true, &TraversePrint<string>);

        lst1.Clear();
        v4 = move(lst1);
        TraversePreOrder(loctestnum, loctesterr, v4, true, &TraversePrint<string>);
        EqualLinear(loctestnum, loctesterr, lst1, v4, true);
        Size(loctestnum, loctesterr, v4, true, 0);

        InsertAtBack(loctestnum, loctesterr, lst1, true, string("Ti"));
        v4 = move(lst1);
        TraversePreOrder(loctestnum, loctesterr, v4, true, &TraversePrint<string>);

        v4.Clear();
        v4.Resize(2);
        SetAt(loctestnum, loctesterr, v4, true, 0, string("Ti"));
        SetAt(loctestnum, loctesterr, v4, true, 1, string("Voglio"));

        MapPreOrder(loctestnum, loctesterr, v4, true, [](string &str) { MapStringNonEmptyAppend(str, "<--Hello"); });
        



    }
    catch (...)
    {
        loctestnum++;
        loctesterr++;
        cout << endl
             << "Unmanaged error! " << endl;
    }
    cout << "End of Vector<String> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}



  /* ************************************************************************** */



  void testVector(unsigned &testnum, unsigned &testerr)
{
    unsigned loctestnum = 0, loctesterr = 0;
    testVectorInt(loctestnum, loctesterr);
    testVectorFloat(loctestnum, loctesterr);
    testVectorString(loctestnum, loctesterr);
    testnum += loctestnum;
    testerr += loctesterr;
    cout << endl
         << "Exercise 1 - Vector (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}
/* ************************************************************************** */

void testListInt(unsigned &testnum, unsigned &testerr){
    unsigned loctestnum = 0, loctesterr = 0;
    cout << endl
         << "Begin of List<int> Test:" << endl;
    try
    {
        // Test estesi per List<int> (copertura completa)
        lasd::List<int> lst1;
        Empty(loctestnum, loctesterr, lst1, true);
        Size(loctestnum, loctesterr, lst1, true, 0);

        // Insert front/back e accesso
        InsertAtBack(loctestnum, loctesterr, lst1, true, 25);
        InsertAtFront(loctestnum, loctesterr, lst1, true, 90);
        InsertAtBack(loctestnum, loctesterr, lst1, true, 1);
        InsertAtFront(loctestnum, loctesterr, lst1, true, 2);
        InsertAtBack(loctestnum, loctesterr, lst1, true, 3);

        cout<<"Funzionamento operator []"<<endl;
        for(int i = 0; i < 5; i++){
            cout<< lst1[i] << "->";
        };
        cout<<" "<<endl;

        // Accessi validi e invalidi
        GetAt(loctestnum, loctesterr, lst1, false, 10, 0);
        SetAt(loctestnum, loctesterr, lst1, true, 1, 7);
        SetAt(loctestnum, loctesterr, lst1, false, 5, 7);
        InsertAtFront(loctestnum, loctesterr, lst1, true, 7999);
        GetAt(loctestnum, loctesterr, lst1, true, 0, 7999);
        GetFront(loctestnum, loctesterr, lst1, true, 7999);
        InsertAtBack(loctestnum, loctesterr, lst1, true, 900);
        GetBack(loctestnum, loctesterr, lst1, true, 900);

        // Map e Fold
        MapPreOrder(loctestnum, loctesterr, lst1, true, &MapDouble<int>);
        MapPostOrder(loctestnum, loctesterr, lst1, true, &MapDouble<int>);
        FoldPreOrder(loctestnum, loctesterr, lst1, true, &FoldAdd<int>, 0, 35748);
        FoldPostOrder(loctestnum, loctesterr, lst1, true, &FoldAdd<int>, 0, 35748);
        FoldPreOrder(loctestnum, loctesterr, lst1, true, &FoldParity, 0, 0);
        FoldPostOrder(loctestnum, loctesterr, lst1, true, &FoldParity, 0, 0);

        // Traverse
        TraversePreOrder(loctestnum, loctesterr, lst1, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, lst1, true, &TraversePrint<int>);

        // Exists
        Exists(loctestnum, loctesterr, lst1, false, 99911);
        Exists(loctestnum, loctesterr, lst1, true, 3600);

        // Copy e Move
        lasd::List<int> lst2(lst1);
        EqualList(loctestnum, loctesterr, lst1, lst2, true);
        NonEqualList(loctestnum, loctesterr, lst1, lst2, false);

        InsertAtFront(loctestnum, loctesterr, lst2, true, generateRandomInt());
        NonEqualList(loctestnum, loctesterr, lst1, lst2, true);

        lasd::List<int> lst3 = std::move(lst2);
        Empty(loctestnum, loctesterr, lst2, true);
        NonEqualList(loctestnum, loctesterr, lst1, lst2, true);
        TraversePreOrder(loctestnum, loctesterr, lst3, true, &TraversePrint<int>);

        // Insert/Remove molteplici
        for (int i = 0; i < 10; ++i) {
        InsertAtBack(loctestnum, loctesterr, lst3, true, generateRandomInt());
        }
        for (int i = 0; i < 5; ++i) {
        InsertAtFront(loctestnum, loctesterr, lst3, true, generateRandomInt());
        }
        TraversePostOrder(loctestnum, loctesterr, lst3, true, &TraversePrint<int>);



        // Clear
        lst3.Clear();
        Empty(loctestnum, loctesterr, lst3, true);
        Size(loctestnum, loctesterr, lst3, true, 0);

        // Altri test di confronto
        lasd::List<int> lst4;
        for (int i = 0; i < 5; ++i) {
        InsertAtBack(loctestnum, loctesterr, lst4, true, generateRandomInt());
        }
        lasd::List<int> lst5(lst4);
        EqualList(loctestnum, loctesterr, lst4, lst5, true);
        InsertAtBack(loctestnum, loctesterr, lst5, true, generateRandomInt());
        NonEqualList(loctestnum, loctesterr, lst4, lst5, true);

        // Map su lista vuota
        MapPreOrder(loctestnum, loctesterr, lst3, true, [](int &d) { d = 1; });
        MapPostOrder(loctestnum, loctesterr, lst3, true, [](int &d) { d = 1; });

        // Fold su lista vuota
        FoldPreOrder(loctestnum, loctesterr, lst3, true, &FoldParity, 0, 0);
        FoldPostOrder(loctestnum, loctesterr, lst3, true, &FoldParity, 0, 0);

        // Exists su vuota
        Exists(loctestnum, loctesterr, lst3, false, 0);

        // Riempimento massiccio + clear
        for (int i = 0; i < 40; ++i) {
        InsertAtBack(loctestnum, loctesterr, lst3, true, generateRandomInt());
        }
        Size(loctestnum, loctesterr, lst3, true, 40);
        lst3.Clear();
        Size(loctestnum, loctesterr, lst3, true, 0);
        Empty(loctestnum, loctesterr, lst3, true);

        // Confronti post clear
        EqualList(loctestnum, loctesterr, lst3, lst4, false);
        EqualLinear(loctestnum, loctesterr, lst3, lst4, false);

        // Map/Fold misti
        for (int i = 0; i < 10; ++i) {
        InsertAtBack(loctestnum, loctesterr, lst3, true, generateRandomInt());
        }
        MapPreOrder(loctestnum, loctesterr, lst3, true, [](int &d) { d *= -1; });

        TraversePreOrder(loctestnum, loctesterr, lst3, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, lst3, true, &TraversePrint<int>);

        lasd::Vector<int> v5(10);
        for (int i = 0; i < 10; ++i) {
            SetAt(loctestnum, loctesterr, v5, true, i, generateRandomInt());
        }

        lst3.Clear();
        Empty(loctestnum, loctesterr, lst3, true);
        lst3 = v5;
        EqualLinear(loctestnum, loctesterr, lst3, v5, true);
        NonEqualLinear(loctestnum, loctesterr, lst3, v5, false);
        Size(loctestnum, loctesterr, lst3, true, 10);
        TraversePreOrder(loctestnum, loctesterr, lst3, true, &TraversePrint<int>);

        lst3.Clear();
        lst3 = std::move(v5);
        EqualLinear(loctestnum, loctesterr, lst3, v5, true);
        Size(loctestnum, loctesterr, lst3, true, 10);
        TraversePreOrder(loctestnum, loctesterr, lst3, true, &TraversePrint<int>);

        lasd::SortableVector<int> sv1(10);
        for (int i = 0; i < 10; ++i) {
            SetAt(loctestnum, loctesterr, sv1, true, i, generateRandomInt());
        }
        sv1.Sort();
        lst3.Clear();
        lasd::List<int> lst6(std::move(sv1));
        EqualLinear(loctestnum, loctesterr, lst3, sv1, false);
        TraversePreOrder(loctestnum, loctesterr, lst6, true, &TraversePrint<int>);

        lst6.Clear();

        InsertAtFront(loctestnum, loctesterr, lst6, true, std::move(1));

        RemoveFromFront(loctestnum, loctesterr, lst6, true);

        InsertAtBack(loctestnum, loctesterr, lst6, true, 1);

        FrontNRemove(loctestnum, loctesterr, lst6, true,1);

        lst6.Clear();

        RemoveFromFront(loctestnum, loctesterr, lst6, false);
        RemoveFromBack(loctestnum, loctesterr, lst6, false);
        FrontNRemove(loctestnum, loctesterr, lst6, false, 1);
        BackNRemove(loctestnum, loctesterr, lst6, false, 1);

        InsertAtFrontMove(loctestnum,loctesterr,lst6,true,std::move(1));
        InsertAtFrontMove(loctestnum,loctesterr,lst6,true,std::move(2));
        InsertAtFrontMove(loctestnum,loctesterr,lst6,true,std::move(3));



        lasd::List<int> lst7;

        lst7 = lst6;

        RemoveFromBack(loctestnum, loctesterr, lst6, true);
        BackNRemove(loctestnum, loctesterr, lst6, true, 2);

        lst7.Clear();

        Size(loctestnum,loctesterr,lst7,true,0);
        RemoveFromFront(loctestnum,loctesterr,lst7,false);
        FrontNRemove(loctestnum,loctesterr,lst7,false,1);
        RemoveFromBack(loctestnum,loctesterr,lst7,false);

        
        InsertAtFrontMove(loctestnum,loctesterr,lst7,true,std::move(1));

        RemoveFromBack(loctestnum,loctesterr,lst7,true);

        Empty(loctestnum,loctesterr,lst7,true);

        InsertAtFrontMove(loctestnum,loctesterr,lst7,true,std::move(1));

        NonEqualList(loctestnum,loctesterr,lst7,lst6,true);

        lst7 = std::move(lst6);




        


        
    }
    catch (...)
    {
        loctestnum++;
        loctesterr++;
        cout << endl
             << "Unmanaged error! " << endl;
    }
    cout << "End of List<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

    /* ************************************************************************** */
    
    void testListDouble(unsigned &testnum, unsigned &testerr){
    unsigned loctestnum = 0, loctesterr = 0;
        cout << endl
            << "Begin of List<double> Test:" << endl;
        try{
            // Test estesi per List<int> (copertura completa)
        lasd::List<double> lst1;
        Empty(loctestnum, loctesterr, lst1, true);
        Size(loctestnum, loctesterr, lst1, true, 0);

        // Insert front/back e accesso
        InsertAtBack(loctestnum, loctesterr, lst1, true, 45.9);
        InsertAtFront(loctestnum, loctesterr, lst1, true, 90.10);
        SetFront(loctestnum, loctesterr, lst1, true, 25.5);
        InsertAtBack(loctestnum, loctesterr, lst1, true, 1.0);
        InsertAtFront(loctestnum, loctesterr, lst1, true, 2.3);
        InsertAtBack(loctestnum, loctesterr, lst1, true, 3.9);
        MapPreOrder(loctestnum, loctesterr, lst1, true, &MyMapPrint<double>);

        cout<<"Funzionamento operator []"<<endl;
        for(int i = 0; i < 5; i++){
            cout<< lst1[i] << "->";
        };
        cout<<" "<<endl;

        // Accessi validi e invalidi
        GetAt(loctestnum, loctesterr, lst1, false, 10, 0.10);
        SetAt(loctestnum, loctesterr, lst1, true, 1, 25.5);
        SetAt(loctestnum, loctesterr, lst1, false, 5, 7.0);
        InsertAtFront(loctestnum, loctesterr, lst1, true, 24.2);
        GetAt(loctestnum, loctesterr, lst1, true, 0, 24.2);
        GetFront(loctestnum, loctesterr, lst1, true, 24.2);
        InsertAtBack(loctestnum, loctesterr, lst1, true, 89.1);
        GetBack(loctestnum, loctesterr, lst1, true, 89.1);

        // Map e Fold
        MapPreOrder(loctestnum, loctesterr, lst1, true, &MapDouble<double>);
        MapPostOrder(loctestnum, loctesterr, lst1, true, &MapDouble<double>);
        FoldPreOrder(loctestnum, loctesterr, lst1, true, &FoldAdd<double>, 0, 765);
        FoldPostOrder(loctestnum, loctesterr, lst1, false, &FoldAdd<double>, 0, 10);
        FoldPreOrder(loctestnum, loctesterr, lst1, false, &FoldParity, 0, 0);
        FoldPostOrder(loctestnum, loctesterr, lst1, false, &FoldParity, 0, 0);


        // Traverse
        TraversePreOrder(loctestnum, loctesterr, lst1, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, lst1, true, &TraversePrint<double>);

        // Exists
        Exists(loctestnum, loctesterr, lst1, false, 91829.1);

        // Copy e Move
        lasd::List<double> lst2(lst1);
        EqualList(loctestnum, loctesterr, lst1, lst2, true);
        NonEqualList(loctestnum, loctesterr, lst1, lst2, false);

        InsertAtFront(loctestnum, loctesterr, lst2, true, generateRandomDouble());
        NonEqualList(loctestnum, loctesterr, lst1, lst2, true);

        lasd::List<double>lst3 = std::move(lst2);
        Empty(loctestnum, loctesterr, lst2, true);
        NonEqualList(loctestnum, loctesterr, lst1, lst2, true);
        TraversePreOrder(loctestnum, loctesterr, lst3, true, &TraversePrint<double>);

        // Insert/Remove molteplici
        for (int i = 0; i < 10; ++i) {
        InsertAtBack(loctestnum, loctesterr, lst3, true, generateRandomDouble());
        }
        for (int i = 0; i < 5; ++i) {
        InsertAtFront(loctestnum, loctesterr, lst3, true, generateRandomDouble());
        }
        TraversePostOrder(loctestnum, loctesterr, lst3, true, &TraversePrint<int>);


        // Clear
        lst3.Clear();
        Empty(loctestnum, loctesterr, lst3, true);
        Size(loctestnum, loctesterr, lst3, true, 0);

        // Altri test di confronto
        lasd::List<double> lst4;
        for (int i = 0; i < 5; ++i) {
        InsertAtBack(loctestnum, loctesterr, lst4, true, generateRandomDouble());
        }
        lasd::List<double> lst5(lst4);
        EqualList(loctestnum, loctesterr, lst4, lst5, true);
        InsertAtBack(loctestnum, loctesterr, lst5, true, generateRandomDouble());
        NonEqualList(loctestnum, loctesterr, lst4, lst5, true);

        // Map su lista vuota
        MapPreOrder(loctestnum, loctesterr, lst3, true, [](double &d) { d = 1.0; });
        MapPostOrder(loctestnum, loctesterr, lst3, true, [](double &d) { d = 1.0; });

        // Fold su lista vuota
        FoldPreOrder(loctestnum, loctesterr, lst3, true, &FoldParity, 0, 0);
        FoldPostOrder(loctestnum, loctesterr, lst3, true, &FoldParity, 0, 0);

        // Exists su vuota
        Exists(loctestnum, loctesterr, lst3, false, 0.0);

        // Riempimento massiccio + clear
        for (int i = 0; i < 40; ++i) {
        InsertAtBack(loctestnum, loctesterr, lst3, true, generateRandomDouble());
        }
        Size(loctestnum, loctesterr, lst3, true, 40);
        lst3.Clear();
        Size(loctestnum, loctesterr, lst3, true, 0);
        Empty(loctestnum, loctesterr, lst3, true);

        // Confronti post clear
        EqualList(loctestnum, loctesterr, lst3, lst4, false);
        EqualLinear(loctestnum, loctesterr, lst3, lst4, false);

        // Map/Fold misti
        for (int i = 0; i < 5; ++i) {
        InsertAtBack(loctestnum, loctesterr, lst3, true, generateRandomDouble());
        }
        MapPreOrder(loctestnum, loctesterr, lst3, true, [](double &d) { d *= -1.0; });

        TraversePreOrder(loctestnum, loctesterr, lst3, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, lst3, true, &TraversePrint<double>);

        }catch(...){
            loctestnum++;
            loctesterr++;
            cout << endl
                << "Unmanaged error! " << endl;

        }
        cout << "End of List<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
        testnum += loctestnum;
        testerr += loctesterr;
    }

 /* ************************************************************************** */
    void testListString(unsigned &testnum, unsigned &testerr){
    unsigned loctestnum = 0, loctesterr = 0;
        cout << endl
            << "Begin of List<string> Test:" << endl;
        try{
            // Test estesi per List<int> (copertura completa)
        lasd::List<string> lst1;
        Empty(loctestnum, loctesterr, lst1, true);
        Size(loctestnum, loctesterr, lst1, true, 0);

        // Insert front/back e accesso
        InsertAtBack(loctestnum, loctesterr, lst1, true, string("Il"));
        InsertAtFront(loctestnum, loctesterr, lst1, true, string("Napoli"));
        InsertAtBack(loctestnum, loctesterr, lst1, true, string("campione"));
        InsertAtFront(loctestnum, loctesterr, lst1, true, string("d'Italia"));
        InsertAtBack(loctestnum, loctesterr, lst1, true,string("2022/23"));

        cout<<"Funzionamento operator []"<<endl;
        for(int i = 0; i < 5; i++){
            cout<< lst1[i] << "->";
        };
        cout<<" "<<endl;

        // Accessi validi e invalidi
        GetAt(loctestnum, loctesterr,lst1,false , 10,string(""));
        SetAt(loctestnum, loctesterr,lst1,true , 1,string("2022/23"));
        SetAt(loctestnum, loctesterr,lst1,false , 5,string(""));
        InsertAtFront(loctestnum, loctesterr,lst1,true ,string("Milan"));
        GetAt(loctestnum, loctesterr,lst1,true , 0,string("Milan"));
        GetFront(loctestnum, loctesterr,lst1,true ,string("Milan"));
        InsertAtBack(loctestnum, loctesterr,lst1,true ,string("Inter"));
        GetBack(loctestnum, loctesterr,lst1,true ,string("Inter"));

        // Map e Fold
        MapPreOrder(loctestnum, loctesterr,lst1,true ,&MyMapPrint<string>);
        MapPostOrder(loctestnum, loctesterr,lst1,true ,&MyMapPrint<string>);
        FoldPreOrder(loctestnum, loctesterr,lst1,true ,&FoldStringConcatenate,string(""),string("Miland'Italia2022/23Ilcampione2022/23Inter"));
        FoldPostOrder(loctestnum, loctesterr,lst1,true ,&FoldStringConcatenate,string(""),string("Inter2022/23campioneIl2022/23d'ItaliaMilan"));
        MapPreOrder(loctestnum, loctesterr, lst1, true, [](std::string &str) { str.append("Ciao"); });




        }catch(...){
            loctestnum++;
            loctesterr++;
            cout << endl
                << "Unmanaged error! " << endl;

        }
        cout << "End of List<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
        testnum += loctestnum;
        testerr += loctesterr;
    }
/* ************************************************************************** */



void testList(unsigned &testnum, unsigned &testerr)
{
    unsigned loctestnum = 0, loctesterr = 0;
    testListInt(loctestnum, loctesterr);
    testListDouble(loctestnum, loctesterr);
    testListString(loctestnum, loctesterr);
    testnum += loctestnum;
    testerr += loctesterr;
    cout << endl
         << "Exercise 1 - List (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

 /* ************************************************************************** */

    void testSetVecInt(lasd::Vector<int> & vec, unsigned &testnum, unsigned &testerr){
        unsigned loctestnum = 0, loctesterr = 0;
        cout << endl
                << "Begin of SetVec<int> Test:" << endl;
            try
            {
                lasd::SetVec<int> stv1(vec);
                Empty(loctestnum, loctesterr, stv1, false);
                Size(loctestnum, loctesterr, stv1, true, 1);
                // Insert front/back e accesso
                InsertC(loctestnum, loctesterr, stv1, true, 25);
                InsertC(loctestnum, loctesterr, stv1, true, 90);
                InsertC(loctestnum, loctesterr, stv1, true, 1);
                InsertC(loctestnum, loctesterr, stv1, true, 2);
                InsertC(loctestnum, loctesterr, stv1, true, 3);
                TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<int>);
                Size(loctestnum, loctesterr, stv1, true,6);

                cout<<"Funzionamento operator []"<<endl;
                for(int i = 0; i < 5; i++){
                    cout<< stv1[i] << "->";
                };
                cout<<" "<<endl;

                lasd::Vector<int> v2(5);
                Empty(loctestnum, loctesterr, v2, false);
                for(int i = 0; i < 5; i++)
                {
                    SetAt(loctestnum, loctesterr, v2, true, i, generateUniqueRandomInt());
                }
                InsertSomeC(loctestnum, loctesterr, stv1, true, v2);
                TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<int>);


                v2.Clear();
                stv1.Clear();
                Empty(loctestnum, loctesterr, stv1, true);
                Size(loctestnum, loctesterr, stv1, true, 0);

                stv1.Resize(5);
                for(int i = 0; i < 5; i++)
                {
                    InsertM(loctestnum, loctesterr, stv1, true, generateUniqueRandomInt());
                }
                TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<int>);

                stv1.Clear();
                stv1.Resize(2);
                InsertC(loctestnum, loctesterr, stv1, true, 1);
                InsertC(loctestnum, loctesterr, stv1, false, 1);

                stv1.Clear();
                stv1.Resize(5);

                v2.Resize(5);
                for(int i = 0; i < 5; i++)
                {
                    SetAt(loctestnum, loctesterr, v2, true, i, i+1);
                }
                InsertAllC(loctestnum, loctesterr, stv1, true, v2);
                lasd::SetVec<int> stv2(v2);
                EqualSetVec(loctestnum, loctesterr, stv1, stv2, true);

                InsertM(loctestnum, loctesterr, stv2, true, 10);

                NonEqualSetVec(loctestnum, loctesterr, stv1, stv2, true);

                Remove(loctestnum, loctesterr, stv2, true, 1);
                RemoveSome(loctestnum, loctesterr, stv2, true, v2);
                TraversePreOrder(loctestnum, loctesterr, stv2, true, &TraversePrint<int>);

                InsertSomeC(loctestnum, loctesterr, stv2, true, v2);
                TraversePreOrder(loctestnum, loctesterr, stv2, true, &TraversePrint<int>);
                RemoveAll(loctestnum, loctesterr, stv2, true, v2);

                stv1.Clear();
                stv2.Clear();
                
                stv1.Resize(5);
                for(int i = 0; i < 5; i++)
                {
                    InsertC(loctestnum, loctesterr, stv1, true, i+1);
                }

                TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<int>);


                Min(loctestnum, loctesterr, stv1, true, 1);
                Max(loctestnum, loctesterr, stv1, true, 5);

                RemoveMin(loctestnum, loctesterr, stv1, true);
                RemoveMax(loctestnum, loctesterr, stv1, true);

                MinNRemove(loctestnum, loctesterr, stv1, true, 2);
                MaxNRemove(loctestnum, loctesterr, stv1, true, 4);
                TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<int>);
                Min(loctestnum, loctesterr, stv1, true, 3);
                Max(loctestnum, loctesterr, stv1, true, 3);

                stv1.Clear();

                stv1.Resize(5);
                for(int i = 0; i < 5; i++)
                {
                    InsertC(loctestnum, loctesterr, stv1, true, i*2);
                }
                TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<int>);

                Successor(loctestnum, loctesterr, stv1, true, 2,4);
                Predecessor(loctestnum, loctesterr, stv1, true, 2,0);

                SuccessorNRemove(loctestnum, loctesterr, stv1, true, 2,4);
                PredecessorNRemove(loctestnum, loctesterr, stv1, true, 2,0);
                TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<int>);

                RemoveSuccessor(loctestnum, loctesterr, stv1, true, 2);
                RemovePredecessor(loctestnum, loctesterr, stv1, false, 2);

                stv1.Clear();
                stv1.Resize(5);
                stv2.Resize(5);
                for(int i = 0; i < 5; i++)
                {
                    InsertC(loctestnum, loctesterr, stv1, true, i);
                }  
                
                stv1 = stv2;
                EqualSetVec(loctestnum, loctesterr, stv1, stv2, true);

                InsertC(loctestnum, loctesterr, stv2, true, 1);

                stv1 = std::move(stv2);

                Empty(loctestnum, loctesterr, stv2, true);
                EqualSetVec(loctestnum, loctesterr, stv1, stv2, false);

                Exists(loctestnum, loctesterr, stv1, true, 1);

                for(int i = 0; i < 4; i++)
                {
                    InsertC(loctestnum, loctesterr, stv1, true, i*3);
                }  

                for(ulong i = 0; i < stv1.Size() ; i++)
                {
                    cout << stv1[i] << " ";
                }
                cout<<"\n";

                stv1.Clear();

                stv1.Resize(5);
                for(int i = 0; i < 5; i++)
                {
                    InsertC(loctestnum, loctesterr, stv1, true, i);
                }
                TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<int>);
                FoldPreOrder(loctestnum, loctesterr, stv1, true, &FoldAdd<int>, 1, 11);
                TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<int>);
                FoldPostOrder(loctestnum, loctesterr, stv1, true, &FoldMultiply<int>, 0, 0);

                lasd::Vector<int> v3(5);
                for(int i = 0; i < 5; i++)
                {
                    SetAt(loctestnum, loctesterr, v3, true, i, generateUniqueRandomInt());
                }
                stv1 = v3;
                TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<int>);
                TraversePreOrder(loctestnum, loctesterr, v3, true, &TraversePrint<int>);
                NonEqualLinear(loctestnum, loctesterr, stv1, v3, true);

                stv1.Clear();
                v3.Clear();

                stv1.Resize(5);
                v3.Resize(5);
                for(int i = 0; i < 5; i++)
                {
                    SetAt(loctestnum, loctesterr, v3, true, i, i);
                }  
                stv1 = std::move(v3);
                EqualLinear(loctestnum, loctesterr, stv1, v3, true);
                TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<int>);
                NonEqualLinear(loctestnum, loctesterr, stv1, v3, false);


                stv1.Clear();
                v3.Clear();

                v3.Resize(5);
                stv1.Resize(10);

                for(int i = 0; i < 5; i++)
                {
                    SetAt(loctestnum, loctesterr, v3, true, i, i);
                }

                InsertAllC(loctestnum, loctesterr, stv1, true, v3);
                TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<int>);

                stv1.Clear();
                stv1.Resize(5);
                lasd::SetVec<int> stv90;
                stv90.Resize(10);

                InsertC(loctestnum, loctesterr, stv1, true, 1);
                InsertC(loctestnum, loctesterr, stv1, true, 2);
                InsertC(loctestnum, loctesterr, stv1, true, 3);
                InsertC(loctestnum, loctesterr, stv1, true, 4);
                InsertC(loctestnum, loctesterr, stv1, true, 5);

                InsertC(loctestnum, loctesterr, stv90, true, 1);
                InsertC(loctestnum, loctesterr, stv90, true, 2);
                InsertC(loctestnum, loctesterr, stv90, true, 3);
                InsertC(loctestnum, loctesterr, stv90, true, 4);
                InsertC(loctestnum, loctesterr, stv90, true, 5);

                EqualSetVec(loctestnum, loctesterr, stv1, stv90, true);

                lasd::List<int> lst1;
                InsertAtBack(loctestnum, loctesterr, lst1, true, 1);
                InsertAtBack(loctestnum, loctesterr, lst1, true, 2);
                InsertAtBack(loctestnum, loctesterr, lst1, true, 35);
                InsertAtBack(loctestnum, loctesterr, lst1, true, 31);
                InsertAtBack(loctestnum, loctesterr, lst1, true, 4);
                MapPreOrder(loctestnum, loctesterr, lst1, true, &MyMapPrint<int>);
                lasd::SetVec<int> stv3(lst1);
                EqualLinear(loctestnum, loctesterr, stv1, lst1, false);
                TraversePreOrder(loctestnum, loctesterr, stv3, true, &TraversePrint<int>);

                lst1.Clear();
                stv3.Clear();

                InsertAtFront(loctestnum, loctesterr, lst1, true, 1);
                InsertAtFront(loctestnum, loctesterr, lst1, true, 2);
                InsertAtFront(loctestnum, loctesterr, lst1, true, 35);

                stv3 = std::move(lst1);
                EqualLinear(loctestnum, loctesterr, stv1, lst1, false);
                TraversePreOrder(loctestnum, loctesterr, stv3, true, &TraversePrint<int>);
                stv3.Clear();
                lst1.Clear();

                lasd::SortableVector<int> sv1(5);
                    SetAt(loctestnum, loctesterr, sv1, true, 0,1);
                    SetAt(loctestnum, loctesterr, sv1, true, 1,222);
                    SetAt(loctestnum, loctesterr, sv1, true, 2,192);
                    SetAt(loctestnum, loctesterr, sv1, true, 3,1731);
                    SetAt(loctestnum, loctesterr, sv1, true, 4,4);

                
                TraversePreOrder(loctestnum, loctesterr, sv1, true, &TraversePrint<int>);
                stv3 = sv1;
                sv1.Sort();
                EqualLinear(loctestnum, loctesterr, stv3, sv1, true);

                lasd::SetVec<int> stv5;

                stv5.Resize(1);
                Empty(loctestnum, loctesterr, stv5, true);

                stv5.Resize(5);
                Size(loctestnum, loctesterr, stv5, false, 5);
                stv5.Resize(3);
                Size(loctestnum, loctesterr, stv5, false, 3);

                stv5.Resize(0);
                Min(loctestnum, loctesterr, stv5, false, 0);
                Max(loctestnum, loctesterr, stv5, false, 0);
                MinNRemove(loctestnum, loctesterr, stv5, false, 0);
                MaxNRemove(loctestnum, loctesterr, stv5, false, 0);
                RemoveMin(loctestnum, loctesterr, stv5, false);
                RemoveMax(loctestnum, loctesterr, stv5, false);
                SuccessorNRemove(loctestnum, loctesterr, stv5, false, 0, 0);
                PredecessorNRemove(loctestnum, loctesterr, stv5, false, 0, 0);
                Successor(loctestnum, loctesterr, stv5, false, 0, 0);
                Predecessor(loctestnum, loctesterr, stv5, false, 0, 0);
                RemoveSuccessor(loctestnum, loctesterr, stv5, false, 0);
                RemovePredecessor(loctestnum, loctesterr, stv5, false, 0);
                stv5.Clear();
                Empty(loctestnum, loctesterr, stv5, true);

                stv5.Resize(10);
                for(int i = 0; i < 10; i++)
                {
                    InsertC(loctestnum,loctesterr,stv5,i+10);
                };
                TraversePreOrder(loctestnum, loctesterr, stv5, true, &TraversePrint<int>);

                lasd::SetVec<int> stv10;

                InsertM(loctestnum,loctesterr,stv10,1);
                InsertM(loctestnum,loctesterr,stv10,2);
                InsertM(loctestnum,loctesterr,stv10,3);
                InsertM(loctestnum,loctesterr,stv10,4);

                lasd::SetVec<int> stv11(stv10);

                EqualSetVec(loctestnum,loctesterr,stv10,stv11,true);

                InsertM(loctestnum,loctesterr,stv11,19);

                lasd::SetVec<int> stv12(std::move(stv11));
                
                EqualSetVec(loctestnum,loctesterr,stv12,stv11,false);

                InsertC(loctestnum,loctesterr,stv12,222);

                NonEqualSetVec(loctestnum,loctesterr,stv12,stv11,true);


                stv10.Clear();

                InsertM(loctestnum,loctesterr,stv10,1);
                InsertM(loctestnum,loctesterr,stv10,2);
                InsertM(loctestnum,loctesterr,stv10,3);
                InsertM(loctestnum,loctesterr,stv10,4);

                RemovePredecessor(loctestnum,loctesterr,stv10,true,5);
               




                



                

            }catch(...)
            {
                loctestnum++;
                loctesterr++;
                cout << endl
                    << "Unmanaged error! " << endl;
            }
        cout << "End of SetVec<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
        testnum += loctestnum;
        testerr += loctesterr;
    }

    /* ************************************************************************** */



    void testSetVecDouble(lasd::Vector<double>& vec, unsigned &testnum, unsigned &testerr){
        unsigned loctestnum = 0, loctesterr = 0;
        cout << endl
                << "Begin of SetVec<Double> Test:" << endl;
            try
            {
                lasd::SetVec<double> stv1(vec);
                Empty(loctestnum, loctesterr, stv1, false);
                Size(loctestnum, loctesterr, stv1, true, 1);
                // Insert front/back e accesso
                InsertC(loctestnum, loctesterr, stv1, true, 34.2);
                InsertC(loctestnum, loctesterr, stv1, true, 75.1);
                InsertC(loctestnum, loctesterr, stv1, true, 1.02);
                InsertC(loctestnum, loctesterr, stv1, true, 80.2);
                InsertC(loctestnum, loctesterr, stv1, true, 50.2);
                TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<int>);
                Size(loctestnum, loctesterr, stv1, true,6);

                lasd::Vector<double> v2(5);
                Empty(loctestnum, loctesterr, v2, false);
                for(int i = 0; i < 5; i++)
                {
                    SetAt(loctestnum, loctesterr, v2, true, i, generateUniqueRandomDouble());
                }
                InsertSomeC(loctestnum, loctesterr, stv1, true, v2);
                TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<int>);

                v2.Clear();
                stv1.Clear();
                Empty(loctestnum, loctesterr, stv1, true);
                Size(loctestnum, loctesterr, stv1, true, 0);

                stv1.Resize(5);
                for(int i = 0; i < 5; i++)
                {
                    InsertM(loctestnum, loctesterr, stv1, true, generateRandomDouble());
                }
                TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<int>);

                stv1.Clear();
                stv1.Resize(2);
                InsertC(loctestnum, loctesterr, stv1, true, 1.1);
                InsertC(loctestnum, loctesterr, stv1, true, 890.2);

                stv1.Clear();
                stv1.Resize(5);

                v2.Resize(5);
                for(int i = 0; i < 5; i++)
                {
                    SetAt(loctestnum, loctesterr, v2, true, i, i+1.1);
                }
                InsertAllC(loctestnum, loctesterr, stv1, true, v2);
                lasd::SetVec<double> stv2(v2);
                EqualSetVec(loctestnum, loctesterr, stv1, stv2, true);

                InsertM(loctestnum, loctesterr, stv2, true, 10.0);

                NonEqualSetVec(loctestnum, loctesterr, stv1, stv2, true);

                Remove(loctestnum, loctesterr, stv2, true, 1.1);
                RemoveSome(loctestnum, loctesterr, stv2, true, v2);
                TraversePreOrder(loctestnum, loctesterr, stv2, true, &TraversePrint<int>);

                InsertSomeC(loctestnum, loctesterr, stv2, true, v2);
                TraversePreOrder(loctestnum, loctesterr, stv2, true, &TraversePrint<int>);
                RemoveAll(loctestnum, loctesterr, stv2, true, v2);

                stv1.Clear();
                stv2.Clear();
                
                stv1.Resize(5);
                for(int i = 0; i < 5; i++)
                {
                    InsertC(loctestnum, loctesterr, stv1, true, i+1.2);
                }

                TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<int>);


                Min(loctestnum, loctesterr, stv1, true, 1.2);
                Max(loctestnum, loctesterr, stv1, true, 5.2);

                RemoveMin(loctestnum, loctesterr, stv1, true);
                RemoveMax(loctestnum, loctesterr, stv1, true);

                MinNRemove(loctestnum, loctesterr, stv1, true, 2.2);
                MaxNRemove(loctestnum, loctesterr, stv1, true, 4.2);
                TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<int>);
                Min(loctestnum, loctesterr, stv1, true, 3.2);
                Max(loctestnum, loctesterr, stv1, true, 3.2);

                stv1.Clear();

                stv1.Resize(5);
                for(int i = 0; i < 5; i++)
                {
                    InsertC(loctestnum, loctesterr, stv1, true, i*2.0);
                }
                TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<int>);

                Successor(loctestnum, loctesterr, stv1, true, 2.0,4.0);
                Predecessor(loctestnum, loctesterr, stv1, true, 2.0,0.0);

                SuccessorNRemove(loctestnum, loctesterr, stv1, true, 2.0,4.0);
                PredecessorNRemove(loctestnum, loctesterr, stv1, true, 2.0,0.0);
                TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<int>);

                RemoveSuccessor(loctestnum, loctesterr, stv1, true, 2.0);
                RemovePredecessor(loctestnum, loctesterr, stv1, false, 2.0);

                stv1.Clear();
                stv1.Resize(5);
                stv2.Resize(5);
                for(int i = 0; i < 5; i++)
                {
                    InsertC(loctestnum, loctesterr, stv1, true, i + 1.0);
                }  
                
                stv1 = stv2;
                EqualSetVec(loctestnum, loctesterr, stv1, stv2, true);

                InsertC(loctestnum, loctesterr, stv2, true, 1.0);

                stv1 = std::move(stv2);

                Empty(loctestnum, loctesterr, stv2, true);
                EqualSetVec(loctestnum, loctesterr, stv1, stv2, false);

                Exists(loctestnum, loctesterr, stv1, true, 1.0);

                for(double i = 0.0; i < 4; i++)
                {
                    InsertC(loctestnum, loctesterr, stv1, true, i*3.1);
                }  

                for(ulong i = 0; i < stv1.Size() ; i++)
                {
                    cout << stv1[i] << " ";
                }
                cout<<"\n";


                stv1.Clear();

                stv1.Resize(5);
                for(double i = 0.0; i < 5; i++)
                {
                    InsertC(loctestnum, loctesterr, stv1, true, i);
                }
                TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<double>);
                FoldPreOrder(loctestnum, loctesterr, stv1, true, &FoldAdd<double>, 1.0, 11.0);
                TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<double>);
                FoldPostOrder(loctestnum, loctesterr, stv1, true, &FoldMultiply<double>, 0.0, 0.0);

                lasd::Vector<double> v3(5);
                for(int i = 0; i < 5; i++)
                {
                    SetAt(loctestnum, loctesterr, v3, true, i, generateUniqueRandomDouble());
                }
                
                stv1 = v3;
                TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<double>);
                TraversePreOrder(loctestnum, loctesterr, v3, true, &TraversePrint<double>);
                NonEqualLinear(loctestnum, loctesterr, stv1, v3, true);

                stv1.Clear();
                v3.Clear();

                stv1.Resize(5);
                v3.Resize(5);
                for(int i = 0; i < 5; i++)
                {
                    SetAt(loctestnum, loctesterr, v3, true, i, i+1.0);
                }  
                stv1 = std::move(v3);
                EqualLinear(loctestnum, loctesterr, stv1, v3, true);
                TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<double>);
                NonEqualLinear(loctestnum, loctesterr, stv1, v3, false);


                stv1.Clear();
                v3.Clear();

                v3.Resize(5);
                stv1.Resize(10);

                for(int i = 0; i < 5; i++)
                {
                    SetAt(loctestnum, loctesterr, v3, true, i, i + 2.5);
                }

                InsertAllC(loctestnum, loctesterr, stv1, true, v3);
                TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<double>);

                stv1.Clear();
                stv1.Resize(5);
                lasd::SetVec<double> stv90;
                stv90.Resize(10);

                InsertC(loctestnum, loctesterr, stv1, true, 1.0);
                InsertC(loctestnum, loctesterr, stv1, true, 2.2);
                InsertC(loctestnum, loctesterr, stv1, true, 3.3);
                InsertC(loctestnum, loctesterr, stv1, true, 4.4);
                InsertC(loctestnum, loctesterr, stv1, true, 5.5);

                InsertC(loctestnum, loctesterr, stv90, true, 1.0);
                InsertC(loctestnum, loctesterr, stv90, true, 2.2);
                InsertC(loctestnum, loctesterr, stv90, true, 3.3);
                InsertC(loctestnum, loctesterr, stv90, true, 4.4);
                InsertC(loctestnum, loctesterr, stv90, true, 5.5);

                EqualSetVec(loctestnum, loctesterr, stv1, stv90, true);

                lasd::List<double> lst1;
                InsertAtBack(loctestnum, loctesterr, lst1, true, 1.1);
                InsertAtBack(loctestnum, loctesterr, lst1, true, 2.2);
                InsertAtBack(loctestnum, loctesterr, lst1, true, 35.35);
                InsertAtBack(loctestnum, loctesterr, lst1, true, 31.31);
                InsertAtBack(loctestnum, loctesterr, lst1, true, 4.4);
                MapPreOrder(loctestnum, loctesterr, lst1, true, &MyMapPrint<double>);
                lasd::SetVec<double> stv3(lst1);
                EqualLinear(loctestnum, loctesterr, stv1, lst1, false);
                TraversePreOrder(loctestnum, loctesterr, stv3, true, &TraversePrint<double>);

                lst1.Clear();
                stv3.Clear();

                InsertAtFront(loctestnum, loctesterr, lst1, true, 1.1);
                InsertAtFront(loctestnum, loctesterr, lst1, true, 2.2);
                InsertAtFront(loctestnum, loctesterr, lst1, true, 35.35);

                stv3 = std::move(lst1);
                EqualLinear(loctestnum, loctesterr, stv1, lst1, false);
                TraversePreOrder(loctestnum, loctesterr, stv3, true, &TraversePrint<double>);
                stv3.Clear();
                lst1.Clear();

                lasd::SortableVector<double> sv1(5);
                    SetAt(loctestnum, loctesterr, sv1, true, 0,1.1);
                    SetAt(loctestnum, loctesterr, sv1, true, 1,222.22);
                    SetAt(loctestnum, loctesterr, sv1, true, 2,192.55);
                    SetAt(loctestnum, loctesterr, sv1, true, 3,1731.908);
                    SetAt(loctestnum, loctesterr, sv1, true, 4,4.23);

                
                TraversePreOrder(loctestnum, loctesterr, sv1, true, &TraversePrint<double>);
                stv3 = sv1;
                sv1.Sort();
                EqualLinear(loctestnum, loctesterr, stv3, sv1, true);



            }catch(...)
            {
                loctestnum++;
                loctesterr++;
                cout << endl
                    << "Unmanaged error! " << endl;
            }
        cout << "End of SetVec<Double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
        testnum += loctestnum;
        testerr += loctesterr;
    }
 /* ************************************************************************** */

 void testSetVecString(lasd::Vector<string>& vec, unsigned &testnum, unsigned &testerr){
        unsigned loctestnum = 0, loctesterr = 0;
        cout << endl
                << "Begin of SetVec<String> Test:" << endl;
            try
            {
                 // Prepara un Vector<string> di partenza
                    lasd::Vector<string> vec(5);
                    for(int i = 0; i < 5; i++) {
                        // imposto ogni elemento con string("init"+to_string(i))
                        SetAt(loctestnum, loctesterr, vec, true, i, string("init" + to_string(i)));
                    }

                    // Costruisco un SetVec<string> a partire da vec
                    lasd::SetVec<string> stv1(vec);
                    Empty(loctestnum, loctesterr, stv1, false);
                    Size(loctestnum, loctesterr, stv1, true, 5);

                    // Insert front/back e accesso
                    InsertC(loctestnum, loctesterr, stv1, true, string("apple"));
                    InsertC(loctestnum, loctesterr, stv1, true, string("banana"));
                    InsertC(loctestnum, loctesterr, stv1, true, string("cherry"));
                    InsertC(loctestnum, loctesterr, stv1, true, string("date"));
                    InsertC(loctestnum, loctesterr, stv1, true, string("elderberry"));
                    TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<string>);
                    Size(loctestnum, loctesterr, stv1, true, 10);

                    // Inserimento di alcuni elementi da un altro Vector<string>
                    lasd::Vector<string> v2(5);
                    Empty(loctestnum, loctesterr, v2, false);
                    for(int i = 0; i < 5; i++) {
                        SetAt(loctestnum, loctesterr, v2, true, i, string("randU" + to_string(i)));
                    }
                    InsertSomeC(loctestnum, loctesterr, stv1, true, v2);
                    TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<string>);

                    // Clear e nuovo test di Empty/Size
                    v2.Clear();
                    stv1.Clear();
                    Empty(loctestnum, loctesterr, stv1, true);
                    Size(loctestnum, loctesterr, stv1, true, 0);

                    // Resize + InsertM
                    stv1.Resize(5);
                    for(int i = 0; i < 5; i++) {
                        InsertM(loctestnum, loctesterr, stv1, true, string("mval" + to_string(i)));
                    }
                    TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<string>);

                    // Clear, Resize a 2 e due InsertC
                    stv1.Clear();
                    stv1.Resize(2);
                    InsertC(loctestnum, loctesterr, stv1, true, string("one"));
                    InsertC(loctestnum, loctesterr, stv1, true, string("two"));

                    // Clear e Resize a 5
                    stv1.Clear();
                    stv1.Resize(5);

                    // Preparo v2 con 5 stringhe e faccio InsertAllC + confronto
                    v2.Resize(5);
                    for(int i = 0; i < 5; i++) {
                        SetAt(loctestnum, loctesterr, v2, true, i, string("v2_" + to_string(i)));
                    }
                    InsertAllC(loctestnum, loctesterr, stv1, true, v2);
                    lasd::SetVec<string> stv2(v2);
                    EqualSetVec(loctestnum, loctesterr, stv1, stv2, true);

                    // Modifico stv2 e confronto nuovamente
                    InsertM(loctestnum, loctesterr, stv2, true, string("extra"));
                    NonEqualSetVec(loctestnum, loctesterr, stv1, stv2, true);

                    // Rimozioni di singolo e di un insieme, poi stampa
                    Remove(loctestnum, loctesterr, stv2, true, string("extra"));
                    RemoveSome(loctestnum, loctesterr, stv2, true, v2);
                    TraversePreOrder(loctestnum, loctesterr, stv2, true, &TraversePrint<string>);

                    // Reinserisco e poi rimuovo tutto
                    InsertSomeC(loctestnum, loctesterr, stv2, true, v2);
                    TraversePreOrder(loctestnum, loctesterr, stv2, true, &TraversePrint<string>);
                    RemoveAll(loctestnum, loctesterr, stv2, true, v2);

                    // Nuovi test di Min/Max/RemoveMin/RemoveMax
                    stv1.Clear();
                    stv2.Clear();
                    stv1.Resize(5);
                    for(int i = 0; i < 5; i++) {
                        InsertC(loctestnum, loctesterr, stv1, true, string("sval" + to_string(i)));
                    }
                    TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<string>);
                    Min(loctestnum, loctesterr, stv1, true, string("sval0"));
                    Max(loctestnum, loctesterr, stv1, true, string("sval4"));
                    RemoveMin(loctestnum, loctesterr, stv1, true);
                    RemoveMax(loctestnum, loctesterr, stv1, true);
                    MinNRemove(loctestnum, loctesterr, stv1, true, string("sval1"));
                    MaxNRemove(loctestnum, loctesterr, stv1, true, string("sval3"));
                    TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<string>);
                    Min(loctestnum, loctesterr, stv1, true, string("sval2"));
                    Max(loctestnum, loctesterr, stv1, true, string("sval2"));

                    // Test di Successor/Predecessor
                    stv1.Clear();
                    stv1.Resize(5);
                    for(int i = 0; i < 5; i++) {
                        InsertC(loctestnum, loctesterr, stv1, true, string("item" + to_string(i*2)));
                    }
                    TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<string>);
                    Successor(loctestnum, loctesterr, stv1, true, string("item2"), string("item4"));
                    Predecessor(loctestnum, loctesterr, stv1, true, string("item2"), string("item0"));
                    SuccessorNRemove(loctestnum, loctesterr, stv1, true, string("item2"), string("item4"));
                    PredecessorNRemove(loctestnum, loctesterr, stv1, true, string("item2"), string("item0"));
                    TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<string>);
                    RemoveSuccessor(loctestnum, loctesterr, stv1, true, string("item2"));
                    RemovePredecessor(loctestnum, loctesterr, stv1, false, string("item2"));

                    // Assegnazione e move
                    stv1.Clear();
                    stv1.Resize(5);
                    stv2.Resize(5);
                    for(int i = 0; i < 5; i++) {
                        InsertC(loctestnum, loctesterr, stv1, true, string("num" + to_string(i+1)));
                    }
                    stv1 = stv2;
                    EqualSetVec(loctestnum, loctesterr, stv1, stv2, true);
                    InsertC(loctestnum, loctesterr, stv2, true, string("num1"));
                    stv1 = std::move(stv2);
                    Empty(loctestnum, loctesterr, stv2, true);
                    EqualSetVec(loctestnum, loctesterr, stv1, stv2, false);

                    // Exists + stampa con operatore []
                    Exists(loctestnum, loctesterr, stv1, true, string("num1"));
                    for(size_t i = 0; i < stv1.Size(); i++) {
                        cout << stv1[i] << " ";
                    }
                    cout << "\n";

                    // Fold e confronto con Vector<string>
                    stv1.Clear();
                    stv1.Resize(5);
                    for(size_t i = 0; i < 5; i++) {
                        InsertC(loctestnum, loctesterr, stv1, true, string("x" + to_string(i)));
                    }
                    TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<string>);
                    FoldPreOrder(loctestnum, loctesterr, stv1, true, &FoldStringConcatenate, string(""), string("x0x1x2x3x4"));
                    TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<string>);
                    FoldPostOrder(loctestnum, loctesterr, stv1, true, &FoldStringConcatenate, string(""), string("x4x3x2x1x0"));

                    // Confronto con Vector<string> v3
                    lasd::Vector<string> v3(5);
                    for(int i = 0; i < 5; i++) {
                        SetAt(loctestnum, loctesterr, v3, true, i, string("U" + to_string(i)));
                    }
                    stv1 = v3;
                    TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<string>);
                    TraversePreOrder(loctestnum, loctesterr, v3, true, &TraversePrint<string>);
                    NonEqualLinear(loctestnum, loctesterr, stv1, v3, false);

                    stv1.Clear();
                    v3.Clear();
                    stv1.Resize(5);
                    v3.Resize(5);
                    for(int i = 0; i < 5; i++) {
                        SetAt(loctestnum, loctesterr, v3, true, i, string("L" + to_string(i+1)));
                    }
                    stv1 = std::move(v3);
                    EqualLinear(loctestnum, loctesterr, stv1, v3, false);
                    TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<string>);
                    NonEqualLinear(loctestnum, loctesterr, stv1, v3, true);

                    // Ultimo test di InsertAllC con capacità ampliata
                    stv1.Clear();
                    v3.Clear();
                    v3.Resize(5);
                    stv1.Resize(10);
                    for(int i = 0; i < 5; i++) {
                        SetAt(loctestnum, loctesterr, v3, true, i, string("O" + to_string(i+2)));
                    }
                    InsertAllC(loctestnum, loctesterr, stv1, true, v3);
                    TraversePreOrder(loctestnum, loctesterr, stv1, true, &TraversePrint<string>);

                    // Confronto finale fra due SetVec<string>
                    stv1.Clear();
                    stv1.Resize(5);
                    lasd::SetVec<string> stv90;
                    stv90.Resize(10);
                    InsertC(loctestnum, loctesterr, stv1, true, string("a"));
                    InsertC(loctestnum, loctesterr, stv1, true, string("bb"));
                    InsertC(loctestnum, loctesterr, stv1, true, string("ccc"));
                    InsertC(loctestnum, loctesterr, stv1, true, string("dddd"));
                    InsertC(loctestnum, loctesterr, stv1, true, string("eeeee"));
                    InsertC(loctestnum, loctesterr, stv90, true, string("a"));
                    InsertC(loctestnum, loctesterr, stv90, true, string("bb"));
                    InsertC(loctestnum, loctesterr, stv90, true, string("ccc"));
                    InsertC(loctestnum, loctesterr, stv90, true, string("dddd"));
                    InsertC(loctestnum, loctesterr, stv90, true, string("eeeee"));
                    EqualSetVec(loctestnum, loctesterr, stv1, stv90, true);

                    // Test di List<string> e conversione a SetVec<string>
                    lasd::List<string> lst1;
                    InsertAtBack(loctestnum, loctesterr, lst1, true, string("1.1"));
                    InsertAtBack(loctestnum, loctesterr, lst1, true, string("2.2"));
                    InsertAtBack(loctestnum, loctesterr, lst1, true, string("35.35"));
                    InsertAtBack(loctestnum, loctesterr, lst1, true, string("31.31"));
                    InsertAtBack(loctestnum, loctesterr, lst1, true, string("4.4"));
                    MapPreOrder(loctestnum, loctesterr, lst1, true, &MyMapPrint<string>);
                    lasd::SetVec<string> stv3(lst1);
                    EqualLinear(loctestnum, loctesterr, stv3, lst1, false);
                    TraversePreOrder(loctestnum, loctesterr, stv3, true, &TraversePrint<string>);
                    lst1.Clear(); stv3.Clear();

                    // Test di move da List<string> a SetVec<string>
                    InsertAtFront(loctestnum, loctesterr, lst1, true, string("A"));
                    InsertAtFront(loctestnum, loctesterr, lst1, true, string("B"));
                    InsertAtFront(loctestnum, loctesterr, lst1, true, string("C"));
                    stv3 = std::move(lst1);
                    EqualLinear(loctestnum, loctesterr, stv3, lst1, false);
                    TraversePreOrder(loctestnum, loctesterr, stv3, true, &TraversePrint<string>);
                    stv3.Clear(); lst1.Clear();

                    // Test di SortableVector<string>
                    lasd::SortableVector<string> sv1(5);
                    SetAt(loctestnum, loctesterr, sv1, true, 0, string("X"));
                    SetAt(loctestnum, loctesterr, sv1, true, 1, string("Z"));
                    SetAt(loctestnum, loctesterr, sv1, true, 2, string("Y"));
                    SetAt(loctestnum, loctesterr, sv1, true, 3, string("W"));
                    SetAt(loctestnum, loctesterr, sv1, true, 4, string("V"));
                    TraversePreOrder(loctestnum, loctesterr, sv1, true, &TraversePrint<string>);
                    stv3 = sv1;
                    sv1.Sort();
                    EqualLinear(loctestnum, loctesterr, stv3, sv1, true);


            }catch(...)
            {
                loctestnum++;
                loctesterr++;
                cout << endl
                    << "Unmanaged error! " << endl;
            }
        cout << "End of SetVec<String> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
        testnum += loctestnum;
        testerr += loctesterr;
    }

  /* ************************************************************************** */

    void testSetListInt(lasd::List<int> & lst, unsigned &testnum, unsigned &testerr){
        unsigned loctestnum = 0, loctesterr = 0;
        cout << endl
                << "Begin of SetList<int> Test:" << endl;
            try
            {
                InsertAtBack(loctestnum,loctesterr,lst,true,1);
                InsertAtBack(loctestnum,loctesterr,lst,true,1000);
                InsertAtBack(loctestnum,loctesterr,lst,true,23);
                InsertAtBack(loctestnum,loctesterr,lst,true,11);

                lasd::SetLst<int> stl1(lst);
                Empty(loctestnum, loctesterr, stl1, false);
                Size(loctestnum, loctesterr, stl1, false, 0);
                // Insert front/back e accesso
                InsertC(loctestnum, loctesterr, stl1, true, 25);
                InsertC(loctestnum, loctesterr, stl1, true, 90);
                InsertC(loctestnum, loctesterr, stl1, false, 1);
                InsertC(loctestnum, loctesterr, stl1, true, 2);
                InsertC(loctestnum, loctesterr, stl1, true, 3);
                TraversePreOrder(loctestnum, loctesterr, stl1, true, &TraversePrint<int>);
                Size(loctestnum, loctesterr, stl1, true,8);
            



                lasd::SetLst<int> stl2(stl1);

                Empty(loctestnum, loctesterr, stl2, false);
                Size(loctestnum, loctesterr, stl2, false, 0);

                Size(loctestnum,loctesterr,stl2,true,8);

                for(int i=0; i<8; i++){
                    InsertM(loctestnum,loctesterr,stl2, i+1);
                }

                TraversePreOrder(loctestnum, loctesterr, stl2, true, &TraversePrint<int>);
            


                stl1.Clear();

                stl1 = std::move(stl2);

                Empty(loctestnum,loctesterr,stl2,true);

                EqualSetLst(loctestnum,loctesterr,stl1,stl2,false);
                NonEqualList(loctestnum,loctesterr,stl1,stl2,true);

                stl2 = stl1;

                EqualSetLst(loctestnum,loctesterr,stl1,stl2,true);


                lasd::SetLst<int> stl3(std::move(stl1));

                EqualSetLst(loctestnum,loctesterr,stl2,stl3,true);


                stl3.Clear();


                Min(loctestnum,loctesterr,stl2,true,1);
                RemoveMin(loctestnum,loctesterr,stl2,true);
                MinNRemove(loctestnum,loctesterr,stl2,true,2);

                Max(loctestnum,loctesterr,stl2,true,1000);
                RemoveMax(loctestnum,loctesterr,stl2,true);
                MaxNRemove(loctestnum,loctesterr,stl2,true,90);

                Predecessor(loctestnum,loctesterr,stl2,true,4,3);
                Predecessor(loctestnum,loctesterr,stl2,false,1,0);
                RemovePredecessor(loctestnum,loctesterr,stl2,true,4);
                RemovePredecessor(loctestnum,loctesterr,stl2,false,1);
                PredecessorNRemove(loctestnum,loctesterr,stl2,true,5,4);
                PredecessorNRemove(loctestnum,loctesterr,stl2,false,1,0);

                Successor(loctestnum,loctesterr,stl2,true,5,6);
                Successor(loctestnum,loctesterr,stl2,false,3,4);
                RemoveSuccessor(loctestnum,loctesterr,stl2,true,5);
                RemoveSuccessor(loctestnum,loctesterr,stl2,false,10000);
                SuccessorNRemove(loctestnum,loctesterr,stl2,true,5,7);
                SuccessorNRemove(loctestnum,loctesterr,stl2,false,10000,999999);

                TraversePreOrder(loctestnum, loctesterr, stl2, true, &TraversePrint<int>);

                Exists(loctestnum,loctesterr,stl2,true,5);

                lasd::Vector<int> vec(3);

                SetAt(loctestnum,loctesterr,vec,true,0,10);
                SetAt(loctestnum,loctesterr,vec,true,1,14);
                SetAt(loctestnum,loctesterr,vec,true,2,19);

                lasd::SetLst<int> stl4(vec);
                TraversePreOrder(loctestnum, loctesterr, stl4, true, &TraversePrint<int>);
                TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
                EqualLinear(loctestnum,loctesterr,stl4,vec,true);

                lasd::SetLst<int> stl5;

                stl5 = stl4;

                EqualSetLst(loctestnum,loctesterr,stl4,stl5,true);

                cout<<"--------prova operatore ==--------"<<endl;
                for(int i = 0; i< 3; i++){
                    if(stl5 == stl4){
                        cout<<"ciao sono uguali"<<endl;
                    }
                }

                InsertM(loctestnum,loctesterr,stl5,2);
                cout<<"--------prova operatore !=--------"<<endl;
                int operatore = 0;
                
                for(int i = 0; i< 3; i++){
                    if(stl5 != stl4){
                        operatore = 1;
                        break;
                    }
                }

                if(operatore == 1){
                    cout<<"ciao siamo diversi"<<endl;
                }



                lasd::SetLst<int> stl7;

                Empty(loctestnum,loctesterr,stl7,true);
                Size(loctestnum,loctesterr,stl7,true,0);

                Min(loctestnum,loctesterr,stl7,false,1);
                RemoveMin(loctestnum,loctesterr,stl7,false);
                MinNRemove(loctestnum,loctesterr,stl7,false,2);

                Max(loctestnum,loctesterr,stl7,false,1000);
                RemoveMax(loctestnum,loctesterr,stl7,false);
                MaxNRemove(loctestnum,loctesterr,stl7,false,90);

                Predecessor(loctestnum,loctesterr,stl7,false,4,3);
                RemovePredecessor(loctestnum,loctesterr,stl7,false,4);
                PredecessorNRemove(loctestnum,loctesterr,stl7,false,5,4);

                Successor(loctestnum,loctesterr,stl7,false,5,6);
                RemoveSuccessor(loctestnum,loctesterr,stl7,false,5);
                SuccessorNRemove(loctestnum,loctesterr,stl7,false,5,7);



                InsertM(loctestnum,loctesterr,stl7, 10);
                Min(loctestnum,loctesterr,stl7,true,10);
                Max(loctestnum,loctesterr,stl7,true,10);
                Predecessor(loctestnum,loctesterr,stl7,false,10,9);
                Successor(loctestnum,loctesterr,stl7,false,10,11);
                RemovePredecessor(loctestnum,loctesterr,stl7,false,10);
                RemoveSuccessor(loctestnum,loctesterr,stl7,false,10);
                PredecessorNRemove(loctestnum,loctesterr,stl7,false,10,9);
                SuccessorNRemove(loctestnum,loctesterr,stl7,false,10,11);


                stl7.Clear();
                lasd::List<int> lst1;
                InsertAtBack(loctestnum,loctesterr,lst1,true,1);
                InsertAtBack(loctestnum,loctesterr,lst1,true,100);
                InsertAtBack(loctestnum,loctesterr,lst1,true,87);
                InsertAtBack(loctestnum,loctesterr,lst1,true,32);

                lasd::SetLst<int> stl8(lst1);
                
                TraversePreOrder(loctestnum, loctesterr, stl8, true, &TraversePrint<int>);
                TraversePreOrder(loctestnum, loctesterr, lst1, true, &TraversePrint<int>);
                NonEqualLinear(loctestnum,loctesterr,stl8,lst1,true);


                stl8.Clear(); 
                
                lasd::SetLst<int> stl9;
                lasd::Vector<int> vec1(5);
                for(int i = 0; i < 5; i++)
                {
                    SetAt(loctestnum, loctesterr, vec1, true, i, i);
                }
                InsertAllC(loctestnum, loctesterr, stl9, true, vec1);
                TraversePreOrder(loctestnum, loctesterr, stl9, true, &TraversePrint<int>);

                InsertC(loctestnum, loctesterr, stl9, false, 1);
                InsertC(loctestnum, loctesterr, stl9, false, 2);
                InsertC(loctestnum, loctesterr, stl9, false, 3);
                RemoveAll(loctestnum, loctesterr, stl9, true, vec1);
   
                for(int i = 0; i < 5; i++)
                {
                    
                    SetAt(loctestnum, loctesterr, vec1, true, i, generateUniqueRandomInt());
                }
        

                TraversePreOrder(loctestnum, loctesterr, vec1, true, &TraversePrint<int>);

                InsertAllC(loctestnum, loctesterr, stl9, true, vec1);

                TraversePreOrder(loctestnum, loctesterr, stl9, true, &TraversePrint<int>);

            }catch(...)
            {
                loctestnum++;
                loctesterr++;
                cout << endl
                    << "Unmanaged error! " << endl;
            }
        cout << "End of SetList<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
        testnum += loctestnum;
        testerr += loctesterr;
    }

  /* ************************************************************************** */

void testSetListDouble(lasd::List<double> & lst, unsigned &testnum, unsigned &testerr){
        unsigned loctestnum = 0, loctesterr = 0;
        cout << endl
                << "Begin of SetList<double> Test:" << endl;
            try
            {
                InsertAtBack(loctestnum,loctesterr,lst,true,1.1);
                InsertAtBack(loctestnum,loctesterr,lst,true,999.9);
                InsertAtBack(loctestnum,loctesterr,lst,true,23.7);
                InsertAtBack(loctestnum,loctesterr,lst,true,11.5);

                lasd::SetLst<double> stl1(lst);
                Empty(loctestnum, loctesterr, stl1, false);
                Size(loctestnum, loctesterr, stl1, false, 0);
                // Insert front/back e accesso
                InsertC(loctestnum, loctesterr, stl1, true, 25.3);
                InsertC(loctestnum, loctesterr, stl1, true, 90.8);
                InsertC(loctestnum, loctesterr, stl1, true, 1.2);
                InsertC(loctestnum, loctesterr, stl1, true, 2.4);
                InsertC(loctestnum, loctesterr, stl1, true, 3.9);
                TraversePreOrder(loctestnum, loctesterr, stl1, true, &TraversePrint<double>);
                Size(loctestnum, loctesterr, stl1, true, 9);

                

                lasd::SetLst<double> stl2(stl1);

                Empty(loctestnum, loctesterr, stl2, false);
                Size(loctestnum, loctesterr, stl2, false, 0);

                Size(loctestnum,loctesterr,stl2,true,9);

                for(int i=0; i<8; i++){
                    InsertM(loctestnum,loctesterr,stl2, i + 1.5);
                }

                TraversePreOrder(loctestnum, loctesterr, stl2, true, &TraversePrint<double>);
               

                stl1.Clear();

                stl1 = std::move(stl2);

                Empty(loctestnum,loctesterr,stl2,true);

                EqualSetLst(loctestnum,loctesterr,stl1,stl2,false);
                NonEqualList(loctestnum,loctesterr,stl1,stl2,true);

                stl2 = stl1;

                EqualSetLst(loctestnum,loctesterr,stl1,stl2,true);

                lasd::SetLst<double> stl3(std::move(stl1));

                EqualSetLst(loctestnum,loctesterr,stl2,stl3,true);

                stl3.Clear();

                Min(loctestnum,loctesterr,stl2,true,1.1);
                RemoveMin(loctestnum,loctesterr,stl2,true);
                MinNRemove(loctestnum,loctesterr,stl2,true,1.2);

                Max(loctestnum,loctesterr,stl2,true,999.9);
                RemoveMax(loctestnum,loctesterr,stl2,true);
                MaxNRemove(loctestnum,loctesterr,stl2,true,90.8);

                Predecessor(loctestnum,loctesterr,stl2,true,4.0,3.9);
                Predecessor(loctestnum,loctesterr,stl2,false,1.1,0.0);
                RemovePredecessor(loctestnum,loctesterr,stl2,true,4.0);
                RemovePredecessor(loctestnum,loctesterr,stl2,false,1.1);
                PredecessorNRemove(loctestnum,loctesterr,stl2,true,5.0,4.5);
                PredecessorNRemove(loctestnum,loctesterr,stl2,false,1.1,0.0);

                Successor(loctestnum,loctesterr,stl2,true,5.0,5.5);
                Successor(loctestnum,loctesterr,stl2,false,3.3,4.4);
                RemoveSuccessor(loctestnum,loctesterr,stl2,true,5.0);
                RemoveSuccessor(loctestnum,loctesterr,stl2,false,10000.0);
                SuccessorNRemove(loctestnum,loctesterr,stl2,true,5.0,6.5);
                SuccessorNRemove(loctestnum,loctesterr,stl2,false,10000.0,999999.9);

                TraversePreOrder(loctestnum, loctesterr, stl2, true, &TraversePrint<double>);

                Exists(loctestnum,loctesterr,stl2,false,5.0);

                lasd::Vector<double> vec(3);

                SetAt(loctestnum,loctesterr,vec,true,0,10.1);
                SetAt(loctestnum,loctesterr,vec,true,1,14.6);
                SetAt(loctestnum,loctesterr,vec,true,2,19.9);

                lasd::SetLst<double> stl4(vec);
                TraversePreOrder(loctestnum, loctesterr, stl4, true, &TraversePrint<double>);
                TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<double>);
                EqualLinear(loctestnum,loctesterr,stl4,vec,true);

                lasd::SetLst<double> stl5;

                stl5 = stl4;

                EqualSetLst(loctestnum,loctesterr,stl4,stl5,true);

                cout<<"--------prova operatore ==--------"<<endl;
                for(int i = 0; i< 3; i++){
                    if(stl5 == stl4){
                        cout<<"ciao sono uguali"<<endl;
                    }
                }

                InsertM(loctestnum,loctesterr,stl5,2.7);
                cout<<"--------prova operatore !=--------"<<endl;
                int operatore = 0;

                for(int i = 0; i< 3; i++){
                    if(stl5 != stl4){
                        operatore = 1;
                        break;
                    }
                }

                if(operatore == 1){
                    cout<<"ciao siamo diversi"<<endl;
                }

                lasd::SetLst<double> stl7;

                Empty(loctestnum,loctesterr,stl7,true);
                Size(loctestnum,loctesterr,stl7,true,0);

                Min(loctestnum,loctesterr,stl7,false,1.0);
                RemoveMin(loctestnum,loctesterr,stl7,false);
                MinNRemove(loctestnum,loctesterr,stl7,false,2.0);

                Max(loctestnum,loctesterr,stl7,false,1000.0);
                RemoveMax(loctestnum,loctesterr,stl7,false);
                MaxNRemove(loctestnum,loctesterr,stl7,false,90.0);

                Predecessor(loctestnum,loctesterr,stl7,false,4.0,3.0);
                RemovePredecessor(loctestnum,loctesterr,stl7,false,4.0);
                PredecessorNRemove(loctestnum,loctesterr,stl7,false,5.0,4.0);

                Successor(loctestnum,loctesterr,stl7,false,5.0,7.0);
                RemoveSuccessor(loctestnum,loctesterr,stl7,false,5.0);
                SuccessorNRemove(loctestnum,loctesterr,stl7,false,5.0,7.0);

                InsertM(loctestnum,loctesterr,stl7, 10.5);
                Min(loctestnum,loctesterr,stl7,true,10.5);
                Max(loctestnum,loctesterr,stl7,true,10.5);
                Predecessor(loctestnum,loctesterr,stl7,false,10.5,9.8);
                Successor(loctestnum,loctesterr,stl7,false,10.5,11.1);
                RemovePredecessor(loctestnum,loctesterr,stl7,false,10.5);
                RemoveSuccessor(loctestnum,loctesterr,stl7,false,10.5);
                PredecessorNRemove(loctestnum,loctesterr,stl7,false,10.5,9.8);
                SuccessorNRemove(loctestnum,loctesterr,stl7,false,10.5,11.1);

                stl7.Clear();
                lasd::List<double> lst1;
                InsertAtBack(loctestnum,loctesterr,lst1,true,1.7);
                InsertAtBack(loctestnum,loctesterr,lst1,true,100.4);
                InsertAtBack(loctestnum,loctesterr,lst1,true,87.3);
                InsertAtBack(loctestnum,loctesterr,lst1,true,32.9);

                lasd::SetLst<double> stl8(lst1);

                TraversePreOrder(loctestnum, loctesterr, stl8, true, &TraversePrint<double>);
                TraversePreOrder(loctestnum, loctesterr, lst1, true, &TraversePrint<double>);
                NonEqualLinear(loctestnum,loctesterr,stl8,lst1,true);



            }catch(...)
            {
                loctestnum++;
                loctesterr++;
                cout << endl
                    << "Unmanaged error! " << endl;
            }
        cout << "End of SetList<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
        testnum += loctestnum;
        testerr += loctesterr;
    }

  /*  ************************************************************************** */

  void testSetListString(lasd::List<string> & lst, unsigned &testnum, unsigned &testerr){
        unsigned loctestnum = 0, loctesterr = 0;
        cout << endl
                << "Begin of SetList<double> Test:" << endl;
            try
            {
                InsertAtBack(loctestnum, loctesterr, lst, true, string("mela"));
                InsertAtBack(loctestnum, loctesterr, lst, true, string("banana"));
                InsertAtBack(loctestnum, loctesterr, lst, true, string("kiwi"));
                InsertAtBack(loctestnum, loctesterr, lst, true, string("ananas"));

                lasd::SetLst<string> stl1(lst);
                Empty(loctestnum, loctesterr, stl1, false);
                Size(loctestnum, loctesterr, stl1, false, 0);

                InsertC(loctestnum, loctesterr, stl1, true, string("fragola"));
                InsertC(loctestnum, loctesterr, stl1, true, string("uva"));
                InsertC(loctestnum, loctesterr, stl1, false, string("mela"));
                InsertC(loctestnum, loctesterr, stl1, true, string("ciliegia"));
                InsertC(loctestnum, loctesterr, stl1, true, string("pesca"));

                TraversePreOrder(loctestnum, loctesterr, stl1, true, &TraversePrint<string>);
                Size(loctestnum, loctesterr, stl1, true, 8);

               

                lasd::SetLst<string> stl2(stl1);
                Empty(loctestnum, loctesterr, stl2, false);
                Size(loctestnum, loctesterr, stl2, false, 0);
                Size(loctestnum, loctesterr, stl2, true, 8);

                for(int i = 0; i < 8; i++){
                    InsertM(loctestnum, loctesterr, stl2, string("valore") + to_string(i));
                }

                TraversePreOrder(loctestnum, loctesterr, stl2, true, &TraversePrint<string>);
              

                stl1.Clear();
                stl1 = std::move(stl2);

                Empty(loctestnum, loctesterr, stl2, true);
                EqualSetLst(loctestnum, loctesterr, stl1, stl2, false);
                NonEqualList(loctestnum, loctesterr, stl1, stl2, true);

                stl2 = stl1;
                EqualSetLst(loctestnum, loctesterr, stl1, stl2, true);

                lasd::SetLst<string> stl3(std::move(stl1));
                EqualSetLst(loctestnum, loctesterr, stl2, stl3, true);

                stl3.Clear();

                Min(loctestnum, loctesterr, stl2, true, string("ananas"));
                RemoveMin(loctestnum, loctesterr, stl2, true);
                MinNRemove(loctestnum, loctesterr, stl2, true, string("banana"));

                Max(loctestnum, loctesterr, stl2, true, string("valore7"));
                RemoveMax(loctestnum, loctesterr, stl2, true);
                MaxNRemove(loctestnum, loctesterr, stl2, true, string("valore6"));

                Predecessor(loctestnum, loctesterr, stl2, false, string("ciliegia"), string("banana"));
                Predecessor(loctestnum, loctesterr, stl2, false, string("ananas"), string(""));
                RemovePredecessor(loctestnum, loctesterr, stl2, false, string("ciliegia"));
                RemovePredecessor(loctestnum, loctesterr, stl2, false, string("ananas"));
                PredecessorNRemove(loctestnum, loctesterr, stl2, true, string("pesca"), string("mela"));
                PredecessorNRemove(loctestnum, loctesterr, stl2, false, string("ananas"), string(""));

                Successor(loctestnum, loctesterr, stl2, true, string("banana"), string("ciliegia"));
                Successor(loctestnum, loctesterr, stl2, false, string("valore7"), string("valore8"));
                RemoveSuccessor(loctestnum, loctesterr, stl2, true, string("banana"));
                RemoveSuccessor(loctestnum, loctesterr, stl2, false, string("zucchina"));
                SuccessorNRemove(loctestnum, loctesterr, stl2, true, string("banana"), string("fragola"));
                SuccessorNRemove(loctestnum, loctesterr, stl2, false, string("zucchina"), string(""));

                TraversePreOrder(loctestnum, loctesterr, stl2, true, &TraversePrint<string>);
                Exists(loctestnum, loctesterr, stl2, true, string("pesca"));

                lasd::Vector<string> vec(3);
                SetAt(loctestnum, loctesterr, vec, true, 0, string("limone"));
                SetAt(loctestnum, loctesterr, vec, true, 1, string("pera"));
                SetAt(loctestnum, loctesterr, vec, true, 2, string("cocco"));

                lasd::SetLst<string> stl4(vec);
                TraversePreOrder(loctestnum, loctesterr, stl4, true, &TraversePrint<string>);
                TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<string>);
                NonEqualLinear(loctestnum, loctesterr, stl4, vec, true);

                lasd::SetLst<string> stl5;
                stl5 = stl4;
                EqualSetLst(loctestnum, loctesterr, stl4, stl5, true);

                cout << "--------prova operatore ==--------" << endl;
                for(int i = 0; i < 3; i++){
                    if(stl5 == stl4){
                        cout << "ciao sono uguali" << endl;
                    }
                }

                InsertM(loctestnum, loctesterr, stl5, string("pera"));
                cout << "--------prova operatore !=--------" << endl;
                int operatore = 0;
                for(int i = 0; i < 3; i++){
                    if(stl5 != stl4){
                        operatore = 1;
                        break;
                    }
                }
                if(operatore == 1){
                    cout << "ciao siamo diversi" << endl;
                }

                lasd::SetLst<string> stl7;
                Empty(loctestnum, loctesterr, stl7, true);
                Size(loctestnum, loctesterr, stl7, true, 0);

                Min(loctestnum, loctesterr, stl7, false, string("a"));
                RemoveMin(loctestnum, loctesterr, stl7, false);
                MinNRemove(loctestnum, loctesterr, stl7, false, string("b"));

                Max(loctestnum, loctesterr, stl7, false, string("z"));
                RemoveMax(loctestnum, loctesterr, stl7, false);
                MaxNRemove(loctestnum, loctesterr, stl7, false, string("y"));

                Predecessor(loctestnum, loctesterr, stl7, false, string("mango"), string("lime"));
                RemovePredecessor(loctestnum, loctesterr, stl7, false, string("mango"));
                PredecessorNRemove(loctestnum, loctesterr, stl7, false, string("mango"), string("lime"));

                Successor(loctestnum, loctesterr, stl7, false, string("mango"), string("melone"));
                RemoveSuccessor(loctestnum, loctesterr, stl7, false, string("mango"));
                SuccessorNRemove(loctestnum, loctesterr, stl7, false, string("mango"), string("melone"));

                InsertM(loctestnum, loctesterr, stl7, string("melograno"));
                Min(loctestnum, loctesterr, stl7, true, string("melograno"));
                Max(loctestnum, loctesterr, stl7, true, string("melograno"));
                Predecessor(loctestnum, loctesterr, stl7, false, string("melograno"), string("melone"));
                Successor(loctestnum, loctesterr, stl7, false, string("melograno"), string("menta"));
                RemovePredecessor(loctestnum, loctesterr, stl7, false, string("melograno"));
                RemoveSuccessor(loctestnum, loctesterr, stl7, false, string("melograno"));
                PredecessorNRemove(loctestnum, loctesterr, stl7, false, string("melograno"), string("melone"));
                SuccessorNRemove(loctestnum, loctesterr, stl7, false, string("melograno"), string("menta"));

                stl7.Clear();
                lasd::List<string> lst1;
                InsertAtBack(loctestnum, loctesterr, lst1, true, string("mango"));
                InsertAtBack(loctestnum, loctesterr, lst1, true, string("cocomero"));
                InsertAtBack(loctestnum, loctesterr, lst1, true, string("fico"));
                InsertAtBack(loctestnum, loctesterr, lst1, true, string("papaya"));

                lasd::SetLst<string> stl8(lst1);

                TraversePreOrder(loctestnum, loctesterr, stl8, true, &TraversePrint<string>);
                TraversePreOrder(loctestnum, loctesterr, lst1, true, &TraversePrint<string>);
                NonEqualLinear(loctestnum, loctesterr, stl8, lst1, true);

                

            }catch(...)
            {
                loctestnum++;
                loctesterr++;
                cout << endl
                    << "Unmanaged error! " << endl;
            }
        cout << "End of SetList<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
        testnum += loctestnum;
        testerr += loctesterr;
    }
   

  /* ************************************************************************** */
    void testSet(unsigned &testnum, unsigned &testerr){
        unsigned loctestnum = 0, loctesterr = 0;
        lasd::Vector<int> v1(5);
        testSetVecInt(v1,loctestnum, loctesterr);
        lasd::Vector<double> v2(5);
        testSetVecDouble(v2,loctestnum,loctesterr);
        lasd::Vector<string> v3(5);
        testSetVecString(v3,loctestnum,loctesterr);


        lasd::List<int> lst1;
        testSetListInt(lst1,loctestnum,loctesterr);
        lasd::List<double> lst2;
        testSetListDouble(lst2,loctestnum,loctesterr);
        lasd::List<string> lst3;
        testSetListString(lst3,loctestnum,loctesterr);

        testnum += loctestnum;
        testerr += loctesterr;
        cout << endl
             << "Exercise 1 - Set (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;

    }
    /* ************************************************************************** */
void mytest()
{
    cout << endl << "~*~#~*~ Welcome to the LASD MyTest Suite ~*~#~*~ " << endl;

    uint loctestnum, loctesterr;
    uint stestnum = 0, stesterr = 0;

    loctestnum = 0; loctesterr = 0;
    testVector(loctestnum, loctesterr);
    stestnum += loctestnum; stesterr += loctesterr;

    loctestnum = 0; loctesterr = 0;
    testList(loctestnum, loctesterr);
    stestnum += loctestnum; stesterr += loctesterr;

    loctestnum = 0; loctesterr = 0;
    testSet(loctestnum, loctesterr);
    stestnum += loctestnum; stesterr += loctesterr;


    cout << endl << "Exercise 1 (MyTest) (Errors/Tests: " << stesterr << "/" << stestnum << ")";

    cout << endl << "Goodbye!" << endl;
}
}
