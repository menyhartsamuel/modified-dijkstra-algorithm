#include "Graph.h"

Graph::Graph(int n)
	: adjacent(new EdgeList[n])
	, verticesCount(n)
	, edgesCount(0) {}

Graph::~Graph()
{
	delete[] adjacent;
}

Graph::Graph(const Graph & other)
	: verticesCount(other.verticesCount)
	, edgesCount(other.edgesCount)
	, adjacent(new EdgeList[verticesCount]())
{
	for (int i = 0; i < verticesCount; ++i)
	{
		adjacent[i] = EdgeList(other.adjacent[i]);
	}
}

Graph & Graph::operator=(const Graph & other)
{
	delete[] adjacent;
	verticesCount = other.verticesCount;
	edgesCount = other.edgesCount;
	adjacent = new EdgeList[verticesCount];
	for (int i = 0; i < verticesCount; ++i) 
	{
		adjacent[i] = EdgeList(other.adjacent[i]);
	}
	return *this;
}

int Graph::getVerticesCount() const
{
	return verticesCount;
}

int Graph::getEdgesCount() const
{
	return edgesCount;
}

EdgeList Graph::getAdjacent(int i) const
{
	if (0 < i && i <= verticesCount) 
	{
		return adjacent[i - 1];
	} 
	else 
	{
		throw Graph::INDEX_IS_NOT_EXIST;
	}
}

void Graph::addEdge(int i1, int i2, double w)
{
	if (0 < i1 && i1 <= verticesCount &&
		0 < i2 && i2 <= verticesCount) 
	{
		adjacent[i1-1].addEdge(Edge(i2, w));
		edgesCount++;
	} 
	else 
	{
		throw Graph::INDEX_IS_NOT_EXIST;
	}
}

void Graph::removeEdge(int i1, int i2, double w) 
{
	if (0 < i1 && i1 <= verticesCount &&
		0 < i2 && i2 <= verticesCount) 
	{
		if (adjacent[i1 - 1].removeEdge(Edge(i2, w))) 
		{
			edgesCount--;
		}
	} 
	else
	{
		throw Graph::INDEX_IS_NOT_EXIST;
	}
}

std::ostream & operator<<(std::ostream & os, const Graph & g)
{
	for (int i = 0; i < g.verticesCount; ++i) 
	{
		os << i + 1 << ": ";
		for(EdgeIterator it = g.adjacent[i].begin(); it!= g.adjacent[i].end(); ++it) 
		{
			os << "(" << (*it).index << ", " << (*it).weight << ") ";
		}
		os << std::endl;
	}
	return os;
}

EdgeList::EdgeList(Edge edge, EdgeList * next)
	:edge(edge)
	, next(next) {}

EdgeList::~EdgeList()
{
	delete next;
}

EdgeList::EdgeList(const EdgeList & other) 
	: edge(other.edge)
	, next(NULL)
{
	if (other.next != NULL)
		next = new EdgeList(*other.next);
}

EdgeList & EdgeList::operator=(const EdgeList & other) 
{
	delete next;
	edge = other.edge;
	if (other.next) 
	{
		next = new EdgeList(*other.next);
	}
	else 
	{
		next = 0;
	}
	return *this;
}

void EdgeList::addEdge(Edge edge)
{
	next = new EdgeList(edge, next);
}

bool EdgeList::removeEdge(Edge edge)
{
	EdgeList *p = this;
	while (p->next != NULL && p->next->edge != edge) 
	{
		p = p->next;
	}
	if (p->next != NULL) 
	{
		EdgeList *q = p->next;
		p->next = q->next;
		delete q;
		return true;
	}
	return false;
}

EdgeIterator EdgeList::begin() const
{
	return EdgeIterator(next);
}

EdgeIterator EdgeList::end() const
{
	return EdgeIterator(0);
}

EdgeIterator::EdgeIterator(const EdgeList * p)
	: p(p) {}

bool EdgeIterator::operator==(EdgeIterator & other) const
{
	return p == other.p;
}

bool EdgeIterator::operator!=(EdgeIterator & other) const
{
	return !(*this == other);
}

EdgeIterator EdgeIterator::operator++()
{
	p = p->next;
	return *this;
}

Edge EdgeIterator::operator*() const
{
	return p->edge;
}