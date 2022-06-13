// TextToRender.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include "Grammar.h"
#include "NDFA.h"
#include "converters/ShapeAndColorConverter.h"

#include <sstream>
#include <algorithm>
#include <iterator>

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
    NDFA ndfa = NDFA(*g);
    if (ndfa.CreateNDFA()) {
        ndfa.TurnToDFA();
    }
    ndfa.PrintModel();
    std::cout << std::endl;

    std::cout << "Final check to see if the DFA is determenistic, is it? " << ndfa.isDetermenistic() << std::endl;
    //ndfa.PrintModel();
    //KEEP IN MIND, PREVENT MEMMORY LEAKS ETC!

    std::cout << "type in the input: \n";
    std::string input;
    std::getline(std::cin >> std::ws, input);
    std::cout << std::endl;
    
    std::cout << "Input length: " << input.length() << std::endl;

    std::string tmp = "";
    for (int i = 0; i < input.length(); i++) {
        if (input.at(i) != ' ' && input.at(i) != ',' && input.at(i) != '.') {
            std::cout << "input added:" << input.at(i) << "..." << std::endl;
            tmp += input.at(i);
        }
            

        if ((input.at(i) == ' ' || input.at(i) == ',' || input.at(i) == '.' || i == input.length()-1) && tmp.length() != 0) {
            if (tmp != "") {
                std::cout << "Check for the word:"<< tmp  << "..." << std::endl;
                ndfa.CheckForNextState(tmp);
                tmp = "";
            }
        }
        
    }
    ndfa.PrintCurrentState();
    ShapeAndColorConverter conv = ShapeAndColorConverter();
    std::shared_ptr<RenderObject> ro = conv.GetObject(ndfa.GetTransitionsMade());
    std::cout << "Object made: ";
    ro->PrintInfo();
    std::cout << std::endl;

    delete g;
    g = NULL;
}

