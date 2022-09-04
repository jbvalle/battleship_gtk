	sudo apt -y install gcc-9 g++-9 &&
	sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 9 &&
	sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-9 9 &&
	sudo update-alternatives --config gcc &&
	sudo update-alternatives --config g++
