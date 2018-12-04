#ifndef _heap_h
#define _heap_h
#include<tgmath.h>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

/*
 * Class Heap
 * ----------
 * This is the class you should implement.
 * It is a template class, Compare can be greater<int>, less<int> and so on.
 * When you define a Heap like Heap<greater<int>>, it should be a maxHeap (who's top this the max element)
 * When you define a Heap like Heap<less<int>>, it should be a minHeap (who's top this the min element)
 * So, when you want to compare two element while implement the member function, you shoud use the member variable cmp, rather than <,<=,>,>=
 */
template<class Compare>
class Heap
{
private:
	// use elements to store the element
	map<int, vector<int>> elements;

	// cmp is a comparer that can help you to compare two element's priority
	// Usage:
	// cmp(element_1, element_2)
	// if element_1's priority is higher than element_2, it will return true, otherwise, return false
	// Example:
	// when you define a Heap like Heap<greater<int>>, it means Compare is greater<int>, and cmp is a instance of greater<int>
	// So, cmp(1,2) and cmp(1,1) will return false and cmp(2,1) will return true
	// when you define a Heap like Heap<less<int>>, it means Compare is less<int>, and cmp is a instance of less<int>
	// So, cmp(2,1) and cmp(1,1) will return false and cmp(1,2) will return true
	// By this way, you can implement minHeap and maxHeap using one class
	Compare cmp;

	// the Top element's index, can make the code more readable
	// It's up to you whether to use it
	pair<int, int> topIndex = make_pair(0, 0);

	// Some help function, can improve the code structure
	// It's up to you whether to use them
	
	pair<int, int> getParentIndex(pair<int, int> index)
	{
		if (index.second%2 == 0)//get the parent node
		{
				pair<int, int> ret = make_pair(index.first - 1, index.second/2);
				if (isInRange(ret))
				{
					return ret;
				}
				else
				{
					return(make_pair(0,0));
				}
		}
		else
		{
				pair<int, int> ret = make_pair(index.first - 1, (index.second - 1) / 2);
				if (isInRange(ret))
				{
					return ret;
				}
				else
				{
					return(make_pair(0, 0));
				}
		}
		
	}
	bool isInRange(pair<int, int> index)//if it is in range ,return true
	{
		if (index.first < elements.size() && index.first >= 0)
		{
			if (index.second < elements[index.first].size() && index.second >= 0)
			{
				return true;
			}
		}
		return false;
	}
	bool isTop(pair<int, int> index)//return top
	{
		if (index == topIndex)
		{
			return true;
		}
	}
	void swap(pair<int, int> index_1, pair<int, int> index_2)//swap two node 
	{
		int temp = elements[index_1.first][index_1.second];
		elements[index_1.first][index_1.second]= elements[index_2.first][index_2.second];
		elements[index_2.first][index_2.second] = temp;
	}
	pair<int, int> findIndex(int element)//find a known element
	{
		for (int i = 0; i < elements.size();i++)
		{
			for (int j = 0; j < elements[i].size(); j++)
			{
				if (elements[i][j] == element)
				{
					return make_pair(i,j);
				}
			}
		}
	}
	void shift_up(pair<int, int> index)
	{
		do
		{
			swap(index, getParentIndex(index));
			index = getParentIndex(index);
		} while (index.first > 0&&!cmp(elements[getParentIndex(index).first][getParentIndex(index).second], elements[index.first][index.second]));
		shift_down(index);//in case it was larger/smaller than the node below it 
	}
	void shift_down(pair<int, int> index)
	{
		do
		{
			pair<int, int> index1 = make_pair(index.first + 1, index.second * 2);// the two nodes below it
			pair<int, int> index2 = make_pair(index.first + 1, index.second * 2 + 1);
			if (!isInRange(index1))
			{
				return;
			}
			if (!isInRange(index2))
			{
				if (!cmp(elements[index.first][index.second], elements[index1.first][index1.second]))
				{
					swap(index, index1);
				}
				return;
			}
			if (cmp(elements[index1.first][index1.second], elements[index2.first][index2.second]))// consider the left node first
			{
				if (!cmp(elements[index.first][index.second], elements[index1.first][index1.second]))
				{
					swap(index, index1);
					index = index1;
					continue;
				}
				if (!cmp(elements[index.first][index.second], elements[index2.first][index2.second]))
				{
					swap(index, index2);
					index = index2;
					continue;
				}
			}
			else//consider the right node first
			{
				if (!cmp(elements[index.first][index.second], elements[index2.first][index2.second]))
				{
					swap(index, index2);
					index = index2;
					continue;
				}
				if (!cmp(elements[index.first][index.second], elements[index1.first][index1.second]))
				{
					swap(index, index1);
					index = index1;
					continue;
				}

			}
			break;
			

		} while (index.first<=elements.size()-1);
		
	}

public:
	/*
	 * Constructor: Heap()
	 * Usage: Heap<greater<int>> maxHeap
	 */
	Heap();

