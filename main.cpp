#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
#include "Graph.h"
#include "PriorityQueue.h"

std::string dijkstra(const Graph &g, const int s, const double min);
void filemanager(std::ifstream &ifs, std::ofstream &ofs);

struct Vertice
{
	int i;
	int p;
	double d;

	Vertice(int i = 0, int p = 0, double d = 0)
		: i(i)
		, p(p)
		, d(d) {}

	bool operator<(Vertice other) const
	{
		return d < other.d;
	}
	bool operator>(Vertice other) const
	{
		return d > other.d;
	}
	bool operator==(Vertice other) const
	{
		return (i == other.i && p == other.p && d == other.d);
	}
	bool operator!=(Vertice other) const
	{
		return !(*this == other);
	}
};

int main(int argc, char *argv[])
{
	std::string filename;
	if (argc == 2) 
	{
		filename = argv[1];
	}
	else 
	{
		std::cout << "Adja meg a fajlt: ";
		std::cin >> filename;
	}

	std::ifstream ifs(filename.c_str());
	std::ofstream ofs("result.txt");
	if (ifs.fail())
	{
		std::cerr << "Hibas fajlnev!" << std::endl;
		system("pause");
		exit(1);
	}

	try
	{
		filemanager(ifs, ofs);
	}
	catch (Graph::Exception) {
		std::cerr << "Graf: nem letezo csucs." << std::endl;
	}
	catch (PriorityQueue<Vertice, std::greater<Vertice>>::Exception) {
		std::cerr << "Prioritási sor: memoria hiba." << std::endl;
	}

	if (ifs.fail()) 
	{
		std::cerr << "Hibas bemenet!" << std::endl;
		system("pause");
		exit(1);
	}

	ifs.close();
	ofs.close();
	system("pause");
	return 0;
}

void filemanager(std::ifstream &ifs, std::ofstream &ofs)
{
	int networkIndex = 0, taskIndex;

	int n;
	ifs >> n;
	while (n != 0)
	{
		networkIndex++;
		taskIndex = 0;

		Graph g(n);

		std::cout << networkIndex << ". halozat:" << std::endl;
		ofs << networkIndex << ". halozat:" << std::endl;

		int v1, v2;
		double w;
		ifs >> v1;
		ifs >> v2;
		ifs >> w;
		while (v1 != 0 && v2 != 0 && w != 0) 
		{
			g.addEdge(v1, v2, w);
			ifs >> v1;
			ifs >> v2;
			ifs >> w;
		}

		int sv;
		double sl;
		ifs >> sv;
		ifs >> sl;
		while (sv != 0 && sl != 0) 
		{
			taskIndex++;
			std::string result = dijkstra(g, sv, sl);
			std::cout << taskIndex << ". feladat:" << result << std::endl;
			ofs << taskIndex << ". feladat:" << result << std::endl;
			ifs >> sv;
			ifs >> sl;
		}
		ifs >> n;
	}
}

std::string dijkstra(const Graph &g, const int s, const double min) 
{
	int n = g.getVerticesCount();
	std::vector<Vertice> vertices;
	std::vector<bool> done;

	for (int i = 0; i < n; ++i) 
	{
		vertices.push_back(Vertice(i+1, 0, 0));
		done.push_back(false);
	}
	vertices[s-1].d = 1;

	PriorityQueue<Vertice, std::greater<Vertice>> pq(n);
	pq.push(vertices[s - 1]);
	while (!pq.empty()) 
	{ 
		Vertice u = pq.pop();
		done[u.i-1] = true;
		EdgeList adj = g.getAdjacent(u.i);
		for (EdgeIterator it = adj.begin(); it != adj.end(); ++it) 
		{
			Vertice& v = vertices[(*it).index-1];
			double w_uv = (*it).weight;
			if (done[v.i-1] == false) 
			{
				if (v.d < u.d * w_uv) 
				{
					if (v.d == 0) 
					{
						v.d = u.d * w_uv;
						v.p = u.i;
						pq.push(v);
					}
					else
					{
						Vertice tmp = v;
						v.d = u.d * w_uv;
						v.p = u.i;
						pq.modify(tmp, v);
					}
				}
			}
		}
	}
	std::string result;
	for (int i = 0; i < n; ++i) 
	{
		if(vertices[i].d < min)
			result += " " + std::to_string(i+1);
	}
	if (result.empty()) 
		return " minden csucs elerheto";
	else 
		return result;
}