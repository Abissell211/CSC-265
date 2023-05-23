template <class Item>
List<Item>::List()
{
  count = 0;
  
  for(int i = 0; i < 100; i++)
    array[i] = 0;
}

template <class Item>
void List<Item>::insert(const Item& entry)
{
  if(count < 100)
  {
    array[count] = entry;
    count++;
  }
}

template <class Item>
void List<Item>::print() const
{
  for(int i = 0; i < count; i++)
    cout << array[i] << endl;
}
