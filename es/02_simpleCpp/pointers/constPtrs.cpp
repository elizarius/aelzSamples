#include <iostream>
#include <algorithm>
#include <iterator>

int main(){

    //A raw variable that can be modified
	std::cout << std::endl;
    std::cout << "** Raw variable can be modified : " << std::endl;

    int number {5};// Not constant, can change number any way we want
    std::cout << "number : " << number <<"\t&number : " << &number<<std::endl;
    //Modify
    number = 12;
    number += 7;
    std::cout << "number : " << number <<"\t&number : " << &number<<std::endl;
    std::fill_n(std::ostream_iterator<char>(std::cout), 60, '-');
    std::cout << std::endl;
    


	//Pointer : Can modify the data and the pointer itself
    int *p_number1 {nullptr};
    int  number1{23};
    
    p_number1 = &number1;
    std::cout <<std::endl<<"** Pointer and value pointed to: both modifiable : " << std::endl;
    std::cout << "p_number1 : " << p_number1 <<"\t Value *p_number1 : " << *p_number1<<std::endl;

    //Change the pointed to value through pointer
    std::cout <<std::endl<<"Modify the value via ptr: *p_n = XXX: " << std::endl;
    *p_number1 = 432;
	std::cout << "p_number1 : " << p_number1 <<"\t Value *p_number1 : " << *p_number1<<std::endl;    
    std::cout << "number1 : " << number1 << std::endl;

    //Change the pointer itself to make it point somewhere else
	std::cout << "Modify the pointer to another value: p_n = &N2" << std::endl;
    int number2 {56};
    p_number1 = &number2;
    std::cout << "p_number1 : " << p_number1 <<"\t Value *p_number1 : " << *p_number1<<std::endl;    
    std::cout << "number1 : " << number1 <<"\tnumber2 : " << number2<<std::endl;
    std::fill_n(std::ostream_iterator<char>(std::cout), 60, '-');
    std::cout << std::endl;


    //Pointer to const
	//Pointer pointing to constant data : You can't modify the data through pointer
    std::cout << std::endl;
    std::cout << "const int*  Pointer to const: ptr is modifiable, can't modify the data through pointer: " << std::endl;
	int number3 {632}; // Although you can omit the const on number3 here and it is still 
                             // going to compile, it is advised to be as explicit as possible in
                             // your code and put the const in front. Make your intents CLEAR.
							 
    const int* p_number3 {&number3}; // Can't modify number3 through p_number3
    
    std::cout << "p_number3 :" << p_number3 << "\t*p_number3 : " << *p_number3 << std::endl;
	
	std::cout << std::endl;
    std::cout << "Modifying the value: *p_number3 = 444 --> COMPILE ERROR : " << std::endl;
    //*p_number3 = 444; // Compile error 
                      
    //Although we can't change what's pointed to by p_number3,
	//we can still change where it's pointing

    std::cout << "Changing the address:  p_number3 = &number4; : " << std::endl;
    int number4 {872};
    p_number3 = &number4;
    std::cout << "p_number3 :" << p_number3 << "\t*p_number3 : " << *p_number3 << std::endl;
    std::fill_n(std::ostream_iterator<char>(std::cout), 60, '-');
    std::cout << std::endl;


	//Pointer is constant (can't make it point anywere else), but pointed to value can change
    std::cout << std::endl;
    std::cout << "int * const: Const pointer: ptr cannot change but pointed value can change : " << std::endl;
    int number7 {982};
    
    int * const p_number7 { &number7};
    std::cout << "p_number7 :" << p_number7 << "\t*p_number7 : " << *p_number7<< std::endl;

    std::cout << " *p_number7 = 456:  Changing value pointed : " << std::endl;
    *p_number7 = 456;
    std::cout << "p_number7 :" << p_number7 << "\t*p_number7 : " << *p_number7<< std::endl;
    std::fill_n(std::ostream_iterator<char>(std::cout), 60, '-');
    std::cout << std::endl;

	//const keyword applies to the variable name.
    /*
	std::cout << "const keyword applies to a variable name : " << std::endl;
	
	int protected_var {10}; // Can make it const to protect it if we want.Show this
	
	//p_protected_var is a pointer to const data, we can't
	//modify the data through this pointer : regardless of
	//whether the data itself is declared const or not.
	const int* p_protected_var {&protected_var};
	
	//*p_protected_var = 55;
	protected_var = 66;
	std::cout << "protected_var : " << protected_var << std::endl;
	std::cout << "p_protected_var : " << p_protected_var << std::endl;
	std::cout << "*p_protected_var : " << *p_protected_var << std::endl;
	std::cout << std::endl;

	//You can't set up a modifiable pointer to const data though,
	//You'll get a compiler error :Invalid convertion from 'const type*' to 'type*'.
	const int some_data{55};
	//int * p_some_data {&some_data}; // Compiler error.
	//*p_some_data = 66;
    */


	//Both pointer and pointed to value are constant
    /*
    const int number5 {459};
    const int* const p_number5 {&number5 };
    std::cout << "Pointer is constant, value pointed to is constant : " << std::endl;
    std::cout << "p_number5 :" << p_number5 << std::endl;
    std::cout << "*p_number5 : " << *p_number5 << std::endl;
    
    //Can't modify the pointed to value through the pointer
    std::cout << "Changing value pointed to by p_number5 through the pointer (Compile Error) " << std::endl;
    //*p_number5 = 222; // Error : Trying to assign to read only location
    
    //Can't change where the pointer is pointing to : The pointer is now itself constant
    std::cout << "Changing the pointer p_number5 address itself (Compile Error) "<< std::endl;
    int number6 {333};
    //p_number5 = &number6;  // Error : Trying to assign to read only location
	
	std::cout << std::endl;
    */

   
    return 0;
}
