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
	itvl_a.move(2).print("itvl_a.move(2)", "\n");
	itvl_a.moveSelf(3).print("itvl_a.moveSelf(3)", "\n");
	(itvl_a ^= itvl_b).print("itvl_a ^ itvl_b ", "\n");
	::printf("itvl_a.hasItW(itvl_b): %d\n", itvl_a.hasIntersectionWith(itvl_b));


	IntervalSet<int>set_0(Vector<int>({ 2,1,6,7,10,16,19 }), 2, true);
	IntervalSet<int>set_1(Vector<int>({ 3,5,6,2 }), 1, true);

	str.print("str: ", "\n");
	str.truncate(set_0).print("str.truncate(set_0): ", "\n");
	str.truncateSelf(set_0).print("str.truncateSelf(set_0): ", "\n");


	set_0.print("set_0: ");
	set_0.simplify().print("set_0.simplify(): ");
	set_0.move(2).print("set_0.moveSelf(2): ");
	set_1.print("set_1: ");
	(set_0 ^= set_1).print("set_0 ^= set_1: ");
	::printf("set_0.area(true): %d\n", set_0.area(true));
	(set_0 ^ Interval<int>(1, 6)).print("set_0 ^ [1, 6]: ");
	//(Interval<unsigned int>(1, 6) ^ set).print();
	(set_0 ^= {1, 2}).print("set_0 ^= [1, 2]: ");

	Vector<int>vec({ 1, 2, 3, 4, 5 });
	Vector<int>vectr(vec.truncate(0, 4));
	Vector<int>vectrs(vec.truncate(set_1));
	//vec.truncateSelf(0, 5);
	::printf("vec: ");
	vec.traverse([](int const& a) {::printf("%d ", a); return true; }); ::printf("\n");
	::printf("vec.truncate: ");
	vectr.traverse([](int const& a) {::printf("%d ", a); return true; }); ::printf("\n");
	::printf("vec.truncateSelf(set_1): ");
	vectrs.traverse([](int const& a) {::printf("%d ", a); return true; }); ::printf("\n");

	bool A(false), B(true);
	/*Node<bool, LogicOprand, LogicOperator> n('^'), nl(&A), nr(&B);
	n.left = &nl;
	n.right = &nr;

	::printf("%d", n()());*/
}