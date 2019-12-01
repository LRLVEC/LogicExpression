#include <cstdio>
#include <_Expression.h>
#include <_File.h>
#include <random>

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
	if (str.length == 0)return nullptr;


}
int main()
{
	File file("./");
	String<char> str(file.find("a.txt").readText());
	Vector<int> p(str.find("aba"));
	str.truncate({ 2,4 }).print();
	//str.findAndDelete("aba");
	//Vector<int> pos0(str.find("("));
	//Vector<int> pos1(str.find(")"));
	p.traverse([](const int& a) {::printf("%d ", a); return true; });
	::printf("\n");
	//pos1.traverse([](const int& a) {::printf("%d ", a); return true; });
	//::printf("\n");

	Interval<unsigned int> sa(1, 4), sb(2, 5);
	sa.print();
	(sa ^= sb).print();
	::printf("%d\n", sa.hasIntersectionWith(sb));


	IntervalSet<unsigned int>set(Vector<int>({ 2,1,6,7,10 }), 2);
	set.print();
	set.simplify().print();
	::printf("%d\n", set.area(false));

	bool A(false), B(true);
	/*Node<bool, LogicOprand, LogicOperator> n('^'), nl(&A), nr(&B);
	n.left = &nl;
	n.right = &nr;

	::printf("%d", n()());*/
}