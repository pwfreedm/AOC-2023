
#include <cstdint>
#include <fstream>
#include <iterator>
#include <iostream>
#include <string>
#include <regex>
#include <format>

int main()
{
    std::fstream file("/Inputs/Day1Input.txt");
    std::string line;
    int sum = 0;
    std::vector nums = {"0","one","two","three","four","five","six","seven","eight","nine"};
    while (std::getline(file, line, '\n'))
    {
       //find all values, put them in the range [beg, end)
       std::regex exp("\\d|one|two|three|four|five|six|seven|eight|nine");
       auto beg = std::sregex_iterator(line.begin(), line.end(), exp);
       auto end = std::sregex_iterator();

       int toAdv = std::distance(beg, end) - 1;
       std::string val = (*beg).str();
       auto strToN = std::find(nums.begin(), nums.end(), val);
       int fv = val.length() > 1 ? std::distance(nums.begin(),strToN) : stoi(val);
       std::advance(beg, toAdv);
       val = (*beg).str();
       strToN = std::find(nums.begin(), nums.end(), val);
       int sv = val.length() > 1 ? std::distance(nums.begin(),strToN) : stoi(val);

       sum += fv * 10 + sv;
    }
    std::cout << sum << std::endl;
}