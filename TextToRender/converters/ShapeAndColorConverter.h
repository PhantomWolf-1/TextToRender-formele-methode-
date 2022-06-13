#pragma once
#include "Converter.h"

class ShapeAndColorConverter : public Converter
{
private:



public:
	 
	// Inherited via Converter
	virtual std::shared_ptr<RenderObject> GetObject(std::vector<std::string> input) override;

};

