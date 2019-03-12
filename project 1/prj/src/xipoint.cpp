////////////////////////////////////////////////////////////////////////////////
// Module Name:  xipoint.h/cpp
// Authors:      Sergey Shershakov
// Version:      0.2.0
// Date:         14.01.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////


#include "xipoint.h"

#include <algorithm>        // min

namespace xi {

    typedef unsigned  int Uint;

    Point::Point(int x, int y)
    {
        _x = x;
        _y = y;
    }

    void Point::shift(int shf)
    {
        _x += shf;
        _y += shf;
    }

    void Point::shift(int xSh, int ySh)
    {
        _x += xSh;
        _y += ySh;
    }

    void Point::shift(const Point &pt)
    {
        _x += pt._x;
        _y += pt._y;
    }

    int Point::getX() const
    {
        return _x;
    };

    int Point::getY() const
    {
        return _y;
    }

    void Point::setX(int x)
    {
        _x = x;
    }

    void Point::setY(int y)
    {
        _y = y;
    }

    PointArray::PointArray()
    {
        _size = 0;
        _arr = nullptr;
    }

    PointArray::PointArray(const Point points[], Uint n)
    {
        _size = n;
        _arr = new Point[n];
        for (int i = 0; i < n; ++i)
        {
            _arr[i] = points[i];
        }
    }

    PointArray::PointArray(const PointArray &pv)
    {
        _size = pv._size;
        _arr = new Point[pv._size];
        for (int i = 0; i < pv._size; ++i)
        {
            _arr[i] = pv._arr[i];
        }
    }

    PointArray::~PointArray()
    {
        delete[] _arr;
    }

    void PointArray::append(const Point &pt)
    {
        this->resize(_size + 1);
        _arr[_size - 1] = pt;
    }

    //check for nullptr
    void PointArray::insert(const Point &pt, Uint pos)
    {
        if (pos >= _size)
            pos = _size;
        this->resize(_size + 1);
        for (int i = _size - 1; i > pos; --i)
            _arr[i] = _arr[i - 1];
        _arr[pos] = pt;

        /*
        if (pos >= _size)
            pos = _size++;
        Point *tempArr = new Point[_size];
        for (int i = 0; i < pos; ++i)
            tempArr[i] = _arr[i];
        tempArr[pos] = pt;
        for(int i = pos + 1; i < _size; ++i)
            tempArr[i] = _arr[i - 1];
        delete[] _arr;
        _arr = tempArr;
        */
    }

    //check for nullptr
    void PointArray::remove(Uint pos)
    {
        Point *tempArr = new Point[_size - 1];
        for (int i = 0; i < pos; ++i)
            tempArr[i] = _arr[i];
        for (int i = pos; i < _size - 1; ++i)
            tempArr[i] = _arr[i + 1];
        delete[] _arr;
        --_size;
        _arr = tempArr;
    }

    void PointArray::clear()
    {
        delete[] _arr;
        _size = 0;
    }

    const Uint PointArray::getSize() const
    {
        return _size;
    }

    const Point *PointArray::get(Uint pos) const
    {
        if (pos < _size)
            return &_arr[pos];
        else
            return nullptr;
    }

    Point *PointArray::get(Uint pos)
    {
        if (pos < _size)
            return &_arr[pos];
        else
            return nullptr;
    }


    void PointArray::resize(Uint n)
    {
        Point *tempArr = new Point[n];
        int elemToCopy = 0;
        if (_size < n)
            elemToCopy = _size;
        else
            elemToCopy = n;
        for (int i = 0; i < elemToCopy; ++i)
            tempArr[i] = _arr[i];
        delete[] _arr;
        _size = n;
        _arr = tempArr;
    }
// TODO: put the method implementations here



} // namespace xi {