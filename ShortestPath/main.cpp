#include "iostream"
#include "string"
#include "STL.h"
#include "Graph.h"

using namespace std;

Point getPoint(string text, STLParser stlParser)
{
	Point point;
	vector<Point> points = stlParser._points;
	int index;
	cout << " input " << text << " point " << " (nomber from 1 to " << points.size() << "):";
	cin >> index;
	for (auto it = points.begin(); it != points.end(); it++)
	{
		if (index == it->_index)
		{
			point._index = it->_index;
			point._x = it->_x;
			point._y = it->_y;
			point._z = it->_z;
		}
	}
	return point;
}
int main()
{
	string name2 = "bunny";
	string dir = "STL\\";
	string format = ".stl";
	string path = dir + name2 + format;
	string decision;
	cout << "Use default path?(y/n)";
	cin >> decision;
	if (decision != "y" && (decision != "Y"))
	{
		cout << "input the path to stl file: ";
		cin >> path;
	}

	cout << "Path to stl file: " << path << endl;
	STLParser stlParser(path);

	stlParser.parse();
	cout << "Show all vertex?(y/n)";
	cin >> decision;
	if (decision == "y" || (decision == "Y"))
		stlParser.outputPoints();
	cout << "Number of vertex on surface: " << stlParser._points.size() << endl;

	PathFinding pathFinding(stlParser);
	pathFinding.setGraph(pathFinding.getVertexMatrix());
	Point source, target;

	while (true)
	{
		source = getPoint("source", stlParser);
		target = getPoint("target", stlParser);
		cout << "___________________Resume____________________________________________________\n";
		pathFinding.findShortestPath(source, target, stlParser);
		cout << "Repeat?(y/n)";
		cin >> decision;
		if (decision != "y" && (decision != "Y"))
			break;
	}
	return 0;
}
