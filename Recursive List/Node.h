#ifndef MS_LIST_Node_H
#define MS_LIST_Node_H

//Made By: Shane Soderstrom
//Date: 7/8/17

#include <cstdlib>
#include <exception>

/**
* Modify this header file to include the method bodies inline with the class definition here,
* the same way you would do if you were writing C# or Java code.
* Feel free to finish the documentation if it bothers you, though you aren't being graded on that for this project.
* Some functions have dummy values so that the code compiles. You need to change them in order to make it work.
*/

typedef int value_type;
class Node
{
private:
	value_type data;
	Node* next_ptr;

public:
	Node(const value_type& d = value_type(), Node* next_ptr = NULL)
	{
		data = d;
	};

	Node(const Node& source)
	{
		data = source.data;
		next_ptr = source.next_ptr;
	}

	~Node()
	{
		//apparently nothing here because there is no dynamic memory being allocated
	}

	Node* next()
	{
		return next_ptr;
		//return (Node*)NULL;
	}

	void set_next(Node* ptr)
	{
		next_ptr = ptr;
	}

	value_type get_data()
	{
		return data;
	}

	void set_data(const value_type& d)
	{
		data = d;
	}

	Node operator =(const Node& source)
	{
		data = source.data;
		next_ptr = source.next_ptr;
		return *this;
	}

	/**
	* Node1 < Node2 if Node1.data < Node2.data
	*@param other another node to comapre to this one
	*@return true if this node < other node, false otherwise
	*/
	bool operator <(const Node& other)
	{
		return data < other.data;
	}

	/**
	* Node1 > Node2 if Node1.data > Node2.data
	*@param other another node to comapre to this one
	*@return true if this node > other node, false otherwise
	*/
	bool operator >(const Node& other)
	{
		return data > other.data;
	}

	/**
	* Node1 == Node2 if Node1.data == Node2.data
	*@param other another node to comapre to this one
	*@return true if this node == other node, false otherwise
	*/
	bool operator ==(const Node& other) {
		return data == other.data;
	}
};

#endif