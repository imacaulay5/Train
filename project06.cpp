#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "train.h"

int main()
{
	using namespace std;

	// Name of file to be processed
	string filename;
	// Create new input stream for file
	ifstream infile;
	// Number of cars in train
	int numCars;

	// Retrieve file to process from input
	cout << "Enter the name of the file to be processed: ";
	cin >> filename;

	// Open the file
	infile.open(filename);

	// Check if file was successfully opened
	if( !infile.is_open() )
	{
		cerr << "Can't open " << filename << " file for output.\n";
		exit(EXIT_FAILURE);
	}

	// Get number of cars in train from file
	infile >> numCars;

	cout << "There are " << numCars << " cars in this train.\n"
		 << "The data for each car are :\n\n";

	// Create new train
	Train locomotive = Train(numCars);

	// Create file pointer
	ifstream *fp = &infile;

	// Read info from file 
	locomotive.fillTrain(fp);

	// Close the file
	infile.close();

	// Print infor of each each car in train
	locomotive.printTrain();

    cout << "-------------------------------\n"
   			<< "-------------------------------\n\n";

 	// Calculate total cost and weight for train and print 
    locomotive.findTotals();

    // Print visual to standard output
	locomotive.printPicture();

	return 0;
}
