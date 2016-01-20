#ifndef WORLDSPACE_H
#define WORLDSPACE_H

#include <string>
#include <vector>
#include "WorldLocation.h"

using namespace std;



class WorldSpace
{
public:
	//constructor
	class WorldSpace
		();


	//inspector
	float getXSize();
	float getYSize();
	float getZSize();

	WorldLocation getWorldPoint(int X, int Y, int Z);

	//mutator
	void setXSize(float input);
	void setYSize(float input);
	void setZSize(float input);

	//facilitator
	std::string ShowWorldSize();


private:
	vector<WorldLocation> X_;
	vector<WorldLocation> Y_;
	vector<WorldLocation> Z_;
};



#endif // WORLDLOCATION_H