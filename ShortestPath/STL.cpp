#include"STL.h"
#include<fstream>
#include<iostream>
#include<algorithm>
#include<iterator>
float d = 0.001;
//---------------STLParser----------------------
//Constructors
STLParser::STLParser()
{
	_filePath = "";
};
STLParser::STLParser(const std::string& filePath)
{
	_filePath = filePath;
	_index = 0;
	_points.resize(0);
};

//Helpful methods
float STLParser::getPointName(float x, float y, float z)
{
	float index;
	if (std::find_if(_points.begin(), _points.end(), [&](Point point)
	{
		if (point._x == x && point._y == y && point._z == z)
		{
			index = point._index;
			return true;
		}
		return false;
	}) == _points.end())
	{
		_index++;
		index = _index;
		_points.push_back(Point(index, x, y, z));
	}
	return index;
}

Point STLParser::parsePoint(std::ifstream& input, bool hasIndex)
{
	float x = parseFloat(input);
	float y = parseFloat(input);
	float z = parseFloat(input);
	float index = 0;
	if (hasIndex)
		index = getPointName(x, y, z);
	return Point(index, x, y, z);
}
float STLParser::parseFloat(std::ifstream& input) {
	char forfloat[sizeof(float)];
	input.read(forfloat, sizeof(float));
	return *(float*)forfloat;;
}

//Main methods
void STLParser::parse()
{
	std::ifstream input(_filePath, std::ios::binary | std::ios::in);
	if (!input)
	{
		std::cout << "\nCan't read file! Such file doesn't exist!\n";
	}

	char header[80];
	char numOfTriangles[4];
	char atrr[2];

	input.read(header, 80);
	input.read(numOfTriangles, 4);

	for (unsigned int i = 0; i < *(unsigned int*)numOfTriangles; i++)
	{
		Point normal = parsePoint(input, false);
		Point point1 = parsePoint(input, true);
		Point point2 = parsePoint(input, true);
		Point point3 = parsePoint(input, true);
		Triangle triangle(normal, point1, point2, point3);
		_triangles.push_back(triangle);
		input.read(atrr, 2);
	}
}

void STLParser::outputPoints()
{
	std::cout << "number, x, y, z \n";
	std::ostream_iterator<Point> os(std::cout, "\n");
	std::copy(_points.begin(), _points.end(), os);
}
//---------------Point---------------------

Point::Point(float index, float x, float y, float z)
{
	_index = index;
	_x = x;
	_y = y;
	_z = z;
}
std::ostream& operator<<(std::ostream& out, const Point& point)
{
	out << point._index << " (" << point._x << ", " << point._y << ", " << point._z << ")";
	return out;
}

bool operator==(const Point& point1, const Point& point2)
{
	if (fabs(point1._x - point2._x) < d && fabs(point1._y - point2._y) < d && fabs(point1._z - point2._z) < d)
		return true;
	return false;
}

//---------------Triangle---------------------
Triangle::Triangle() : _normal(), _point1(), _point2(), _point3() {};
Triangle::Triangle(Point normal, const Point& point1, const Point& point2, const Point& point3) {
	_normal = normal;
	_point1 = point1;
	_point2 = point2;
	_point3 = point3;
}

std::ostream& operator<<(std::ostream& out, const Triangle& triangle) {
	out << "\nTriangle:\n";
	out << "Normal:" << triangle._normal << std::endl;
	out << "Point1:" << triangle._point1 << std::endl;
	out << "Point2:" << triangle._point2 << std::endl;
	out << "Point3:" << triangle._point3 << std::endl;
	return out;
}
