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

	std::cout << "Number of Players: " << players << std::endl;

	GBMap map_test(players, true);
	int res_test[] = { 3, 1, 1, 3 };
	int res_test0[] = { 3, 3, 3, 3 };
	int res_test1[] = { 1, 1, 1, 1 };
	int res_test2[] = { 3, 3, 3, 3 };
	int res_test3[] = { 3, 3, 3, 3 };
	Scoring sc{};
	map_test.put_resource(3, 2, res_test0, sc);
	map_test.put_resource(2, 3, res_test1, sc);
	map_test.put_resource(3, 4, res_test2, sc);
	map_test.put_resource(4, 3, res_test3, sc);
	map_test.put_resource(3, 3, res_test, sc);
	sc.display_res();
	std::cout << "connected: " << sc.connected(89) << std::endl;
	map_test.display_map();


	VGMap village_test{};
	village_test.put_building_sim();	
	int score_temp = sc.get_score(village_test);
	village_test.display_village();
	std::cout << "village score: " << score_temp << std::endl;


	/*int numbers[3][3] = { 1, 30, 3,
		4, 40, 6,
		7, 50, 9 };


	int* row = numbers[0]; // Decay array to int pointer, pointing to numbers[x][0]
	row++;
	row++;
	
	int(*ptr)[3] = numbers;
	int* my_elem = *numbers;
	my_elem++;
	int(*ptr1)[3] = (int(*)[3]) my_elem;

	std::cout << *my_elem << " ";

	std::cout << **(ptr1+1) << " "; //(ptr1++)

	std::cout << *(*(ptr +1) + 1 ) << " ";

	std::cout << *row << " ";
	std::cout << "\n";*/

	system("pause");
	return 0;
}