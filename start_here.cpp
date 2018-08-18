#include "symbols_lib.hpp"

#define DEFAULT_SIZE 6000

int main()
{
	cout << "Enter the path of the file: ";
	char * path = new char[50];
	cin >> path;

	FILE * file = NULL;
	file = fopen(path,"r");

	if(file)
	{
		char * buffer = new char[DEFAULT_SIZE];
		int size_of_the_text = 0;
		char temp;
		while((temp = getc(file)) != EOF)
		{
			*(buffer + size_of_the_text) = temp;
			size_of_the_text++;
		}		
		symbol * temp_table = handle_text(buffer,size_of_the_text);
		symbol * table = get_fact_table(temp_table);
		int size = fact_size(table);
		delete [] temp_table;
		for(int i = 0; i < size; i++)
		{
			cout << "SYMBOL [" << (table + i) -> getValue() << " qua: "<<(table + i) -> getQuantity() <<"] with PROBABILITY: " << (table + i) -> getProbability() << endl;
		}
	}

	return 0;
}