#include "ShapeAndColorConverter.h"

enum Shape {CUBE, PYRAMID};
enum Color {RED, GREEN, BLUE};



std::shared_ptr<RenderObject> ShapeAndColorConverter::GetObject(std::vector<std::string> input)
{
	//std::vector<Vertex> vertices;
	/*Shape s;
	Color c;*/

	std::string shape = "";
	std::string color = "" ;

	for (int i = 0; i < input.size(); i++) {

		if (input.at(i) == "cube" || input.at(i) == "kubus") {
			//s = CUBE;
			shape = "cube";
		}
		else if (input.at(i) == "pyramid" || input.at(i) == "pyramide") {
			//s = PYRAMID;
			shape = "pyramid";
		}

		if (input.at(i) == "red" || input.at(i) == "rood") {
			//c = RED;
			color = "red";
		}
		else if (input.at(i) == "green" || input.at(i) == "groen") {
			//c = GREEN;
			color = "green";
		}
		else if (input.at(i) == "blue" || input.at(i) == "blauw") {
			//c = BLUE;
			color = "blue";
		}


	}

	/*switch (s)
	{
	case CUBE:

		break;
	case PYRAMID:
		break;
	default:
		break;
	}*/
	

	std::shared_ptr<RenderObject> ro = std::make_shared<RenderObject>(shape, color);
	return ro;
}
