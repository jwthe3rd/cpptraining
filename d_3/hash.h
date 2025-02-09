#include <bits/stdc++.h>


struct HashTable
{
    // Basic structure of a Hash table
    int size;

    vector<vector<int>> table;

    void addItem(int key)
    {
        int index = hashFunction(key);
        table[index].push_back(key);
    }

    // User defined hash variables

    void deleteItem(int key);

    int hashFunction(int x);

    void displayHash();

    // Constructor to init

    HashTable(int b)
    {
        this->size = b;

        table.resize(size);
    }

};


