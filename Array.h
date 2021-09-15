#ifndef ARRAY
#define ARRAY
#include <utility> 
#include <new>
template <typename T>
class Array2d;
template <typename Type>class Array
{
private:
	int *capacity, *size, size_mas, link_counter;
	Type **mas;
	friend Array2d<Type>;
public:
	Array();
	Array(const Array &copy);
	Array(Array &&ar_move);
	Array& operator=(const Array &copy)
	{
		Array temp(copy);
		swap(temp);
		return this;
	};
	Array& operator=(Array &&ar_move)
	{
		Array temp(std::move(ar_move));
		swap(temp);
		return this;
	};
	void reserve(int n, int n_size);
	void reserve(int* n_mas, int n_size);
	void swap(Array &swap_array);
	virtual ~Array();
};
template<typename T>
Array<T>::Array(const Array &copy) :capacity(0), size(0), size_mas(0), link_counter(1), mas(0)
{
	reserve(copy.capacity, copy.size_mas);
	for (int i = 0; i < copy.size_mas; i++)
	{

		for (int j = 0; j < copy.size[i]; j++)
		{
			mas[i][j] = copy.mas[i][j];
		}
		size[i] = copy.size[i];
	}
	size_mas = copy.size_mas;
}

template<typename T>
Array<T>::Array(Array &&ar_move) :capacity(std::move(ar_move.capacity)), size(std::move(ar_move.size)), size_mas(std::move(ar_move.size_mas)), link_counter(std::move(ar_move.link_counter)), mas(std::move(ar_move.mas))
{
}
template<typename T>
Array<T>::Array() : capacity(0), size(0), size_mas(0), link_counter(1), mas(0)
{

}
template<typename T>
Array<T>::~Array()
{
	for (int i = 0; i < size_mas; i++)
	{
		delete[] mas[i];
	}
	delete[] mas;
	delete[] capacity;
	delete[] size;
}
template<typename T>
void Array<T>::swap(Array &swap_array)
{
	std::swap(mas, swap_array.mas);
	std::swap(capacity, swap_array.capacity);
	std::swap(size, swap_array.size);
	std::swap(size_mas, swap_array.size_mas);
	std::swap(link_counter, swap_array.link_counter);
}
template<typename T>
void Array<T>::reserve(int* n_mas, int n_size)
{
	if (size_mas < n_size)
	{
		T** temp = new T*[n_size]();
		int *temp_size = new int[n_size]();
		int *temp_capacity = new int[n_size]();
		int i = 0;
		for (; i < size_mas; i++)
		{
			if (size[i] < n_mas[i])
			{
				temp[i] = new T[n_mas[i]]();
				for (int j = 0; j < size[i]; j++)
				{
					temp[i][j] = mas[i][j];
				}
				temp_capacity[i] = n_mas[i];
			}
			else
			{
				temp[i] = new T[capacity[i]]();
				for (int j = 0; j < size[i]; j++)
				{
					temp[i][j] = mas[i][j];
				}
				temp_capacity[i] = capacity[i];
			}temp_size[i] = size[i];
		}
		for (; i < n_size; i++)
		{
			temp[i] = new T[n_mas[i]]();
			temp_size[i] = 0;
			temp_capacity[i] = n_mas[i];
		}
		for (i = 0; i < size_mas; i++)
		{
			delete[] mas[i];
		}
		delete[] mas;
		delete[] size;
		delete[] capacity;
		mas = temp;
		size = temp_size;
		capacity = temp_capacity;

	}

}
template<typename T>
void Array<T>::reserve(int n, int n_size)
{
	if (n >= 0 && n < size_mas && size[n] < n_size)
	{
		T* temp_mas = new T[n_size]();
		for (int i = 0; i < size[n]; i++)
		{
			temp_mas[i] = mas[n][i];
		}
		delete[] mas[n];
		mas[n] = temp_mas;
		capacity[n] = n_size;
	}
}
#endif