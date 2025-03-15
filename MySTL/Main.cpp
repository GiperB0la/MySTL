#include "include/Array.h"
#include "include/Vector.h"
#include "include/List.h"
#include "include/Forward_list.h"
#include "include/Deque.h"
#include "include/String.h"
#include "include/Memory.h"
#include "include/Unordered_map.h"
#include "include/Unordered_set.h"


int main()
{
	myStd::Array<int, 4> Array = { 5, 3, 4, 9 };
	myStd::Vector<int> Vector = { 5, 3, 4, 9 };
	myStd::List<int> List = { 5, 3, 4, 9 };
	myStd::Forward_list<int> Forward_list = { 5, 3, 4, 9 };
	myStd::Deque<int> Deque = { 5, 3, 4, 9 };
	myStd::String String = "Hello, World!";
	myStd::Auto_ptr<int> Auto_ptr = new int(10);
	myStd::Unique_ptr<int> Unique_ptr = new int(10);
	myStd::Shared_ptr<int> Shared_ptr = new int(10);
	myStd::Unordered_map<int, myStd::String> Unordered_map;
	myStd::Unordered_set<myStd::String> Unordered_set;

	return 0;
}