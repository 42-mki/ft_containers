#include <iostream>
#include <string>
#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"
#include "set.hpp"

using std::cout;
using std::endl;

template <typename F, typename S>
std::ostream& operator<<(std::ostream& out, const ft::pair<F, S>& p)
{
	out << '(' << p.first << ", " << p.second << ')';
	return out;
}
template <typename T>
std::ostream& operator<<(std::ostream& out, const ft::vector<T>& v)
{
	out << '[';
	if (!v.empty())
	{
		out << v[0];
		for (size_t i = 1; i < v.size(); ++i)
			out << ", " << v[i];
	}
	out << ']';
	return out;
}
template <typename K, typename V>
std::ostream& operator<<(std::ostream& out, const ft::map<K, V>& m)
{
	out << '{';
	if (!m.empty())
	{
		typename ft::map<K, V>::const_iterator itr = m.begin();
		out << itr->first << ':' << itr->second;
		++itr;
		for (; itr != m.end(); ++itr)
			out << ", " << itr->first << ':' << itr->second;
	}
	out << '}';
	return out;
}
template <typename K>
std::ostream& operator<<(std::ostream& out, const ft::set<K>& s)
{
	out << '{';
	if (!s.empty())
	{
		typename ft::set<K>::const_iterator itr = s.begin();
		out << *itr;
		++itr;
		for (; itr != s.end(); ++itr)
			out << ", " << *itr;
	}
	out << '}';
	return out;
}

int main()
{
	cout << "---------vector---------" << endl;
	ft::vector<int> vbase;
	for (int i = 3; i < 9; ++i)
		vbase.push_back(i);
	ft::vector<int> v(vbase.begin(), vbase.end());
	cout << v << endl;;
	v.insert(v.begin() + 1, 11);
	cout << v << endl;
	v.pop_back();
	cout << v << endl;
	v.erase(v.begin() + 3);
	cout << v << endl;

	cout << "---------stack---------" << endl;
	ft::stack<int> s;
	for (int i = 5; i < 10; ++i)
		s.push(i*i);
	while (!s.empty())
	{
		cout << s.top() << ' ';
		s.pop();
	}
	cout << endl;

	cout << "---------map---------" << endl;
	ft::map<std::string, double> m;
	m["2nd_string"] = 212.11;
	m["1st_string"] = 111.11;
	m["3rd_string"] = 333.11;
	for (size_t i = 0; i < v.size(); ++i)
		m.insert(ft::make_pair(std::string("strnum") + static_cast<char>('0' + i%10), static_cast<double>(i*i*i)));
	cout << m << endl;
	cout << m.size() << endl;
	cout << m["strnum3"] << endl;

	cout << "---------set---------" << endl;
	ft::set<std::string> ss;
	for (ft::map<std::string, double>::iterator itr = m.begin(); itr != m.end(); ++itr)
		ss.insert(itr->first);
	cout << ss << endl;
	cout << ss.size() << endl;

	ft::set<int> si;
	si.insert(1);
	si.insert(2);
	si.insert(3);
	si.insert(1);
	si.insert(4);
	si.insert(5);
	si.insert(6);
	for (ft::set<int>::reverse_iterator r = si.rbegin(); r != si.rend(); ++r)
		cout << *r << ' ';
	return 0;
}
