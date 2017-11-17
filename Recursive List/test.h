#ifndef TEST_H
#define TEST_H
#include <cstddef>
#include <iostream>
using std::size_t;

// Unit Test Scaffolding: Users call test_, fail_, succeed_, throw_, nothrow_, and report_
// AUTHOR: Chuck Allison (Creative Commons License, 2001 - 2017)

namespace {
	enum { EQUAL, LESS, LESS_EQ, GREATER, GREATER_EQ, CLOSE };
	size_t nPass{ 0 };
	size_t nFail{ 0 };
	void do_fail(const char* text, const char* fileName, long lineNumber) {
		std::cout << "FAILURE: " << text << " in file " << fileName
			<< " on line " << lineNumber << std::endl;
		++nFail;
	}
	void do_test(const char* condText, bool cond, const char* fileName, long lineNumber) {
		if (!cond)
			do_fail(condText, fileName, lineNumber);
		else
			++nPass;
	}
	template<typename T>
	void do_compare(int op, const char* lstr, T left, const char* rstr,
		T right, const char* fileName, long lineNumber) {
		switch (op) {
		case EQUAL:
			if (left == right)
				++nPass;
			else {
				std::cout << "FAILURE:  in file " << fileName
					<< " on line " << lineNumber << ": " << left
					<< "=" << right << std::endl;
				++nFail;
			}
			break;
		case LESS:
			if (left < right)
				++nPass;
			else {
				std::cout << "FAILURE:  in file " << fileName
					<< " on line " << lineNumber << ": " << left
					<< "<" << right << std::endl;
				++nFail;
			}
			break;
		case LESS_EQ:
			if (left <= right)
				++nPass;
			else {
				std::cout << "FAILURE:  in file " << fileName
					<< " on line " << lineNumber << ": " << left
					<< "<=" << right << std::endl;
				++nFail;
			}
			break;
		case GREATER:
			if (left > right)
				++nPass;
			else {
				std::cout << "FAILURE:  in file " << fileName
					<< " on line " << lineNumber << ": " << left
					<< ">" << right << std::endl;
				++nFail;
			}
			break;
		case GREATER_EQ:
			if (left >= right)
				++nPass;
			else {
				std::cout << "FAILURE:  in file " << fileName
					<< " on line " << lineNumber << ": " << left
					<< ">=" << right << std::endl;
				++nFail;
			}
			break;
		}
	}
	void succeed_() {
		++nPass;
	}
	void report_() {
		std::cout << "\nTest Report:\n\n";
		std::cout << "\tNumber of Passes = " << nPass << std::endl;
		std::cout << "\tNumber of Failures = " << nFail << std::endl;
	}
}
#define test_(cond) do_test(#cond, cond, __FILE__, __LINE__)
#define fail_(text) do_fail(text, __FILE__, __LINE__)
#define assert_equal(left,right) do_compare(EQUAL,#left,left,#right,right,__FILE__,__LINE__)
#define assert_less(left,right) do_compare(LESS,#left,left,#right,right,__FILE__,__LINE__)
#define assert_less_eq(left,right) do_compare(LESS_EQ,#left,left,#right,right,__FILE__,__LINE__)
#define assert_greater(left,right) do_compare(GREATER,#left,left,#right,right,__FILE__,__LINE__)
#define assert_greater_eq(left,right) do_compare(GREATER_EQ,#left,left,#right,right,__FILE__,__LINE__)
#define throw_(text,T)                      \
    try {                                   \
        text;                               \
        std::cout << "THROW ";              \
        do_fail(#text,__FILE__,__LINE__);   \
    } catch (T&) {                          \
        ++nPass;                            \
    } catch (...) {                         \
        std::cout << "THROW ";              \
        do_fail(#text,__FILE__,__LINE__);   \
    }

#define nothrow_(text)                      \
    try {                                   \
        text;                               \
        ++nPass;                            \
    } catch (...) {                         \
        std::cout << "NOTHROW ";            \
        do_fail(#text,__FILE__,__LINE__);   \
    }        
#endif
