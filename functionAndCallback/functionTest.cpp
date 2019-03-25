/*
* Author: Chengx
* Date: 2019-3-25
* Description:
*/

#include "functionAndCallback.h"
using namespace std;
using namespace std::placeholders;

//normal function
int addVal(int a, int b)
{
	return a + b;
}

//member function
class class_demo
{
public:
	int addVal(int a, int b)
	{
		return a + b;
	}
	// int operator()(int x) const
	// {
	//     return x * x;
	// }
};

//callback
class demo_class
{
private:
	typedef function<void(int)> func_t;
	func_t func;
	int n;
public:
	demo_class(int i) :n(i){}
	template<typename CallBack>
	void accept(CallBack f)
	{
		func = f;
	}
	void run()
	{
		func(n);
	}
};
//double the input param
void call_back_func(int i)
{
	cout << "call_back_func: " << i * 2 << endl;
}

//functor with status
class call_back_obj
{
private:
	int x;
public:
	call_back_obj(int i) :x(i){}
	void operator()(int i)
	{
		cout << "call_back_obj : " << i * x++ << endl;
	}
};

//member funcitons with bind
class call_back_factory
{
public:
	void call_back_func1(int a)
	{
		cout << "call_back_func1: " << 2 * a << endl;
	}

	void call_back_func2(int a, int b)
	{
		cout << "call_back_fun2: " << 2 * a * b << endl;
	}
};

int main()
{
	//normal function
	cout << "normal function" << endl;
	function<int(int, int)> f = addVal;
	if (f)
	{
		cout << "1 + 2 = " << f(1, 2) << endl;
	}

	//member function1
	cout << "member function1" << endl;
	class_demo cd;
	function<int(class_demo&, int, int)> f1;
	f1 = bind(&class_demo::addVal, _1, _2, _3);
	cout << "2 + 3 = " << f1(cd, 2, 3) << endl;

	//member function2
	cout << "member function2" << endl;
	function<int(int, int)> f2;
	f2 = bind(&class_demo::addVal, &cd, _1, _2);
	cout << "3 + 4 = " << f2(3, 4) << endl;

	//for callback
	cout << "for callback" << endl;
	demo_class dc(10);
	dc.accept(call_back_func);
	dc.run();

	//functor with status
	cout << "functor with status" << endl;
	call_back_obj cbo(2);
	dc.accept(ref(cbo));
	dc.run();
	dc.run();

	//member funcitons with bind
	cout << "member funcitons with bind" << endl;
	call_back_factory cbf;
	dc.accept(bind(&call_back_factory::call_back_func1, &cbf, _1));
	dc.run();

	dc.accept(bind(&call_back_factory::call_back_func2, &cbf, _1, 5));
	dc.run();
	return 0;
}
