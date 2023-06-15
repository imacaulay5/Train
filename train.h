#ifndef TRAIN_H_
#define TRAIN_H_

class Train;

enum cargoType { autos, coal, cattle, hogs, eggs };

class Car
{
	friend class Train;

	private:
		int carNum;
		cargoType cargo;
		std::string cargoString;
		std::string origin;
		std::string destination;
		int weight;
		int miles;
		float cost;
	public:
		Car();
		~Car();
		float findCost();
		int getWeight();
		void setCargo(char* cargo);
		void printCar();
		void fillCar(std::ifstream *file);
};

class Train
{
	private:
		friend class Car;
		int numCars;
		Car* train;
	public:
		Train(int n);
		Train(const Train &t);
		~Train();
		void fillTrain(std::ifstream *file);
		void findTotals();
		void printTrain();
		void printPicture();
};
#endif