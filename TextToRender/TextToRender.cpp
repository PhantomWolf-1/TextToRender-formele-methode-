// TextToRender.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include "Grammar.h"

int main()
{
    std::string fileName = "";
    while (fileName == "")
    {
        std::cout << "Language (dutch/nederlands, english/engels):\n";
        std::string language;
        std::cin >> language;
        std::cout << std::endl;
        std::for_each(language.begin(), language.end(), [](char& c) {
            //std::cout << "In lower case" << std::endl;
            c = ::tolower(c);
            });

        
        if (language == "dutch" || language == "nederlands") {
            fileName = "grammatica.txt";
        }
        else if (language == "english" || language == "engels") {
            fileName = "grammar.txt";
        }
        else {
            std::cout << "Language not valid..." << std::endl;
        }
    }

    Grammar *g = new Grammar(fileName);
    //KEEP IN MIND, PREVENT MEMMORY LEAKS ETC!
    delete g;
    g = NULL;

    //TODO:
    //  - look at the basics of making a ndfa based on a grammar (examples from Hans on Brightspace)!!!!!!!!!!!!!
    //  - look at the keywords written at the .txt file which i need to use to make the ndfa and eventually the DFA
}

