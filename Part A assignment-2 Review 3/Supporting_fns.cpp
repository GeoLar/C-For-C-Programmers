
#include "Supporting_fns.h"
#include <iostream>
using namespace std;

/**************************************************************************************************/	
/**************************************************************************************************/	

void print(std::vector<uint32> const &input)
{
	for (int i = 0; i < input.size(); i++) {
		std::cout << input.at(i) << ' ';
	}
	cout << endl;
}

/**************************************************************************************************/	
/**************************************************************************************************/	

void print(std::vector<int32> const &input)
{
	for (int i = 0; i < input.size(); i++) {
		std::cout << input.at(i) << ' ';
	}
	cout << endl;
}