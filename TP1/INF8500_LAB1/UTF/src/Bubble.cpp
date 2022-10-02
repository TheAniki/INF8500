///////////////////////////////////////////////////////////////////////////////
//
//	Bubble.cpp
//
///////////////////////////////////////////////////////////////////////////////
#include "Bubble.h"


///////////////////////////////////////////////////////////////////////////////
//
//	Constructeur
//
///////////////////////////////////////////////////////////////////////////////
Bubble::Bubble( sc_module_name zName )
: sc_module(zName)
{
	SC_METHOD(interface);
}


///////////////////////////////////////////////////////////////////////////////
//
//	Destructeur
//
///////////////////////////////////////////////////////////////////////////////
Bubble::~Bubble()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//	Interface avec le module Reader: sc_thread ou sc_method
//
///////////////////////////////////////////////////////////////////////////////
void Bubble::interface(void)
{	
	// Variable
	unsigned int nbrElem;
	
	// 1ere lecture: nombre d'éléments à trier
	nbrElem = readPort->Read(0);
	unsigned int* elements = new unsigned int[nbrElem];

	// Lecture des éléments à trier
	for (int i = 1; i <= nbrElem; i++)
	{
		elements[i - 1] = readPort->Read(i * 4);
	}

	//Appel à bubble sort
	bubbleSort(elements, nbrElem);
		
	// Arrêt de la simulation
	sc_stop();
}

///////////////////////////////////////////////////////////////////////////////
//
//	Swap method https://www.geeksforgeeks.org/bubble-sort/
//
///////////////////////////////////////////////////////////////////////////////
void swap(unsigned int* xp, unsigned int* yp)
{
    unsigned int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

///////////////////////////////////////////////////////////////////////////////
//
//	bubbleSort
//
///////////////////////////////////////////////////////////////////////////////
void Bubble::bubbleSort(unsigned int *ptr, int counter)
{
	// Affichage avant tri
	cout<<"Avant =>"<<endl;
	for (int i = 0; i < counter; i++)
	{
		cout << "valeur : " << i << " | " << ptr[i] << endl;
	}

	// Tri, https://www.geeksforgeeks.org/bubble-sort/ 
	int i, j;
    for (i = 0; i < counter - 1; i++)
        for (j = 0; j < counter - i - 1; j++)
            if (ptr[j] > ptr[j + 1])
                swap(&ptr[j], &ptr[j + 1]);
	
	// Affichage après tri
	cout<<"Apres =>"<<endl;
	for (int i = 0; i < counter; i++)
	{
		cout << "valeur : " << i << " | " << ptr[i] << endl;
	}
}
