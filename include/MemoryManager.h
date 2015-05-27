#include <iostream>
#include <sstream>

using namespace std;

#define RESERVED_MEMORY (50000 * 24) //Reserved bytes

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
