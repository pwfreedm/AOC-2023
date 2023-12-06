
#include <cstdint>
#include <fstream>
#include <iterator>
#include <iostream>
#include <string>
#include <regex>
#include <format>


const static std::vector nums = {"0","one","two","three","four","five","six","seven","eight","nine"};

int
findValue(std::string &line, std::regex &exp);

int main()
{
    std::fstream file("Inputs/Day1Input.txt");
    std::string line;
    int sum = 0;
    while (std::getline(file, line, '\n'))
    {
       std::regex forward("\\d|one|two|three|four|five|six|seven|eight|nine");
       std::regex backward("\\d|eno|owt|eerht|ruof|evif|xis|neves|thgie|enin");

       int firstNum = findValue(line, forward);
       std::reverse(line.begin(), line.end());
       int secondNum = findValue(line, backward);

       sum += firstNum * 10 + secondNum;
    }
    std::cout << sum << std::endl;
}

/** Searches a string for the first number that appears as either a digit or
    its text name. 
    
    @param line - the line of text to search
*/
int
findValue(std::string &line, std::regex &exp)
{
    auto beg = std::sregex_iterator(line.begin(), line.end(), exp);
    auto end = std::sregex_iterator();

    std::string val = (*beg).str();
    auto strToN = std::find(nums.begin(), nums.end(), val);
    
    //reverse the input if it is a word not in nums, then check again
    if(val.length() > 1 && strToN == nums.end())
    {
        std::reverse(val.begin(), val.end());
        strToN = std::find(nums.begin(), nums.end(), val);
    }

    return val.length() > 1 ? std::distance(nums.begin(),strToN) : stoi(val);
}