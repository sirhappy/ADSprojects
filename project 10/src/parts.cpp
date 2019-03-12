//
// Created by ZV on 03.12.2017.
//

#include <iostream>
#include "parts.h"

using namespace std;

using subpartsMap = map<Part*, int>;    //map of subparts and their quantity
using nameMap = map<string, Part*>;     //map of names and corresponding parts

void Part::describe()
{
    cout << "Part " << name << " subparts are:" << endl;

    if (subparts.empty())
        cout << "There are no subparts" << endl;

    for (subpartsMap::const_iterator it = subparts.begin(); it != subparts.end(); ++it)
        cout << "\t" << it->second << " " << it->first->name << endl;
}

int Part::count_howmany(Part const* p)
{
    if (this == p)  //if searched element is found break recursion
        return 1;

    if (subparts.empty())   //if searched element isn't found break recursion
        return 0;

    int howMany = 0;

    //Recursively count number of searched parts in the tree.
    for (subpartsMap::const_iterator it = subparts.begin(); it != subparts.end(); ++it)
        howMany += it->first->count_howmany(p) * it->second;

    return howMany;
}

int Part::count_howmanyUp(Part* const p)
{
    if (p == this)  //if we reached upper element in our query break recursion
        return 1;

    //if the order of parts in query was wrong and the
    //top element of the tree was reached break recursion
    if (!p->parent)
        return 0;

    //count the quantity of searched parts raising by the tree recursively
    int howMany = p->parent->subparts[p] * count_howmanyUp(p->parent);

    return howMany;
}

Part* NameContainer::lookup(std::string const& name)
{
    //Check if part is present in name_map. If it is, return pointer to it
    nameMap::const_iterator it = name_map.find(name);
    if (it != name_map.end())
        return it->second;

    //Add new Part to name_map and return pointer to it
    Part* newPart = new Part(name);
    name_map.insert(make_pair(name, newPart));

    return newPart;
}

void NameContainer::add_part(std::string const& x, int q, std::string const& y)
{
    //Find or create part and subpart by names
    Part* part = lookup(x);
    Part* subpart = lookup(y);

    //make part parent element of subpart
    subpart->parent = part;

    //insert subpart to subpart's map of part
    part->subparts.insert(make_pair(subpart, q));
}

NameContainer::NameContainer(const NameContainer& other)
{
    for (nameMap::const_iterator it = other.name_map.begin(); it != other.name_map.end(); ++it)
        for (subpartsMap::const_iterator innerIt = it->second->subparts.begin();
             innerIt != it->second->subparts.end();
             ++innerIt)
            add_part(it->second->name, innerIt->second, innerIt->first->name);
}


NameContainer& NameContainer::operator=(const NameContainer& other)
{
    NameContainer temp(other);
    swap(*this, temp);
    return *this;
}

void NameContainer::swap(NameContainer& first, NameContainer& second)
{
    map<string, Part*> tempMap = first.name_map;
    first.name_map = second.name_map;
    second.name_map = tempMap;
}

NameContainer::~NameContainer()
{
    for (nameMap::const_iterator it = name_map.begin(); it != name_map.end(); ++it)
        delete it->second;
}