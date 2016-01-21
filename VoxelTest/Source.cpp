/*
// Currently we have a basic vertex generator and a solver for the quads
// Quad solver is not optimized, still drawing unseen quads

*/

#include <vector>
#include <iostream>

using namespace std;




struct Vertex  //vertex struct - quick and dirty structs :D
{
	int x, y, z;
};


struct Face
{
	Vertex Points[4];
	int QuadLoc[4];
};



//global variables
vector<Vertex> PointList;
bool NoQuad = false;
bool MoveToNext = false;
bool AllThreeTrue;
vector<int> QuadList;
Vertex StartPoint = { 0, 0, 0 };
Vertex CurrentPoint = StartPoint;
int GetID[4];
int GetIntersect[12];
int GridNum =3;
vector<Face> FaceList;



//prototypes
void CreateVerticies();
bool GetQuad(int a, int b, int c, int j);
void ThreeAxisSet();
void EmptyArray();
void QuadChecker();
void QuadCreator();




int main()
{
	CreateVerticies();  //makes the verticies
	
	for (int i = 0; i < GridNum; i++)
	{
		for (int j = 0; j < GridNum; j++)
		{
			for (int k = 0; k < GridNum; k++)
			{

				StartPoint = { i, j, k };   //3D Startpoint to then decript using QuadSolver
				ThreeAxisSet();
				//system("PAUSE");
			}
		}
	}


	cout << "size of PointList: " << PointList.size() << endl;
	cout << "size of QuadList: " << QuadList.size() << endl;
	cout << "number of Quads: " << QuadList.size() / 4 << endl;

	QuadCreator();   // Takes from list into our quad struct
	
	QuadChecker();	// Checks to see if all is well for our quad struct
	
	system("PAUSE");
	return 0;


}





void QuadCreator()
{
	int QuadListCount = 0;
	while (QuadListCount < QuadList.size())
	{
		Vertex TempPoints[4];
		int TempQuads[4];
		Face TempFace;

		for (int i = 0; i < 4; i++)
		{
			TempFace.Points[i] = PointList[QuadList[QuadListCount]];
			TempFace.QuadLoc[i] = QuadList[QuadListCount];
			QuadListCount += 1;

		}
		FaceList.push_back(TempFace);

	}

}





void ThreeAxisSet()  //cycles between 3 axises, XZ, YZ, and XY and refers to the actual quad solver. (THIS IS PART 1)
{
	AllThreeTrue = true;

	for (int j = 0; j < 4; j++)//XZ axis
	{


		switch (j)
		{
		case 0:
			GetQuad(0, 0, 0, j);
			break;
		case 1:
			GetQuad(1, 0, 0, j);
			break;
		case 2:
			GetQuad(1, 0, 1, j);
			break;
		case 3:
			GetQuad(0, 0, 1, j);
			break;
		}
		
	}
	cout << endl << "Connecting Points: " << GetID[0] << " " << GetID[1] << " " << GetID[2] << " " << GetID[3] << endl << endl;
	if (AllThreeTrue)
	{
		GetIntersect[0] = GetID[0];
		GetIntersect[1] = GetID[1];
		GetIntersect[2] = GetID[2];        //these parts are just intersection tests
		GetIntersect[3] = GetID[3];
	}
	EmptyArray();


	for (int j = 0; j < 4; j++) //YZ axis
	{


		switch (j)
		{
		case 0:
			GetQuad(0, 0, 0, j);
			break;
		case 1:
			GetQuad(0, 1, 0, j);
			break;
		case 2:
			GetQuad(0, 1, 1, j);
			break;
		case 3:
			GetQuad(0, 0, 1, j);
			break;
		}
		
	}
	cout << endl << "Connecting Points: " << GetID[0] << " " << GetID[1] << " " << GetID[2] << " " << GetID[3] << endl << endl;
	if (AllThreeTrue)
	{
		GetIntersect[4] = GetID[0];
		GetIntersect[5] = GetID[1];
		GetIntersect[6] = GetID[2];
		GetIntersect[7] = GetID[3];
	}
	EmptyArray();

	for (int j = 0; j < 4; j++) //XY axis
	{


		switch (j)
		{
		case 0:
			GetQuad(0, 0, 0, j);
			break;
		case 1:
			GetQuad(1, 0, 0, j);
			break;
		case 2:
			GetQuad(1, 1, 0, j);
			break;
		case 3:
			GetQuad(0, 1, 0, j);
			break;
		}

	}
	cout << endl << "Connecting Points: " << GetID[0] << " " << GetID[1] << " " << GetID[2] << " " << GetID[3] << endl << endl;
	if (AllThreeTrue)
	{
		GetIntersect[8] = GetID[0];
		GetIntersect[9] = GetID[1];
		GetIntersect[10] = GetID[2];
		GetIntersect[11] = GetID[3];
	}
	EmptyArray();

	if (!AllThreeTrue)
	{
		for (int i = 0; i < 12; i++)
		{
			GetIntersect[i] = NULL;
		}
	}
	else if (AllThreeTrue)
	{
		for (int i = 0; i < 12; i++)
		{
			cout << "Possible Intersection Point: "<< GetIntersect[i] << endl;     //not exactly.. just a test
		}
	}

}




bool GetQuad(int a, int b, int c, int j)     //the actual quad solver, uses a, b, and c, from part 1 and gets the quad
{

	bool NoPointFound = true;
	CurrentPoint = { StartPoint.x + a, StartPoint.y + b, StartPoint.z + c };
	for (int i = 0; i < PointList.size(); i++)
	{
		if (CurrentPoint.x == PointList[i].x && CurrentPoint.y == PointList[i].y && CurrentPoint.z == PointList[i].z)
		{
			GetID[j] = i;
			cout << "Found at: " << i << ", Point is: " << PointList[i].x << " " << PointList[i].y << " " << PointList[i].z << endl;
			NoPointFound = false;
			break;
		}


	}
	if (NoPointFound)
	{
		cout << "NO QUADS!!!" << endl;   //if no vertex, then NO QUAD
		AllThreeTrue = false;
		NoQuad = true;
		return false;
	}

	return true;
}



void CreateVerticies()     //creates a grid of verticies in the x, y, and z directions
{
	int counter = 0;
	for (int i = 0; i < GridNum; i++)
	{
		for (int j = 0; j < GridNum; j++)
		{
			for (int k = 0; k < GridNum; k++)
			{

				PointList.push_back({ i, j, k });
				cout << PointList[counter].x << " " << PointList[counter].y << " " << PointList[counter].z << endl;
				counter += 1;
			}
		}
	}
}




void QuadChecker()
{
	for (int i = 0; i < FaceList.size(); i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << FaceList[i].Points[j].x << " " << FaceList[i].Points[j].y << " " << FaceList[i].Points[j].z << "    ";
		}
		cout << endl;

	}

	cout << endl;

	for (int i = 0; i < FaceList.size(); i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << FaceList[i].QuadLoc[j] << "    ";
		}
		cout << endl;

	}
}



void EmptyArray()     //Pushes from temp array to QuadList, which holds the vector for the actual quads
{
	if (!NoQuad)
	{
		for (int z = 0; z < 4; z++)
		{
			QuadList.push_back(GetID[z]);
			GetID[z] = NULL;
		}
	}
	else
	{
		for (int z = 0; z < 4; z++)
		{
			GetID[z] = NULL;
			NoQuad = false;
		}
	}
}