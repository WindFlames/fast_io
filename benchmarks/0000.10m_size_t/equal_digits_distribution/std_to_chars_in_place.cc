#include"../../../include/fast_io_device.h"
#include"../../timer.h"
#include<random>
#include<charconv>

int main()
{
	constexpr std::size_t N{10000000};
	std::vector<std::size_t> values(N);
	std::mt19937_64 eng;
	std::uniform_int_distribution<std::size_t> uind(0,9);
	std::uniform_int_distribution<std::size_t> dist(0, std::numeric_limits<std::size_t>::digits10);
	std::generate(values.begin(), values.end(), [&]()
	{
		std::size_t ret{};
		std::size_t digits{dist(eng)};
		for(std::size_t i{};i!=digits;++i)
			ret=ret*10+uind(eng);
		return ret;
	});
	{
	fast_io::timer t("output");
	fast_io::obuf_file obf("std_to_chars_in_place.txt");
	for(std::size_t i{};i!=N;++i)
	{
		auto ptr{oreserve(obf,25)};
		if(ptr)[[likely]]
		{
			auto [p,ec]=std::to_chars(ptr,ptr+25,values[i]);
			*p=u8'\n';
			orelease(obf,p+1);
		}
		else
		{
			std::array<char,25> array;
			auto [p,ec]=std::to_chars(array.data(),array.data()+array.size(),values[i]);
			*p=u8'\n';
			write(obf,array.data(),++p);
		}
	}
	}
}

/*
output: 0.20100200000000001s
*/