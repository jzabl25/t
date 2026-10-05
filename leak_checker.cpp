

//
#include <iostream>


//
#include "MyVector.hpp"


//
using
	std::cout, std::endl
	;


//
using
	CPSC131::MyVector::MyVector
	;


//
void leaker()
{
	//
	MyVector<int> v;
	
	//
	for ( int i = 0; i < 10000; i++ ) {
		v.push_back(i);
		v.insert(0, 0);
	}
	for ( int i = 0; i < 5000; i++ ) {
		v.pop_back();
		v.erase(0);
	}
	
	v.insert(1000, 0);
	v.erase(599);
	v.reserve(1000000000);
	
	//
	{
		MyVector<int> v2 = v;
		MyVector<int> v3;
		v3 = v;
		MyVector<int> v4(v);
	}
	
	v.clear();
}

//
int main()
{
	//
	cout << "Hello, my name is Quiche Hollandaise!" << endl;
	
	//
	leaker();
	
	return 0;
}

