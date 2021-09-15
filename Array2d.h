#ifndef ARRAY2D
#define ARRAY2D
#include "Array.h"
template <typename T>
class Array2d
{
private:
	Array<T>* point;
	friend Array<T>;
	void deep_copy();
public:

	Array2d();
	Array2d(Array2d &copy);
	Array2d(Array2d &&ar_move);
	~Array2d();
	class iterator {
	private:
		friend Array2d;
		iterator(T* t_point, int t_n) :it_point(t_point), n(t_n) {};
		T* it_point;
		int n;
	public:
		void operator++() { it_point++; };
		void operator--() { it_point--; };
		bool operator==(iterator it) {
			if (n == it.n) return it_point == it.it_point;
			else return false;
		};
		bool operator!=(iterator it) {
			if (n == it.n) return it_point != it.it_point;
			else return true;
		};
		iterator& operator=(const iterator &it) {
			if (get_link_counter() != 1)
				deep_copy();
			it_point = it.it_point; n = it.n; return *this;
		};
		iterator& operator=(const T& copy) {
			if (get_link_counter() != 1)
				deep_copy();
			*it_point = copy;  return *this;
		};
		iterator operator+(int t_n) { Array2d<T>::iterator temp = iterator(it_point + t_n, n); return temp; };
		int get_row() { return n; };
		~iterator() {};

		T operator*() { return *it_point; };
	};
	friend Array2d<T>::iterator;
	class const_iterator {
	private:
		T* it_point;
		int n;
		const_iterator(T* t_point, int t_n) :it_point(t_point), n(t_n) {};
		friend Array2d;
	public:
		void operator++() { it_point++; };
		void operator--() { it_point--; };
		bool operator==(const_iterator it)
		{
			if (n == it.n) return it_point == it.it_point;
			else return false;
		};
		bool operator!=(const_iterator it) {
			if (n == it.n) return it_point != it.it_point;
			else return true;
		};
		const_iterator operator=(const const_iterator &it) = delete;
		const_iterator operator+(int t_n) { return const_iterator(it_point + t_n, n); }
		int get_row() { return n; };
		~const_iterator() {};
		T operator*() { return *it_point; };
	};
	Array2d<T>& operator=(const Array2d &copy) { Array2d<T> temp(copy); swap(temp); return this; };
	Array2d<T>& operator=(Array2d &&ar_move) { Array2d<T>temp(ar_move); swap(temp); return this; };
	int get_size(int n) { return point->size[n]; };
	int get_capacity(int n) { return point->capacity[n]; };
	int get_size() { return point->size_mas; };
	void reserve(int n, int n_size) { point->reserve(n, n_size); };
	int get_link_counter() { return point->link_counter; }
	void swap(Array2d & swap_array);
	template<typename P> void push_back(int n, const P& in);
	template<typename P> void push_back(int n, P&& in);
	template<typename P> void push(int n, P&& in);
	void push_back(T mas[], int size_mas);
	void push_front(int n, const T& in);
	void erase(iterator & it);
	iterator begin(int n)
	{
		iterator temp(point->mas[n], n);
		return temp;
	};
	iterator end(int n)
	{
		iterator temp(point->mas[n] + point->size[n], n);
		return temp;
	};
	const_iterator cbegin(int n)
	{
		const_iterator temp(point->mas[n], n);
		return temp;
	};
	const_iterator cend(int n)
	{
		const_iterator temp(point->mas[n] + point->size[n], n);
		return temp;
	};


};
template<typename T>
Array2d<T>::Array2d()
{
	point = new Array<T>();
}
template<typename T>
Array2d<T>::Array2d(Array2d &copy)
{
	copy.point->link_counter += 1;
	point = copy.point;
}
template<typename T>
Array2d<T>::Array2d(Array2d &&copy) :point(std::move(copy.point))
{
}
template<typename T>
void Array2d<T>::deep_copy()
{
	point->link_counter -= 1;
	point = new Array<T>(*point);
}
template<typename T>
Array2d<T>::~Array2d()
{
	if (point->link_counter != 1)
		point->link_counter -= 1;
	else
		delete point;
}

template<typename T>
void Array2d<T>::swap(Array2d & swap_array)
{
	std::swap(point, swap_array.point);
}
template<typename T>
void Array2d<T>::erase(iterator &it)
{
	if (get_link_counter() != 1)
		deep_copy();
	int n = it.get_row();
	int temp_n = it.it_point - this->point->mas[n] - 1;
	T *tempmas = new T[point->size[n]]();
	for (int i = 0; i != temp_n; i++)
	{
		tempmas[i] = point->mas[n][i];
	}
	for (; temp_n + 1 != point->size[n]; ++temp_n)
	{
		tempmas[temp_n] = point->mas[n][temp_n + 1];
	}
	point->mas[n] = tempmas;
	point->size[n] -= 1;
}
template<typename T>
template<typename P> void Array2d<T>::push(int n, P&& in)
{
	if (get_link_counter() != 1)
		deep_copy();
	if (n >= 0 && n < point->size_mas)
	{
		if ((point->size[n]) + 1 == point->capacity[n])
		{
			point->reserve(n, point->size[n] * 2 + 1);

		}
		point->mas[n][point->size[n]] = std::forward<P>(in);
		point->size[n] += 1;
	}
}
template<typename T>
template <typename P>
void Array2d<T>::push_back(int n, const P& in)
{
	push(n, in);
}
template<typename T>
template <typename P>
void Array2d<T>::push_back(int n, P&& in)
{
	push(n, in);
}
template<typename T>
void Array2d<T>::push_front(int n, const T& in)
{
	if (get_link_counter() != 1)
		deep_copy();
	if (n >= 0 && n < point->size_mas)
	{
		if (point->size[n] + 1 == point->capacity[n])
		{
			point->reserve(n, point->size[n] * 2 + 1);

		}
		T *tempmas = new T[point->size[n] + 2]();
		for (int i = point->size[n]; i != 0; i--)
		{
			tempmas[i] = point->mas[n][i - 1];
		}
		tempmas[0] = in;
		point->mas[n] = tempmas;
		point->size[n] += 1;

	}
}
template<typename T>
void Array2d<T>::push_back(T mas[], int size_mas)
{
	if (get_link_counter() != 1)
		deep_copy();
	int n = point->size_mas;
	int *temp_mas = new int[n + 1]();
	for (int i = 0; i < n; i++)
	{
		temp_mas[i] = 1;
	}
	temp_mas[n] = size_mas + 1;
	point->reserve(temp_mas, n + 1);
	T *tempmas = new T[size_mas]();
	for (int i = 0; i < size_mas; i++)
	{
		tempmas[i] = mas[i];
	}
	point->mas[n] = tempmas;
	point->size[n] = size_mas;
	point->size_mas += 1;
}
#endif