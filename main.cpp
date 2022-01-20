#include <iostream>
#include <string>
#include <deque>

#include <map>
#include <stack>
#include <vector>
#include <list>

#include "Vector.hpp"
#include "Stack.hpp"
#include "Map.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <chrono>

/*
**  최대 RAM 크기는 2^32 즉 4기가 바이트
**  버퍼 사이즈는 4키로 바이트
*/
#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};

#define COUNT 1000

/*
**  std::stack은 iterator가 없지만, main.cpp에서 제공하는 MutantStack은 iterator를 만들었다.
*/

template<typename T>
class std_MutantStack : public std::stack<T>
{
public:
	std_MutantStack() {}
	std_MutantStack(const std_MutantStack<T>& src) { *this = src; }
	std_MutantStack<T>& operator=(const std_MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~std_MutantStack() {}

	typedef typename std::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

/*
**  std::stack은 iterator가 없지만, main.cpp에서 제공하는 MutantStack은 iterator를 만들었다.
*/

template<typename T>
class ft_MutantStack : public ft::stack<T>
{
public:
	ft_MutantStack() {}
	ft_MutantStack(const ft_MutantStack<T>& src) { *this = src; }
	ft_MutantStack<T>& operator=(const ft_MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~ft_MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

template <typename T>
void    display_std_vector(std::vector<T> &v)
{
    typename std::vector<T>::iterator it;
    
    std::cout << "std::vector->";
    for (it = v.begin(); it < v.end(); it++)
    {
        std::cout << " " << *it;
    }
    std::cout << "\n";
}

template <typename T>
void    display_ft_vector(ft::vector<T> &v)
{
    typename ft::vector<T>::iterator it;
    
    std::cout << " ft::vector->";
    for (it = v.begin(); it < v.end(); it++)
    {
        std::cout << " " << *it;
    }
    std::cout << "\n";
}

template <typename T>
void    display_std_vector_rev(std::vector<T> &v)
{
    typename std::vector<T>::reverse_iterator it;
    
    std::cout << "std::vector::rev->";
    for (it = v.rbegin(); it < v.rend(); it++)
    {
        std::cout << " " << *it;
    }
    std::cout << "\n";
}

template <typename T>
void    display_ft_vector_rev(ft::vector<T> &v)
{
    typename ft::vector<T>::reverse_iterator it;
    
    std::cout << " ft::vector::rev->";
    for (it = v.rbegin(); it < v.rend(); it++)
    {
        std::cout << " " << *it;
    }
    std::cout << "\n";
}

void    test_pair(void)
{
    ft::pair<int, int> p(1, 2);
}

void    test_vector_member_function_diff(void)
{
    {
        std::cout << "------------------------------------------\n";
        std::cout << "----------------Vector Test---------------\n";
        std::cout << "------------------------------------------\n";
        // int벡터 생성
        std::cout << "\n-------------Create Empty Array-----------\n";
        std::vector<int> std_vector;
        ft::vector<int> ft_vector;
        display_std_vector<int>(std_vector);
        display_ft_vector<int>(ft_vector);
    }
    {
        // int벡터 생성하고, 크기를 4만큼 할당되었습니다.
        // 할당된 공간은 0으로 초기화됩니다.
        std::cout << "\n---------------vector(4)-----------------\n";
        std::vector<int> std_vector(4);
        ft::vector<int> ft_vector(4);
        display_std_vector<int>(std_vector);
        display_ft_vector<int>(ft_vector);
    }
    {
        // int벡터 생성하고, 크기를 4만큼 할당되었습니다.
        // 할당된 공간은 2으로 초기화됩니다.
        std::cout << "\n-------------vector(4, 1)----------------\n";
        std::vector<int> std_vector(4, 1);
        ft::vector<int> ft_vector(4, 1);
        display_std_vector<int>(std_vector);
        display_ft_vector<int>(ft_vector);
    }
    {
        std::cout << "\n-------------Copy Constructor------------";
        std::cout << "\n-------------vector(4, 1)----------------\n";
        ft::vector<int> ft_vector(4, 1);
        ft::vector<int> ft_vector_copy(ft_vector);
        display_ft_vector<int>(ft_vector);
        display_ft_vector<int>(ft_vector_copy);
    }
    {
        std::cout << "\n--------------operator=()----------------\n";
        ft::vector<int> ft_vector(4, 1);
        ft::vector<int> ft_vector_copy = ft_vector;
        display_ft_vector<int>(ft_vector);
        display_ft_vector<int>(ft_vector_copy);
    }
    {
        std::cout << "-----------------------------------------\n";
        std::cout << "-------------------Iterators-------------\n";
        std::cout << "-----------------------------------------\n";
        std::vector<int> std_vector;
        ft::vector<int> ft_vector;
        std_vector.push_back(1);
        std_vector.push_back(2);
        std_vector.push_back(3);
        std_vector.push_back(4);
        ft_vector.push_back(1);
        ft_vector.push_back(2);
        ft_vector.push_back(3);
        ft_vector.push_back(4);
        display_std_vector(std_vector);
        display_std_vector_rev(std_vector);
        display_ft_vector(ft_vector);
        display_ft_vector_rev(ft_vector);

        // std::vector<int>::const_iterator std_const_it = std_vector.begin();
        // *std_const_it = 5;
        // ft::vector<int>::const_iterator ft_const_it = ft_vector.begin();
        // *ft_const_it = 5;
    }
    {
        std::cout << "-----------------------------------------\n";
        std::cout << "----------------Capacity-----------------\n";
        std::cout << "-----------------------------------------\n";
        std::cout << "\n-----------------1 2 3 4-----------------\n";
        std::vector<int> std_vector;
        ft::vector<int> ft_vector;
        std_vector.push_back(1);
        std_vector.push_back(2);
        std_vector.push_back(3);
        std_vector.push_back(4);
        ft_vector.push_back(1);
        ft_vector.push_back(2);
        ft_vector.push_back(3);
        ft_vector.push_back(4);
        display_std_vector<int>(std_vector);
        display_ft_vector<int>(ft_vector);

        std::cout << "\n-----------------size()------------------\n";
        std::cout << "std_vector.size(): " << std_vector.size() << "\n";
        std::cout << "ft_vector.size(): " << ft_vector.size() << "\n";

        std::cout << "\n-----------------max_size()--------------\n";
        std::cout << "std_vector.max_size(): " << std_vector.max_size() << "\n";
        std::cout << "ft_vector.max_size(): " << ft_vector.max_size() << "\n";

        std::cout << "\n-----------------resize(3)---------------\n";
        std_vector.resize(3);
        ft_vector.resize(3);
        display_std_vector<int>(std_vector);
        display_ft_vector<int>(ft_vector);
        std::cout << "std_vector.size(): " << std_vector.size() << "\n";
        std::cout << "ft_vector.size(): " << ft_vector.size() << "\n";
        std::cout << "std_vector.capacity(): " << std_vector.capacity() << "\n";
        std::cout << "ft_vector.capacity(): " << ft_vector.capacity() << "\n";

        std::cout << "\n-----------------empty()-----------------\n";
        std::cout << "std_vector.empty(): " << std_vector.empty() << "\n";
        std::cout << "ft_vector.empty(): " << ft_vector.empty() << "\n";

        std::cout << "\n-----------------reserve(8)--------------\n";
        std_vector.reserve(8);
        ft_vector.reserve(8);
        std::cout << "std_vector.size(): " << std_vector.size() << "\n";
        std::cout << "ft_vector.size(): " << ft_vector.size() << "\n";
        std::cout << "std_vector.capacity(): " << std_vector.capacity() << "\n";
        std::cout << "ft_vector.capacity(): " << ft_vector.capacity() << "\n";
    }
    {
        std::cout << "-----------------------------------------\n";
        std::cout << "--------------Element access-------------\n";
        std::cout << "-----------------------------------------\n";
        std::cout << "\n-----------------1 2 3 4-----------------\n";
        std::vector<int> std_vector;
        ft::vector<int> ft_vector;
        std_vector.push_back(1);
        std_vector.push_back(2);
        std_vector.push_back(3);
        std_vector.push_back(4);
        ft_vector.push_back(1);
        ft_vector.push_back(2);
        ft_vector.push_back(3);
        ft_vector.push_back(4);
        display_std_vector<int>(std_vector);
        display_ft_vector<int>(ft_vector);
        std::cout << "\n---------------operator[1]---------------\n";
        std::cout << "std_vector[1]: " << std_vector[1] << "\n";
        std::cout << "ft_vector[1]: " << ft_vector[1] << "\n";
        std::cout << "\n---------------at(2)---------------------\n";
        std::cout << "std_vector.at(2): " << std_vector.at(2) << "\n";
        std::cout << "ft_vector.at(2): " << ft_vector.at(2) << "\n";
        std::cout << "\n---------------front()-------------------\n";
        std::cout << "std_vector.front(): " << std_vector.front() << "\n";
        std::cout << "ft_vector.front(): " << ft_vector.front() << "\n";
        std::cout << "\n---------------back()--------------------\n";
        std::cout << "std_vector.back(): " << std_vector.back() << "\n";
        std::cout << "ft_vector.back(): " << ft_vector.back() << "\n";
    }
    {
        std::cout << "-----------------------------------------\n";
        std::cout << "----------------Modifiers----------------\n";
        std::cout << "-----------------------------------------\n";
        std::cout << "\n---------------1 2 3 4 생성--------------\n";
        std::vector<int> std_vector;
        ft::vector<int> ft_vector;
        std::cout << "\n---------------assign(4, 100)------------\n";
        std_vector.assign(4, 100);
        ft_vector.assign(4, 100);
        display_std_vector<int>(std_vector);
        display_ft_vector<int>(ft_vector);

        std::cout << "\n-----------------pop_back()--------------\n";
        std_vector.pop_back();
        std_vector.pop_back();
        std_vector.pop_back();
        std_vector.pop_back();
        ft_vector.pop_back();
        ft_vector.pop_back();
        ft_vector.pop_back();
        ft_vector.pop_back();
        display_std_vector<int>(std_vector);
        display_ft_vector<int>(ft_vector);
        std::cout << "\n----------------push_back()--------------\n";
        std_vector.push_back(1);
        std_vector.push_back(2);
        std_vector.push_back(3);
        std_vector.push_back(4);
        ft_vector.push_back(1);
        ft_vector.push_back(2);
        ft_vector.push_back(3);
        ft_vector.push_back(4);
        display_std_vector<int>(std_vector);
        display_ft_vector<int>(ft_vector);

        std::cout << "\n------------erase(begin())---------------\n";
        std::vector<int>::iterator std_iter = std_vector.begin();
        ft::vector<int>::iterator ft_iter = ft_vector.begin();
        std_vector.erase(std_iter);
        ft_vector.erase(ft_iter);
        display_std_vector<int>(std_vector);
        display_ft_vector<int>(ft_vector);

        std::cout << "\n------------erase(begin(), begin() + 2)--\n";
        std_vector.erase(std_iter, std_iter + 2);
        ft_vector.erase(ft_iter, ft_iter + 2);
        display_std_vector<int>(std_vector);
        display_ft_vector<int>(ft_vector);

        std::cout << "\n---------------insert()------------------\n";
        std_vector.insert(std_iter, 50);
        ft_vector.insert(ft_iter, 50);
        display_std_vector<int>(std_vector);
        display_ft_vector<int>(ft_vector);
        std::cout << "size: " << std_vector.size() << " capacity: " << std_vector.capacity() << "\n";
        std::cout << "size: " << ft_vector.size() << " capacity: " << ft_vector.capacity() << "\n";

        std_vector.insert(std_iter, 5, 10);
        ft_vector.insert(ft_iter, 5, 10);
        display_std_vector<int>(std_vector);
        display_ft_vector<int>(ft_vector);
        std::cout << "size: " << std_vector.size() << " capacity: " << std_vector.capacity() << "\n";
        std::cout << "size: " << ft_vector.size() << " capacity: " << ft_vector.capacity() << "\n";
        
        std::vector<int> std_temp_vector(5, 99);
        ft::vector<int> ft_temp_vector(5, 99);
        std_vector.insert(std_vector.begin(), std_temp_vector.begin(), std_temp_vector.end());
        ft_vector.insert(ft_vector.begin(), ft_temp_vector.begin(), ft_temp_vector.end());
        display_std_vector<int>(std_vector);
        display_ft_vector<int>(ft_vector);
        std::cout << "size: " << std_vector.size() << " capacity: " << std_vector.capacity() << "\n";
        std::cout << "size: " << ft_vector.size() << " capacity: " << ft_vector.capacity() << "\n";
                
        std::cout << "\n---------------clear()-------------------\n";
        std_vector.clear();
        ft_vector.clear();
        display_std_vector<int>(std_vector);
        display_ft_vector<int>(ft_vector);
        std::cout << "size: " << std_vector.size() << " capacity: " << std_vector.capacity() << "\n";
        std::cout << "size: " << ft_vector.size() << " capacity: " << ft_vector.capacity() << "\n";
        std::cout << "std_vector.empty(): " << std_vector.empty() << "\n";
        std::cout << "ft_vector.empty(): " << ft_vector.empty() << "\n";
        
        std::cout << "\n---------------std_1.swap(std_2)--------\n";
        std::vector<int> std_vector_1(4, 50);
        std::vector<int> std_vector_2(4, 100);
        std::cout << "\n---------------before-------------------\n";
        display_std_vector<int>(std_vector_1);
        display_std_vector<int>(std_vector_2);
        std_vector_1.swap(std_vector_2);
        std::cout << "\n---------------after--------------------\n";
        display_std_vector<int>(std_vector_1);
        display_std_vector<int>(std_vector_2);
        ft::vector<int> ft_vector_1(4, 50);
        ft::vector<int> ft_vector_2(4, 100);
        std::cout << "\n---------------ft_1.swap(ft_2)----------\n";
        std::cout << "\n---------------before-------------------\n";
        display_ft_vector<int>(ft_vector_1);
        display_ft_vector<int>(ft_vector_2);
        ft_vector_1.swap(ft_vector_2);
        std::cout << "\n---------------after--------------------\n";
        display_ft_vector<int>(ft_vector_1);
        display_ft_vector<int>(ft_vector_2);
        
    }
    {
        std::cout << "\n---------------swap(std_1, std_2)-------\n";
        std::vector<int> std_vector_1(4, 50);
        std::vector<int> std_vector_2(4, 100);
        std::cout << "\n---------------before-------------------\n";
        display_std_vector<int>(std_vector_1);
        display_std_vector<int>(std_vector_2);
        swap(std_vector_1, std_vector_2);
        std::cout << "\n---------------after--------------------\n";
        display_std_vector<int>(std_vector_1);
        display_std_vector<int>(std_vector_2);
        ft::vector<int> ft_vector_1(4, 50);
        ft::vector<int> ft_vector_2(4, 100);
        std::cout << "\n---------------swap(ft_1, ft_2)---------\n";
        std::cout << "\n---------------before-------------------\n";
        display_ft_vector<int>(ft_vector_1);
        display_ft_vector<int>(ft_vector_2);
        swap(ft_vector_1, ft_vector_2);
        std::cout << "\n---------------after--------------------\n";
        display_ft_vector<int>(ft_vector_1);
        display_ft_vector<int>(ft_vector_2);
    }
    {
        std::cout << "\n--------------get_allocator()-----------\n";
        std::vector<int> myvector;
        int * p;
        unsigned int i;

        // allocate an array with space for 5 elements using vector's allocator:
        p = myvector.get_allocator().allocate(5);

        // construct values in-place on the array:
        for (i=0; i<5; i++) myvector.get_allocator().construct(&p[i],i);

        std::cout << "The allocated array contains:";
        for (i=0; i<5; i++) std::cout << ' ' << p[i];
        std::cout << '\n';

        // destroy and deallocate:
        for (i=0; i<5; i++) myvector.get_allocator().destroy(&p[i]);
        myvector.get_allocator().deallocate(p,5);
    }
    {
        ft::vector<int> myvector;
        int * p;
        unsigned int i;

        // allocate an array with space for 5 elements using vector's allocator:
        p = myvector.get_allocator().allocate(5);

        // construct values in-place on the array:
        for (i=0; i<5; i++) myvector.get_allocator().construct(&p[i],i);

        std::cout << "The allocated array contains:";
        for (i=0; i<5; i++) std::cout << ' ' << p[i];
        std::cout << '\n';

        // destroy and deallocate:
        for (i=0; i<5; i++) myvector.get_allocator().destroy(&p[i]);
        myvector.get_allocator().deallocate(p,5);
    }
    {
        std::cout << "\n----------------operator()---------------\n";
        std::vector<int> std_vector_1;
        std_vector_1.push_back(1);
        std_vector_1.push_back(2);
        std_vector_1.push_back(3);
        std::vector<int> std_vector_2;
        std_vector_2.push_back(1);
        std_vector_2.push_back(2);
        std_vector_2.push_back(3);
        std::cout << "std_vector_1:";
        display_std_vector<int>(std_vector_1);
        std::cout << "std_vector_2:";
        display_std_vector<int>(std_vector_2);
        std::cout << "1 == 2 --> " << (std_vector_1 == std_vector_2) << "\n";
        std::cout << "1 != 2 --> " << (std_vector_1 != std_vector_2) << "\n";
        std::cout << "1 <  2 --> " << (std_vector_1 < std_vector_2) << "\n";
        std::cout << "1 <= 2 --> " << (std_vector_1 <= std_vector_2) << "\n";
        std::cout << "1 >  2 --> " << (std_vector_1 > std_vector_2) << "\n";
        std::cout << "1 >= 2 --> " << (std_vector_1 >= std_vector_2) << "\n";
    }
    {
        ft::vector<int> ft_vector_1;
        ft_vector_1.push_back(1);
        ft_vector_1.push_back(2);
        ft_vector_1.push_back(3);
        ft::vector<int> ft_vector_2;
        ft_vector_2.push_back(1);
        ft_vector_2.push_back(2);
        ft_vector_2.push_back(3);
        std::cout << "ft_vector_1:";
        display_ft_vector<int>(ft_vector_1);
        std::cout << "ft_vector_2:";
        display_ft_vector<int>(ft_vector_2);
        std::cout << "1 == 2 --> " << (ft_vector_1 == ft_vector_2) << "\n";
        std::cout << "1 != 2 --> " << (ft_vector_1 != ft_vector_2) << "\n";
        std::cout << "1 <  2 --> " << (ft_vector_1 < ft_vector_2) << "\n";
        std::cout << "1 <= 2 --> " << (ft_vector_1 <= ft_vector_2) << "\n";
        std::cout << "1 >  2 --> " << (ft_vector_1 > ft_vector_2) << "\n";
        std::cout << "1 >= 2 --> " << (ft_vector_1 >= ft_vector_2) << "\n";
    }
    {
        std::cout << "\n---------------operator()----------------\n";
        std::vector<int> std_vector_1;
        std_vector_1.push_back(1);
        std_vector_1.push_back(2);
        std_vector_1.push_back(3);
        std::vector<int> std_vector_2;
        std_vector_2.push_back(1);
        std_vector_2.push_back(2);
        std::cout << "std_vector_1:";
        display_std_vector<int>(std_vector_1);
        std::cout << "std_vector_2:";
        display_std_vector<int>(std_vector_2);
        std::cout << "1 == 2 --> " << (std_vector_1 == std_vector_2) << "\n";
        std::cout << "1 != 2 --> " << (std_vector_1 != std_vector_2) << "\n";
        std::cout << "1 <  2 --> " << (std_vector_1 < std_vector_2) << "\n";
        std::cout << "1 <= 2 --> " << (std_vector_1 <= std_vector_2) << "\n";
        std::cout << "1 >  2 --> " << (std_vector_1 > std_vector_2) << "\n";
        std::cout << "1 >= 2 --> " << (std_vector_1 >= std_vector_2) << "\n";
    }
    {
        ft::vector<int> ft_vector_1;
        ft_vector_1.push_back(1);
        ft_vector_1.push_back(2);
        ft_vector_1.push_back(3);
        ft::vector<int> ft_vector_2;
        ft_vector_2.push_back(1);
        ft_vector_2.push_back(2);
        std::cout << "ft_vector_1:";
        display_ft_vector<int>(ft_vector_1);
        std::cout << "ft_vector_2:";
        display_ft_vector<int>(ft_vector_2);
        std::cout << "1 == 2 --> " << (ft_vector_1 == ft_vector_2) << "\n";
        std::cout << "1 != 2 --> " << (ft_vector_1 != ft_vector_2) << "\n";
        std::cout << "1 <  2 --> " << (ft_vector_1 < ft_vector_2) << "\n";
        std::cout << "1 <= 2 --> " << (ft_vector_1 <= ft_vector_2) << "\n";
        std::cout << "1 >  2 --> " << (ft_vector_1 > ft_vector_2) << "\n";
        std::cout << "1 >= 2 --> " << (ft_vector_1 >= ft_vector_2) << "\n";
    }
    {
        std::cout << "\n---------------operator()----------------\n";
        std::vector<std::string> std_vector_1;
        std_vector_1.push_back("apple");
        std_vector_1.push_back("banana");
        std_vector_1.push_back("carrot");
        std::vector<std::string> std_vector_2;
        std_vector_2.push_back("apple");
        std_vector_2.push_back("banana");
        std::cout << "std_vector_1:";
        display_std_vector<std::string>(std_vector_1);
        std::cout << "std_vector_2:";
        display_std_vector<std::string>(std_vector_2);
        std::cout << "1 == 2 --> " << (std_vector_1 == std_vector_2) << "\n";
        std::cout << "1 != 2 --> " << (std_vector_1 != std_vector_2) << "\n";
        std::cout << "1 <  2 --> " << (std_vector_1 < std_vector_2) << "\n";
        std::cout << "1 <= 2 --> " << (std_vector_1 <= std_vector_2) << "\n";
        std::cout << "1 >  2 --> " << (std_vector_1 > std_vector_2) << "\n";
        std::cout << "1 >= 2 --> " << (std_vector_1 >= std_vector_2) << "\n";
    }
    {
        std::cout << "\n---------------operator()----------------\n";
        ft::vector<std::string> ft_vector_1;
        ft_vector_1.push_back("apple");
        ft_vector_1.push_back("banana");
        ft_vector_1.push_back("carrot");
        ft::vector<std::string> ft_vector_2;
        ft_vector_2.push_back("apple");
        ft_vector_2.push_back("banana");
        std::cout << "ft_vector_1:";
        display_ft_vector<std::string>(ft_vector_1);
        std::cout << "ft_vector_2:";
        display_ft_vector<std::string>(ft_vector_2);
        std::cout << "1 == 2 --> " << (ft_vector_1 == ft_vector_2) << "\n";
        std::cout << "1 != 2 --> " << (ft_vector_1 != ft_vector_2) << "\n";
        std::cout << "1 <  2 --> " << (ft_vector_1 < ft_vector_2) << "\n";
        std::cout << "1 <= 2 --> " << (ft_vector_1 <= ft_vector_2) << "\n";
        std::cout << "1 >  2 --> " << (ft_vector_1 > ft_vector_2) << "\n";
        std::cout << "1 >= 2 --> " << (ft_vector_1 >= ft_vector_2) << "\n";
    }
}

void    test_vector_Buffer(void)
{
    std::cout << "---------------------------------------------\n";
    std::cout << "-------------Vector Performance--------------\n";
    std::cout << "---------------------------------------------\n";
	std::vector<Buffer> std_vector_buffer;
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

	for (int i = 0; i < COUNT; i++)
	{
		std_vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		std_vector_buffer[idx].idx = 5;
	}
	std::vector<Buffer>().swap(std_vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			std_vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
    std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
    std::chrono::microseconds std_time = end - start;
    std::cout << "std::vector time: " << std_time.count() << "\n";

    start = std::chrono::system_clock::now();
	ft::vector<Buffer> ft_vector_buffer;

	for (int i = 0; i < COUNT; i++)
	{
		ft_vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		ft_vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(ft_vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			ft_vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
    end = std::chrono::system_clock::now();
    std::chrono::microseconds ft_time = end - start;
    ft_time = end - start;
    std::cout << "ft::vector time: " << ft_time.count() << "\n";
    double diff = static_cast<double> (std_time.count()) / ft_time.count();
    std::cout << "time diff: std::vector is " << diff << "x faster" << "\n";
}

void    test_stack_member_function_diff(void)
{
    {
        std::cout << "\n---------------------stack<int> 생성\n";
        std::stack<int> std_stack;
        ft::stack<int> ft_stack;
        std::cout << "\n---------------------stack.empty()\n";
        std::cout << "std_stack.empty(): " << std_stack.empty() << "\n";
        std::cout << "ft_stack.empty():  " << ft_stack.empty() << "\n";
        std::cout << "\n---------------------stack.size()\n";
        std::cout << "std_stack.size(): " << std_stack.size() << "\n";
        std::cout << "ft_stack.size():  " << ft_stack.size() << "\n";
        // std::cout << "\n---------------------stack.top()\n";
        // std::cout << "std_stack.top(): " << std_stack.top() << "\n";
        // std::cout << "ft_stack.top():  " << ft_stack.top() << "\n";
        std::cout << "\n---------------------stack.push(123)\n";
        std_stack.push(123);
        ft_stack.push(123);
        std::cout << "\n---------------------stack.top()\n";
        std::cout << "std_stack.top(): " << std_stack.top() << "\n";
        std::cout << "ft_stack.top():  " << ft_stack.top() << "\n";
        std::cout << "\n---------------------stack.push(456)\n";
        std_stack.push(456);
        ft_stack.push(456);
        std::cout << "\n---------------------stack.top()\n";
        std::cout << "std_stack.top(): " << std_stack.top() << "\n";
        std::cout << "ft_stack.top():  " << ft_stack.top() << "\n";
        std::cout << "\n---------------------stack.pop()\n";
        std_stack.pop();
        ft_stack.pop();
        std::cout << "\n---------------------stack.top()\n";
        std::cout << "std_stack.top(): " << std_stack.top() << "\n";
        std::cout << "ft_stack.top():  " << ft_stack.top() << "\n";
    }
    {
        std::cout << "\n----------------------relational operators\n";
        ft::stack<std::string> ft_stack_1;
        ft_stack_1.push("apple");
        ft_stack_1.push("banana");
        ft_stack_1.push("carrot");
        ft::stack<std::string> ft_stack_2;
        ft_stack_2.push("apple");
        ft_stack_2.push("banana");
        std::cout << "ft_stack_1: apple, banana, carrot\n";
        std::cout << "ft_stack_2: apple, banana\n";
        std::cout << "1 == 2 --> " << (ft_stack_1 == ft_stack_2) << "\n";
        std::cout << "1 != 2 --> " << (ft_stack_1 != ft_stack_2) << "\n";
        std::cout << "1 <  2 --> " << (ft_stack_1 < ft_stack_2) << "\n";
        std::cout << "1 <= 2 --> " << (ft_stack_1 <= ft_stack_2) << "\n";
        std::cout << "1 >  2 --> " << (ft_stack_1 > ft_stack_2) << "\n";
        std::cout << "1 >= 2 --> " << (ft_stack_1 >= ft_stack_2) << "\n";
    }
    {
        std::cout << "\n----------------------relational operators\n";
        ft::stack<std::string> ft_stack_1;
        ft_stack_1.push("apple");
        ft_stack_1.push("banana");
        ft::stack<std::string> ft_stack_2;
        ft_stack_2.push("apple");
        ft_stack_2.push("banana");
        std::cout << "ft_stack_1: apple, banana\n";
        std::cout << "ft_stack_2: apple, banana\n";
        std::cout << "1 == 2 --> " << (ft_stack_1 == ft_stack_2) << "\n";
        std::cout << "1 != 2 --> " << (ft_stack_1 != ft_stack_2) << "\n";
        std::cout << "1 <  2 --> " << (ft_stack_1 < ft_stack_2) << "\n";
        std::cout << "1 <= 2 --> " << (ft_stack_1 <= ft_stack_2) << "\n";
        std::cout << "1 >  2 --> " << (ft_stack_1 > ft_stack_2) << "\n";
        std::cout << "1 >= 2 --> " << (ft_stack_1 >= ft_stack_2) << "\n";
    }
    {
        std::cout << "\n----------------------relational operators\n";
        ft::stack<std::string> ft_stack_1;
        ft_stack_1.push("apple");
        ft::stack<std::string> ft_stack_2;
        ft_stack_2.push("apple");
        ft_stack_2.push("banana");
        std::cout << "ft_stack_1: apple\n";
        std::cout << "ft_stack_2: apple, banana\n";
        std::cout << "1 == 2 --> " << (ft_stack_1 == ft_stack_2) << "\n";
        std::cout << "1 != 2 --> " << (ft_stack_1 != ft_stack_2) << "\n";
        std::cout << "1 <  2 --> " << (ft_stack_1 < ft_stack_2) << "\n";
        std::cout << "1 <= 2 --> " << (ft_stack_1 <= ft_stack_2) << "\n";
        std::cout << "1 >  2 --> " << (ft_stack_1 > ft_stack_2) << "\n";
        std::cout << "1 >= 2 --> " << (ft_stack_1 >= ft_stack_2) << "\n";
    }
}


void    test_stack_Buffer_dequeBuffer()
{
	std::stack<Buffer, std::deque<Buffer> > std_stack_deq_buffer;
	ft::stack<Buffer, std::deque<Buffer> > ft_stack_deq_buffer;
}

void    test_stack_Buffer_listBuffer()
{
	std::stack<Buffer, std::list<Buffer> > std_stack_deq_buffer;
	ft::stack<Buffer, std::list<Buffer> > ft_stack_deq_buffer;
}

void    test_mutant_stack_char(void)
{
    std::cout << "\n----------------------test mutant stack\n";
    {
        std_MutantStack<char> iterable_stack;
        for (char letter = 'a'; letter <= 'z'; letter++)
            iterable_stack.push(letter);
        for (std_MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
        {
            std::cout << *it;
        }
        std::cout << std::endl;
    }
    {
        ft_MutantStack<char> iterable_stack;
        for (char letter = 'a'; letter <= 'z'; letter++)
            iterable_stack.push(letter);
        for (ft_MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
        {
            std::cout << *it;
        }
        std::cout << std::endl;
    }
}

template <typename Key, typename T>
void    display_std_map(std::map<Key, T> &std_map)
{
    std::cout << "display_std_map\n";
    for (typename std::map<Key, T>::iterator it = std_map.begin(); it != std_map.end(); ++it)
        std::cout << "key: " << (*it).first << " value: " << (*it).second << "\n";
    std::cout << "\n";
}

template <typename Key, typename T>
void    display_std_map_rev(std::map<Key, T> &std_map)
{
    std::cout << "display_std_map_rev\n";
    for (typename std::map<Key, T>::reverse_iterator it = std_map.rbegin(); it != std_map.rend(); ++it)
        std::cout << "key: " << (*it).first << " value: " << (*it).second << "\n";
    std::cout << "\n";
}

template <typename Key, typename T>
void    display_ft_map(ft::map<Key, T> &ft_map)
{
    std::cout << "display_ft_map\n";
    for (typename ft::map<Key, T>::iterator it = ft_map.begin(); it != ft_map.end(); ++it)
        std::cout << "key: " << (*it).first << " value: " << (*it).second << "\n";
    std::cout << "\n";
}

template <typename Key, typename T>
void    display_ft_map_rev(ft::map<Key, T> &ft_map)
{
    std::cout << "display_ft_map_rev\n";
    for (typename ft::map<Key, T>::reverse_iterator it = ft_map.rbegin(); it != ft_map.rend(); ++it)
        std::cout << "key: " << (*it).first << " value: " << (*it).second << "\n";
    std::cout << "\n";
}

void    test_map_member_function_diff()
{
    {
        std::cout << "\n----------------------map<int> 생성\n";
        std::map<int, std::string> std_map;
        ft::map<int, std::string> ft_map;
        std::cout << "------------------------------------\n";
        std::cout << "----------------------Capacity------\n";
        std::cout << "------------------------------------\n";
        std::cout << "\n----------------------map.empty()\n";
        std::cout << "std_map.empty(): " << std_map.empty() << "\n";
        std::cout << "ft_map.empty():  " << ft_map.empty() << "\n";
        std::cout << "\n----------------------map.size()\n";
        std::cout << "std_map.size(): " << std_map.size() << "\n";
        std::cout << "ft_map.size():  " << ft_map.size() << "\n";
        std::cout << "\n----------------------map.insert(std::make_pair())\n";
        std::cout << "std_map.insert(std::make_pair()): " << (*std_map.insert(std::make_pair(1, "apple")).first).second << "\n";
        std::cout << "ft_map.insert(std::make_pair()):  " << (*ft_map.insert(ft::make_pair(1, "apple")).first).second << "\n";
        std::cout << "\n----------------------map.empty()\n";
        std::cout << "std_map.empty(): " << std_map.empty() << "\n";
        std::cout << "ft_map.empty():  " << ft_map.empty() << "\n";
        std::cout << "\n----------------------map.size()\n";
        std::cout << "std_map.size(): " << std_map.size() << "\n";
        std::cout << "ft_map.size():  " << ft_map.size() << "\n";
        std::cout << "\n----------------------map.max_size()\n";
        std::cout << "std_map.max_size(): " << std_map.max_size() << "\n";
        std::cout << "ft_map.max_size():  " << ft_map.max_size() << "\n";
    }
    {
        std::map<int, std::string> std_map;
        ft::map<int, std::string> ft_map;
        std_map.insert(std::make_pair(1, "a"));
        std_map.insert(std::make_pair(2, "b"));
        std_map.insert(std::make_pair(11, "c"));
        std_map.insert(std::make_pair(12, "d"));
        std_map.insert(std::make_pair(21, "e"));
        std_map.insert(std::make_pair(22, "f"));
        ft_map.insert(ft::make_pair(11, "c"));
        ft_map.insert(ft::make_pair(12, "d"));
        ft_map.insert(ft::make_pair(21, "e"));
        ft_map.insert(ft::make_pair(22, "f"));
        ft_map.insert(ft::make_pair(1, "a"));
        ft_map.insert(ft::make_pair(1, "a"));
        ft_map.insert(ft::make_pair(1, "a"));
        ft_map.insert(ft::make_pair(1, "a"));
        ft_map.insert(ft::make_pair(2, "b"));
        std::cout << "------------------------------------\n";
        std::cout << "---------------------Iterators------\n";
        std::cout << "------------------------------------\n";
        display_std_map(std_map);
        display_std_map_rev(std_map);
        display_ft_map(ft_map);
        display_ft_map_rev(ft_map);
        std::cout << "-----------------------------------\n";
        std::cout << "-------------------Operations------\n";
        std::cout << "-----------------------------------\n";
        std::cout << "\n----------------------map.count(1)\n";
        std::cout << "std_map.count(1): " << std_map.count(1) << "\n";
        std::cout << "ft_map.count(1):  " << ft_map.count(1) << "\n";
        std::cout << "\n----------------------map.count(2)\n";
        std::cout << "std_map.count(2): " << std_map.count(2) << "\n";
        std::cout << "ft_map.count(2):  " << ft_map.count(2) << "\n";
        std::cout << "\n----------------------map.count(3)\n";
        std::cout << "std_map.count(3): " << std_map.count(3) << "\n";
        std::cout << "ft_map.count(3):  " << ft_map.count(3) << "\n";
        std::cout << "\n----------------------map.find(1)\n";
        std::cout << "std_map.find(1)->second: " << std_map.find(1)->second << "\n";
        std::cout << "ft_map.find(1)->second:  " << ft_map.find(1)->second << "\n";
        std::cout << "\n----------------------map.lower_bound\n";
        std::cout << "std_map.lower_bound(1)->second: " << std_map.lower_bound(1)->second << "\n";
        std::cout << "std_map.lower_bound(2)->second: " << std_map.lower_bound(2)->second << "\n";
        std::cout << "std_map.lower_bound(3)->second: " << std_map.lower_bound(3)->second << "\n";
        std::cout << "ft_map.lower_bound(1)->second: " << ft_map.lower_bound(1)->second << "\n";
        std::cout << "ft_map.lower_bound(2)->second: " << ft_map.lower_bound(2)->second << "\n";
        std::cout << "ft_map.lower_bound(3)->second: " << ft_map.lower_bound(3)->second << "\n";
        std::cout << "\n----------------------map.upper_bound\n";
        std::cout << "std_map.upper_bound(1)->second: " << std_map.upper_bound(1)->second << "\n";
        std::cout << "std_map.upper_bound(2)->second: " << std_map.upper_bound(2)->second << "\n";
        std::cout << "std_map.upper_bound(3)->second: " << std_map.upper_bound(3)->second << "\n";
        std::cout << "ft_map.upper_bound(1)->second: " << ft_map.upper_bound(1)->second << "\n";
        std::cout << "ft_map.upper_bound(2)->second: " << ft_map.upper_bound(2)->second << "\n";
        std::cout << "ft_map.upper_bound(3)->second: " << ft_map.upper_bound(3)->second << "\n";
        std::cout << "\n----------------------map.equal_range\n";
        std::cout << "std_map.equal_range(1)->second: " << std_map.equal_range(1).second->second << "\n";
        std::cout << "std_map.equal_range(2)->second: " << std_map.equal_range(2).second->second << "\n";
        std::cout << "std_map.equal_range(3)->second: " << std_map.equal_range(3).second->second << "\n";
        std::cout << "ft_map.equal_range(1)->second: " << ft_map.equal_range(1).second->second << "\n";
        std::cout << "ft_map.equal_range(2)->second: " << ft_map.equal_range(2).second->second << "\n";
        std::cout << "ft_map.equal_range(3)->second: " << ft_map.equal_range(3).second->second << "\n";
    }
    std::cout << "\n----------------------element access\n";
    {
        std::map<char,std::string> mymap;

        mymap['a']="an element";
        mymap['b']="another element";
        mymap['c']=mymap['b'];

        std::cout << "mymap['a'] is " << mymap['a'] << '\n';
        std::cout << "mymap['b'] is " << mymap['b'] << '\n';
        std::cout << "mymap['c'] is " << mymap['c'] << '\n';
        std::cout << "mymap['d'] is " << mymap['d'] << '\n';

        std::cout << "mymap now contains " << mymap.size() << " elements.\n";
    }
    {
        ft::map<char,std::string> mymap;

        mymap['a']="an element";
        mymap['b']="another element";
        mymap['c']=mymap['b'];

        std::cout << "mymap['a'] is " << mymap['a'] << '\n';
        std::cout << "mymap['b'] is " << mymap['b'] << '\n';
        std::cout << "mymap['c'] is " << mymap['c'] << '\n';
        std::cout << "mymap['d'] is " << mymap['d'] << '\n';

        std::cout << "mymap now contains " << mymap.size() << " elements.\n";
    }
    std::cout << "\n----------------------map.erase\n";
    {
        std::map<char,int> mymap;
        std::map<char,int>::iterator it;

        // insert some values:
        mymap['a']=10;
        mymap['b']=20;
        mymap['c']=30;
        mymap['d']=40;
        mymap['e']=50;
        mymap['f']=60;

        it=mymap.find('b');
        mymap.erase (it);                   // erasing by iterator

        mymap.erase ('c');                  // erasing by key

        // show content:
        for (it=mymap.begin(); it!=mymap.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';
    }
    {
        ft::map<char,int> mymap;
        ft::map<char,int>::iterator it;

        // insert some values:
        mymap['a']=10;
        mymap['b']=20;
        mymap['c']=30;
        mymap['d']=40;
        mymap['e']=50;
        mymap['f']=60;

        it=mymap.find('b');
        mymap.erase (it);                   // erasing by iterator

        mymap.erase ('c');                  // erasing by key
        // show content:
        for (it=mymap.begin(); it!=mymap.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';
    }
    std::cout << "\n----------------------map.swap\n";
    {
        std::map<char,int> foo,bar;

        foo['x']=100;
        foo['y']=200;

        bar['a']=11;
        bar['b']=22;
        bar['c']=33;

        foo.swap(bar);

        std::cout << "foo contains:\n";
        for (std::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';

        std::cout << "bar contains:\n";
        for (std::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';
    }
    {
        ft::map<char,int> foo,bar;

        foo['x']=100;
        foo['y']=200;

        bar['a']=11;
        bar['b']=22;
        bar['c']=33;

        foo.swap(bar);

        std::cout << "foo contains:\n";
        for (ft::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';

        std::cout << "bar contains:\n";
        for (ft::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';
    }
    std::cout << "\n----------------------map.clear\n";
    {
        std::map<char,int> mymap;

        mymap['x']=100;
        mymap['y']=200;
        mymap['z']=300;

        std::cout << "mymap contains:\n";
        for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';

        mymap.clear();
        mymap['a']=1101;
        mymap['b']=2202;

        std::cout << "mymap contains:\n";
        for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';
    }
    {
        std::map<char,int> mymap;

        mymap['x']=100;
        mymap['y']=200;
        mymap['z']=300;

        std::cout << "mymap contains:\n";
        for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';

        mymap.clear();
        mymap['a']=1101;
        mymap['b']=2202;

        std::cout << "mymap contains:\n";
        for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';

    }
    std::cout << "\n----------------------map.key_compare\n";
    {
        std::map<char,int> mymap;

        std::map<char,int>::key_compare mycomp = mymap.key_comp();

        mymap['a']=100;
        mymap['b']=200;
        mymap['c']=300;

        std::cout << "mymap contains:\n";

        char highest = mymap.rbegin()->first;     // key value of last element

        std::map<char,int>::iterator it = mymap.begin();
        do {
            std::cout << it->first << " => " << it->second << '\n';
        } while ( mycomp((*it++).first, highest) );

        std::cout << '\n';
    }
    {
        ft::map<char,int> mymap;

        ft::map<char,int>::key_compare mycomp = mymap.key_comp();

        mymap['a']=100;
        mymap['b']=200;
        mymap['c']=300;

        std::cout << "mymap contains:\n";

        char highest = mymap.rbegin()->first;     // key value of last element

        ft::map<char,int>::iterator it = mymap.begin();
        do {
            std::cout << it->first << " => " << it->second << '\n';
        } while ( mycomp((*it++).first, highest) );

        std::cout << '\n';
    }
    std::cout << "\n----------------------map.value_compare\n";
    {
        std::map<char,int> mymap;

        mymap['x']=1001;
        mymap['y']=2002;
        mymap['z']=3003;

        std::cout << "mymap contains:\n";

        std::pair<char,int> highest = *mymap.rbegin();          // last element

        std::map<char,int>::iterator it = mymap.begin();
        do {
            std::cout << it->first << " => " << it->second << '\n';
        } while ( mymap.value_comp()(*it++, highest) );
    }
    {
        ft::map<char,int> mymap;

        mymap['x']=1001;
        mymap['y']=2002;
        mymap['z']=3003;

        std::cout << "mymap contains:\n";

        ft::pair<char,int> highest = *mymap.rbegin();          // last element

        ft::map<char,int>::iterator it = mymap.begin();
        do {
            std::cout << it->first << " => " << it->second << '\n';
        } while ( mymap.value_comp()(*it++, highest) );
    }
}

void    test_map_int_int()
{
    {

        std::map<int, int> std_map_int;
        std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

        
        for (int i = 0; i < COUNT; ++i)
        {
            std_map_int.insert(std::make_pair(rand(), rand()));
        }

        int sum = 0;
        for (int i = 0; i < 1000; i++)
        {
            int access = rand();
            sum += std_map_int[access];
        }
        std::cout << "should    be constant with the same seed: " << sum << std::endl;

        {
            std::map<int, int> copy = std_map_int;
        }
        std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
        std::chrono::microseconds std_time = end - start;
        std::cout << "std::map time: " << std_time.count() << "\n";

        ft::map<int, int> ft_map_int;

        
        start = std::chrono::system_clock::now();
        for (int i = 0; i < COUNT; ++i)
        {
            ft_map_int.insert(ft::make_pair(rand(), rand()));
        }

        sum = 0;
        for (int i = 0; i < 1000; i++)
        {
            int access = rand();
            sum += ft_map_int[access];
        }
        std::cout << "should    be constant with the same seed: " << sum << std::endl;

        {
            ft::map<int, int> copy = ft_map_int;
        }
        end = std::chrono::system_clock::now();
        std::chrono::microseconds ft_time = end - start;
        std::cout << "ft::map time: " << ft_time.count() << "\n";
    }

}

int main(void)
{
    /*
    **  vector test 
    */
    // test_vector_member_function_diff();
    // test_vector_Buffer();
    /*
    **  stack test 
    */
    // test_stack_member_function_diff();
    // test_stack_Buffer_dequeBuffer();
    // test_mutant_stack_char();
    /*
    **  map test 
    */
    test_map_member_function_diff();
    test_map_int_int();
    // system("leaks container");
	return (0);
}
