
#ifndef MYTEST_HPP
#define MYTEST_HPP
#include<iostream>
#include<string.h>


/* ************************************************************************** */

namespace mytestlasd{
void mytest();

template <typename Data>
void MyMapPrint(Data& dat) {
  std::cout << dat << " ";
}

}


/* ************************************************************************** */

#endif
