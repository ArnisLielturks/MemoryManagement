#include "../include/MemoryManager.h"

MemoryManager::MemoryManager()
{
	freestore = new char[RESERVED_MEMORY];
	last = -1;
}

MemoryManager::~MemoryManager()
{
	delete freestore;
}

void* MemoryManager::allocate(size_t object_size)
{
    int current = last + 1;
    if ((last + object_size) > RESERVED_MEMORY -1) {
      ostringstream oss;
      oss << "No memory available size(" << object_size << "), current position(" << current << ")";
      throw OutOfMemoryException(oss.str());
    }
    last+=object_size;
    return &freestore[current];
}

void* MemoryManager::getPointer(int num)
{
	return &freestore[num];
}
