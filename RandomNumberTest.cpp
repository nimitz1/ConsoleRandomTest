/*----This is a random number generator which also tests the set of numbers for true randomness----
Project overview:
1. Generate a set of random numbers, the amount is chosen by the user
2. Evaluate with a basic test to see if the numbers generated are random enough
//----*/
// include libraries
#include <stdlib.h>
#include <iostream>
#include <string>


//include the std namespace for easier coding with io
using namespace std;

//declaring global variables
string userInput = "Empty";
//int inputNumber = 0;
int maxValue = 1000;
double estimate = 0;

//declaring functions
int blockTest(int* numberSet, int inputNumber, double estimate);
int input(int inputNumber);

//main function of the program
int main() {


	//Starting text for console
	cout << "\nThis is a Random Number Test for the C++ random library.\n\n";


	//initialize local variables
	int val = 0;
	int inputNumber = input(val);
	int median = round(inputNumber / 2);

	//allocate memory
	int* numberSet = new int[inputNumber];

	//Generate random values
	for (int i = 0; i < inputNumber; i++) {
		numberSet[i] = rand() % inputNumber;
		//cout << "\n" << numberSet[i];
	}

	//Ask user for input before continuing
	system("pause");

	cout << "\n";
	cout << inputNumber << " values have been generated!\n\n";

	system("pause");

	//true randomness check
	cout << "\nThe estimate for true randomness deviates from the median by: " << median - blockTest(numberSet, inputNumber, estimate);
	cout << "\n";

	//clear memory
	delete[]numberSet;

	return 0;
}//end main

//Get the amount of number in to be in the set
int input(int inputNumber) {

	//initialize function variables
	bool charCheck = true;
	char minus = '-';

	//check user input
	while (charCheck) {

		cout << "\nEnter amount of values to be tested {0-1000}: ";
		cin >> userInput;

		//check for valid input
		for (int i = 0; i < userInput.length(); i++) {
			if (isdigit(userInput[i])) {
				charCheck = false;
			}
			else {
				if (i == 0 && userInput[0] == minus)
					charCheck = false;
				else {
					cout << "\nPlease enter a number.";
					charCheck = true;
					break;
				}
			}
		}//end for


		if (charCheck)
			continue;
		else
		{
			inputNumber = stoi(userInput);
			if (inputNumber >= 1000 || inputNumber < 0) {
				cout << "\nPlease enter a number between {0-1000}.";
				charCheck = true;
			}//end if
		}

	}//end while

	return inputNumber;

}//end userInput

//Divide the number set into smaller number sets
//Compare the averages
int blockTest(int* numberSet, int inputNumber, double estimate) {

	//initialize local variables
	const int numberOfBlocks = 4;
	double* average = new double[numberOfBlocks];
	int addValues = 0;

	//subdivide set into smaller sets
	int smallerSetSize = inputNumber / numberOfBlocks;

	//average out the averages of the smaller sets to get estimation of randomness
	for (int j = 1; j < numberOfBlocks; j++) {
		for (int i = (smallerSetSize * (j - 1)); i < (smallerSetSize * j); i++) {
			addValues += numberSet[i];
		}
		average[j - 1] = (double)addValues / (double)smallerSetSize;
		addValues = 0;
	}//end for

	//include the rest of the array
	for (int i = (smallerSetSize * 3); i < inputNumber; i++) {
		addValues += numberSet[i];
	}//end for
	average[numberOfBlocks - 1] = (double)addValues / (double)smallerSetSize;
	addValues = 0;

	for (int i = 0; i < numberOfBlocks; i++) {
		addValues += average[i];
	}//end for

	estimate = (double)addValues / (double)numberOfBlocks;
	addValues = 0;

	return estimate;
}//end blockTest
