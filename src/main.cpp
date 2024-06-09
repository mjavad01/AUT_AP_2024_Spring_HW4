#include <gtest/gtest.h>

#include <iostream>

#include "message.h"
#include "server.h"
#include "stl.h"
#include "user.h"

int main(int argc, char **argv) {
	if (false)	// make false to run unit-tests
	{
		// Server server;
		// User david = server.create_user("david");
		// User jenifer = server.create_user("jenifer");
		// bool result = david.send_voice_message("jenifer");
		// std::cout<< result << std::endl;

	} else {
		::testing::InitGoogleTest(&argc, argv);
		std::cout << "RUNNING TESTS ..." << std::endl;
		int ret{RUN_ALL_TESTS()};
		if (!ret)
			std::cout << "<<<SUCCESS>>>" << std::endl;
		else
			std::cout << "FAILED" << std::endl;
	}
	return 0;
}