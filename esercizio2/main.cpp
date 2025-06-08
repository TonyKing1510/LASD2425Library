
#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */
using namespace mytestlasd;

int main() {
  std::cout << "**-----Lasd Libraries 2025 Menu-----**" << std::endl;
  std::cout << "**-----     (1) lasd test      -----**" << std::endl;
  std::cout << "**-----      (2) my test       -----**" << std::endl;
  std::cout << "Insersci il numero da scegliere "<<std::endl;
    int x;
    
    std::cin>>x;
    switch(x){
        case 1:
            lasdtest();
            break;
        case 2:
            mytest();
            break;
    }
}
