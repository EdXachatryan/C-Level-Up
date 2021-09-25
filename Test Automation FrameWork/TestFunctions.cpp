#include <stdlib.h>
#include <iostream>

bool testIsEqualZerro()
{
	std::cout << "Starte isEqualZerro test function" << std::endl;
	std::cout << "5 is not equal zerro" << std::endl;
	return false;
}

bool testConnection()
{
	std::cout << "64 bytes from 175.517.100.131: icmp_seq=1 ttl=86 time=85.1 ms" << std::endl;
	std::cout << "64 bytes from 175.517.100.131: icmp_seq=1 ttl=86 time=85.1 ms" << std::endl;
	std::cout << "64 bytes from 175.517.100.131: icmp_seq=1 ttl=86 time=85.1 ms" << std::endl;
	std::cout << "64 bytes from 175.517.100.131: icmp_seq=1 ttl=86 time=85.1 ms" << std::endl;;
	return true;
}

bool testDevidZerro ()
{
	std::cout << "Starte testDevidZerro test function" << std::endl;
	std::cout << "run 5/0" << std::endl;
	std::abort();
}