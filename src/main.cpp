#include <iostream>
#include <ctime>
#include "../include/MemoryManager.h"
using namespace std;

//GLOBAL memory manager class
MemoryManager manager;

//Object that will utilize the memory manager
class SomeObject {
public:
  SomeObject(){};
  SomeObject(int a, int b, int c): x(a), y(b), z(c) {}
  float x;
  float y;
  float z;
  float a;
  float b;
  float c;
  //Override new operator to use memory manager instead
  inline void* operator new(size_t size) {
    return reinterpret_cast<SomeObject*>(manager.allocate(size));
  }
};

//Class without memory manager, will allocate memory on heap
class SomeObject2 {
public:
  SomeObject2(){};
  SomeObject2(int a, int b, int c): x(a), y(b), z(c) {}
  float x;
  float y;
  float z;
  float a;
  float b;
  float c;
};

int main(int argc, char* argv[])
{
  cout << "MM\tVS\tDynamic" << endl;
  for (int steps = 0; steps < 10; steps++) {
    long first, second;
    manager.last = -1;
    long start_time = clock();
    SomeObject *arr[500000];
    //Create many objects using memory manager
    for(int i=0; i < 500000; i++) {
      try {
        arr[i] = new SomeObject(i,i*10,i*100);
      } catch(OutOfMemoryException &ex) {
        cout << "exception occured 1 " << ex.what() << endl;
      }
    }
    first = (clock() - start_time);
    cout << first;


    //Create many objects using dynamic memory allocation
    start_time = clock();
    SomeObject2 *arr2[500000];
    for(int i=0; i < 500000; i++) {
      arr2[i] = new SomeObject2(i, i+2, i+4);
    }
    //Delete all the objects in the array
    for(int i=0; i < 500000; i++) {
      delete arr2[i];
    }

    second = (clock() - start_time);
    cout << "\tVS\t" << second;
    float faster = ((float)second/(float)first);
    cout << "\t" << faster << " times faster" << endl;
  }
  cout << endl << endl;

  //Just some test to show first few objects from the memory manager
  for (int i=0; i < 5; i++) {
    SomeObject *end = reinterpret_cast<SomeObject*>(manager.getPointer(i*sizeof(SomeObject)));
    cout << end->x << "; " << end->y << "; " << end->z << endl;
  }
  return 0;
}
