#pragma once
#include <iostream>
#include <vector>

//class Vertex 
//{
//public:
//	std::vector<float> position;
//	std::vector<int> ColorInRGB;
//};

class RenderObject
{
private:
	//std::vector<Vertex> vertices;
	std::string shape;
	std::string color;

public:
	//RenderObject(std::vector<Vertex> vert);
	RenderObject(std::string s, std::string c);
	~RenderObject();

	void PrintInfo();
};

