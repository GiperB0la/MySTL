#pragma
#include "String.h"
#include "Vector.h"
#include "Forward_list.h"
#include <functional>


namespace myStd
{
	template<typename T1, typename T2>
	class Unordered_map
	{
	public:
		Unordered_map() : bucketValue(2), sizeValue(0) {
			for (int i = 0; i < bucketValue; ++i) {
				bucket.emplace_back();
			}
		};
		~Unordered_map() {};


		int size() { return sizeValue; }
		void insert(T1 key, T2 meaning);
		void erase(T1 key);
		bool find(T1 key);
		int get(T1 key);
		bool empty() { if (sizeValue == 0) return 1; else return 0; }

	private:
		int hash(T1 key) { return std::hash<T1>{}(key) % bucket.size(); }
		void inBucket(bool flag);

		int sizeValue;
		int bucketValue;
		myStd::MyVector<myStd::MyForward_list<myStd::MyVector<myStd::string>>> bucket;
	};

	template<typename T1, typename T2>
	void Unordered_map<T1, T2>::inBucket(bool flag)
	{
		if (flag)
			bucketValue *= 2;
		else if (!flag && bucketValue > 2)
			bucketValue /= 2;
		sizeValue = 0;

		myStd::MyVector<myStd::MyVector<myStd::string>> vec;
		for (myStd::MyForward_list<myStd::MyVector<myStd::string>> n : bucket) {
			for (myStd::MyVector<myStd::string> h : n) {
				vec.push_back(h);
			}
		}

		bucket.clear();
		for (int i = 0; i < bucketValue; i++) {
			bucket.emplace_back();
		}

		for (myStd::MyVector<myStd::string> n : vec) {
			insert(n.at(0), std::stoi(n.at(1)));
		}
	}

	template<typename T1, typename T2>
	void Unordered_map<T1, T2>::insert(T1 key, T2 meaning)
	{
		if (!find(key)) {
			myStd::MyVector<myStd::string> bucketVec;
			bucketVec.push_back(key);
			bucketVec.push_back(std::to_string(meaning));

			if (sizeValue != bucketValue)
				bucket.at(hash(key)).push_front(bucketVec);
			else {
				inBucket(1);
				bucket.at(hash(key)).push_front(bucketVec);
			}
			sizeValue++;
		}
	}

	template<typename T1, typename T2>
	bool Unordered_map<T1, T2>::find(T1 key)
	{
		for (myStd::MyVector<myStd::string> n : bucket[hash(key)]) {
			for (myStd::string h : n) {
				if (h == key)
					return 1;
			}
		}
		return 0;
	}

	template<typename T1, typename T2>
	void Unordered_map<T1, T2>::erase(T1 key)
	{
		if (find(key)) {
			for (myStd::MyVector<myStd::string> n : bucket[hash(key)]) {
				for (myStd::string h : n) {
					if (h == key) {
						sizeValue--;
						bucket[hash(key)].remove(n);
						if (sizeValue != bucketValue)
							inBucket(0);
						return;
					}
				}
			}
		}
	}

	template<typename T1, typename T2>
	int Unordered_map<T1, T2>::get(T1 key)
	{
		if (find(key)) {
			for (myStd::MyVector<myStd::string> n : bucket[hash(key)]) {
				for (myStd::string h : n) {
					if (h == key) {
						return std::stoi(n.at(1));
					}
				}
			}
		}
		return -1;
	}
}