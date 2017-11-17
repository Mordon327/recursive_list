#ifndef MAIN_SAVITCH_LIST_H
#define MAIN_SAVITCH_LIST_H

//Made By: Shane Soderstrom
//Date: 7/8/17

/**
* Modify this code with method bodies inline with signatures,
* as you would in C# or Java.  Do not put method bodies in a separate
* .cpp file. Some code has dummy return values, just to make it compile.
* You may need to add other header files as well, depending on how you do console i/o
* for print.
*/

#include <cstdlib>
#include <exception>
#include "node.h"

using std::out_of_range;
using std::cout;
using std::endl;

typedef int value_type;


class List
{
private:

	Node *head;
	Node *tail;

public:
	// postcondition: list is initialized
	List() 
	{
		head = NULL;
		tail = NULL;
	};

	/**
	* copy constructor
	*@param other the List that we will make a deep copy of.
	*/
	List(List& other)
	{

		//{	
		//if (&other == this)
		//{
		//	return;
		//}
		//else if (other.head == nullptr;)
		//{
		//	return;
		//}
		//else
		//{
		//	head = new Node(*other.head);
		//	Node *currentOther = other.head;
		//	Node *currentThis = head;

		//	while (currentOther->next() != nullptr)
		//	{
		//		Node *aNode = new Node(*currentOther->next());
		//		currentThis->set_next(aNode);
		//		currentOther = currentOther->next();
		//		currentThis = currentThis->next();
		//	}
		//	tail = currentThis;
		//}
		//};


		if (other.isEmpty())
		{
			return;
		}
		else
		{
			List list;
			Node * nextNode;
			nextNode = new Node(other.head->get_data(), other.head->next());
			Node* temp = other.head;
			nextNode->set_data(temp->get_data());
			list.head = nextNode;
			nextNode->set_next(temp->next());
			temp = temp->next();

			for (int i = 0; i < other.length() - 1; i++)
			{	
				nextNode->set_data(temp->get_data());
				Node* nextTemp;
				nextTemp = new Node(0, NULL);
				temp = temp->next();
				nextNode->set_next(nextTemp);
				nextNode = nextNode->next();
				if (nextNode != NULL)
				{
					list.tail = nextNode;
				}
			}	
		}
	};

	/**
	* Print the list to the console
	*/
	void print() 
	{
		int size = length();
		int count = 0;
		Node* temp = nullptr;

		for (temp = head; count < size; temp = temp->next()) {
			if (count == (size - 1)) {
				std::cout << temp->get_data() << std::endl;
			}
			else {
				std::cout << temp->get_data() << ", ";
			}
		}

		return;
	};


	/** postcondition: d is inserted at position index, items past that point
	* move one position (to the "right"). List length increases by 1.
	* throw std::out_of_range error if index is < 0 or > length of the array.
	*@param index
	*@param d
	*/
	void insert(int index, value_type d) 
	{		
		int listLength = length();

		if (listLength < index || index < 0)
		{
			throw out_of_range("Bad index.");
		}

		else if (isEmpty())
		{
			head = tail = new Node(d, NULL);
		}

		else
		{
			Node * newNode = new Node(d, NULL);

			if (index == 0)
			{
				newNode->set_next(head);
				head = newNode;
				if (listLength == 0)
				tail = newNode;
			}

			else if (listLength == index)
			{
				tail->set_next(newNode);
				tail = tail->next();
			}
			else
			{
				Node * temp = head;

				for (int i = 0; i < index - 1; i++)
				{
					temp = temp->next();
				}

				newNode->set_next(temp->next());
				temp->set_next(newNode);
			}
		}
		listLength++;
	};

	/**
	* move one position to the "left"). List length is shorter by 1.
	* @param index
	* postcondition: node at position index is removed, items past that point
	* Cursor points "at" node now at position index.
	* throw std::out_of_range error if index is < 0 or > length of the array.
	*/
	void remove(int index)
	{
		int listLength = length();
		if (isEmpty() || listLength < index || index < 0)
		{
			throw out_of_range("Bad index.");
		}
		else
		{
			Node * temp = head;
			if (index == 0)
			{
				head = head->next();
				delete temp;
			}
			else if (index == listLength)
			{
				for (int i = 0; i < index - 1; i++)
				{
					temp = temp->next();
				}
				tail = temp;
				temp = temp->next();
				delete temp;
			}
			else
			{
				Node* deadNode;
				for (int i = 0; i < index - 1; i++)
				{
					temp = temp->next();
				}
				deadNode = temp->next();
				temp->set_next(deadNode->next());
				delete deadNode;
			}
		}
		
		
	};

