#pragma once

void show_matches_reg(std::string str, std::regex reg) {
	std::sregex_iterator currMatch(str.begin(), str.end(), reg);
	std::sregex_iterator lastMatch;

	for (auto i = currMatch; i != lastMatch; ++i) {
		std::smatch match = *i;
		std::string s = match.str();
		std::cout << s << "\n";
	}
	std::cout << "\n";
}

void push_matches_vec(std::string str, std::regex reg, std::vector<int> &vec) {
	std::sregex_iterator currMatch(str.begin(), str.end(), reg);
	std::sregex_iterator lastMatch;

	for (auto i = currMatch; i != lastMatch; ++i) { //std::sregex_iterator
		std::smatch match = *i;

		std::string s = match.str();
		int in = std::stoi(s);

		//std::cout << s << "\n";

		vec.push_back(in);
	}
}

void push_matches_vec(std::string str, std::regex reg, std::vector<std::string> &vec) {
	std::sregex_iterator currMatch(str.begin(), str.end(), reg);
	std::sregex_iterator lastMatch;

	for (auto i = currMatch; i != lastMatch; ++i) { //std::sregex_iterator
		std::smatch match = *i;
		std::string s = match.str();
		vec.push_back(s);
	}
}

std::string init_mask(int maskCount) {
	std::bitset<32> mask;
	for (int i = 31; i > 31 - maskCount; i--) { // - maskFromVec
		mask |= 1UL << i;
	}
	std::string str = mask.to_string();
	str.insert(8, ".");
	str.insert(17, ".");
	str.insert(26, ".");
	return str;
}

int get_mask(std::vector<int> &vec) {
	int retVal;
	if (vec.size() == 5) {
		retVal = vec.back();
		vec.pop_back();
	}
	else {
		std::cout << "Vector does not contain 5 elements => no mask";
	}
	return retVal;
}

std::string print_decimal(std::vector<int> vecInt) {
	std::string retVal = "";
	for (int &i : vecInt) {
		retVal = retVal+std::to_string(i)+".";
	}
	retVal.pop_back();
	return retVal;
}

std::string print_decimal(std::vector<unsigned long> vecInt) {
	std::string retVal = "";
	for (auto &i : vecInt) {
		retVal = retVal + std::to_string(i) + ".";
	}
	retVal.pop_back();
	return retVal;
}

std::string print_binary(std::vector<int> vecInt) {
	std::string retVal = "";
	for (int &i : vecInt) {
		std::bitset<8> bset2(i);
		retVal = retVal + bset2.to_string() + ".";
	}
	retVal.pop_back();
	return retVal;
}

std::string print_binary(std::vector<unsigned long> vecInt) {
	std::string retVal = "";
	for (auto &i : vecInt) {
		std::bitset<8> bset2(i);
		retVal = retVal + bset2.to_string() + ".";
	}
	retVal.pop_back();
	return retVal;
}

std::vector<unsigned long> convertMask(std::vector<std::string> &vec) {
	std::vector<unsigned long> retVec;
	for (auto &j : vec) {
		unsigned long value = std::bitset<64>(j).to_ulong();
		retVec.push_back(value);
		//std::cout << j << " ";
	}
	return retVec;
}

std::vector<int> netIP(std::vector<int> host, std::vector<unsigned long> mask) {
	//std::cout << "\nIp of the network: ";
	std::vector<int> retVec;
	for (int i = 0; i < 4; i++) {
		int a = host.at(i);// & vecUnsigned.at(0) vector ma hosta
		int b = mask.at(i); //vecunisgnet ma maske

		int res = a;
		res = res & b;
		//should be
		//a = a &b; cout a, ale pozniej to sprawdze, czy na pewno bo tak dziala legit 
		//std::cout << res << ".";
		retVec.push_back(res);
	}
	return retVec;
}

std::vector<int> broadcastIP(std::vector<int> net, std::vector<unsigned long> mask) {
	//std::cout << "\nIp of the broadcast: ";
	std::vector<int> retVec;
	for (int i = 0; i < 4; i++) {
		int a = net.at(i);
		int b = mask.at(i);
		b = ~b;
		b += 256;
		b += a;
		retVec.push_back(b);
	}
	return retVec;
}

long int max_host(int mask) {
	return pow(2, 32 - mask) - 2;
}

void first_host(std::vector <int> netVec) {
	netVec.at(netVec.size() - 1) += 1;
	netVec.at(netVec.size() - 1) %= 256;
	std::cout << "First Host IP in dec: " << print_decimal(netVec) << "\n";
	std::cout << "First Host IP in bin: " << print_binary(netVec) << "\n\n";
}

void last_host(std::vector<int> broadcastVec) {
	broadcastVec.at(broadcastVec.size() - 1) -= 1;
	std::cout << "Last Host IP in dec: " << print_decimal(broadcastVec) << "\n";
	std::cout << "Last Host IP in bin: " << print_binary(broadcastVec) << "\n\n";
}

char network_class(std::vector<int> ip) {
	if (ip.at(0) < 128)
		return 'A';
	else if (ip.at(0) < 192)
		return 'B';
	else if (ip.at(0) < 224)
		return 'C';
	else if (ip.at(0) < 240)
		return 'D';
	else
		return 'E';
}

bool check_if_good(std::vector <int> vec) {
	if (!(vec.at(0) > 0 && vec.at(0) <= 255))
		return false;
	if (!(vec.at(1) > 0 && vec.at(1) <= 255))
		return false;
	if (!(vec.at(2) > 0 && vec.at(2) <= 255))
		return false;
	if (!(vec.at(3) > 0 && vec.at(3) <= 255))
		return false;
	if (!(vec.at(4) > 0 && vec.at(4) <= 32))
		return false;
	return true;
}

std::string set_ip(int argc, char **argv) {
	if (argc == 1)
		return "172.16.160.200/18"; //172.16.160.200/24 192.168.1.145/25
	else if (argc == 2)
		return argv[1];
}

void ping_host(std::vector<int> addres) {
	char x;
	std::cout << "Do you want to ping " << print_decimal(addres) << "?[Y/n]\n";
	std::cin >> x;
	if (x == 'Y' || x == 'y') {
		std::string toPing = "ping " + print_decimal(addres);
		system(toPing.c_str());
	}
	else if (x == 'n' || x == 'N') {
		std::cout << "You decieded no to ping " << print_decimal(addres) << "\n";
	}
	else return;
}

bool is_private(std::vector<int> addres) {
	if ((addres.at(0) == 10) || ((addres.at(0) == 172) && (16 <= addres.at(1) <= 31))
		|| ((addres.at(0) == 192) && (addres.at(1) == 168))) 
			return true;
	else return false;
}