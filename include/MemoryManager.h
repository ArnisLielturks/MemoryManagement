#pragma once
#include <iostream>
#include <sstream>

using namespace std;

//How much bytes to reserve for the memory manager class
#define RESERVED_MEMORY (500000 * 24) //Reserved bytes

//Simple exception to throw for the memory manager class
struct OutOfMemoryException : public exception
{
    string s;
    OutOfMemoryException(string ss) : s(ss) {}
    ~OutOfMemoryException() throw () {}
    const char* what() const throw() {
        return s.c_str();
    }
};

class MemoryManager {
public:
	MemoryManager();
	~MemoryManager();
	void* allocate(size_t size);
	void* getPointer(int num);
	int last;
private:
	char *freestore;
};
