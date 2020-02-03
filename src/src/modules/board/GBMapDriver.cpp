#include "GBMapDriver.h"



GBMapDriver::GBMapDriver()
{
}


GBMapDriver::~GBMapDriver()
{
}

int main(int argc, const char * argv[]) {

	int id = 11;
	int players = 4;

	/*GBMap map1(&id, &players);

	std::cout << "Board ID: " << map1.getIdAddress() << std::endl;
	std::cout << "Number of Players: " << map1.getNumberOfPlayers() << std::endl;*/

	std::cout << "Number of Players: " << players << std::endl;

	GBMap map_test(players, true);
	int res_test[] = { 2, 2, 2, 2 };
	Scoring sc{};
	map_test.put_resource(3, 3, res_test, sc);
	sc.display_res();
	map_test.display_map();

	int numbers[3][3] = { 1, 30, 3,
		4, 40, 6,
		7, 50, 9 };


	int* row = numbers[0]; // Decay array to int pointer, pointing to numbers[x][0]
	row++;
	row++;

	int(*ptr)[3] = numbers;

	std::cout << *(*(ptr +1) + 1 ) << " ";

	std::cout << *row << " ";
	std::cout << "\n";

	system("pause");
	return 0;
}