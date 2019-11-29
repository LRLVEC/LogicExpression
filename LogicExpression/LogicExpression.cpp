#include <cstdio>
#include <_Expression.h>
#include <_File.h>

using namespace Expression;
struct LogicOprand :Oprand<bool>
{
	bool* op;
	bool allocated;
	LogicOprand()
		:
		op((bool*)::malloc(sizeof(bool))),
		allocated(true)
	{
		*op = false;
	}
	LogicOprand(bool const& _op)
		:
		op((bool*)::malloc(sizeof(bool))),
		allocated(true)
	{
		*op = _op;
	}
	LogicOprand(bool* _op)
		:
		op(_op),
		allocated(false)
	{
	}
	~LogicOprand()
	{
		if (allocated)::free(op);
		allocated = false;
	}
	bool operator()()const
	{
		return *op;
	}
	bool operator=(bool const& a)
	{
		return *op = a;
	}
};
struct LogicOperator :Operator<bool>
{
	char op;
	LogicOperator(char _op)
		:op(_op)
	{
	}
	bool operator()(Oprand<bool>const* a, Oprand<bool>const* b)const
	{
		switch (op)
		{
			case '+': return a->operator()() || b->operator()();
			case '*': return a->operator()() * b->operator()();
			case '!': return !b->operator()();
			case '^': return a->operator()() ^ b->operator()();
			case '(': return b->operator()();
			default: return false;
		}
	}
};
Node<bool, LogicOprand, LogicOperator>* Build(String<char> const& str)
{
	//...
	return nullptr;
}
int main()
{
	File file("./");
	file.find("a.txt").readText().print();
	bool A(false), B(true);
	Node<bool, LogicOprand, LogicOperator> n('^'), nl(&A), nr(&B);
	n.left = &nl;
	n.right = &nr;

	::printf("%d", n()());
}