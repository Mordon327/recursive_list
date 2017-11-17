#include <iostream>
#include <sstream>
#include "test.h"
#include "list.h"
#include "node.h"

using namespace std;

/**
* Tests for List
*/
	void test_empty()
	{
		List list;
		bool x = list.isEmpty();
		assert_equal(true,x);
		assert_equal(0,list.length());
	}
	

	void test_insert_to_empty()
	{
		List list;
		int len = 4;
		int expected[] = { 5, 10, 20, 30 };
		for (int i = 1; i < len; i++) {
			list.insert(i-1,expected[i]);
			assert_equal(expected[i],list.at(i-1));
		}
		
		list.insert(0,expected[0]);
		for (int i = 0; i < len; i++) {
			assert_equal(expected[i], list.at(i));
		}
	}

	void test_insert_in_middle()
	{
		List list;
		add(10, list);
		add(20, list);
		add(30,list);
		list.insert(1,(value_type)15);
		int len = 4;
		int expected[] = { 10,15,20,30 };
		for (int i = 0; i < len; i++) {
			assert_equal(expected[i], list.at(i));
		}
	}

	void test_insert_out_of_bounds()
	{
		List list;
		throw_(list.insert(1,10), std::out_of_range);
		add(10, list);
		add(20, list);
		throw_(list.insert(5,30), std::out_of_range);
	}

	void test_remove_middle_first_last()
	{
		List list;
		value_type expected[] = { 10, 30 };
		for (int i = 10; i < 40; i += 10) {
			add(i,list);
		}
		list.remove(1);
		assert_equal(2,list.length());
		for (int i = 0; i < 2; i++)
		{
			assert_equal(expected[i],list.at(i));
		}
		
		list.remove(0);
		assert_equal(1,list.length());
		assert_equal(30, list.at(0));
		list.remove(0);
		assert_equal(true, list.isEmpty());
	}

	void test_romove_middle_last_first()
	{
		List list;
		value_type expected[] = { 10, 30 };
		for (int i = 10; i < 40; i += 10) {
			add(i, list);
		}
		list.remove(1);
		int size = list.length();
		assert_equal(2,size);
		for (int i = 0; i < 2; i++)
		{
			assert_equal(expected[i],list.at(i));
		}
		
		list.remove(size-1);
		assert_equal(1, list.length());
		assert_equal(10, list.at(0));
		list.remove(0);
		test_(list.isEmpty());
	}


	void test_copy_constructor() {
		List original;
		add(10, original);
		add(20, original);

		List copy1(original);
		add(30, original);
		
		int expValues[] = { 10, 20 };
		for (int i = 0; i < 2; i++)
		{
			assert_equal(expValues[i], copy1.at(i));
		}
		test_(original.length() > copy1.length());
	}

	void test_find() {
		List list;
		value_type expected[] = { 10, 20, 30, 40, 50 };
		for (int i = 10; i < 60; i += 10) {
			add(i, list);
		}
		int pos = list.find(10);
		assert_equal(0, pos);
		pos = list.find(30);
		assert_equal(2,pos);
		pos = list.find(50);
		assert_equal(4, pos);
		pos = list.find(100);
		assert_equal(-1, pos);
	}
	
	void test_at() {
		//it's been tested other places
	}
	
	void test_length() {
		//tested enough other places
	}
	
	void test_append() 
	{
		List list;
		List list1;
		//test nominal list
		value_type expected[6] = { 10, 20, 30, 40, 50, 60 };
		for (int i = 10; i < 40; i += 10) {
			add(i,list);
		}
		for (int i = 40; i < 70; i += 10) {
			add(i,list1);
		}
		list.append(list1);
		for (int i = 0; i < 6; i++) {
			test_(expected[i]== list.at(i));
		}
		
		List *list3 = new List();
		List *list4 = new List();

		for (int i = 10; i < 40; i += 10) {
			add(i, *list3);
		}
		for (int i = 40; i < 70; i += 10) {
			add(i, *list4);
		}
		list3->append(*list4);
		for (int i = 0; i < 6; i++) {
			test_(expected[i] == list3->at(i));
		}
		delete list3;
		delete list4;

	}
	void test_op_assignment() {
		List original;
		List copy1;
		copy1 = original;
		add(10,original);
		assert_equal(10,original.at(0));
		test_(copy1.isEmpty());

	}

	void test_op_assign_self() {
		List original;
		original.insert(0,10);
		original = original;
		assert_equal(1, original.length());
		assert_equal(10, original.at(0));
	}

	void test_random_insertion()
	{
		int values[6] = {5, 4, 7, 22, 18, 10};
		int expected[6] = { 4,5,7,10,18,22 };
		List list;
		for (int value : values)
		{
			add(value, list);
		}
		for (int i = 0; i < 6; i++) {
			assert_equal(expected[i], list.at(i));
		}
	}

	void test_print()
	{
		List list;
		int expValues[] = { 10, 20, 30, 40, 50 };
		for (int value : expValues) {
			add(value, list);
		}
		ostringstream oss;
		streambuf* p_cout_streambuf = cout.rdbuf();
		cout.rdbuf(oss.rdbuf());

		list.print();

		cout.rdbuf(p_cout_streambuf); // restore
									  // test your oss content...
		test_(oss && oss.str() == "10 20 30 40 50 \n");

	}

	
	void list_unit_tests() {
		test_empty();
		test_insert_to_empty();
		test_insert_in_middle();
		test_insert_out_of_bounds();
		test_append();
		test_at();
		test_length();
		test_remove_middle_first_last();
		test_romove_middle_last_first();
		test_find();
		test_copy_constructor();
		test_op_assignment();
		test_op_assign_self();
		test_random_insertion();
		test_print();
	}
	/**
	* Node Unit Tests
	*/
	void test_empty_node()
	{
		Node node;
		test_(NULL == node.next());
		assert_equal(0, node.get_data());

	}

	void test_nominal_node()
	{
		Node node;
		Node node1;
		node.set_data(1);
		node1.set_data(2);
		node.set_next(&node1);
		assert_equal(1, node.get_data());
		assert_equal(&node1, node.next());
		assert_equal(2, node1.get_data());
		test_(NULL == node1.next());
	}

	void test_node_copy_constructor()
	{
		Node node;
		Node node1;
		node.set_data(35);
		node1 = node;
		assert_equal(node.get_data(), node1.get_data());
		node.set_data(82);
		test_(node1.get_data() != node.get_data());
		node1.set_data(77);
		assert_equal(77, node1.get_data());

		node = Node(5);
		assert_equal(5, node.get_data());

	}
	void test_node_set()
	{
		// tested enough elsewhere
	}
	void test_node_next()
	{
		//currently tested in test_nominal_node
	}
	
	void test_relational_ops()
	{
		Node node;
		Node node1 = Node(1);
		Node node2 = node1;
		
		test_(node < node1);
		test_(node1 > node);
		test_(node1 == node2);


	}
	void node_unit_tests()
	{
		test_empty_node();
		test_nominal_node();
		test_node_copy_constructor();
		test_node_set();
		test_node_next();
		test_relational_ops();
	}

	
	int main()
	{
		node_unit_tests();
		list_unit_tests();
		report_();
		std::cin.ignore(); 
		return 0;

	}
