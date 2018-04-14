#pragma once
#include<vector>
#include"STL.h"

#define FLOAT_MAX 999999.0
class PathFinding {
private:
	std::vector<std::vector<float>> _vertexMatrix;
	std::vector < std::vector<float>> _graph;
public:
	//Constructors
	PathFinding(STLParser stlParser);
	PathFinding(const std::vector<std::vector<float>>& _vertexMatrix);

	//Helpful methods
	float findDistance(const Point& point1, const Point& point2);
	int findMinDistance(const std::vector<float>& distances, const std::vector<bool>& shortestPathSet);
	void inizializeGraph(int size);
	int getIndex(const Point& point, STLParser& stlParser);

	//Main methods
	void findShortestPath(Point& source, Point& target, STLParser& stlParser);
	void outputMatrix(const std::vector<std::vector<float>>& matrix, const std::string& name, char delimiter);
	void outputPath(const std::vector<int>& parent, int v, const std::vector<Point>& _points);

	//Getter setter
	void setVertexMatrix(const std::vector<Triangle>& triangles);
	void setVertexMatrix(const std::vector<std::vector<float>>& _vertexMatrix);
	std::vector<std::vector<float>> getVertexMatrix();

	void setGraph(const std::vector<std::vector<float>>& vertexMatrix);
	std::vector<std::vector<float>> getGraph();
};
