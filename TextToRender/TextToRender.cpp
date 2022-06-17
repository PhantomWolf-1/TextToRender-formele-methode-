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



void TestApplication()
{
    std::string englishGrammar = "grammar.txt";
    std::string dutchGrammar = "grammatica.txt";

    Grammar* g = new Grammar(dutchGrammar);
    NDFA ndfa = NDFA(*g);
    if (ndfa.CreateNDFA()) {
            ndfa.TurnToDFA();
     }

    std::string testInput1 = "ik wil de vorm kubus met de kleur rood";
    std::string testInput2 = "vorm kubus kleur blauw";
    std::string testInput3 = "ik wil een groene bol";
    std::string testInput4 = "Ik wil de vorm pyramide met de kleur groen, maar toch wil ik gaan voor de vorm kubus aangezien die bij de kleur mooier is";

    ndfa.LoopThroughModel(testInput1);
    ndfa.PrintCurrentState();
    if (ndfa.IsCurrentStateFinal())
        std::cout << "Input 1 is valid" << std::endl;
    else
        std::cout << "Input 1 is invalid" << std::endl;
    ndfa.ResetValues();

    ndfa.LoopThroughModel(testInput2);
    ndfa.PrintCurrentState();
    if (ndfa.IsCurrentStateFinal())
        std::cout << "Input 2 is valid" << std::endl;
    else
        std::cout << "Input 2 is invalid" << std::endl;
    ndfa.ResetValues();

    ndfa.LoopThroughModel(testInput3);
    ndfa.PrintCurrentState();
    if (ndfa.IsCurrentStateFinal())
        std::cout << "Input 3 is valid" << std::endl;
    else
        std::cout << "Input 3 is invalid" << std::endl;
    ndfa.ResetValues();

    ndfa.LoopThroughModel(testInput4);
    ndfa.PrintCurrentState();
    if (ndfa.IsCurrentStateFinal())
        std::cout << "Input 4 is valid" << std::endl;
    else
        std::cout << "Input 4 is invalid" << std::endl;
    ndfa.ResetValues();

}


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

    ndfa.LoopThroughModel(input);
    ndfa.PrintCurrentState();
    ShapeAndColorConverter conv = ShapeAndColorConverter();
    std::shared_ptr<RenderObject> ro = conv.GetObject(ndfa.GetTransitionsMade());
    std::cout << "Object made: ";
    ro->PrintInfo();
    std::cout << std::endl;

    ndfa.ResetValues();

    delete g;
    g = NULL;

    //TestApplication();
}