	/*
	 * Constructor: Heap(vector<int> init_elements)
	 * Usage: Heap<greater<int>> maxHeap(init_elements)
	 * ------------------------------------------------
	 * You should implement this Method with O(mlog(n)) time complexity (m = init_elements.size(), n = elements.size())
	 */
	Heap(vector<int> init_elements);

	/*
	 * Destructor: ~Heap()
	 * Usage: usually implicit
	 */
	~Heap();

	/*
	 * Method: insert(int element)
	 * Usage: maxHeap.insert(1)
	 * ------------------------
	 * Add the new element in to the end of elements and shift_up this element
	 * You should implement this Method with O(log(n)) time complexity (n = elements.size())
	 */
	void insert(int element);

	/*
	 * Method: insert(vector<int> new_elements)
	 * Usage: maxHeap.insert(new_elements)
	 * ------------------------
	 * Add the new element in to the end of elements and shift_up this element one by one
	 * You should implement this Method with O(mlog(n)) time complexity (m = new_elements.size(), n = elements.size())
	 */
	void insert(vector<int> new_elements);

	/*
	 * Method: erase(int element)
	 * Usage: maxHeap.erase(1)
	 * ------------------------
	 * Swap this element with the elements's last element, delete the last element, and shift_down the swapped element
	 * You should implement this Method with O(log(n)) time complexity (n = elements.size())
	 */
	bool erase(int element);

	/*
	 * Method: pop()
	 * Usage: maxHeap.pop()
	 * ------------------------
	 * Swap the top element with the elements's last element, delete and return the last element, and shift_down the swapped element
	 * You should implement this Method with O(log(n)) time complexity (n = elements.size())
	 */
	int pop();

	/*
	 * Method: top()
	 * Usage: maxHeap.top()
	 * ------------------------
	 * return the top element
	 * You should implement this Method with O(log(1)) time complexity
	 */
	int top();

	/*
	 * Method: size()
	 * Usage: maxHeap.size()
	 * ------------------------
	 * return the number of element in the Heap
	 * You should implement this Method with O(log(1)) time complexity
	 */
	int size();
	/*
	    I add it myself for debugging
	*/
	void print();
};

template<class Compare>
Heap<Compare>::Heap()
{
	// you code here
}

template<class Compare>
Heap<Compare>::~Heap()
{

}

template<class Compare>
Heap<Compare>::Heap(vector<int> init_elements)
{
	elements[0].push_back(init_elements[0]);
	for (int i = 1; i < init_elements.size(); i++)
	{
		insert(init_elements[i]);
	}
}

template<class Compare>
void Heap<Compare>::insert(int element)
{
	if (elements[elements.size() - 1].size() < pow(2, elements.size() - 1))
	{
		elements[elements.size() - 1].push_back(element);
	}
	else
	{
		elements[elements.size()] = { element};
	}
	shift_up(make_pair(elements.size() - 1, elements[elements.size() - 1].size()-1));
	

}

template<class Compare>
void Heap<Compare>::insert(vector<int> new_elements)
{
	for (int i = 0; i < new_elements.size(); i++)
	{
		if (elements[elements.size() - 1].size() < pow(2, elements.size() - 1))
		{
			elements[elements.size() - 1].push_back(new_elements[i]);
		}
		else
		{
			elements[elements.size()] = { new_elements[i]};
		}
		shift_up(make_pair(elements.size() - 1, elements[elements.size() - 1].size() - 1));
	}
}



template<class Compare>
bool Heap<Compare>::erase(int element)
{
	pair<int, int> temp=findIndex( element);
	pair<int, int> last = { elements.size() - 1,elements[elements.size() - 1].size() - 1 };
	swap(temp, last);
	elements[elements.size() - 1].pop_back();
	shift_down(temp);
	return true;
}

template<class Compare>
int Heap<Compare>::pop()
{
	pair<int, int> first = { 0,0 };
	pair<int, int> last = { elements.size() - 1,elements[elements.size() - 1].size() - 1 };
	int temp = elements[0][0];
	swap(first, last);
	elements[elements.size() - 1].pop_back();
	shift_down(first);
	return temp;
}

template<class Compare>
int Heap<Compare>::top()
{
	return elements[0][0];
}

template<class Compare>
int Heap<Compare>::size()
{
	int size = 0;
	for (int i = 0; i < elements.size(); i++)
	{
		size += elements[i].size();
	}
	return size;
}
template<class Compare>
void Heap<Compare>::print()
{
	for (int i = 0; i < elements.size(); i++)
	{
		for (int j = 0; j < elements[i].size(); j++)
		{
			std::cout << elements[i][j]<<" ";
		}
		std::cout << endl;
	}
}
#endif
