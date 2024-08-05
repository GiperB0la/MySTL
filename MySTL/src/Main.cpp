#include "../include/Header.h"


/*
* using namespace myStd;
* myStd::MyArray          -  std::array
* myStd::MyVector         -  std::vector
* myStd::MyList           -  std::list
* myStd::MyForward_list   -  std::forward_list
* myStd::MyDeque          -  std::deque
* myStd::MyUnordered_map  -  std::unordered_map
* myStd::MyUnordered_set  -  std::unordered_set
* myStd::string           -  std::string
* myStd::MyAuto_ptr       -  std::auto_ptr
* myStd::MyUnique_ptr     -  std::unique_ptr
* myStd::MyShared_ptr     -  std::shared_ptr
*/


int main()
{
	MyArray<int, 4> Array             = { 5, 3, 4, 9 };
	MyVector<int> Vector              = { 5, 3, 4, 9 };
	MyList<int> List                  = { 5, 3, 4, 9 };
	MyForward_list<int> Forward_list  = { 5, 3, 4, 9 };
	MyDeque<int> Deque                = { 5, 3, 4, 9 };
	myStd::string String              = "Hello, World!";
	MyAuto_ptr<int> Auto_ptr          = new int(10);
	MyUnique_ptr<int> Unique_ptr      = new int(10);
	MyShared_ptr<int> Shared_ptr      = new int(10);
	MyUnordered_map<int, myStd::string> Unordered_map;
	MyUnordered_set<myStd::string> Unordered_set;

	return 0;
}