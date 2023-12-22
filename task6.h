#pragma once
#include "general.h"

class ConsoleFor6 : public Console
{
public:
	ConsoleFor6();
	~ConsoleFor6();
	int run();
};

struct Vertex
{
	string name = "";
	Vertex() = default;
	Vertex(string name)
	{
		this->name = name;
	}

	bool operator < (const Vertex& v) const
	{
		return name < v.name;
	}
	bool operator == (const Vertex& v) const
	{
		return name == v.name;
	}
};

struct Edge
{
	Vertex from;
	Vertex to;
	double weight = 0;
	Edge(Vertex from, Vertex to, double weight)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;
	}

	bool operator < (const Edge& e) const
	{
		if (from == (e.from))
			return to < e.to;
		else
			return from < e.from;
	}
};

struct Graph
{
	set<Vertex> vertices = set<Vertex>();
	set<Edge> edges = set<Edge>();
	Graph() = default;
};

void putToGraph(Graph& g, set<Vertex> vertices, set<Edge> edges);

void addToGraphNonDirected(Graph& g);

void printGraph(Graph g);

map<string, pair<string, double>> makeBellmanFordMap(Graph g, string source);

pair<vector<string>, double> getPath(Graph g, string source, string dest);