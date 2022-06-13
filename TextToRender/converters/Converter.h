#pragma once

#include <iostream>
#include <vector>

#include "../RenderObject.h"



class Converter{

private:
	
public:
	Converter(){};

	virtual std::shared_ptr<RenderObject> GetObject(std::vector<std::string> input) = 0;
};
