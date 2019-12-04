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
	Expr te(str);
	Vector<IntervalSet<int>> vi(te.getParentheses());
	vi.traverse([](IntervalSet<int>const& a) {a.print(); return true; });

	//Vector<int> p(str.find("aba"));
	//str.truncate({ 2,4 }).print();
	//str.findAndDelete("aba");
	//Vector<int> pos0(str.find("("));
	//Vector<int> pos1(str.find(")"));
	//p.traverse([](const int& a) {::printf("%d ", a); return true; });
	//::printf("\n");
	//pos1.traverse([](const int& a) {::printf("%d ", a); return true; });
	//::printf("\n");

	Interval<unsigned int> itvl_a(1, 4), itvl_b(2, 5);
	itvl_a.print("itvl_a: ", "\n");
	itvl_b.print("itvl_b: ", "\n");
	(itvl_a ^= itvl_b).print("itvl_a ^ itvl_b ", "\n");
	::printf("itvl_a.hasItW(itvl_b): %d\n", itvl_a.hasIntersectionWith(itvl_b));


	IntervalSet<unsigned int>set(Vector<int>({ 2,1,6,7,10 }), 2, true);
	set.print("set: ");
	set.simplify().print("set.simplify(): ");
	::printf("set.area(): %d\n", set.area(true));
	(set ^ Interval<unsigned int>(1, 6)).print("set ^ [1, 6]: ");
	//(Interval<unsigned int>(1, 6) ^ set).print();
	(set ^= {1, 2}).print("set ^= [1, 2]: ");

	Vector<int>vec({ 1, 2, 3, 4, 5 });
	Vector<int>vectr(vec.truncate(0, 4));
	vec.truncateSelf(0, 5);
	vec.traverse([](int const& a) {::printf("%d ", a); return true; });
	vectr.traverse([](int const& a) {::printf("%d ", a); return true; });

	bool A(false), B(true);
	/*Node<bool, LogicOprand, LogicOperator> n('^'), nl(&A), nr(&B);
	n.left = &nl;
	n.right = &nr;

	::printf("%d", n()());*/
}