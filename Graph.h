#pragma once

#include <iostream>

struct Edge {
	int index;
	double weight;

	Edge(int i, double w = 1)
		: index(i)
		, weight(w) {}

	bool operator==(Edge other) const
	{
		return (index == other.index && weight == other.weight);
	}
	bool operator!=(Edge other) const
	{
		return !(*this == other);
	}
};

class EdgeList;

class EdgeIterator
{
	public:
		EdgeIterator(const EdgeList *p);
		bool operator ==(EdgeIterator & other) const;
		bool operator !=(EdgeIterator & other) const;

		EdgeIterator operator ++();
		Edge operator *() const;

	private:
		const EdgeList *p;
};

class EdgeList {
	public:
		EdgeList(Edge edge = Edge(0), EdgeList * next = NULL);
		~EdgeList();
		EdgeList(const EdgeList & other);
		EdgeList& operator=(const EdgeList & other);

		void addEdge(Edge edge);
		bool removeEdge(Edge edge);

		friend class EdgeIterator;
		EdgeIterator begin() const;
		EdgeIterator end() const;

	private:
		Edge edge;
		EdgeList *next;
};

class Graph
{
	public:
		enum Exception { INDEX_IS_NOT_EXIST };

		Graph(int n);
		~Graph();
		Graph(const Graph & other);
		Graph& operator=(const Graph & other);

		int getVerticesCount() const;
		int getEdgesCount() const;
		EdgeList getAdjacent(int i) const;
		void addEdge(int i1, int i2, double weight = 1);
		void removeEdge(int i1, int i2, double weight = 1);

		friend std::ostream &operator<<(std::ostream &os, const Graph &g);

	private:
		int verticesCount;
		int edgesCount;
		EdgeList *adjacent;
};