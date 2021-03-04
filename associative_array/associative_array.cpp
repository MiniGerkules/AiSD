#include <iostream>
#include "Map.h"

using namespace std;

int main()
{
    try
    {
        Map<size_t, string>* map = new Map<size_t, string>();
        
        if (map == nullptr)
            throw domain_error("Memory allocation error for red-black tree!");

        cout << "Let's add some values to our associative array:" << endl;
        map->insert(10, "abc");
        map->insert(50, "123");
        map->insert(75, "LETI");
        map->insert(100, "C++");
        map->insert(125, "Bjarne Stroustrup.");
        map->insert(150, "C will live forever!");
        map->insert(175, "The ideas are over.");

        map->print();

        cout << "\nAll keys of an associative array:" << endl;
        vector<size_t>* keys = map->get_keys();
        for (size_t i = 0; i < keys->size(); ++i)
            cout << (*keys)[i] << " ";
        keys->clear();

        cout << "\n\nAll values of an associative array:" << endl;
        vector<string>* values = map->get_values();
        for (size_t i = 0; i < values->size(); ++i)
            cout << (*values)[i] << " ";
        values->clear();
        
        cout << endl;
        cout << "\nRemove the root of the red-black tree:" << endl;
        map->remove(50);
        map->print();

        cout << "\nLet's find a non-existent element:" << endl;
        try
        {
            map->find(200);
        }
        catch (domain_error error)
        {
            cerr << "ERROR: " << error.what() << endl;
        }

        cout << "\nFind an existing item with key 175:" << endl;
        cout << "Item with key 175 contains value = " << map->find(175)->get_value() << endl;

        delete map;
    }
    catch (domain_error error)
    {
        cerr << "ERROR: " << error.what() << endl;
    }
    catch (out_of_range error)
    {
        cerr << "ERROR: " << error.what() << endl;
    }

    return 0;
}
