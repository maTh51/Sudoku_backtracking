#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>

struct No{
    int _line;
    int _column;
    int _ql;
    int _qc;
    int _refer = 0;
    int _fixo;
    No *_prox;
};

class Stack{
    private:
      No *_ini;
      int _tamanho;

    public:
      Stack();
      //~Stack();
      void add_stack(int, int, int, int, int, int);
      No remove_stack();
      No get_first();

};

#endif
