#include <iostream>
#include <string>
#include <deque>

#include <map>
#include <stack>
#include <vector>

#include "Vector.hpp"
#include "Stack.hpp"
// #include "Map.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <cmath>

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

#define COUNT (MAX_RAM / (int)sizeof(Buffer))

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

void    test_vector(void)
{
    {
        std::cout << "--------------------------\n";
        std::cout << "--------Constructor-------\n";
        std::cout << "--------------------------\n";
        // int벡터 생성
        std::cout << "\n-------빈 vector 생성-------\n";
        std::vector<int> std_vector;
        ft::vector<int> ft_vector;
        display_std_vector<int>(std_vector);
        display_ft_vector<int>(ft_vector);
    }
    {
        // int벡터 생성하고, 크기를 4만큼 할당되었습니다.
        // 할당된 공간은 0으로 초기화됩니다.
        std::cout << "\n-------vector(4) 생성-------\n";
        std::vector<int> std_vector(4);
        ft::vector<int> ft_vector(4);
        display_std_vector<int>(std_vector);
        display_ft_vector<int>(ft_vector);
    }
    {
        // int벡터 생성하고, 크기를 4만큼 할당되었습니다.
        // 할당된 공간은 2으로 초기화됩니다.
        std::cout << "\n-------vector(4, 1) 생성-------\n";
        std::vector<int> std_vector(4, 1);
        ft::vector<int> ft_vector(4, 1);
        display_std_vector<int>(std_vector);
        display_ft_vector<int>(ft_vector);
    }
    {
        std::cout << "\n-------복사 생성자-------\n";
        ft::vector<int> ft_vector(4, 1);
        ft::vector<int> ft_vector_copy(ft_vector);
        display_ft_vector<int>(ft_vector);
        display_ft_vector<int>(ft_vector_copy);
    }
    {
        std::cout << "\n-------대입 연산자 오버로딩-------\n";
        ft::vector<int> ft_vector(4, 1);
        ft::vector<int> ft_vector_copy = ft_vector;
        display_ft_vector<int>(ft_vector);
        display_ft_vector<int>(ft_vector_copy);
    }
    {
        std::cout << "-----------------------------\n";
        std::cout << "--------Iterators-------\n";
        std::cout << "-----------------------------\n";
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
    }
    {
        std::cout << "-----------------------------\n";
        std::cout << "--------Capacity-------------\n";
        std::cout << "-----------------------------\n";
        std::cout << "\n-------1 2 3 4 생성-------\n";
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

        std::cout << "\n-------size()------\n";
        std::cout << "std_vector.size(): " << std_vector.size() << "\n";
        std::cout << "ft_vector.size(): " << ft_vector.size() << "\n";

        std::cout << "\n-------max_size()------\n";
        std::cout << "std_vector.max_size(): " << std_vector.max_size() << "\n";
        std::cout << "ft_vector.max_size(): " << ft_vector.max_size() << "\n";

        std::cout << "\n-------resize(3)------\n";
        std_vector.resize(3);
        ft_vector.resize(3);
        display_std_vector<int>(std_vector);
        display_ft_vector<int>(ft_vector);

        std::cout << "\n-------capacity()------\n";
        std::cout << "std_vector.capacity(): " << std_vector.capacity() << "\n";
        std::cout << "ft_vector.capacity(): " << ft_vector.capacity() << "\n";

        std::cout << "\n-------empty()------\n";
        std::cout << "std_vector.empty(): " << std_vector.empty() << "\n";
        std::cout << "ft_vector.empty(): " << ft_vector.empty() << "\n";

        std::cout << "\n-------reserve(8)------\n";
        std_vector.reserve(8);
        ft_vector.reserve(8);
        std::cout << "std_vector.capacity(): " << std_vector.capacity() << "\n";
        std::cout << "ft_vector.capacity(): " << ft_vector.capacity() << "\n";
    }
    {
        std::cout << "-----------------------------\n";
        std::cout << "--------Element access-------\n";
        std::cout << "-----------------------------\n";
        std::cout << "\n-------1 2 3 4 생성-------\n";
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
        std::cout << "\n-------operator[1]------\n";
        std::cout << "std_vector[1]: " << std_vector[1] << "\n";
        std::cout << "ft_vector[1]: " << ft_vector[1] << "\n";
        std::cout << "\n-------at(2)------\n";
        std::cout << "std_vector.at(2): " << std_vector.at(2) << "\n";
        std::cout << "ft_vector.at(2): " << ft_vector.at(2) << "\n";
        std::cout << "\n-------front()------\n";
        std::cout << "std_vector.front(): " << std_vector.front() << "\n";
        std::cout << "ft_vector.front(): " << ft_vector.front() << "\n";
        std::cout << "\n-------back()------\n";
        std::cout << "std_vector.back(): " << std_vector.back() << "\n";
        std::cout << "ft_vector.back(): " << ft_vector.back() << "\n";
    }
    {
        std::cout << "-----------------------------\n";
        std::cout << "--------Modifiers-------------\n";
        std::cout << "-----------------------------\n";
        std::cout << "\n-------1 2 3 4 생성-------\n";
        std::vector<int> std_vector;
        ft::vector<int> ft_vector;
        std::cout << "\n-------push_back()------\n";
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
        std::cout << "\n-------pop_back()------\n";
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

        std::cout << "\n-------assign(4, 100)------\n";
        std_vector.assign(4, 100);
        ft_vector.assign(4, 100);
        display_std_vector<int>(std_vector);
        display_ft_vector<int>(ft_vector);

        std::cout << "\n-------erase()------\n";
        std::vector<int>::iterator std_iter = std_vector.begin();
        ft::vector<int>::iterator ft_iter = ft_vector.begin();
        // erase(it);
        std_vector.erase(std_iter);
        ft_vector.erase(ft_iter);
        display_std_vector<int>(std_vector);
        display_ft_vector<int>(ft_vector);
        // erase(from, to);
        std_vector.erase(std_iter, std_iter + 2);
        ft_vector.erase(ft_iter, ft_iter + 2);
        display_std_vector<int>(std_vector);
        display_ft_vector<int>(ft_vector);

        std::cout << "\n-------insert()------\n";
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
                
        std::cout << "\n-------clear()------\n";
        std_vector.clear();
        ft_vector.clear();
        display_std_vector<int>(std_vector);
        display_ft_vector<int>(ft_vector);
        std::cout << "size: " << std_vector.size() << " capacity: " << std_vector.capacity() << "\n";
        std::cout << "size: " << ft_vector.size() << " capacity: " << ft_vector.capacity() << "\n";
        std::cout << "std_vector.empty(): " << std_vector.empty() << "\n";
        std::cout << "ft_vector.empty(): " << ft_vector.empty() << "\n";
        
        std::cout << "\n-------swap()------\n";
        std::vector<int> std_vector_1(4, 50);
        std::vector<int> std_vector_2(4, 100);
        std::cout << "\n-------before------\n";
        display_std_vector<int>(std_vector_1);
        display_std_vector<int>(std_vector_2);
        std_vector_1.swap(std_vector_2);
        std::cout << "\n-------after------\n";
        display_std_vector<int>(std_vector_1);
        display_std_vector<int>(std_vector_2);
        ft::vector<int> ft_vector_1(4, 50);
        ft::vector<int> ft_vector_2(4, 100);
        std::cout << "\n-------before------\n";
        display_ft_vector<int>(ft_vector_1);
        display_ft_vector<int>(ft_vector_2);
        ft_vector_1.swap(ft_vector_2);
        std::cout << "\n-------after------\n";
        display_ft_vector<int>(ft_vector_1);
        display_ft_vector<int>(ft_vector_2);
        
    }
    {
        std::cout << "\n-------swap()------\n";
        std::vector<int> std_vector_1(4, 50);
        std::vector<int> std_vector_2(4, 100);
        std::cout << "\n-------before------\n";
        display_std_vector<int>(std_vector_1);
        display_std_vector<int>(std_vector_2);
        swap(std_vector_1, std_vector_2);
        std::cout << "\n-------after------\n";
        display_std_vector<int>(std_vector_1);
        display_std_vector<int>(std_vector_2);
        ft::vector<int> ft_vector_1(4, 50);
        ft::vector<int> ft_vector_2(4, 100);
        std::cout << "\n-------before------\n";
        display_ft_vector<int>(ft_vector_1);
        display_ft_vector<int>(ft_vector_2);
        swap(ft_vector_1, ft_vector_2);
        std::cout << "\n-------after------\n";
        display_ft_vector<int>(ft_vector_1);
        display_ft_vector<int>(ft_vector_2);
    }
    {
        std::cout << "\n-------get_allocator()------\n";
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
        std::cout << "\n-------operator()------\n";
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
        std::cout << "\n-------operator()------\n";
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
        std::cout << "\n-------operator()------\n";
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
        std::cout << "\n-------operator()------\n";
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
	std::vector<Buffer> std_vector_buffer;

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
}

void    test_stack(void)
{
    {
        std::cout << "\n------stack<int> 생성-------\n";
        std::stack<int> std_stack;
        ft::stack<int> ft_stack;
        std::cout << "\n------stack.empty()-------\n";
        std::cout << "std_stack.empty(): " << std_stack.empty() << "\n";
        std::cout << "ft_stack.empty():  " << ft_stack.empty() << "\n";
        std::cout << "\n------stack.size()-------\n";
        std::cout << "std_stack.size(): " << std_stack.size() << "\n";
        std::cout << "ft_stack.size():  " << ft_stack.size() << "\n";
        // std::cout << "\n------stack.top()-------\n";
        // std::cout << "std_stack.top(): " << std_stack.top() << "\n";
        // std::cout << "ft_stack.top():  " << ft_stack.top() << "\n";
        std::cout << "\n------stack.push(123)-------\n";
        std_stack.push(123);
        ft_stack.push(123);
        std::cout << "\n------stack.top()-------\n";
        std::cout << "std_stack.top(): " << std_stack.top() << "\n";
        std::cout << "ft_stack.top():  " << ft_stack.top() << "\n";
        std::cout << "\n------stack.push(456)-------\n";
        std_stack.push(456);
        ft_stack.push(456);
        std::cout << "\n------stack.top()-------\n";
        std::cout << "std_stack.top(): " << std_stack.top() << "\n";
        std::cout << "ft_stack.top():  " << ft_stack.top() << "\n";
        std::cout << "\n------stack.pop()-------\n";
        std_stack.pop();
        ft_stack.pop();
        std::cout << "\n------stack.top()-------\n";
        std::cout << "std_stack.top(): " << std_stack.top() << "\n";
        std::cout << "ft_stack.top():  " << ft_stack.top() << "\n";
    }
    {
        std::cout << "\n-------relational operators------\n";
        ft::stack<std::string> ft_stack_1;
        ft_stack_1.push("apple");
        ft_stack_1.push("banana");
        ft_stack_1.push("carrot");
        ft::stack<std::string> ft_stack_2;
        ft_stack_2.push("apple");
        ft_stack_2.push("banana");
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

void    test_mutant_stack_char(void)
{
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

// void    test_map_int_int()
// {
//     std::map<int, int> map_int;

	
// 	for (int i = 0; i < COUNT; ++i)
// 	{
// 		map_int.insert(std::make_pair(rand(), rand()));
// 	}

// 	int sum = 0;
// 	for (int i = 0; i < 10000; i++)
// 	{
// 		int access = rand();
// 		sum += map_int[access];
// 	}
// 	std::cout << "should    be constant with the same seed: " << sum << std::endl;

// 	{
// 		std::map<int, int> copy = map_int;
// 	}
// }

int main(int argc, char** argv) {
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed    please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed  = atoi(argv[0]);
	srand(seed);
    

    test_pair();
/*
**  vector test 
*/
    test_vector();
    // test_vector_Buffer();
/*
**  stack test 
*/
    test_stack();
    test_stack_Buffer_dequeBuffer();
    test_mutant_stack_char();
/*
**  map test 
*/
    // test_map_int_int();

	return (0);
}