#include <iostream> 
#include "HashMap.hpp"
#include <string>
#include "usercom.hpp"

int main()
{
    std::string input;
    HashMap hm;
    unsigned int debug = 0; //Start with debgger off 
    while(input != "QUIT")
    {
        std::getline(std::cin, input, '\n');
        commandString(input, hm, debug);

    }
    std::cout << "GOODBYE" << std::endl;
    
   

    return 0;
}
