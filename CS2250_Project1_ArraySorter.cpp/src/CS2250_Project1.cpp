//============================================================================
// Name        : CS2250_Project1.cpp
// Author      : Tristan Longhibler
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iomanip>
using namespace std;

void initialize_array(int array[], int size)
{

	for(int i=0; i < size; i++)
	{
		array[i] =i;
	}

}

int * shuffle_array(const int array[], int size)
{

	int* newArray = new int[size];

	for(int i=0; i < size; i++)
	{

		newArray[i] = array[i];

	}

	for(int i=0; i < size; i++)
	{

		int j = rand()%size;

		int temp = newArray[i];

		newArray[i] = newArray[j];

		newArray[j] = temp;

	}

	return newArray;

}

int * createOddArray(const int array[], int size, int & newArraySize)
{

	int oddCount=0;

	for(int i=0; i < size; i++)
	{

		if(array[i]%2!=0)
		{
			oddCount++;
		}

	}

	newArraySize = oddCount;

	int* newArray = new int[newArraySize];

	int index=0;

	for(int i=0; i<size; i++)
	{

		if(array[i]%2!=0)
		{

			newArray[index]=array[i];

			index++;

		}

	}

	return newArray;

}

int * createEvenArray(const int array[], int size, int & newArraySize)
{

	int evenNumberCount=0;

	for(int i=0; i<size; i++)
	{

		if(array[i]%2==0)
		{

			evenNumberCount++;

		}

	}

	newArraySize = evenNumberCount;

	int* newArray = new int[newArraySize];

	int index=0;

	for(int i=0; i<size; i++)
	{

		if(array[i]%2==0)
		{

			newArray[index]=array[i];

			index++;

		}

	}

	return newArray;

}

void sort_array(int *array,int size)
{

	for(int i=0; i<size; i++)
	{
		for(int j=i+1; j<size; j++)
		{
			if(array[i]>array[j])
			{

				int temp = array[i];

				array[i] = array[j];

				array[j] = temp;

			}

		}

	}

}

void print_array(const int array[], int size)
{

	cout<<"[";

	for(int i=0; i<size; i++)
	{
		cout<<array[i]<<" ";
	}

	cout<<"]\n";

}

void array_war(int *firstArray, int firstArraySize, int * secondArray, int secondArraySize)
{
	int arraySize=0;

	if(firstArraySize>secondArraySize)
	{
		arraySize = firstArraySize;
	}
	else
	{
		arraySize = secondArraySize;
	}

	int * newArray =new int[arraySize];

	int i=0;

	while(i<arraySize)
	{
		if(i<firstArraySize && i<secondArraySize)
		{
			if(firstArray[i]>secondArray[i])
			{
				newArray[i] = firstArray[i];
			}
			else
			{
				newArray[i] = secondArray[i];
			}
		}
		else if(i<firstArraySize)
		{
			newArray[i] = firstArray[i];
		}
		else if(i<secondArraySize)
		{
			newArray[i] = secondArray[i];
		}
		i++;
	}

	cout<<"The winners are:";

	print_array(newArray,arraySize);

	cout<<"The sorted winners are:";

	sort_array(newArray,arraySize);

	print_array(newArray,arraySize);
}

int main()
{

	int size;

	cout<<"Please enter the size of the array: ";

	cin>> size;

	//check number if in range

	if(size<1 || size>52)
	{
		cout<<"Size out of range";

		return 0;
	}
	int array[size];

	//initialize array
	initialize_array(array,size);

	//shuffle array

	int* shuffledArray = shuffle_array(array,size);

	//print both array

	cout<<"The original array is:";

	print_array(array,size);

	cout<<"The shuffled array is:";

	print_array(shuffledArray,size);

	//get odd array

	int oddArrayCount;

	int * oddArray = createOddArray(shuffledArray,size,oddArrayCount);

	cout<<"The odd array is:";

	print_array(oddArray,oddArrayCount);

	//get even array

	int evenArrayCount;

	int * evenArray = createEvenArray(shuffledArray,size,evenArrayCount);

	cout<<"The even array is:";

	print_array(evenArray,evenArrayCount);

	//call array war

	array_war(oddArray,oddArrayCount,evenArray,evenArrayCount);

	return 0;
}
