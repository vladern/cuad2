#include <iostream>
#include "tabbcom.h"
#include "tcomplejo.h"
#include "tvectorcom.h"
using namespace std;

int
main(void)
{
  TABBCom a;

  TComplejo c1(68, 1);
  TComplejo c2(56, 1);
  TComplejo c3(84, 1);
  TComplejo c4(35, 1);
  TComplejo c5(60, 1);
  TComplejo c6(80, 1);
  TComplejo c7(98, 1);

  a.Insertar(c1);
  a.Insertar(c2);
  a.Insertar(c3);
  a.Insertar(c4);
  a.Insertar(c5);
  a.Insertar(c6);
  a.Insertar(c7);

  TListaCom l1;
  if(l1.EsVacia())
  {
    cout<<"true"<<endl;
  }else
  {
     cout<<"false"<<endl;
  }
  l1.InsCabeza(c1);
  l1.InsCabeza(c2);
  l1.InsCabeza(c5);

  if(a.examen(l1))
  {
    cout<<"Si hay camino"<<endl;
  }else
  {
    cout<<"No hay camino"<<endl;
  }
  
return 1;

}
