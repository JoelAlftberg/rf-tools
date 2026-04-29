#include "cli/cli.h"

int main(int argc, char* argv[])
{

	cli::CLI cli{argc, argv};

	try{
		cli.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << "\n";
		return 1;
	}

	return 0;
}