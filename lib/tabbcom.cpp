#include "tabbcom.h"

TNodoABB::TNodoABB():e()
{
    this->iz=NULL;
    this->de=NULL;
}
void TNodoABB::Copia(const TNodoABB& miNodo)
{
    this->e=miNodo.e;
	this->iz=NULL;
	this->de=NULL;
}
TNodoABB::TNodoABB(const TNodoABB& n)
{
    this->Copia(n);
}

TNodoABB::~TNodoABB()
{
    if(this!=NULL)
    {
        this->de=NULL;
        this->iz=NULL;
    }
}

TNodoABB& TNodoABB::operator=(const TNodoABB& nod)
{
    if(this != &nod)
    {
        (*this).~TNodoABB();
        Copia(nod);
    }
    return *this;
}

