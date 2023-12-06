
#include <iostream> 
#include <fstream> 
#include <regex> 
#include <string> 
#include <sstream>
#include <cstring> 
#include <format>

struct cubeCounts
{
    int blue{};
    int green{};
    int red{};

    bool checkValidity()
    {
        return blue <= 14 && green <= 13 && red <= 12;
    }

    void reset()
    {
        blue = 0; 
        green = 0;
        red = 0;
    }
};

int
main()
{
    std::fstream file("Inputs/Day2Input.txt");
    std::string line;
    int sum = 0;

    //just track game ID by hand instead of parseing it
    int id = 1;

    //matching against "# b" for the pattern for blue count, same with red/green. 
    //Saving semicolons to differentiate trials
    std::regex exp ("(\\d+ (b|r|g))|;");
    while (std::getline(file, line, '\n'))
    {
        cubeCounts cubes;
        std::sregex_iterator begin(line.begin(), line.end(), exp);
        std::sregex_iterator end;
        std::cout << std::format("Does begin equal end? {}\n", begin == end);
        while(begin != end)
        {
            std::string token = (*begin).str();
            std::cout << std::format("Token is: {}\n", token) << std::endl;
            if(token.length() <= 1)
            {
                //if we reach a semicolon and there are too many of one kind of cube
                if(!cubes.checkValidity()) break;
                //if input to this point is valid
                cubes.reset();
                std::advance(begin, 1);
                continue;
            }
            //if not a delimiter, figure out which kind of cube it is and add that amount
            std::string num; std::string color; 
            sscanf(token.c_str(), " ", num.data(), color.data());
            std::cout << std::format("X{}X    X{}X\n",std::string(num), std::string(color));
            if(strcmp(color.c_str(), "b") == 0)
            {
                std::cout << "inside blue" << std::endl;
                cubes.blue = std::stoi(std::string(num));
            } 
            else if(strcmp(color.c_str(), "r") == 0)
            {
                std::cout << "inside red" << std::endl;
                cubes.red = std::stoi(num);
            }
            else 
            {
                std::cout << "inside green" << std::endl;
                cubes.green = std::stoi(std::string(num));
            }
            std::advance(begin, 1);
        }
        sum += id * cubes.checkValidity();
        ++id; 
    }
    std::cout << sum << std::endl;
}