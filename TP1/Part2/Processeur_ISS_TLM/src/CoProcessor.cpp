///////////////////////////////////////////////////////////////////////////////
//
//	CoProcessor.cpp
//
///////////////////////////////////////////////////////////////////////////////
#include "CoProcessor.h"
#include <iostream>
#include <vector>
using namespace std;


///////////////////////////////////////////////////////////////////////////////
//
//	Constructeur
//
///////////////////////////////////////////////////////////////////////////////
CoProcessor::CoProcessor( sc_module_name zName )
: sc_module(zName)
{
	SC_THREAD(thread);
	sensitive << ClockPort.pos();
		
	reg[0] = 0x0000;
	reg[1] = 0x0000;
	reg[2] = 0x0000;
	reg[3] = 0x0000;
}


///////////////////////////////////////////////////////////////////////////////
//
//	Destructeur
//
///////////////////////////////////////////////////////////////////////////////
CoProcessor::~CoProcessor()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//	thread
//
///////////////////////////////////////////////////////////////////////////////
void CoProcessor::thread(void)
{
	// Variables locales
	unsigned int nbrElem;
	std::vector<unsigned int> elements;

	// Boucle infinie
	while(1)
	{
		
	    // On attend une transaction 
		do {
			wait(CoProcessor_Enable_InPort.default_event());
		} while(!CoProcessor_Enable_InPort.read());

		//Lecture adresse			
		switch(CoProcessor_Data_InPort.read())
		{
			// Write (du point de vue du processeur)
			// Lecture et stockage du nombre d'éléments à trier
			case 0x2000:
				CoProcessor_Ready_OutPort.write(true);
				do {
					wait(CoProcessor_Enable_InPort.default_event());
				} while(CoProcessor_Enable_InPort.read());
				CoProcessor_Ready_OutPort.write(false);

				nbrElem = CoProcessor_Data_InPort.read();
				reg[0].write(nbrElem);
				break;
			// Lecture des éléments à trier et tri (appel à bubbleSort)
			case 0x2001:
				CoProcessor_Ready_OutPort.write(true);
				do {
					wait(CoProcessor_Enable_InPort.default_event());
				} while(CoProcessor_Enable_InPort.read());
				CoProcessor_Ready_OutPort.write(false);

				elements.push_back(CoProcessor_Data_InPort.read());

				if (elements.size() >= nbrElem) {
					reg[2].write(0x0001);
					bubbleSort(&elements.at(0), nbrElem);
				}
				break;
			
			// Read (du point de vue du processeur)
			// Lecture du registre d'état du coprocesseur
			case 0x2002:
				CoProcessor_Data_OutPort.write(reg[2]);
				CoProcessor_Ready_OutPort.write(true);

			// Lecture du nombre d'éléments à envoyer au processeur
			case 0x2003:
			// Lecture des élément triés
			case 0x2004:

			default:
				reg[2] = 0x0000;
				elements.clear();
				break;
		}
	}
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
void CoProcessor::bubbleSort(unsigned int *ptr, int n_elements)
{
	// Affichage avant tri
	cout<<"Avant =>"<<endl;
	for (int i = 0; i < n_elements; i++)
	{
		cout << "[pos | val] : " << i << " | " << ptr[i] << endl;
	}

	// Tri, https://www.geeksforgeeks.org/bubble-sort/ 
	int i, j;
    for (i = 0; i < n_elements - 1; i++)
        for (j = 0; j < n_elements - i - 1; j++)
            if (ptr[j] > ptr[j + 1])
                swap(&ptr[j], &ptr[j + 1]);
	
	// Affichage après tri
	cout<<"Apres =>"<<endl;
	for (int i = 0; i < n_elements; i++)
	{
		cout << "[pos | val] : " << i << " | " << ptr[i] << endl;
	}
	reg[2].write(0x0002);
}