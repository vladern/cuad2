#ifndef TLISTACOM_H_
#define TLISTACOM_H_
#include "tcomplejo.h"
class TNodoABB
{
    private:
        // El elemento del nodo
        TComplejo e;
        // El nodo anterior
        TNodoABB *iz;
        // El nodo siguiente
        TNodoABB *de;
    public:
        // Constructor por defecto
        TNodoABB ();
        // Constructor de copia
        TNodoABB (const TNodoABB &);
        // Destructor
        ~TNodoABB();
        //copia
        void Copia(const TNodoABB &);
        // Sobrecarga del operador asignación
        TNodoABB& operator=(const TListaNodo &);
};
class TABBCom
{
    private:
        // Puntero al nodo
        TNodoABB *nodo;
        // AUXILIAR : Devuelve el recorrido en inorden
        void InordenAux(TVectorCom &, int &);
        // AUXILIAR : Devuelve el recorrido en preorden
        void PreordenAux(TVectorCom &, int &);
        // AUXILIAR : Devuelve el recorrido en postorden
        void PostordenAux(TVectorCom &, int &);
    public:
        // Constructor por defecto
        TABBCom ();
        // Constructor de copia
        TABBCom (TABBCom &);
        // Destructor
        ~TABBCom ();
        // Sobrecarga del operador asignación
        TABBCom & operator=( TABBCom &);
        //--------------------Metodos-----------------------
        //--------------------------------------------------
        //--------------------------------------------------
        //--------------------------------------------------
        // Sobrecarga del operador igualdad
        bool operator==(TABBCom &);
        // Devuelve TRUE si el árbol está vacío, FALSE en caso contrario
        bool EsVacio();
        // Inserta el elemento en el árbol
        bool Insertar(TComplejo &);
        // Borra el elemento en el árbol
        bool Borrar(TComplejo &);
        // Devuelve TRUE si el elemento está en el árbol, FALSE en caso contrario
        bool Buscar(TComplejo &);
        // Devuelve el elemento en la raíz del árbol
        TComplejo Raiz();
        // Devuelve la altura del árbol (la altura de un árbol vacío es 0)
        int Altura();
        // Devuelve el número de nodos del árbol (un árbol vacío posee 0 nodos)
        int Nodos();
        // Devuelve el número de nodos hoja en el árbol (la raíz puede ser nodo hoja)
        int NodosHoja();
        // Devuelve el recorrido en inorden
        TVectorCom Inorden();
        // Devuelve el recorrido en preorden
        TVectorCom Preorden();
        // Devuelve el recorrido en postorden
        TVectorCom Postorden();
        // Devuelve el recorrido en niveles
        TVectorCom Niveles();
        // Sobrecarga del operador salida
        friend ostream & operator<<(ostream &, TABBCom &);
};

#endif