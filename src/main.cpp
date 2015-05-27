#include <iostream>
#include <ctime>
#include "../include/MemoryManager.h"
using namespace std;

//GLOBAL memory manager class
MemoryManager manager;

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
  inline void* operator new(size_t size) {
    return reinterpret_cast<SomeObject*>(manager.allocate(size));
  }
};

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
    manager.last = -1;
    long start_time = clock();
    SomeObject *arr[50000];
    for(int i=0; i < 50000; i++) {
      try {
        arr[i] = new SomeObject(i,i*10,i*100);
      } catch(OutOfMemoryException &ex) {
        cout << "exception occured 1 " << ex.what() << endl;
      }
    }
    cout << (clock() - start_time);



    start_time = clock();
    SomeObject2 *arr2[50000];
    for(int i=0; i < 50000; i++) {
      arr2[i] = new SomeObject2(i, i+2, i+4);
    }

    for(int i=0; i < 50000; i++) {
      delete arr2[i];
    }

    cout << "\tVS\t" << (clock() - start_time) << endl;
  }
  cout << endl << endl;
  for (int i=0; i < 10; i++) {
    SomeObject *end = reinterpret_cast<SomeObject*>(manager.getPointer(i*24));
    cout << end->x << "; " << end->y << "; " << end->z << endl;
  }
  return 0;
}
