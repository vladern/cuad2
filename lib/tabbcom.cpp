#include "tabbcom.h"

TNodoABB::TNodoABB():item(),iz(),de()
{

}
TNodoABB::TNodoABB(TNodoABB &nodo):item(nodo.item),iz(nodo.iz),de(nodo.de)
{

}
TNodoABB::~TNodoABB()
{

}
/*
*
*--------------------ABBComplejo----------------------
*
*/
// Constructor por defecto
TABBCom::TABBCom()
{
    this->nodo=NULL;
}
// Constructor de copia
TABBCom::TABBCom(TABBCom& arbol)
{
    this->nodo=NULL;
    this->Copia(arbol);
}
// Destructor
TABBCom::~TABBCom()
{
    if(this!=NULL)
    {
        delete nodo;
        this->nodo=NULL;
    }
}
// Sobrecarga del operador asignación
TABBCom& TABBCom::operator=(TABBCom& arbol)
{
    if(this != &arbol)
    {
        (*this).~TABBCom();
        Copia(arbol);
    }
}
//copia
void TABBCom::Copia(const TABBCom& arbol)
{
    if(arbol.nodo!=NULL)
    {
        //nodo auxiliar
        TNodoABB * aux = new TNodoABB();
        aux->item = arbol.nodo->item;
        this->nodo=aux;
        //Recursivamente para todos los demas subarboles
        this->Copia(arbol.nodo->iz);
        this->Copia(arbol.nodo->de);
        //Termino con la recursion y me voy a tomarme unas cervezas :)
    }else
    {
        this->nodo=NULL;
    }
}
// Devuelve TRUE si el árbol está vacío, FALSE en caso contrario
bool TABBCom::EsVacio() const
{
    if(this->nodo==NULL)
    {
        return true;
    }else
    {
        return false;
    }
}
// Devuelve el número de nodos del árbol (un árbol vacío posee 0 nodos)
int TABBCom::Nodos()
{
    if(this->EsVacio())
    {
        return 1;
    }else
    {
        //voy recoriendo todos los nodos recursivamente por la izquierda y derecha
        int tot = this->nodo->iz.Nodos() + this->nodo->de.Nodos();
        return tot;
    }
}
//Inorde auxiliar
void TABBCom::InordenAux(TVectorCom &v,int &posicion)
{
	if(nodo!=NULL)
	{
        //itero recursivamente por el subarbol izquierdo
		this->nodo->iz.InordenAux(v,posicion);
        //inserto la raiz en el vector
		v[posicion]=this->nodo->item;
        //itero recursivamente por el subarbol derecho
        this->nodo->de.InordenAux(v,posicion);
		posicion++;
	}
}
void TABBCom::PreordenAux(TVectorCom &v,int &posicion)
{
	if(nodo!=NULL)
	{
		v[posicion]=this->nodo->item;
		posicion++;
		this->nodo->iz.PreordenAux(v,posicion);
		this->nodo->de.PreordenAux(v,posicion);
	}
}
void TABBCom::PostordenAux(TVectorCom &v,int &posicion)
{
	if(nodo!=NULL)
	{
		this->nodo->iz.PostordenAux(v,posicion);
		this->nodo->de.PostordenAux(v,posicion);
		v[posicion]=this->nodo->item;
		posicion++;
	}
}
// Devuelve el recorrido en inorden
TVectorCom TABBCom::Inorden()
{
    if(this->EsVacio())
    {
        //creo el vector con el numero de nodos que tiene el arbol
        TVectorCom vec = TVectorCom(this->Nodos());
        int pos = 1;
        //llamo a la función recursiva para llenar el vector
        this->InordenAux(vec,pos);
        return vec;
    }else
    {
        TVectorCom vec;
        return vec;
    }
}