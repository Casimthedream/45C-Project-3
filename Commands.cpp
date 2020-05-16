#include "HashMap.hpp" 
#include <iostream> 
#include <string> 
#include <boost/algorithm/string.hpp>

std::string create(const std::string& user,const std::string& pass, HashMap& hm) 
{
    if (hm.contains(user) == true)
    {
        return "EXISTS";
    }
    else 
    {
        hm.add(user,pass); 
        return "CREATED";
    }
}

std::string login(const std::string& user,const std::string& pass, const HashMap& hm) 
{
    if (hm.contains(user) == true)
    {
        if (hm.value(user) == pass)
        {
           return "SUCCEEDED"; 
        }
        return "FAILED"; 
    }
    else
    {
       
        return "FAILED"; 
    }
}

std::string remove(const std::string& user, HashMap& hm) 
{
    if (hm.remove(user) == true)
    {
        return "REMOVED";
    }
    return "NONEXISTENT";
}

std::string clear(HashMap& hm)
{
    HashMap temp; 
    hm = temp; 
    return "CLEARED";  
} 

std::string parse(std::string input)
{
    boost::trim_left(input); 
    std::string temp = input.substr(input.find(" ")); 
    return temp;  
}

std::string returnFirst(std::string input)
{
    boost::trim_left(input); 
    std::string temp = input.substr(0, input.find(" ")); 
    return temp;  
}

void commandString(std::string input, HashMap& hm, unsigned int& debug)
{
    try{

    
        std::string command = returnFirst(input);  

        if (command == "CREATE")
        {
            input = parse(input); 
        
            std::string user = returnFirst(input); 
            input = parse(input);
            std::string pass = returnFirst(input); 
        
            std::cout<<create(user,pass,hm)<<std::endl; 


            
        }
        else if (command == "LOGIN")
        {
            input = parse(input); 
            std::string user = returnFirst(input); 
        
            if (user == "COUNT" && debug == 1)
            {
                std::cout<<hm.size()<<std::endl; 
            }
            else if (user == "COUNT" && debug == 0)
            {
                std::cout << "INVLAID" <<std::endl;
            }
            else
            {
                input = parse(input);
                std::string pass = returnFirst(input); 
                std::cout<<login(user,pass,hm)<<std::endl; 
            }
            
        }
        else if (command == "REMOVE")
        {
            input = parse(input);
            std::string user = returnFirst(input);         
            std::cout << remove(user, hm)<<std::endl;
            
        }
        else if (command == "CLEAR")
        {
            std::cout << clear(hm) <<std::endl;
        }
        else if (command == "DEBUG")
        {
            input = parse(input);
            std::string ans = returnFirst(input);   
            if(ans == "ON" && debug == 1)
            {
                std::cout << "ON ALREADY" <<std::endl;
            }
            else if (ans == "ON" && debug == 0)
            {
                debug = 1;
                std::cout << "ON NOW" <<std::endl;
            }
            else if (ans == "OFF" && debug == 1)
            {
                debug = 0;
                std::cout << "OFF NOW" <<std::endl;
            }
            else if (ans == "OFF" && debug == 0)
            {
                std::cout << "OFF ALREADY" <<std::endl;
            }
        }
        else if (command == "BUCKET" && debug == 1)
        {
            std::cout<<hm.bucketCount()<<std::endl; 
        }
        else if (command == "LOAD" && debug == 1)
        {
            std::cout<<hm.loadFactor()<<std::endl; 
        }
        else if (command == "MAX" && debug == 1)
        {
            std::cout<<hm.maxBucketSize()<<std::endl; 
        }
        else if (command == "QUIT")
        {
            return;  
        }
        else
        {
        std::cout << "INVLAID" <<std::endl;
        }
    
    }
    catch(...)
    {
        std::cout << "INVLAID" <<std::endl;
    }
}



