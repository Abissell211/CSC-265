#ifndef LIST_H
#define LIST_H

#include <iostream>

using namespace std;

template <class Item>
class List
{
  public:
    List();
    void insert(const Item& entry);
    void print() const;
  private:
    Item array[100];
    int count;
};

#include "List.cpp"

#endif
