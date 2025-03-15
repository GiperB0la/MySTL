#pragma
#include "Vector.h"
#include <initializer_list>


namespace myStd
{
	template<typename T>
	class Deque
	{
	public:
		Deque() : sizeValue(0) {
			blocks.push_back(myStd::MyVector<T>());
		};
		Deque(std::initializer_list<T> initList) : sizeValue(initList.size()) {
			int i = 0;
			myStd::MyVector<T> vec;
			for (T val : initList) {
				vec.push_back(val);
				i++;
				if (i == 4) {
					blocks.push_back(vec);
					vec.clear();
				}
			}
			blocks.push_back(vec);
		}
		Deque(const Deque& other) {
			sizeValue = other.sizeValue;
			blocks = other.blocks;
		}
		Deque(Deque&& other) {
			sizeValue = other.sizeValue;
			blocks = other.blocks;
			other.sizeValue = 0;
			other.blocks.clear();
		}
		~Deque() { clear(); };

		void push_back(T value);
		void push_front(T value);
		void pop_back();
		void pop_front();
		void clear();
		bool empty() {
			if (sizeValue == 0)
				return 1;
			return 0;
		}
		void info();

		int size() { return sizeValue; }
		T& at(int index);

		const Deque<T>& operator=(const Deque<T>& other);
		const Deque<T>& operator=(Deque<T>&& other);
		T& operator[](int index);

		class iterator
		{
		public:
			iterator() : iter(nullptr) {};
			iterator(T* ptr) : iter(ptr) {};
			~iterator() {};

			T& operator*() {
				return *iter;
			}

			iterator& operator++() {
				++iter;
				return *this;
			}

			iterator& operator++(int) {
				++iter;
				return *this;
			}

			iterator& operator--() {
				--iter;
				return *this;
			}

			iterator& operator--(int) {
				--iter;
				return *this;
			}

			iterator& operator+=(T value) {
				iter += value;
				return *this;
			}

			iterator& operator-=(T value) {
				iter -= value;
				return *this;
			}

			iterator operator+(T value) const {
				iterator temp = *this;
				temp.iter += value;
				return temp;
			}

			iterator operator-(T value) const {
				iterator temp = *this;
				temp.iter -= value;
				return temp;
			}

			bool operator==(const iterator& other) const {
				if (iter == other.iter)
					return true;
				return false;
			}

			bool operator!=(const iterator& other) const {
				if (iter != other.iter)
					return true;
				return false;
			}

		private:
			T* iter;
		};

		iterator begin() { return iterator(&(blocks.at(0).at(0))); }
		iterator end() { return iterator(&(blocks.at(blocks.size() - 1).at(blocks.at(blocks.size() - 1).size() - 1))); }

	private:
		myStd::MyVector<myStd::MyVector<T>> blocks;
		int sizeValue;
	};

	template<typename T>
	const Deque<T>& Deque<T>::operator=(const Deque<T>& other)
	{
		if (this != &other) {
			blocks.clear();
			blocks = other.blocks;
			sizeValue = other.sizeValue;
		}
		return *this;
	}

	template<typename T>
	const Deque<T>& Deque<T>::operator=(Deque<T>&& other)
	{
		if (this != &other) {
			blocks.clear();
			blocks = other.blocks;
			sizeValue = other.sizeValue;
			other.sizeValue = 0;
			other.blocks.clear();
		}
		return *this;
	}

	template<typename T>
	void Deque<T>::push_back(T value)
	{
		if (blocks.at(blocks.size() - 1).size() == 4) {
			blocks.push_back(myStd::MyVector<T>());
		}
		blocks.at(blocks.size() - 1).push_back(value);
		sizeValue++;
	}

	template<typename T>
	void Deque<T>::push_front(T value)
	{
		if (blocks.at(0).size() == 4) {
			myStd::MyVector<myStd::MyVector<T>> newBlocks(blocks.size() + 1);
			int i = 0;
			for (myStd::MyVector<T> block : blocks) {
				newBlocks.at(i + 1) = block;
				i++;
			}
			blocks = std::move(newBlocks);
			blocks.at(0).push_back(value);
		}
		else {
			myStd::MyVector<T> block;
			block.push_back(value);
			for (T val : blocks.at(0)) {
				block.push_back(val);
			}
			blocks.at(0) = std::move(block);
		}
		
		sizeValue++;
	}

	template<typename T>
	void Deque<T>::pop_back()
	{
		if (blocks.at(blocks.size() - 1).size() == 0) {
			blocks.pop_back();
		}
		blocks.at(blocks.size() - 1).pop_back();
		if (blocks.at(blocks.size() - 1).size() == 0) {
			blocks.pop_back();
		}
		sizeValue--;
	}

	template<typename T>
	void Deque<T>::pop_front()
	{
		myStd::MyVector<T> block;
		for (int i = 1; i < blocks.at(0).size(); ++i) {
			block.push_back(blocks.at(0).at(i));
		}

		blocks.at(0) = std::move(block);

		bool flag = true;
		if (blocks.at(0).empty()) {
			myStd::MyVector<myStd::MyVector<T>> newBlocks;
			for (myStd::MyVector<T> block : blocks) {
				if (flag) {
					flag = false;
					continue;
				}
				newBlocks.push_back(block);
			}
			blocks = std::move(newBlocks);
		}

		sizeValue--;
	}

	template<typename T>
	void Deque<T>::info()
	{
		std::cout << "{ ";
		int i = 0;
		for (myStd::MyVector<T> block : blocks) {
			for (T elem : block) {
				std::cout << elem;
				if (i < sizeValue - 1) {
					std::cout << ", ";
				}
				i++;
			}
		}
		std::cout << " }" << std::endl;
	}

	template<typename T>
	T& Deque<T>::at(int index)
	{
		if (index >= 0 && index < sizeValue) {
			int n = 0;
			while (index > 4) {
				index -= 4;
				n++;
			}
			if (index >= blocks.at(n).size()) {
				index = index - blocks.at(n).size();
				n++;
			}
			return blocks.at(n).at(index);
		}
		else {
			std::cout << "Index out of range 'at()'" << std::endl;
		}
	}

	template<typename T>
	T& Deque<T>::operator[](int index)
	{
		if (index >= 0 && index < sizeValue) {
			int n = 0;
			while (index > 4) {
				index -= 4;
				n++;
			}
			if (index >= blocks.at(n).size()) {
				index = index - blocks.at(n).size();
				n++;
			}
			return blocks.at(n).at(index);
		}
		else {
			std::cout << "Index out of range 'at()'" << std::endl;
		}
	}

	template<typename T>
	void Deque<T>::clear()
	{
		myStd::MyVector<myStd::MyVector<T>> newBlocks(1);
		blocks = std::move(newBlocks);
		sizeValue = 0;
	}
}