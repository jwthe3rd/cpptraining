#include "./hash.h"

using namespace std;


void HashTable::deleteItem(int key)
{
    int index = hashFunction(key);

    auto it = find(table[index].begin(), table[index].end(), key);

    if (it!=table[index].end())
    {
        table[index].erase(it);
    }
}


void HashTable::displayHash() 
{
    for (int i = 0; i < size; i++)
    {
        cout << i;
        for (int x : table[i])
        {
            cout << "--->" << x;
        }
        cout << endl;
    }
}

int HashTable::hashFunction(int x)
{
    return (x*2 % size);
}


int main()
{

    vector<int> a = {4, 66, 77, 5, 0, 81};

    HashTable h(81);

    for (int key : a)
        h.addItem(key);

    h.deleteItem(0);

    h.displayHash();



    return 0;
}

