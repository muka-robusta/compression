#include <iostream>
#include <cstdlib>

/*

*	What do you need to know, when reading thius code:
		
*		I don`t like use arrays in c++, instead that i am 
*		using adresses
	
	/NO    a[5]
	/YES *(a + 5)
		
*		In my opinion it is less complicates and works 
*		quickly. And to pass different variables to function
*		arguments we need to use adresses.


*/

class symbol {
	char value;
	int quantity;
	float probability;

public:

	void setValue(char sy){value = sy;}
	void setQuantity(int value){quantity = value;}
	void setProbability(float value){probability = value;}

	char getValue(){return value;}
	int getQuantity(){return quantity;}
	float getProbability(){return probability;}

	friend fact_size(symbol*);
	friend void quick_sort(symbol*,int,int);
	friend void init_table(symbol*);//init table of symbols as hash-table
	friend symbol * handle_text(char*,int); 

};



//--------------sorting type: quick - sort
//It`s up to you to choose type of sorting
//(you can use even bubble - sort) 
void quick_sort(symbol * syms,int first,int last)
{
	if(first < last)
	{
		// sorting by last
		int last_value = (syms + last) -> quantity;
		int i = first - 1;
		int j = first;
		
		for(;j < last;j++)
		{
			if((syms + j) -> quantity < last_value)
			{
				i++;
				symbol temp = *(syms + i);
				*(syms + i) = *(syms + j);
				*(syms + j) = temp;	
			}
		}

		symbol temp = *(syms + last);
		*(syms + last) = *(syms + i);
		*(syms + i) = temp;

		quick_sort(syms,first,i);
		quick_sort(syms,i + 2,last);

	}	

}


void init_table(symbol * sy)
{
	for(int i = 0; i < 256; i++)
	{
		(sy + i) -> value = (char) i; 
	}
	return;
}

symbol * handle_text(char * text, int size)
{
	//creating the char of all symbols
	symbols * syms = new symbols[256];
	init_table(syms);
	for(int i = 0; i < size; i++)
	{
		(syms + (*(text + i))) -> quantity += 1;
	}
	return syms;
}


int fact_size(symbol * syms)//the array must be sorted
{
	int size = 0;
	for(int i = 0; i < 256;i++)
	{
		if((syms + i)->quantity > 0)
		{
			size++;
		}
	}
	return size;
}

symbol * get_fact_table(symbol * all_sy)//sorting here probabilities
{
	int fact_size = fact_size(all_sy);
	quick_sort(all_sy);
	symbol * fact_syms = new symbol[fact_size];
	for(int i = 0; i < fact_size; i++)
	{
		*(fact_syms + i) = *(all_sy + i);
		float prob =((float) (fact_syms + i) -> getQuantity()) / fact_size;
		(fact_syms) -> setProbability(prob);
	}
	return fact_syms;
}


