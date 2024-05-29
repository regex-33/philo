#include <iostream>
#include <string.h>

//using namespace std;

class cars
{
	public:
		cars(){
			std::cout << "hello tst" << std::endl;
		}
};

int main()
{
	int x = 33, b = 9889;
	cars testtt;
	std::string test = "youssef ";
	std::string hello = "achtatal ";
	std::cout << test.append(hello) << test.length() << std::endl;
	return 0;
}
