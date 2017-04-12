#include "tabbcom.h"
#include <queue>
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
TABBCom::TABBCom(const TABBCom& arbol)
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
TABBCom& TABBCom::operator=(const TABBCom& arbol)
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
int TABBCom::Nodos()const
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
TVectorCom TABBCom::Preorden()
{
    if(this->EsVacio())
    {
        //creo el vector con el numero de nodos que tiene el arbol
        TVectorCom vec = TVectorCom(this->Nodos());
        int pos = 1;
        //llamo a la función recursiva para llenar el vector
        this->PreordenAux(vec,pos);
        return vec;
    }else
    {
        TVectorCom vec;
        return vec;
    }
}
TVectorCom TABBCom::Postorden()
{
    if(this->EsVacio())
    {
        //creo el vector con el numero de nodos que tiene el arbol
        TVectorCom vec = TVectorCom(this->Nodos());
        int pos = 1;
        //llamo a la función recursiva para llenar el vector
        this->PostordenAux(vec,pos);
        return vec;
    }else
    {
        TVectorCom vec;
        return vec;
    }
}
// Devuelve el recorrido en niveles
TVectorCom TABBCom::Niveles()
{
    //cola de abb s
    queue<TABBCom> c;
    //una arbol abb
    TABBCom aux;
    int pos=1;
    //vector
    TVectorCom vec(this->Nodos());
    // encolar en c
    c.push((*this));
    // mientras la cola no es vacia
    while(!c.empty())
    {
        //auxiliar es igual a lo que haya en la cola
        aux = c.front();
        vec[pos]=aux.nodo->item;
        //desencolar
        c.pop();
        //si el subarbol de la izquierda no es vacio se inserta en cabeza el subarbol izquierdo
        if(!aux.nodo->iz.EsVacio())
            c.push(aux.nodo->iz);
        //si el subarbol de la derecha no es vacio se inserta en cabeza el subarbol derecho
        if(!aux.nodo->de.EsVacio())
            c.push(aux.nodo->de);
        //se aumenta la posición
        pos++;
    }
    return vec;
}
// Devuelve la altura del árbol (la altura de un árbol vacío es 0)
int TABBCom::Altura()const
{
    if(this->EsVacio())
    {
        return 0;
    }else
    {
        return 1 + max(this->nodo->iz.Altura(),this->nodo->de.Altura());
    }
}
// Sobrecarga del operador igualdad
bool TABBCom::operator==(TABBCom& arbol)
{
    if(this->Inorden()==arbol.Inorden())
        return true;

    return false;
}
// Devuelve TRUE si el elemento está en el árbol, FALSE en caso contrario
bool TABBCom::Buscar(const TComplejo& com)
{
    //vector con elementos en inorden
    TVectorCom vec = this->Inorden();
    //recorro todos los elemento en busca del que me han pasado   
    for(int i=1;i<=this->Nodos();i++)
    {
        if(vec[i]==com)
        {
            return true;
        }
    }
    return false;
}
// Inserta el elemento en el árbol
bool TABBCom::Insertar(const TComplejo& com)
{
    if(!this->Buscar(com))
    {
        
    }
    return false;
}