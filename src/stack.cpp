#include "stack.hpp"

Stack::Stack(){
    this->_ini = nullptr;
    _tamanho = 0;
}

No Stack::get_first(){
    No aux;
    aux._refer = -1;
    if(this->_ini == nullptr)
        return(aux);
    else{
        aux._refer = this->_ini->_refer;
        return(aux);
    }
}

/* Destrutor sendo chamado duas vezes
Stack::~Stack(){
    No *prox = this->_ini;
    No *aux;
    while(prox != nullptr){
        aux = prox;
        prox = prox->_prox;
        delete aux;
    }
}*/


void Stack::add_stack(int a, int b, int c, int d, int e, int f){
    No *novo = new No();
    novo->_line = a;
    novo->_column = b;
    novo->_ql = c;
    novo->_qc = d;
    novo->_refer = e;
    novo->_fixo = f;
    No *aux = this->_ini;
    this->_ini = novo;
    novo->_prox = aux;
    this->_tamanho++;
}

No Stack::remove_stack(){
    No *aux = this->_ini;
    No *prox = aux->_prox;
    No apagado;
    
    this->_ini = prox;
    apagado._line = aux->_line;
    apagado._column = aux->_column;
    apagado._ql = aux ->_ql;
    apagado._qc = aux -> _qc;
    apagado._refer = aux->_refer;
    apagado._fixo = aux->_fixo;
    delete aux;
    this->_tamanho--;
    return(apagado);
}