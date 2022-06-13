#include "RenderObject.h"





RenderObject::RenderObject(std::string s, std::string c) : shape (s), color(c)
{

}

RenderObject::~RenderObject()
{
}

void RenderObject::PrintInfo()
{
	std::cout << "RenderObject " << shape << ", with the color: " << color << std::endl;
}
