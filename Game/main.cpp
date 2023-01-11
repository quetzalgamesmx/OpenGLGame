#include "MyGame.h"
#include <iostream>
using namespace std;

int main() {

	try {
		MyGame game;
		game.run();
	}
	catch (const exception& e) {
		wclog<< e.what() << std::endl;
		return -1;
	}
	

	return 0;
}