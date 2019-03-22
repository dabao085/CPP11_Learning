/*
 * Author: Chengx
 * Date: 2019-3-22
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

class demo_calss
{
public:
    int print(int a, int b)
    {
        return a + b;
    }
};

class demo_class_with_var
{
public:
    demo_class_with_var():x(0){}
private:
    int x;
};

class point
{
public:
    point(int a = 0, int b = 0):x(a), y(b){}
    void print()
    {
        cout << "x: " << x << "y: " << y << endl;
    }
    int x, y;
};

int main()
{
    //bind normal function
    cout << bind(addVal, 1, 2)() << endl;   //print 3
    int x;
    cout << "input x: " << endl;
    cin >> x;
    cout << bind(addVal, _1, 3)(x) << endl; //print x + 3
    int y;
    cout << "input x, y:" << endl;
    cin >> x >> y;
    cout << bind(addVal, _1, _2)(x, y) << endl; //print x + y
    cout << "input x, y:" << endl;
    cin >> x >> y;
    cout << bind(addVal, _2, _1)(x, y) << endl; //print y + x, the order is changed


    //bind member function
    demo_calss dc;
    cout << bind(&demo_calss::print, dc, 1, 2)() << endl; //print 3
    cout << "input x: " << endl;
    cin >> x;
    cout << bind(&demo_calss::print, dc, _1, 3)(x) << endl; //print x + 3
    cout << "input x, y: " << endl;
    cin >> x >> y;
    cout << bind(&demo_calss::print, dc, _1, _2)(x, y) << endl; //print x + y

    //use STL algorithm
    vector<point> pvec(10);
    for_each(pvec.begin(), pvec.end(), bind(&point::print, _1));

    //bind member variable
    vector<int> ivec(10);
    transform(pvec.begin(), pvec.end(), ivec.begin(), bind(&point::x, _1));
    for(const auto &a : ivec)
        cout << a << " ";
    cout << endl;

    //bind functor
    cout << "input x: " << endl;
    cin >> x;
    cout << bind(greater<int>(), _1, 10)(x) << endl;   //check x > 10?
    cout << "input x, y: " << endl;
    cin >> x >> y;
    cout << bind(plus<int>(), _1, _2)(x, y) << endl;    //calculate x + y
    cout << "input x: " << endl;
    cin >> x;
    cout << bind(modulus<int>(), _1, 3)(x) << endl;
    return 0;
}