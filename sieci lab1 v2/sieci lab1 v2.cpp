#include "pch.h"
#include <iostream>
#include <regex>
#include <bitset>
#include <vector>
#include <cstdlib> 

void show_matches(std::string str, std::regex reg) {
	std::sregex_iterator currMatch(str.begin(), str.end(), reg);
	std::sregex_iterator lastMatch;

	for (auto i = currMatch; i != lastMatch; ++i) { //std::sregex_iterator
		std::smatch match = *i;
		std::string s = match.str();
		std::cout << s << "\n";
		//std::cout << match.format(" $& ") << "\n";
		//std::cout << match.str();
	}
	std::cout << "\n";
}

void show_matches(std::string str, std::regex reg, std::vector<int> &vec) {
	std::sregex_iterator currMatch(str.begin(), str.end(), reg);
	std::sregex_iterator lastMatch;

	for (auto i = currMatch; i != lastMatch; ++i) { //std::sregex_iterator
		std::smatch match = *i;
		std::string s = match.str();
		int in = std::stoi(s);
		std::cout << s << "\n";
		vec.push_back(in);
		//std::cout << match.format(" $& ") << "\n";
		//std::cout << match.str();
	}
	std::cout << "\n";
}

void show_matches2(std::string str, std::regex reg, std::vector<std::string> &vec) {
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

int main()
{
	std::string ip = "172.16.160.200/16";
	std::regex regIp(R"(([0-9]{1,3}).([0-9]{1,3}).([0-9]{1,3}).([0-9]{1,3})/([0-9]+))");
	show_matches(ip, regIp);

	std::regex regIp2(R"([0-9]{1,3})");
	show_matches(ip, regIp2);

	int a = 145;
	int b = 128;
	a = a & b;

	std::bitset<8> bset(a);

	std::cout << "\na po andowaniu: " << a;
	std::cout << "\na po andowaniu ale w 10tnym" << bset.to_ulong();
	std::cout << "\na po andowaniu ale w dwojkowym" << bset << "\n";

	std::vector<int> vector;
	show_matches(ip, regIp2, vector);
	int maskFromVec = vector.back();
	vector.pop_back();
	std::cout << "Vecotr: \n";
	
	for (int &i : vector) {
		std::bitset<8> bset2(i);
		std::cout << "Dwojkowo: "<<i << " ";
		std::cout << "Binarnie: "<<bset2 << "\n";
	}
	std::bitset<32> mask2(0);
	std::cout << mask2 << "\n";

	for (int i = 31; i > 31 - maskFromVec; i--) { // - maskFromVec
		mask2 |= 1UL << i;
	}
	std::cout << mask2;

	std::string xd = mask2.to_string();
	std::cout << "\n" << xd;
	

	int sizeOfString = std::size(xd);
	xd.insert(8, ".");
	xd.insert(17, ".");
	xd.insert(26, ".");
	
	std::vector<std::string> vec2;
	std::vector<int> vec22;
	std::cout << "\n" << xd << "\n";
	std::regex regMask(R"(([0-1]{8}))");
	show_matches2(xd, regMask,vec2);


	std::vector<unsigned long> vecUnsigned;


	std::cout << "Vector w binarnym:: \n\n";
	for (auto &j : vec2) {
			//int integer = std::stoi(j);
			//std::bitset<8> bset22(std::stoi(j));
			//std::cout << "Dwojkowo: " << integer << " ";
			//std::cout << "Binarnie: " << bset22 << "\n";
		unsigned long value = std::bitset<64>(j).to_ulong();
		vecUnsigned.push_back(value);
		std::cout << j << " ";
	}
	std::cout << "Wektor w dziesitnym: \n";
	//std::cout << "test wektor: " << vec2.at(2);
	for (auto k : vecUnsigned) {
		std::cout << k << " ";
	}

	/*show_matches(xd, regMask,vec22);
	std::cout << "Vector:: \n\n";
	for (auto j : vec22) {
			//int integer = std::stoi(j);
			std::bitset<8> bset22(j);
			std::cout << "Dwojkowo: " << j << " ";
			std::cout << "Binarnie: " << bset22 << "\n";
	}*/

	/*std::string  test= "1101";
	unsigned long value = std::bitset<64>(test).to_ulong();
	std::cout << value << std::endl;*/
	
	std::cout << "\n\n\n";
	vecUnsigned.at(2) = 192;
	//test adresu sieci
	for (int i = 0; i < 4; i++) {
		int a = vector.at(i);// & vecUnsigned.at(0)
		//std::cout << "host: " << a << "\n";
		int b = vecUnsigned.at(i);
		//std::cout << "Maska: " << b << "\n";
		int res = a;
		res = res & b;
		
		std::cout << res << ".";
	}
	

}