	/**
	* find the value in the list.
	* @param the target value to find
	* @return if d is in the list then return position of first occurance else return -1.
	*/
	int find(value_type d) 
	{
		if (isEmpty())
		{
			return -1;
		}

		else
		{
			//find where the value is
			Node * temp = head;
			int listLength = length();
			for (int i = 0; i < listLength; i++)
			{
				int test = temp->get_data();
				if (test == d)
				{
					return i;
				}
				temp = temp->next();
				
			}
		}
		return -1;
	};

	/**
	* Return the value at position n in the list.
	* throw outof range exception if n is < 0 or > size
	* @param n the index of the target item.
	* @return the value at position n, or an exception if n is out of range.
	*/
	value_type at(int n) 
	{
		Node * temp = head;
		int listLength = length();
		if (n < 0 || listLength < n)
		{
			throw out_of_range("Bad index.");
			return 0;
		}
		else if (n == listLength)
		{
			return tail->get_data();
		}
		//find where at is and return data.
		else
		{
			for (int i = 0; i < n; i++)
			{
				temp = temp->next();
			}
		}
		return temp->get_data();
	};


	/**
	* Return the length of the list
	*@return the length of the list as an integer
	*/
	int length() 
	{
		Node* cursor = head;
		int count = 0;
		
		while (cursor != NULL)
		{
			count++;
			cursor = cursor->next();
		}
		return count;
	};

	/**destructively append a list onto the end of the list
	* the size increases by the length of the appended list
	*/
	List append(List& other) 
	{
		if (other.isEmpty())
		{
			return (*this);
		}
		else
		{
			tail->set_next(other.head);
			tail = other.tail;
			return (*this);
		}
	};

	/**
	* Destructor
	*/
	~List()
	{
		//couldn't get the destructor to work correctly.
		//while (head != nullptr && !isEmpty())
		//{
		//	int size = length();
		//	for (int i = 0; i < size; i++)
		//	remove(0);
		//}
	};

	/**
	*@return return true if empty, false otherwise
	* quickest way is check if head == NULL.
	*/
	bool isEmpty() 
	{
		return head == NULL;
	};


	/**
	* assignment operator
	//Make a copy of the list on the right-hand side
	//and return that
	*/
	List operator =(const List& source) 
	{
		//since I cant get source.length to work, I'm counting the size the long way.
		List list;
		Node* cursor = source.head;
		int count = 0;

		while (cursor != NULL)
		{
			count++;
			cursor = cursor->next();
		}

		//if the list is empty
		if (count == 0)
		{
			return list;
		}
		else
		{
			Node * nextNode;
			nextNode = new Node(source.head->get_data(), source.head->next());
			Node* temp = source.head;
			nextNode->set_data(temp->get_data());
			list.head = nextNode;
			nextNode->set_next(temp->next());
			temp = temp->next();

			//make a new list with nodes that have the same values.
			for (int i = 0; i < count - 1; i++)
			{
				nextNode->set_data(temp->get_data());
				Node* nextTemp;
				nextTemp = new Node(0, NULL);
				temp = temp->next();
				nextNode->set_next(nextTemp);
				nextNode = nextNode->next();
				if (nextNode != NULL)
				{
					list.tail = nextNode;
				}
			}
			return list;
		}
	};
};

/**
* Add the data item d to the specified list in sorted order.
* This means find where it should be and insert it there.
*@param d
*@param list
*/
void add(value_type d, List &list) 
{
	if (!list.isEmpty())
	{
		int i;
		for (i = 0; i < list.length(); i++)
		{
			if (list.at(i) > d)
			break;
		}
		list.insert(i, d);
	}
	else
	{
		list.insert(0, d);
	}
};
#endif