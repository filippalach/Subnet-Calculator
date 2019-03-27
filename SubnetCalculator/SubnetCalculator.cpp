#include "pch.h"
#include "functions.h"

int main()
{
	std::string ip = "172.16.160.200/24";

	std::regex regIp(R"(([0-9]{1,3}).([0-9]{1,3}).([0-9]{1,3}).([0-9]{1,3})/([0-9]+))");

	show_matches_reg(ip, regIp);

	std::regex regIp2(R"([0-9]{1,3})");

	show_matches_reg(ip, regIp2);

	std::vector<int> vector;

	push_matches_vec(ip, regIp2, vector);

	int maskFromVec = get_mask(vector); // zgarnam info o masce i popuje ostatni elemtn i mam 4
	//std::cout << "maska: " << maskFromVec << "\n";
	//std::cout << "size: " << vector.size() << "\n";
	//vector.pop_back();
	//std::cout << "size2: " << vector.size() << "\n";
	//std::cout << "Vecotr: \n";

	/*for (int &i : vector) {
		std::bitset<8> bset2(i);
		std::cout << "Dziesietnie: "<<i << " ";
		std::cout << "Binarnie: "<<bset2 << "\n";
	}*/
	printHostDec(vector);
	printHostBinary(vector);
	/*std::bitset<32> mask2(0);
	std::cout << mask2 << "\n";

	for (int i = 31; i > 31 - maskFromVec; i--) { // - maskFromVec
		mask2 |= 1UL << i;
	}
	std::cout << mask2;*/

	//std::bitset<32> maska;
	std::string parsed = init_mask(maskFromVec);
	std::cout << "\nparsed string: " << parsed << "\n";
	//std::string xd = maska.to_string();

	//std::cout << "maska: "<<xd;

	//std::string xd = mask2.to_string();
	//std::cout << "\n" << xd;


	//int sizeOfString = std::size(xd);
	//xd.insert(8, ".");
	//xd.insert(17, ".");
	//xd.insert(26, ".");

	std::vector<std::string> vec2; //vec2 jest w binarnych stringach
	std::vector<int> vec22;
	//std::cout << "\n" << xd << "\n";

	std::regex regMask(R"(([0-1]{8}))");
	show_matches_string(parsed, regMask, vec2);

	std::vector<unsigned long> vecUnsigned; //string sparsowany na inty - dzieisetna reprezentacja

	std::cout << "Vector w binarnym:: \n\n";
	for (auto j : vec2) {
		std::cout << j << " ";
	}
	/*for (auto &j : vec2) { //vec 2 to nie maska
			//int integer = std::stoi(j);
			//std::bitset<8> bset22(std::stoi(j));
			//std::cout << "Dwojkowo: " << integer << " ";
			//std::cout << "Binarnie: " << bset22 << "\n";
		unsigned long value = std::bitset<64>(j).to_ulong();
		vecUnsigned.push_back(value);
		std::cout << j << " ";
	}*/
	vecUnsigned = convertMask(vec2);
	std::cout << "\nWektor w dziesitnym: \n";
	//std::cout << "test wektor: " << vec2.at(2);
	for (int i : vecUnsigned) {
		std::cout << i << " ";
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

	//vecUnsigned.at(2) = 192;

	//test adresu sieci
	/*for (int i = 0; i < 4; i++) {
		int a = vector.at(i);// & vecUnsigned.at(0) vector ma hosta
		//std::cout << "host: " << a << "\n";
		int b = vecUnsigned.at(i); //vecunisgnet ma maske
		//std::cout << "Maska: " << b << "\n";
		int res = a;
		res = res & b;

		std::cout << res << ".";
	}*/
	netIP(vector, vecUnsigned);
	broadcastIP(vector, vecUnsigned);
}