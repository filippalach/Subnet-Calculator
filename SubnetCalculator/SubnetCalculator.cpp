#include "pch.h"
#include "functions.h"

int main(int argc, char **argv)
{
	std::string ip=set_ip(argc,argv);

	std::regex regIpMask(R"(([0-9]{1,3}).([0-9]{1,3}).([0-9]{1,3}).([0-9]{1,3})/([0-9]+))");

	show_matches_reg(ip, regIpMask);

	std::regex regIp(R"([0-9]{1,3})");

	show_matches_reg(ip, regIp);

	std::vector<int> adressInt;

	push_matches_vec(ip, regIp, adressInt);

	if (check_if_good(adressInt))
		std::cout << "\nGiven addres is valid\n";
	else {
		std::cout << "\nGiven address is not valid\n";
		return 1;
	}

	int maskFromVec = get_mask(adressInt);

	std::cout << "Decimal Host: " << print_decimal(adressInt) << "\n";
	std::cout << "Binary Host: " << print_binary(adressInt) << "\n";

	std::string parsed = init_mask(maskFromVec);
	//std::cout << "\nMask represented in binary: " << parsed << "\n";

	std::vector<std::string> adressString; //vec2 jest w binarnych stringach
	std::regex regMask(R"(([0-1]{8}))");
	push_matches_vec(parsed, regMask, adressString);

	std::vector<unsigned long> addresULong; //przechowa forme dzieisaetna z maski
	addresULong = convertMask(adressString); //konwersja do dziesietnego ze stringa

	std::cout << "\nMask addres in dec: " << print_decimal(addresULong) << "\n";
	std::cout << "Mask addres in bin: " << print_binary(addresULong) << "\n\n";

	std::vector<int> net;
	net = netIP(adressInt, addresULong);

	std::cout << "Network IP in dec is: " << print_decimal(net) << "\n";
	std::cout << "Network IP in bin is: " << print_binary(net) << "\n\n";

	std::vector<int> broadcast;
	broadcast = broadcastIP(net, addresULong);

	std::cout << "Bradcast adress in dec: " << print_decimal(broadcast) << "\n";
	std::cout << "Bradcast adress in bin: " << print_binary(broadcast) << "\n\n";

	std::cout << "Max amout of hosts is: " << max_host(maskFromVec) << "\n\n";

	first_host(net);
	last_host(broadcast);

	std::cout << "Network Class is: " << network_class(adressInt) << "\n";
	std::cout << "Ip addres is private: " << is_private(adressInt) << "\n";

	ping_host(adressInt);

	system("PAUSE");
}