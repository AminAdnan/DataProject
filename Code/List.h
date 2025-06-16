#pragma once
#include <iostream>
using namespace std;




template<typename t>
class List
{
public:
    t* values;
    int capacity;
    int counter;

    List(int c = 100)
    {
        capacity = c;
        counter = 0;
        values = new t[capacity];
    }

    bool insert(t item)
    {
        if (counter < capacity)
        {
            values[counter] = item;
            counter++;
            return true;
        }
        return false;
    }

    int size()
    {
        return counter;
    }


    void print()
    {
        for (int i = 0; i < counter; ++i)
        {
            cout << values[i] << " ";
        }
        cout << endl;
    }

    bool insertAt(t item, int index)
    {
        t temp;
        t temp2;
        if (counter < capacity)
        {
            temp = values[index + 1];
            int a = 0;
            values[index + 1] = values[index];
            for (int i = index + 1; i < counter; ++i)
            {
                temp2 = values[i + 1];
                values[i + 1] = temp;
                int j = 0;
                temp = temp2;


            }
            values[index] = item;
            counter++;
            return true;
        }
        return false;
    }

    int search(t item)
    {
        for (int i = 0; i < counter; ++i)
        {
            if (values[i] == item)
            {
                return i;
            }
        }
        return -1;
    }


    bool insertAfter(t inserted, t item)
    {
        int index = search(item);
        if (index == -1)
        {
            return false;
        }

        return insertAt(inserted, index + 1);
    }

    bool insertBefore(t inserted, t item)
    {
        int index = search(item);
        if (index == -1)
        {
            return false;
        }

        return insertAt(inserted, index);
    }

    bool isEmpty()
    {
        return (counter == 0);
    }

    bool isFull()
    {
        return (counter == capacity);
    }

    bool remove(t item)
    {
        int index = search(item);
        if (index == -1)
        {
            return false;
        }

        for (int i = index; i < capacity; ++i)
        {
            values[i] = values[i + 1];
        }
        counter--;
        return true;

    }

    bool removeAt(int index)
    {
        if (index < 0 || index >= counter)
            return false;

        for (int i = index; i < counter - 1; ++i)
            values[i] = values[i + 1];

        counter--;
        return true;
    }

    bool removeAfter(t item)
    {
        int index = search(item) + 1;
        if (index == -1)
        {
            return false;
        }

        for (int i = index; i < capacity; ++i)
        {
            values[i] = values[i + 1];
        }
        counter--;
        return true;

    }

   

    bool removeBefore(t item)
    {
        int index = search(item) - 1;
        if (index == -1)
        {
            return false;
        }

        for (int i = index; i < capacity; ++i)
        {
            values[i] = values[i + 1];
        }
        counter--;
        return true;


    }

    bool operator==(List& l)
    {
        if (l.counter != counter)
        {
            return false;
        }
        for (int i = 0; i < counter; ++i)
        {
            if (values[i] != l.values[i])
            {
                return false;
            }
        }
        return true;

    }

   


};