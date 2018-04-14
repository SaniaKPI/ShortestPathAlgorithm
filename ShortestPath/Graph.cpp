#include"Graph.h"
#include<iostream>
double Infinity = 999999.0;

PathFinding::PathFinding(STLParser stlParser)
{
	setVertexMatrix(stlParser._triangles);
	inizializeGraph(stlParser._points.size());
}
PathFinding::PathFinding(const std::vector<std::vector<float>>& pointMatrix)
{
	setVertexMatrix(pointMatrix);
}

int PathFinding::findMinDistance(const std::vector<float>& distances, const std::vector<bool>& shortestPathSet)
{
	float min = Infinity;
	int index = 0;
	for (int i = 0; i < distances.size(); i++)
	{
		if (!shortestPathSet[i] && distances[i] <= min)
		{
			min = distances[i];
			index = i;
		}
	}
	return index;
}
float PathFinding::findDistance(const Point& point1, const Point& point2)
{
	return sqrt(pow((point2._x - point1._x), 2) + pow((point2._y - point1._y), 2) + pow((point2._z - point1._z), 2));
}
void PathFinding::inizializeGraph(int size)
{
	_graph.resize(size);
	for (int i = 0; i < size; i++)
		_graph[i].resize(size);
}
int PathFinding::getIndex(const Point& point, STLParser& stlParser)
{
	std::vector<Point> points = stlParser._points;
	for (auto it = points.begin(); it != points.end(); it++)
	{
		if (point == *it)
		{
			return it->_index;
		}
	}
	std::cout << "There is no such point!";
}

void PathFinding::findShortestPath(Point& source, Point& target, STLParser& stlParser)
{
	int size = _graph.size();
	int sourceIndex = getIndex(source, stlParser);
	source._index = sourceIndex;
	int targetIndex = getIndex(target, stlParser);
	target._index = targetIndex;

	std::vector<float> distances(size);
	std::vector<bool> shortestPathSet(size);
	std::vector<int> parent(size);

	for (int i = 0; i < size; i++)
	{
		parent[i] = -1;
		distances[i] = Infinity;
		shortestPathSet[i] = false;
	}

	distances[sourceIndex - 1] = 0;

	for (int i = 0; i < size - 1; i++)
	{
		int u = findMinDistance(distances, shortestPathSet);
		shortestPathSet[u] = true;
		for (int j = 0; j < size; j++)
		{
			if (!shortestPathSet[j] && _graph[u][j] && ((distances[u] + _graph[u][j]) < distances[j]))
			{
				parent[j] = u;
				distances[j] = distances[u] + _graph[u][j];
			}
		}
	}
	float result = distances[targetIndex - 1];

	if (result == Infinity)
	{
		std::cout << "There is no connection between this points!";
	}

	std::cout << "Distance through space:\n" << findDistance(source, target) << std::endl;
	std::cout << "Path:\n";
	outputPath(parent, targetIndex - 1, stlParser._points);
}
void PathFinding::outputMatrix(const std::vector<std::vector<float>>& matrix, const std::string& name, char delimiter)
{
	std::cout << name << ":\n";
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			std::cout << matrix[i][j] << delimiter;
		}
		std::cout << std::endl;
	}
}

void PathFinding::outputPath(const std::vector<int>& parent, int v, const std::vector<Point>& points)
{
	if (parent[v] == -1)
	{

		std::cout << points[v] << "\n";
		return;
	}
	outputPath(parent, parent[v], points);
	std::cout << points[v] << "\n";
}

void PathFinding::setVertexMatrix(const std::vector<Triangle>& triangles)
{
	for (auto it = triangles.begin(); it != triangles.end(); it++)
	{
		_vertexMatrix.push_back({ it->_point1._index, it->_point2._index, findDistance(it->_point1, it->_point2) });
		_vertexMatrix.push_back({ it->_point2._index, it->_point3._index, findDistance(it->_point2, it->_point3) });
		_vertexMatrix.push_back({ it->_point3._index, it->_point1._index, findDistance(it->_point3, it->_point1) });
	}
}
void PathFinding::setVertexMatrix(const std::vector<std::vector<float>>& pointMatrix)
{
	_vertexMatrix = pointMatrix;
}
std::vector<std::vector<float>> PathFinding::getVertexMatrix()
{
	return _vertexMatrix;
}
void PathFinding::setGraph(const std::vector<std::vector<float>>& vertexMatrix)
{
	for (int i = 0; i < vertexMatrix.size(); i++)
	{
		_graph[vertexMatrix[i][0] - 1][vertexMatrix[i][1] - 1] = vertexMatrix[i][2];
	}
}
std::vector<std::vector<float>> PathFinding::getGraph()
{
	return _graph;
}