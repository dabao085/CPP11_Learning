/*
 * Author: Chengx
 * Date: 2019-3-22
 * Description:
*/

#include "functionAndCallback.h"
#include <boost\ref.hpp>
using namespace std;

int main()
{
	//basic usage
	int x = 10;
	reference_wrapper<int> rw(x);
	assert(rw == x);                //implicit
	(int &)rw = 100;                //non-implicit
	assert(x == 100);

	reference_wrapper<int> rw2(rw);	//copy constructor
	assert(rw2.get() == 100);

	string str;
	boost::reference_wrapper<string> rws(str);
	*(rws.get_pointer()) = "welcome to C++ boost ref";
	cout << rws.get().size() << endl;

	//factory usage: ref and cref
	auto rx = ref(x);
	cout << typeid(rx).name() << endl; //class std::reference_wrapper<int>
	auto crx = cref(x);
	cout << typeid(crx).name() << endl; //class std::reference_wrapper<int const >

	//is_reference_wrapper<T>::value and unwrap_reference<T>::type
	vector<int> ivec(10, 1);
	auto arw = cref(ivec);
	assert(!boost::is_reference_wrapper<decltype(arw)>::value);//bug!
	assert(!boost::is_reference_wrapper<decltype(ivec)>::value);

	auto arws = ref(str);
	cout << typeid(boost::unwrap_reference<decltype(rws)>::type).name() << endl;
	
	//unwrap_ref
	string str1("test");
	auto astr1 = boost::ref(str1);
	cout << boost::unwrap_ref(astr1) << endl;

	return 0;
}