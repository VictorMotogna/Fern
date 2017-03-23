#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

#define PI 3.141592

ofstream fo("scene.wrl");

typedef struct point { double x, y, z; } POINT;

void line(POINT A, POINT B)
{
	// exports code in vrml (Virtual Reality Modeling Language)
	// can be interpreted by Cortona 3D viewer
	// code exported to a .wrl extension to be ran

	fo << "Shape{\n";
	fo << "geometry IndexedLineSet{\n";
	fo << "cood Coordinate{\n";
	fo << "point [\n";
	fo << A.x << " " << A.y << " " << A.z << " " << ",\n";
	fo << B.x << " " << B.y << " " << B.z << " " << ",\n";
	fo << "]\n";
	fo << "}\n";
	fo << "coordIndex [\n";
	fo << "0, 1, -1,\n";
	fo << "]\n";
	fo << "}\n";
	fo << "}\n";
}

void tree(POINT P, int n, double l, double u)
{
	POINT P1;
	if (n > 0)
	{
		P1.z = P.z;
		P1.x = P.x + l*cos(u);
		P1.y = P.y + l*sin(u);
		line(P, P1);
		tree(P1, n - 1, l / 2.0, u - PI / 7);
		tree(P1, n - 1, l / 2.0, u + PI / 7);
		tree(P1, n - 1, l / 2.0, u);

		// we need to form a tree that has 3 branches (lines) starting from the last point
		// the branches will be set like this: 1 that continues the last line and forms 180 degrees with the last line
		// and 2 branches that will form a +-PI/7 angle with the line
	}
}

POINT P; // first point

// points are considered "seeds", as only from points can rise branches (with the rule described above)
// lines, formed by 2 different points will always be created in a number of 4: one straight up, and then the 3 that define the rule

int main()
{
	fo << "#VRML V2.0 utf8\n";
	P.x = 0;
	P.y = 0;
	P.z = 0;
	//starting coordinates of the first "seed" (point)

	tree(P, 12, 2, PI / 2); // starting point, no. generations, angle of inclination

	fo.close();
	return 0;
}