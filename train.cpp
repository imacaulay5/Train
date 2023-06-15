// train.cpp -- train member functions
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "train.h"

using namespace std;

Car::Car()
{
	Car::carNum = 0;
	Car::origin = "";
	Car::destination = "";
	Car::weight = 0;
	Car::miles = 0;
	Car::cost = 0;
}

Car::~Car()
{
}

// Calculate cost for specific car based on cargo and returns it
float Car::findCost()
{
	// Price of items per ton-mile
	float price;

	// Retrieve correct price pert ton-mile based on cargo type
	switch( Car::cargo )
	{
		case 0:
			price = 0.165;
			break;

		case 1:
			price = 0.291;
			break;

		case 2:
			price = 0.525;
			break;

		case 3:
			price = 0.631;
			break;

		case 4:
			price = 0.759;
			break;

		default:
			price = 0;
	}

	Car::cost = ( (float) weight )/2000.0
    		* (miles)
    		* price;

    return Car::cost;
}

int Car::getWeight()
{
	return weight;
}

void Car::setCargo(char* cargo)
{
	// Assign correct price to car based off of cargo
	if( strcmp(cargo, "autos") == 0 )
	{
		Car::cargo = autos;
	}
	else if( strcmp(cargo, "coal") == 0 )
	{
		Car::cargo = coal;
	}
	else if( strcmp(cargo, "cattle") == 0 )
	{
		Car::cargo = cattle;
	}
	else if( strcmp(cargo, "hogs") == 0 )
	{
		Car::cargo = hogs;
	}
	else if( strcmp(cargo, "eggs") == 0 )
	{
		Car::cargo = eggs;
	}
}
// Print formatted output for the info on each car
void Car::printCar()
{
	switch( Car::cargo )
	{
		case 0:
			Car::cargoString = "autos";
			break;

		case 1:
			Car::cargoString = "coal";
			break;

		case 2:
			Car::cargoString = "cattle";
			break;

		case 3:
			Car::cargoString = "hogs";
			break;

		case 4:
			Car::cargoString = "eggs";
			break;

		default:
			Car::cargoString = "";
	}

	cout << "Car number\t: " << Car::carNum
		<< "\nCargo\t\t: " << Car::cargoString
		<< "\nOrigin\t\t: " << Car::origin
		<< "\nDestination\t: " << Car::destination
		<< "\nWeight\t\t: " << Car::weight << " pounds\n"
		<< "Distance\t: " << Car::miles << " miles\n"
		<< "Cost\t\t: $ " << fixed << setprecision(2) << Car::cost << "\n" << endl;
}

// Get info from file and fill car
void Car::fillCar(std::ifstream *file)
{
	// Read cargo in as a string
	char* cargo = new char[30];

	*file >> Car::carNum;
	*file >> cargo;
	*file >> Car::origin;
	*file >> Car::destination;
	*file >> Car::weight;
	*file >> Car::miles;

	Car::setCargo( cargo );

	delete[] cargo;

	Car::findCost();
}

Train::Train( int n )
{
	train = new Car[n];
	numCars = n;
}

// Copy Constructor
Train::Train(const Train &t)
{
	Train::train = t.train;
	Train::numCars = t.numCars;
}

Train::~Train()
{
	delete [] train;
}

void Train::fillTrain(std::ifstream *file)
{
	// Retrieve info for each car
	for( int i = 0; i < numCars; i++ )
	{
		train[i].fillCar(file);
	}
}

void Train::findTotals()
{
	float totalCost = 0;
	float totalWeight = 0;

	// Calculate total cost of train
    for( int i = 0; i < numCars; i++ )
    {
    	totalCost += train[i].findCost();
    }

    // Calculate total weight of train
    for( int i = 0; i < numCars; i++ )
    {
    	totalWeight += (float) train[i].getWeight();
    }

	// Convert total weight from pounds to tons
	totalWeight /= 2000;

	cout << "Number of cars\t: " << Train::numCars << endl;
	cout << "Total weight\t: " << fixed << setprecision(2) << totalWeight << " tons" << endl;
	cout << "Total cost\t: $ " << fixed << setprecision(2) << totalCost << "\n" << endl;
}

void Train::printTrain()
{
	// Print out each car of the train
    for(int i = 0; i < numCars; i++)
    {
    	train[i].printCar();
    }
}

void Train::printPicture()
{
	// Keep track of how many cars were printed
	int printedCars = 0;
	// Keep track of train index
	int trainIndex = 0;

	// Print complete line of 5 train cars
	// until remaining cars is less than 5
	while( (Train::numCars - printedCars) >= 5)
	{
		// Print line 1
		for(int i = 0; i < 5; i++)
		{
			cout << "  -------------";
		}
		cout << "\n";

		// Print train car number
		for(int i = 0; i < 5; i++)
		{
			cout << "  | " << setw(10) << train[trainIndex].carNum << "|";
			trainIndex++;
		}
		cout << "\n";
		// Make train index to first car in line
		trainIndex -= 5;

		// Print cargo
		for(int i = 0; i < 5; i++)
		{
			cout << "<-| " << setw(10) << train[trainIndex].cargoString << "|";
			trainIndex++;
		}
		cout << "\n";
		trainIndex -= 5;

		// Print car destination
		for(int i = 0; i < 5; i++)
		{
			cout << "  | " << setw(10) << train[trainIndex].destination << "|";
			trainIndex++;
		}
		cout << "\n";

		// Print train wheels
		for(int i = 0; i < 5; i++)
		{
			cout << "  --O-------O--";
		}
		cout << "\n\n";

		printedCars += 5;
	}

	// Print out remainder of cars
	for(int i = 0; i < (Train::numCars - printedCars); i++)
	{
		cout << "  -------------";
	}
	cout << "\n";

	// Print train car number
	for(int i = 0; i < (Train::numCars - printedCars); i++)
	{
		cout << "  | " << setw(10) << train[trainIndex].carNum << "|";
		trainIndex++;
	}
	cout << "\n";

	// Make train index to first car in line
	trainIndex -= (Train::numCars - printedCars);

	// Print cargo
	for(int i = 0; i < (Train::numCars - printedCars); i++)
	{
		cout << "<-| " << setw(10) << train[trainIndex].cargoString << "|";
		trainIndex++;
	}
	cout << "\n";
	trainIndex -= (Train::numCars - printedCars);

	// Print car destination
	for(int i = 0; i < (Train::numCars - printedCars); i++)
	{
		cout << "  | " << setw(10) << train[trainIndex].destination << "|";
		trainIndex++;
	}
	cout << "\n";

	// Print train wheels
	for(int i = 0; i < (Train::numCars - printedCars); i++)
	{
		cout << "  --O-------O--";
	}
}