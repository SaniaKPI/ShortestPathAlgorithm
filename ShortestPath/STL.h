#pragma once
#include<vector>
#include<string>

class Point
{
public:
	float _index;
	float _x;
	float _y;
	float _z;

	Point() {}
	Point(float index, float x, float y, float z);
	friend std::ostream& operator<<(std::ostream& out, const Point& point);
	friend bool operator==(const Point& point1, const Point& point2);
};

class Triangle
{
public:
	Point _normal;
	Point _point1;
	Point _point2;
	Point _point3;

	Triangle();
	Triangle(Point normal, const Point& point1, const Point& point2, const Point& point3);
	friend std::ostream& operator<<(std::ostream& out, const Triangle& triangle);
};

class STLParser {
public:
	std::string			  _filePath;
	std::vector<Triangle> _triangles;
	std::vector<Point>	  _points;
	float				  _index;

	//Constructors
	STLParser();
	STLParser(const std::string& filePath);

	//Helpful methods
	Point parsePoint(std::ifstream& input, bool hasIndex);
	float getPointName(float x, float y, float z);
	float parseFloat(std::ifstream& input);

	//Main methods
	void parse();
	void outputPoints();




};
