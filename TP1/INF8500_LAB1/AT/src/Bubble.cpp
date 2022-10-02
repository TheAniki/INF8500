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
	SC_THREAD(interface);
	sensitive << clk.pos(); 
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
//	Interface avec le module Reader
//
///////////////////////////////////////////////////////////////////////////////
void Bubble::interface(void)
{
	std::vector<unsigned int> elements;
	int it = 0;
	
	do{		
		this->address.write(it*4);
		this->request.write(true);
		// Attends le signal ack
		do{
			wait(1);
		}while(!this->ack.read());
			
		elements.push_back(this->data.read());	
		this->request.write(false);	
			
	}while(elements[0]>=++it);
	bubbleSort(&elements[1],elements[0]);

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
	std::cout<<"Avant =>"<<std::endl;
	for (int i = 0; i < counter; i++)
	{
		std::cout << "valeur : " << i << " | " << ptr[i] << std::endl;
	}
	std::cout<<std::endl<<"Bubble Begin "<<sc_time_stamp()<<std::endl;
	// Tri, https://www.geeksforgeeks.org/bubble-sort/ 
	int i, j;
    for (i = 0; i < counter - 1; i++)
        for (j = 0; j < counter - i - 1; j++){
            if (ptr[j] > ptr[j + 1])
				swap(&ptr[j], &ptr[j + 1]);
			wait(1);
		}
    std::cout<<std::endl<<"Bubble end "<<sc_time_stamp()<<std::endl;            
	
	// Affichage après tri
	std::cout<<"Apres =>"<<std::endl;
	for (int i = 0; i < counter; i++)
	{
		std::cout << "valeur : " << i << " | " << ptr[i] << std::endl;
	}	
}
