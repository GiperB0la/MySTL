#pragma
#include <string>
#include <vector>
#include <forward_list>


namespace myStd
{
	template<typename T>
	class Unordered_set
	{
	public:
		Unordered_set() : bucketValue(2), sizeValue(0) {
			for (int i = 0; i < bucketValue; ++i) {
				bucket.emplace_back();
			}
		};
		~Unordered_set() {};


		int size() { return sizeValue; }
		void add(T value);
		int contains(T value);
		void remove(T value);

	private:
		int hash(T key) { return std::hash<T>{}(key) % bucket.size(); }
		void inBucket(bool flag);

		int sizeValue;
		int bucketValue;
		myStd::MyVector<std::forward_list<T>> bucket;
	};

	template<typename T>
	void Unordered_set<T>::inBucket(bool flag)
	{
		if (flag)
			bucketValue *= 2;
		else if (!flag && bucketValue > 2)
			bucketValue /= 2;
		sizeValue = 0;

		std::vector<std::string> vec;
		for (auto n : bucket) {
			for (auto h : n) {
				vec.push_back(h);
			}
		}

		bucket.clear();
		for (int i = 0; i < bucketValue; i++) {
			bucket.emplace_back();
		}

		for (auto n : vec) {
			add(n);
		}
	}

	template<typename T>
	void Unordered_set<T>::add(T value)
	{
		if (!contains(value)) {
			if (sizeValue != bucketValue)
				bucket.at(hash(value)).push_front(value);
			else {
				inBucket(1);
				bucket.at(hash(value)).push_front(value);
			}
			sizeValue++;
		}
	}

	template<typename T>
	int Unordered_set<T>::contains(T value)
	{
		for (auto n : bucket[hash(value)]) {
			if (n == value)
				return 1;
		}
		return 0;
	}

	template<typename T>
	void Unordered_set<T>::remove(T value)
	{
		if (contains(value)) {
			for (auto n : bucket[hash(value)]) {
				if (n == value) {
					sizeValue--;
					bucket[hash(value)].remove(value);
					break;
				}
			}
		}
	}
}