#include "MainManager.hpp"

int main()
{
	try
	{
		MainManager m;
		m.mainFunction();
	}
	catch (const std::exception& error)
	{
		std::cout << "Blad! " << error.what() << std::endl;
	}
}
