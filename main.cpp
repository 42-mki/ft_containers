#include <iostream>
#include <string>
#include <deque>

#include <map>
#include <stack>
#include <vector>

#include <vector.hpp>
// #include <stack.hpp>
// #include <map.hpp>

#include <stdlib.h>
#include <stdio.h>

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
class MutantStack : public std::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename std::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

void    display_vector(std::vector<int> v)
{
    std::vector<int>::iterator it;
    
    for (it = v.begin(); it < v.end(); it++)
    {
        std::cout << " " << *it;
    }
    std::cout << "\n";
}

void    test_vector(void)
{
    // int벡터 생성
    // std::vector<int> v1;
    // std::vector<int> v2;

    // int벡터 생성하고, 크기를 4만큼 할당되었습니다.
    // 할당된 공간은 0으로 초기화됩니다.
    // std::vector<int> v(4);
    
    // int벡터 생성하고, 크기를 4만큼 할당되었습니다.
    // 할당된 공간은 2으로 초기화됩니다.


    std::cout << "\n-------vector 생성-------\n";
    std::vector<int> v1(4, 2);
    ft::vector<int> v2(4, 3);

    std::cout << "\n-------reserve()------\n";
    v1.reserve(8);
    v2.reserve(8);

    std::cout << "\n-------operator[0]------\n";
    std::cout << v1[0] << "\n";
    std::cout << v2[0] << "\n";
    /*
    **  Element access:
    */
    std::cout << "\n-------operator[-1]------\n";
    std::cout << v1[-1] << "\n";
    std::cout << v2[-1] << "\n";

    std::cout << "\n-------at(0)------\n";
    std::cout << v1.at(0) << "\n";
    std::cout << v2.at(0) << "\n";

    // std::cout << "\n-------at(-1)------\n";
    // std::cout << v1.at(-1) << "\n";
    // std::cout << v2.at(-1) << "\n";

    std::cout << "\n-------front()------\n";
    std::cout << v1.front() << "\n";
    std::cout << v2.front() << "\n";

    std::cout << "\n-------back()------\n";
    std::cout << v1.back() << "\n";
    std::cout << v2.back() << "\n";
    /*
    **  Capacity
    */
    std::cout << "\n-------size()------\n";
    std::cout << v1.size() << "\n";
    std::cout << v2.size() << "\n";

    std::cout << "\n-------max_size()------\n";
    std::cout << v1.max_size() << "\n";
    std::cout << v2.max_size() << "\n";

    // std::cout << "\n-------resize()------\n";
    // std::cout << v1.resize() << "\n";
    // std::cout << v2.resize() << "\n";

    std::cout << "\n-------capacity()------\n";
    std::cout << v1.capacity() << "\n";
    std::cout << v2.capacity() << "\n";

    std::cout << "\n-------empty()------\n";
    std::cout << v1.empty() << "\n";
    std::cout << v2.empty() << "\n";
    /*
    **  Modifiers:
    */
    std::cout << "\n-------push_back()------\n";
    v1.push_back(10);
    v2.push_back(10);
    std::cout << v1.at(4) << "\n";
    std::cout << v2.at(4) << "\n";

    std::cout << "\n-------pop_back()------\n";
    v1.pop_back();
    v2.pop_back();
    // std::cout << v1.at(4) << "\n";
    // std::cout << v2.at(4) << "\n";

    std::cout << "\n-------swap()------\n";
    std::vector<int> v3(4, 50);
    ft::vector<int> v4(4, 100);
    v1.swap(v3);
    v2.swap(v4);
    std::cout << v1.at(3) << "\n";
    std::cout << v2.at(3) << "\n";

    // std::cout << "\n-------clear()------\n";
    // std::cout << v1.clear() << "\n";
    // std::cout << v2.clear() << "\n";



}

void    test_vector_int(void)
{
	std::vector<int> vector_int;
}

void    test_vector_string(void)
{
    std::vector<std::string> vector_str;

}

void    test_vector_Buffer(void)
{
	std::vector<Buffer> vector_buffer;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	std::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
}

void    test_stack_int(void)
{
	std::stack<int> stack_int;
}


void    test_stack_Buffer_dequeBuffer()
{
	std::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
}

void    test_mutant_stack_char(void)
{
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;
}

void    test_map_int_int()
{
    std::map<int, int> map_int;

	
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(std::make_pair(rand(), rand()));
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should    be constant with the same seed: " << sum << std::endl;

	{
		std::map<int, int> copy = map_int;
	}
}

int main(int argc, char** argv) {
	if (argc != 2)
	{
		// std::cerr << "Usage: ./test seed" << std::endl;
		// std::cerr << "Provide a seed    please" << std::endl;
		// std::cerr << "Count value:" << COUNT << std::endl;
		// return 1;
	}
	const int seed  = atoi(argv[0]);
	srand(seed);

/*
**  vector test 
*/
    test_vector();
    // test_vector_int();
    // test_vector_string();
    // test_vector_Buffer();
/*
**  stack test 
*/
    // test_stack_int();
    // test_stack_Buffer_dequeBuffer();
    // test_mutant_stack_char();
/*
**  map test 
*/
    // test_map_int_int();

	return (0);
}