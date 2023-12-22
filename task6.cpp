#include "task6.h"

ConsoleFor6::ConsoleFor6()
{
}

ConsoleFor6::~ConsoleFor6()
{
}

int ConsoleFor6::run()
{
	cout << "Выберите номер задания из работы 6:\n";
	cout << "1. Добавить элементы в граф\n";
	cout << "2. Вывести граф\n";
	cout << "3. Найти минимальный путь между вершинами графа\n";
	cout << "0. Перейти к выбору работы\n";
	string key;
	int num;
	Graph g;
	while (1)
	{
		getline(cin, key);
		if (!numcheck(key, 0, 3))
		{
			cout << "Некорректный ввод! Попробуйте ещё раз: ";
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
				cout << "Введите вершину отправления: ";
				getline(cin, source);
				if (g.vertices.contains(Vertex(source)))
					break;
				else
					cout << "Такой вершины не существует!" << endl;
			}
			string dest;
			while (true)
			{
				cout << "Введите вершину назначения: ";
				getline(cin, dest);
				if (g.vertices.contains(Vertex(dest)))
					break;
				else
					cout << "Такой вершины не существует!" << endl;
			}
			pair<vector<string>, double> path = getPath(g, source, dest);
			if (path.first.empty())
				cout << "Между вершинами невозможно найти кратчайший путь!" << endl;
			else
			{
				cout << path.first[0];
				for (int i = 1; i < path.first.size(); i++)
					cout << " -> " << path.first[i];
				cout << endl << "Длина пути = " << path.second << endl;
			}
		}
		else if (num == 0)
			break;
		cout << "Выберите номер из меню: ";
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
	cout << "Количество вершин: ";
	int num = inpInt(0, 100);
	for (int i = 0; i < num; i++)
	{
		int numOfVertBefore = g.vertices.size();
		string inp;
		while (g.vertices.size() == numOfVertBefore)
		{
			cout << "Введите название вершины " << i << ": ";
			getline(cin, inp);
			g.vertices.insert(Vertex(inp));
			if (g.vertices.size() == numOfVertBefore)
			{
				cout << "Такая вершина уже существует!" << endl;
			}
		}
	}

	cout << "Количество рёбер: ";
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
				cout << "Введите название первой вершины ребра " << i << ": ";
				getline(cin, inp);
				newFrom = Vertex(inp);
				if (g.vertices.contains(newFrom))
					break;
				cout << "Такой вершины не существует!" << endl;
			}
			Vertex newTo;
			while (true)
			{
				cout << "Введите название второй вершины ребра " << i << ": ";
				getline(cin, inp);
				newTo = Vertex(inp);
				if (g.vertices.contains(newTo))
					break;
				cout << "Такой вершины не существует!" << endl;
			}
			cout << "Введите вес ребра " << i << ": ";
			int w = inpInt(-1000, 1000);
			g.edges.insert(Edge(newFrom, newTo, w));
			g.edges.insert(Edge(newTo, newFrom, w));
			if (g.vertices.size() == numOfEdgesBefore)
			{
				cout << "Между вершинами уже есть ребро!";
			}
		}
	}
}

void printGraph(Graph g)
{
	if (g.edges.empty())
		cout << "Граф не содержит связей!" << endl;
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

