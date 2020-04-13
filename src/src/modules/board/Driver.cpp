#include "Driver.h"



Driver::Driver()
{
}


Driver::~Driver()
{
}

void test_winner(GBMap &map_test, Scoring &sc) {
	VGMap villages[4];
	int res_test4[] = { 2, 4, 3, 3 };

	while (map_test.get_no_tile() < 49 - 1)
	{
		map_test.add_tile(6, rand() % 6, res_test4, sc);
		sc.display_res();
	}
	map_test.display_map();

	for (int i = 0; i < 4; i++) {
		villages[i].put_building_sim();
		villages[i].display_village();
	}

	sc.get_winner(villages);
}


int main(int argc, const char * argv[]) 
{
	int players = 4;
	bool shipment[4]{ 0 };

	std::cout << "Number of Players: " << players << std::endl;

	Scoring sc;
	GBMap map_test(players, true, sc);
	int res_test[] = { 3, 1, 1, 3 };
	int res_test0[] = { 3, 2, 1, 3 };
	int res_test1[] = { 1, 1, 1, 1 };
	int res_test2[] = { 2, 2, 2, 2 };
	int res_test3[] = { 3, 3, 3, 3 };
	int res_test4[] = { 2, 4, 3, 3 };
	
	/*map_test.add_tile(3, 2, res_test0, sc);
	map_test.add_tile(2, 3, res_test1, sc);
	map_test.add_tile(3, 4, res_test2, sc);
	map_test.add_tile(4, 3, res_test3, sc);
	map_test.add_tile(3, 3, res_test4, sc);
	sc.display_res();*/
	
	map_test.put_resource_sim(sc);
	std::cout << "total tile: " << map_test.get_no_tile() << std::endl;
	std::cout << "map" << std::endl;
	map_test.display_map();
	int type = 3;
	if(!shipment[1]){
		map_test.add_shipment(4, 1, res_test4, sc, type);
		shipment[1] = true;
	}
	else
		std::cout << "already" << std::endl;
	map_test.display_map();
	sc.display_res();


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