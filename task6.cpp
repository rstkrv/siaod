#include "task6.h"

ConsoleFor6::ConsoleFor6()
{
}

ConsoleFor6::~ConsoleFor6()
{
}

int ConsoleFor6::run()
{
	cout << "�������� ����� ������� �� ������ 6:\n";
	cout << "1. �������� �������� � ����\n";
	cout << "2. ������� ����\n";
	cout << "3. ����� ����������� ���� ����� ��������� �����\n";
	cout << "0. ������� � ������ ������\n";
	string key;
	int num;
	Graph g;
	while (1)
	{
		getline(cin, key);
		if (!numcheck(key, 0, 3))
		{
			cout << "������������ ����! ���������� ��� ���: ";
			continue;
		}
		num = stoi(key);
		if (num == 1)
		{
			addToGraphNonDirected(g);
		}
		if (num == 2)
		{
			printGraph(g);
		}
		if (num == 3)
		{
			string source;
			while (true)
			{
				cout << "������� ������� �����������: ";
				getline(cin, source);
				if (g.vertices.contains(Vertex(source)))
					break;
				else
					cout << "����� ������� �� ����������!" << endl;
			}
			string dest;
			while (true)
			{
				cout << "������� ������� ����������: ";
				getline(cin, dest);
				if (g.vertices.contains(Vertex(dest)))
					break;
				else
					cout << "����� ������� �� ����������!" << endl;
			}
			pair<vector<string>, double> path = getPath(g, source, dest);
			if (path.first.empty())
				cout << "����� ��������� ���������� ����� ���������� ����!" << endl;
			else
			{
				cout << path.first[0];
				for (int i = 1; i < path.first.size(); i++)
					cout << " -> " << path.first[i];
				cout << endl << "����� ���� = " << path.second << endl;
			}
		}
		else if (num == 0)
			break;
		cout << "�������� ����� �� ����: ";
	}
	return 0;
}

void putToGraph(Graph& g, set<Vertex> vertices, set<Edge> edges)
{
	for (Vertex v : vertices)
		g.vertices.insert(v);
	for (Edge e : edges)
		g.edges.insert(e);
}

void addToGraphNonDirected(Graph& g)
{
	cout << "���������� ������: ";
	int num = inpInt(0, 100);
	for (int i = 0; i < num; i++)
	{
		int numOfVertBefore = g.vertices.size();
		string inp;
		while (g.vertices.size() == numOfVertBefore)
		{
			cout << "������� �������� ������� " << i << ": ";
			getline(cin, inp);
			g.vertices.insert(Vertex(inp));
			if (g.vertices.size() == numOfVertBefore)
			{
				cout << "����� ������� ��� ����������!" << endl;
			}
		}
	}

	cout << "���������� ����: ";
	num = inpInt(0, 100);
	for (int i = 0; i < num; i++)
	{
		int numOfEdgesBefore = g.edges.size();
		string inp;
		while (g.edges.size() == numOfEdgesBefore)
		{
			Vertex newFrom;
			while (true)
			{
				cout << "������� �������� ������ ������� ����� " << i << ": ";
				getline(cin, inp);
				newFrom = Vertex(inp);
				if (g.vertices.contains(newFrom))
					break;
				cout << "����� ������� �� ����������!" << endl;
			}
			Vertex newTo;
			while (true)
			{
				cout << "������� �������� ������ ������� ����� " << i << ": ";
				getline(cin, inp);
				newTo = Vertex(inp);
				if (g.vertices.contains(newTo))
					break;
				cout << "����� ������� �� ����������!" << endl;
			}
			cout << "������� ��� ����� " << i << ": ";
			int w = inpInt(-1000, 1000);
			g.edges.insert(Edge(newFrom, newTo, w));
			g.edges.insert(Edge(newTo, newFrom, w));
			if (g.vertices.size() == numOfEdgesBefore)
			{
				cout << "����� ��������� ��� ���� �����!";
			}
		}
	}
}

void printGraph(Graph g)
{
	if (g.edges.empty())
		cout << "���� �� �������� ������!" << endl;
	string lastFrom = "";
	for (Edge e : g.edges)
	{
		if (e.from.name != lastFrom)
			cout << e.from.name;
		else
			for (char c : lastFrom)
				cout << " ";
		cout << " - " << e.weight << " -> " << e.to.name << endl;
		lastFrom = e.from.name;
	}
}

pair<vector<string>, double> getPath(Graph g, string source, string dest)
{
	vector<string> path{dest};
	double pathLen = 0;
	string curr = dest;

	try 
	{ 
		map<string, pair<string, double>> bfMap = makeBellmanFordMap(g, source); 
		pathLen = bfMap[curr].second;
		while (curr != source)
		{
			path.push_back(bfMap[curr].first);
			if (pathLen == numeric_limits<double>::infinity())
			{
				path.clear();
				break;
			}
			curr = bfMap[curr].first;
		}
	}
	catch (const runtime_error& e)
	{
		cout << e.what();
		return make_pair(vector<string>(), 0);
	}	

	reverse(path.begin(), path.end());
	return make_pair(path, pathLen);
}

map<string, pair<string, double>> makeBellmanFordMap(Graph g, string source)
{
	map<string, pair<string, double>> path;

	for (Vertex v : g.vertices)
		path.insert(make_pair(v.name, make_pair("", numeric_limits<double>::infinity())));
	path[source].second = 0;
	path[source].first = source;

	for (int i = 0; i < g.vertices.size() - 1; i++)
	{
		bool done = true;
		for (Edge e : g.edges)
			if (path[e.from.name].second + e.weight < path[e.to.name].second)
			{
				done = false;
				path[e.to.name].second = path[e.from.name].second + e.weight;
				path[e.to.name].first = e.from.name;
			}
		if (done)
			break;
	}

	for (Edge e : g.edges)
		if (path[e.from.name].second + e.weight < path[e.to.name].second)
			throw runtime_error("Graph contains a negative-weight cycle!");

	return path;
}

