#include <iostream>
#include <string>
#include <map>

int main(void)
{
    std::map<int, std::string> words;
    
    words.insert(std::make_pair(3, "carrot"));
    words.insert(std::make_pair(1, "apple"));
    words.insert(std::make_pair(152, "apple"));
    words.insert(std::make_pair(2, "banana"));
    words.insert(std::make_pair(-232, "banana"));

    for (std::map<int, std::string>::iterator it = words.begin(); it != words.end(); ++it)
        std::cout << it->first << "\n";
    return 0;
}