// make sure to have a file-level Doxygen documentation block!!!
// read the specs to know which standard library headers cannot be included!!!
#include <algorithm>
#include "vector.hpp"

hlp2::vector::vector() {}

explicit hlp2::vector::vector(size_type n) : 
    data(new value_type[n]{}), 
    sz(0), 
    space(n), 
    allocs(0) 
{}

hlp2::vector::vector(std::initializer_list<int> rhs) : 
    data(new value_type[rhs.size()]), 
    sz(rhs.size()), 
    space(rhs.size()),
    allocs(0)
{
    std::copy(rhs.begin(), rhs.end(), data);
}

hlp2::vector::vector(vector const& rhs) : 
    data(new value_type[rhs.size()]),
    sz(rhs.size()),
    space(rhs.capacity()),
    allocs(0)
{
    for(size_type i = 0; i < sz; ++i) 
    {
        data[i] = rhs.data[i];
    }
}

hlp2::vector::~vector() 
{
    if(data) 
    {
        delete[] data;
        data = nullptr;
    }
}

hlp2::vector& hlp2::vector::operator=(vector const&) 
{
    space = this->capacity();
    data = new int[space];
    sz = this->size();
    allocs++;
    for(size_type i = 0; i < sz; ++i) 
    {
        data[i] = this->data[i];
    }
    return *this;
}

hlp2::vector& hlp2::vector::operator=(std::initializer_list<int> rhs) 
{
    delete[] data;
    sz = rhs.size();
    data = new int[sz];
    for(size_type i = 0; i < sz; ++i) 
    {
        data[i] = rhs.begin()[i];
    }
    return *this;
}

hlp2::vector::reference hlp2::vector::operator[](size_type index) 
{
    return this->data[index];
}

hlp2::vector::const_reference hlp2::vector::operator[](size_type index) const 
{
    return this->data[index];
}

hlp2::vector::size_type hlp2::vector::size() const { return sz; }

hlp2::vector::size_type hlp2::vector::capacity() const { return space; }

bool hlp2::vector::empty() const { return sz == 0; }

void hlp2::vector::push_back(value_type value) 
{
    if(sz >= space) 
    {
        space *= 2;
        pointer temp = new int[space];
        std::copy(data, sizeof(int), temp);
    }
}
