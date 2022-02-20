
#include <iostream>
#include "mysocket.h"

int main() {
	auto server = MySocket();
	
	while (1) {
		server.ConectToServer("192.168.0.105",8888);
	}
	
	return 0;
}
