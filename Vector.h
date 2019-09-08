#pragma once
#include <stdexcept>
#include <cassert>
#include <iostream>

template <typename T>
class Vector
{
public:
	Vector();
	Vector(const Vector& vector);
	~Vector();

	void pushBack(const T& value);
	void insert(const T& value, int index);
	void remove(int index);
	void removeBySwap(int index);
	void clear();
	void addBySwap(const T& value);
	void add(const T& value);
	void swap(int index1, int index2);


	void sort();
	int search(const T& value);

	int linearSearch(const T& value);
	int size() { return _size; };
	int capacity() { return _capacity; };

	T* begin() { return _data; }
	T* end() { return _data + _size; }

	T& operator [] (int index)
	{
		assert(index < _size && index >= 0 && "Index is out of range");

		return _data[index];
	}

	const T& operator [] (int index) const
	{
		assert(index < _size && index >= 0 && "Index is out of range");

		return _data[index];
	}

private:
	T* _data;

	int _size = 0;
	int _capacity = 1;

	void increaseCapacity();
};

template <typename T>
Vector<T>::Vector()
	: _data(new T[1])
{}

template <typename T>
Vector<T>::Vector(const Vector& vector)
	: _data(new T[vector._capacity()])
{
	_size = vector._size();
	_capacity = vector._capacity();

	for (T* itr = vector.begin(); itr < vector.end(); itr++)
	{
		pushback(itr);
	}
}

template <typename T>
Vector<T>::~Vector()
{
	delete[] _data;
}

template <typename T>
void Vector<T>::pushBack(const T& value)
{
	if (_size >= _capacity)
	{
		increaseCapacity();
	}

	_data[_size++] = value;
}

template <typename T>
void Vector<T>::insert(const T& value, int index)
{
	assert(index < _size && index >= 0 && "Index is out of range");

	if (_size >= _capacity)
	{
		increaseCapacity();
	}

	for (int i = _size; i > index; i--)
	{
		_data[i] = _data[i - 1];
	}
	_data[index] = value;

	_size++;
}

template <typename T>
void Vector<T>::remove(int index)
{
	assert(index < _size && index >= 0 && "Index is out of range");

	for (int i = index; i < _size - 1; i++)
	{
		_data[i] = _data[i + 1];
	}

	_size--;
}

template <typename T>
void Vector<T>::removeBySwap(int index)
{
	assert(index < _size && index >= 0 && "Index is out of range");

	index = _data[--size];
}

template <typename T>
int Vector<T>::linearSearch(const T& value)
{
	for (int i = 0; i < _size; i++)
	{
		if (_data[i] == value)
		{
			return i;
		}
	}
	return -1;
}

template <typename T>
void Vector<T>::clear()
{
	delete[] _data;
	_size = 0;
}

template <typename T>
void Vector<T>::addBySwap(const T& value)
{
	if (_size >= _capacity)
	{
		increaseCapacity();
	}

	_data[size - 1] = _data[0];
	_data[0] = value;
	_size++;
}

template <typename T>
void Vector<T>::add(const T& value)
{
	if (_size >= _capacity)
	{
		increaseCapacity();
	}

	for (int i = _size; i > 0; i--)
	{
		_data[i] = _data[i - 1];
	}

	_data[0] = value;

	_size++;
}

template <typename T>
void Vector<T>::swap(int index1, int index2)
{
	assert(index1 < _size && index1 >= 0 && "Index1 is out of range");
	assert(index2 < _size && index2 >= 0 && "Index2 is out of range");

	try
	{
		T temp = _data[index1];
		_data[index1] = _data[index2];
		_data[index2] = temp;
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception thrown with message: " << e.what() << std::endl;
	}
}

template <typename T>
void Vector<T>::sort()
{
	bool swapped = false;

	for (int i = 0; i < _size - 1; i++)
	{
		swapped = false;
		for (int j = 0; j < _size - i - 1; j++)
		{
			if (_data[j] > _data[j + 1])
			{
				swap(j, j + 1);
				swapped = true;
			}
		}

		if (!swapped)
			break;
	}
}

template <typename T>
int Vector<T>::search(const T& value)
{
	sort();
	
	int low = 0;
	int high = _size - 1;
	int mid = 0;

	if (low == high)
		return 0;

	while (low <= high)
	{
		mid = (low + high) / 2;

		if (_data[mid] == value)
			return mid;

		if (_data[mid] < value)
			low = mid + 1;

		if (_data[mid] > value)
			high = mid - 1;
	}

	return -1;
}

template <typename T>
void Vector<T>::increaseCapacity()
{
	_capacity *= 2;

	T* newArray = new T[_capacity];

	try
	{
		for (int i = 0; i < _size; i++)
		{
			newArray[i] = _data[i];
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception thrown with message: " << e.what() << std::endl;
	}

	delete[] _data;
	_data = newArray;
}