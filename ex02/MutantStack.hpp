#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <stack>
#include <deque>

template<typename T, typename Container = std::deque<T> >
class MutantStack : public std::stack<T, Container>
{
public:
	MutantStack();
	MutantStack(const MutantStack& other);
	MutantStack& operator=(const MutantStack& other);
	~MutantStack();

	// イテレータの型定義
	typedef typename Container::iterator iterator;

	// イテレータの関数
	iterator begin();
	iterator end();
};

#include "MutantStack.tpp"

#endif
