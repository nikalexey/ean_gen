#include <tchar.h>
#include <stdint.h>
#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <ctime>

std::vector<uint8_t> GetBarcode()
{
	std::vector<uint8_t> ean(13);
	ean[0] = 2;
	ean[1] = 1;
	ean[2] = 7;
	for(int i = 3; i < 12; i++)
	{
		ean[i] = std::rand() % 9;
	}

	int sum {0};
	for(int i = 0; i < 12; i++)
	{
		sum += (i % 2) ? (ean[i] * 3) 
		               : (ean[i]);
	}
	ean[12] = (10 - sum % 10) % 10;
	return ean;
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc != 2)
	{
		std::wcout << L"Usage: " << argv[0] << L" <num>" << std::endl;
		return 1;
	}
	try
	{
		std::srand( static_cast<uint32_t>( std::time(0) ) );

		uint32_t count { static_cast<uint32_t>(std::stoi(argv[1])) };
		std::set<std::vector<uint8_t>> eans;
		do
		{
			auto ean = GetBarcode();
			eans.insert(ean);
		} while ( eans.size() < count );
		
		for(auto ean: eans)
		{
			for(auto dig: ean)
			{
				std::cout << static_cast<int>(dig);
			}
			std::cout << std::endl;
		}
	}
	catch (const std::exception& ex)
	{
		std::cerr << "exception what = '" << ex.what() << "'" << std::endl;
	}

	return 0;
}

