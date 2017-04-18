#include <iostream>

using namespace std;

#include "tabbcom.h"

int
main(void)
{
	TComplejo a;
	TABBCom arbol;
	if(arbol.Insertar(a))
	{
		cout<<"Ok"<<endl;
	}else
	{
		cout<<"Fail"<<endl;
	}
}