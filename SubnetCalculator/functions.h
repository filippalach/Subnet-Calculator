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

		std::cout << s << "\n";

		vec.push_back(in);
	}
}

void show_matches_string(std::string str, std::regex reg, std::vector<std::string> &vec) {
	std::sregex_iterator currMatch(str.begin(), str.end(), reg);
	std::sregex_iterator lastMatch;

	for (auto i = currMatch; i != lastMatch; ++i) { //std::sregex_iterator
		std::smatch match = *i;
		std::string s = match.str();
		std::cout << s << "\n";
		vec.push_back(s);
		//std::cout << match.format(" $& ") << "\n";
		//std::cout << match.str();
	}
	std::cout << "\n";
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

void printHostDec(std::vector<int> vecInt) {
	std::cout << "\nPrinting Host IP(Decimal representaion): ";
	for (int &i : vecInt) {
		//std::bitset<8> bset2(i);
		std::cout << i << ".";
		//std::cout << "Binary representaion: " << bset2 << "\n";
	}
	std::cout << "\n";
}

void printHostBinary(std::vector<int> vecInt) {
	std::cout << "\nPrinting Host IP(Binary representaion): ";
	for (int &i : vecInt) {
		std::bitset<8> bset2(i);
		std::cout << bset2 << ".";
	}
	std::cout << "\n";
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

void netIP(std::vector<int> host, std::vector<unsigned long> mask) {
	std::cout << "\nIp of the network: ";
	for (int i = 0; i < 4; i++) {
		int a = host.at(i);// & vecUnsigned.at(0) vector ma hosta
		int b = mask.at(i); //vecunisgnet ma maske

		int res = a;
		res = res & b;
		//should be
		//a = a &b; cout a, ale pozniej to sprawdze, czy na pewno bo tak dziala legit 
		std::cout << res << ".";
	}
}

void broadcastIP(std::vector<int> host, std::vector<unsigned long> mask) {
	std::cout << "\nIp of the broadcast: ";
	for (int i = 0; i < 4; i++) {
		int a = host.at(i);
		int b = mask.at(i); //vecunisgnet ma maske 11111111 11111111 11000000 00000000
		//std::cout << b << " ";
												// 00000000 00000000 00111111 11111111
		b = ~b;
		b += 256;//should be
		b += a;
		b = b % 256;
		//a = a &b; cout a, ale pozniej to sprawdze, czy na pewno bo tak dziala legit
		std::cout << b << ".";
	}
}