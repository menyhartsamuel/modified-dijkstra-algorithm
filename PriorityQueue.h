#pragma once
#include <algorithm>

template<class T, class Compare = std::less<T>>
class PriorityQueue
{
	public:
		enum Exception { QUEUE_IS_EMPTY, QUEUE_IS_FULL };

		PriorityQueue(int n);
		~PriorityQueue();
		PriorityQueue(const PriorityQueue & other);
		PriorityQueue& operator=(const PriorityQueue & other);

		bool empty() const;
		bool full() const;
		void clear();
		const T& top() const;
		T pop();
		void push(const T& elem);
		void modify(const T& before, const T& after);

	private:
		int n, m;
		T *t;

		Compare compare;
		void increase(int i);
		void decrease(int i);
};

template<class T, class Compare = std::less<T>>
PriorityQueue<T, Compare>::PriorityQueue(int n)
	: n(n)
	, m(0)
	, t(new T[n]()) {}

template<class T, class Compare = std::less<T>>
PriorityQueue<T, Compare>::~PriorityQueue()
{
	delete[] t;
}

template<class T, class Compare = std::less<T>>
PriorityQueue<T, Compare>::PriorityQueue(const PriorityQueue<T, Compare> & other)
	: n(other.n)
	, m(other.m)
	, t(new T[n]())
{
	for (int i = 0; i < m; ++i)
	{
		t[i] = T(other.t[i]);
	}
}

template<class T, class Compare = std::less<T>>
PriorityQueue<T, Compare> & PriorityQueue<T, Compare>::operator=(const PriorityQueue<T, Compare> & other)
{
	delete[] t;
	n = other.n;
	m = other.m;
	t = new T[n]();
	for (int i = 0; i < m; ++i)
	{
		t[i] = T(other.t[i]);
	}
}

template<class T, class Compare = std::less<T>>
bool PriorityQueue<T, Compare>::empty() const
{
	return m == 0;
}

template<class T, class Compare = std::less<T>>
bool PriorityQueue<T, Compare>::full() const
{
	return m == n;
}

template<class T, class Compare = std::less<T>>
void PriorityQueue<T, Compare>::clear()
{
	m = 0;
}

template<class T, class Compare = std::less<T>>
const T& PriorityQueue<T, Compare>::top() const
{
	if (m > 0)
	{
		return t[0];
	}
	else
	{
		throw PriorityQueue<T, Compare>::QUEUE_IS_EMPTY;
	}
}

template<class T, class Compare = std::less<T>>
T PriorityQueue<T, Compare>::pop()
{
	if (m > 0)
	{
		T elem = t[0];
		m--;
		t[0] = t[m];
		decrease(0);
		return elem;
	}
	else
	{
		throw PriorityQueue<T, Compare>::QUEUE_IS_EMPTY;
	}
}

template<class T, class Compare = std::less<T>>
void PriorityQueue<T, Compare>::push(const T& elem)
{
	if (m < n)
	{
		t[m] = elem;
		increase(m);
		m++;
	}
	else
	{
		throw PriorityQueue<T, Compare>::QUEUE_IS_FULL;
	}
}

template<class T, class Compare = std::less<T>>
void PriorityQueue<T, Compare>::modify(const T& before,const T& after)
{
	int ind = 0;
	while (ind < m && t[ind] != before)
	{
		++ind;
	}
	if (ind != m)
	{
		t[ind] = after;
		if (compare(before, after)) 
		{
			decrease(ind);
		}
		else
		{
			increase(ind);
		}
	}
}

template<class T, class Compare = std::less<T>>
void PriorityQueue<T, Compare>::increase(int i) {
	if (i > 0)
	{
		if (compare(t[i], t[(i - 1) / 2]))
		{
			std::swap(t[i], t[(i - 1) / 2]);
			increase((i - 1) / 2);
		}
	}
}

template<class T, class Compare = std::less<T>>
void PriorityQueue<T, Compare>::decrease(int i) {
	if (i < m / 2)
	{
		int j;
		if (2 * (i + 1) > m || compare(t[2 * (i + 1) - 1], t[2 * (i + 1)])) 
		{
			j = 2 * (i + 1) - 1;
		}
		else
		{
			j = 2 * (i + 1);
		}
		if (compare(t[j], t[i]))
		{
			std::swap(t[i], t[j]);
			decrease(j);
		}
	}
}