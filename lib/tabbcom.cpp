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
    return(*this);
}
//copia
void TABBCom::Copia(const TABBCom& arbol)
{
    if(!arbol.EsVacio())
    {
        //nodo auxiliar
        TNodoABB * aux = new TNodoABB();
        aux->item = arbol.nodo->item;
        this->nodo=aux;
        //Recursivamente para todos los demas subarboles
        this->nodo->iz.Copia(arbol.nodo->iz);
        this->nodo->de.Copia(arbol.nodo->de);
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
        return 0;
    }
    else
	{
		int total= 1 + this->nodo->de.Nodos() + this->nodo->iz.Nodos();
		return total;
	}
}
//Inorde auxiliar
void TABBCom::InordenAux(TVectorCom &v,int &posicion)
{
	if(this->nodo!=NULL)
	{
        //itero recursivamente por el subarbol izquierdo
		this->nodo->iz.InordenAux(v,posicion);
        //inserto la raiz en el vector
		v[posicion]=this->nodo->item;
        posicion++;
        //itero recursivamente por el subarbol derecho
        this->nodo->de.InordenAux(v,posicion);
		
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
    if(!this->EsVacio())
    {
        //creo el vector con el numero de nodos que tiene el arbol
        TVectorCom vec = TVectorCom(this->Nodos()); //esto no tiene ni puto sentido joder :( si hago lo mismo pero en Nodos() no funciona
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
    //si el arbol esta vacio devuelvo un vector vacio
    if(this->nodo==NULL)
    {
        return vec;
    }
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
    if(this->Postorden()==arbol.Postorden())
    {
        return true;
    }
        

    return false;
}
// Devuelve TRUE si el elemento está en el árbol, FALSE en caso contrario
bool TABBCom::Buscar(const TComplejo& com)
{
    if(this->EsVacio())
    {
        return false;
    }
    //si el modulo de la raiz es mayor que el modulo de num. complejo
    if(this->nodo->item.Mod()>com.Mod())
    {
        return this->nodo->iz.Buscar(com);
    }else if(this->nodo->item.Mod()<com.Mod())
    {
        return this->nodo->de.Buscar(com);
    }else
    {
        return true;
    }
}
// Inserta el elemento en el árbol
bool TABBCom::Insertar(TComplejo& com)
{
    //Compruebo que el complejo no este ya insertado
    if(!this->Buscar(com))
    {
        //si el arbol esta vacio iserto el primer elemento
        if(this->EsVacio())
        {
            TNodoABB* aux = new TNodoABB();
            aux->item=com;
            this->nodo=aux;
            return true;
        }
        //si la raiz es mayor que el complejo busco en el subarbol izquierdo
        if(this->nodo->item.Mod()>com.Mod())
        {
            return this->nodo->iz.Insertar(com);
        //si la raiz es menor que el complejo busco en el subarbol derecho
        }else
        {
            return this->nodo->de.Insertar(com);
        }
    }
    return false;
}
//min
TComplejo TABBCom::min()
{
    if(this->EsVacio())
    {
        return TComplejo();
    }else if(this->nodo->iz.EsVacio())
    {
        return this->nodo->item;
    }else
    {
        return this->nodo->iz.min();
    }
}
//auxiliar de borrar
TABBCom TABBCom::BorrarAux(const TComplejo& com)
{
    if(this->EsVacio())
    {
        return (*this);
    }
    if(this->nodo->item.Mod()>com.Mod())
    {
        this->nodo->iz = this->nodo->iz.BorrarAux(com);
        return(*this);
    }else if(this->nodo->item.Mod()<com.Mod())
    {
        this->nodo->de = this->nodo->de.BorrarAux(com);
        return (*this);
    }
    if(this->nodo->item.Mod()==com.Mod() && this->nodo->de.EsVacio())
    {
        return this->nodo->iz;
    }
    if(this->nodo->item.Mod()==com.Mod() && this->nodo->iz.EsVacio())
    {
        return this->nodo->de;
    }
    if(this->nodo->item.Mod()==com.Mod() && (!this->nodo->iz.EsVacio()))
    {
        this->nodo->item = this->nodo->de.min();
        this->nodo->de.BorrarAux(this->nodo->de.min());
        return (*this);
    }
}
// Borra el elemento en el árbol
bool TABBCom::Borrar(const TComplejo& com)
{
    if(this->EsVacio())
    {
        return false;
    }
    this->BorrarAux(com);
    return true;
}
// Devuelve el elemento en la raíz del árbol
TComplejo TABBCom::Raiz()
{
    if(this->EsVacio())
    {
        TComplejo co;
        return co;
    }
    return this->nodo->item;
}
//devuelve true si es hoja
bool TABBCom::EsHoja()
{
    if(this->nodo==NULL)
        return true;
	if(this->nodo->iz.nodo == NULL and this->nodo->de.nodo == NULL)
	{
		return true;
	}else
	{
		return false;
	}
}
// Devuelve el número de nodos hoja en el árbol (la raíz puede ser nodo hoja)
int TABBCom::NodosHoja()
{
    if(this->EsVacio())
        return 0;
    if(this->EsHoja())
    {
        return 1;
    }
    int total = this->nodo->iz.NodosHoja()+this->nodo->de.NodosHoja();
    return (total);
}
ostream& operator<<(ostream& os, TABBCom& com)
{
    os<<com.Niveles();
    return os;
}