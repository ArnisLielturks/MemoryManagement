#include "../include/MemoryManager.h"

MemoryManager::MemoryManager()
{
  //Dynamically allocate memory
	freestore = new char[RESERVED_MEMORY];
	last = -1;
}

MemoryManager::~MemoryManager()
{
  //Do some cleanup when memory manager is no longer needed
	delete freestore;
}

void* MemoryManager::allocate(size_t object_size)
{
    int current = last + 1;
    //Check if there's enough memory in the freestore
    if ((last + object_size) > RESERVED_MEMORY -1) {
      ostringstream oss;
      oss << "No memory available size(" << object_size << "), current position(" << current << ")";
      throw OutOfMemoryException(oss.str());
    }
    last+=object_size;
    //Return pointer to the first available byte
    return &freestore[current];
}

//Get pointer for any byte in the freestore array
void* MemoryManager::getPointer(int num)
{
	return &freestore[num];
}
