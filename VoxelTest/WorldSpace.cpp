#include "WorldSpace.h"
#include <sstream>

using namespace std;

//constructor
WorldSpace::WorldSpace()
{

}



//inspector
float WorldSpace::getXSize()
{
	return X_.size();
}

float WorldSpace::getYSize()
{
	return Y_.size();
}

float WorldSpace::getZSize()
{
	return Z_.size();
}

WorldLocation WorldSpace::getWorldPoint(int X, int Y, int Z)
{

}

//mutator
void WorldSpace::setXSize(float input)
{
	X_.resize(input);
}

void WorldSpace::setYSize(float input)
{
	Y_.resize(input);
}

void WorldSpace::setZSize(float input)
{
	Z_.resize(input);
}


//facilitator
std::string WorldSpace::ShowWorldSize()
{
	stringstream ss;
	ss << getXSize() << ", " << getYSize() << ", " << getZSize();

	return ss.str();
}