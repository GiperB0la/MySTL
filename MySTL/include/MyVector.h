#ifndef VECTOR_H
#define VECTOR_H
#include <initializer_list>


namespace myStd
{
	template<typename T>
	class MyVector
	{
	public:
		MyVector() : capacityValue(4), sizeValue(0) { vector = new T[capacityValue]; }
		MyVector(int sizeValue) : capacityValue(sizeValue), sizeValue(sizeValue) { 
			vector = new T[capacityValue]; 
			for (int i = 0; i < sizeValue; ++i) {
				vector[i] = T();
			}
		}
		MyVector(const MyVector& other);
		MyVector(MyVector&& other);
		MyVector(std::initializer_list<T> initList);
		~MyVector() { delete[] vector; }

		const MyVector<T>& operator=(const MyVector<T>& other);
		const MyVector<T>& operator=(MyVector<T>&& other) noexcept;
		T& operator[](const int index);

		int size() { return sizeValue; }
		int capacity() { return capacityValue; }
		T& at(int index);
		bool empty() { if (sizeValue == 0) return true; else return false; }

		void resize(int quantity);
		void resize(int quantity, T value);
		void reserve(int quantity);
		void push_back(T value);
		void pop_back();
		void emplace_back();
		void info();
		void clear();

		class iterator
		{
		public:
			friend MyVector;
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

		iterator begin() { return iterator(vector); }
		iterator end() { return iterator(vector + sizeValue); }

		class const_iterator
		{
		public:
			const_iterator() : citer(nullptr) {};
			const_iterator(const T* ptr) : citer(ptr) {};
			~const_iterator() {};

			const T& operator*() {
				return *citer;
			}

			const_iterator& operator++() {
				++citer;
				return *this;
			}

			const_iterator& operator--() {
				--citer;
				return *this;
			}

			const_iterator& operator+=(T value) {
				citer += value;
				return *this;
			}

			const_iterator& operator-=(T value) {
				citer -= value;
				return *this;
			}

			const_iterator operator+(T value) const {
				const_iterator temp = *this;
				temp.citer += value;
				return temp;
			}

			const_iterator operator-(T value) const {
				const_iterator temp = *this;
				temp.citer -= value;
				return temp;
			}

			bool operator==(const const_iterator& other) const {
				if (citer == other.citer)
					return true;
				return false;
			}

			bool operator!=(const const_iterator& other) const {
				if (citer != other.citer)
					return true;
				return false;
			}

		private:
			const T* citer;
		};

		const_iterator cbegin() const { return const_iterator(vector); }
		const_iterator cend() const { return const_iterator(vector + sizeValue); }

		class reverse_iterator
		{
		public:
			reverse_iterator() : reverse_iter(nullptr) {};
			reverse_iterator(T* ptr) : reverse_iter(ptr) {};
			~reverse_iterator() {};

			T& operator*() {
				return *reverse_iter;
			}

			reverse_iterator& operator++() {
				--reverse_iter;
				return *this;
			}

			reverse_iterator& operator--() {
				++reverse_iter;
				return *this;
			}

			reverse_iterator& operator+=(T value) {
				reverse_iter -= value;
				return *this;
			}

			reverse_iterator& operator-=(T value) {
				reverse_iter += value;
				return *this;
			}

			reverse_iterator operator+(T value) const {
				const_iterator temp = *this;
				temp.reverse_iter -= value;
				return temp;
			}

			reverse_iterator operator-(T value) const {
				const_iterator temp = *this;
				temp.reverse_iter += value;
				return temp;
			}

			bool operator==(const reverse_iterator& other) const {
				if (reverse_iter == other.reverse_iter + 2)
					return true;
				return false;
			}

			bool operator!=(const reverse_iterator& other) const {
				if (reverse_iter != other.reverse_iter - 2)
					return true;
				return false;
			}

		private:
			T* reverse_iter;
		};

		reverse_iterator rbegin() { return reverse_iterator(vector + sizeValue - 1); }
		reverse_iterator rend() { return reverse_iterator(vector + 1); }

		void insert(iterator& it, T value);
		void erase(iterator& it);

	private:
		T* vector;
		int sizeValue;
		int capacityValue;
		void resizeVector();
	};

	template<typename T>
	MyVector<T>::MyVector(const MyVector& other) : capacityValue(other.capacityValue), sizeValue(other.sizeValue)
	{
		vector = new T[capacityValue];
		for (int i = 0; i < sizeValue; i++) {
			vector[i] = other.vector[i];
		}
	}

	template<typename T>
	MyVector<T>::MyVector(MyVector&& other) : capacityValue(other.capacityValue), sizeValue(other.sizeValue)
	{
		vector = other.vector;
		other.vector = nullptr;
		other.sizeValue = 0;
		other.capacityValue = 0;
	}

	template<typename T>
	MyVector<T>::MyVector(std::initializer_list<T> initList) : capacityValue(initList.size() + 4), sizeValue(initList.size())
	{
		vector = new T[capacityValue];
		int i = 0;
		for (const T& value : initList) {
			vector[i++] = value;
		}
	}

	template<typename T>
	const MyVector<T>& MyVector<T>::operator=(const MyVector<T>& other)
	{
		if (this != &other) {
			delete[] vector;
			capacityValue = other.capacityValue;
			sizeValue = other.sizeValue;

			vector = new T[capacityValue];
			for (int i = 0; i < sizeValue; i++) {
				vector[i] = other.vector[i];
			}
		}

		return *this;
	}

	template<typename T>
	const MyVector<T>& MyVector<T>::operator=(MyVector<T>&& other) noexcept
	{
		if (this != &other) {
			delete[] vector;
			sizeValue = other.sizeValue;
			capacityValue = other.capacityValue;
			vector = other.vector;
			other.vector = nullptr;
			other.sizeValue = 0;
			other.capacityValue = 0;
		}

		return *this;
	}

	template<typename T>
	T& MyVector<T>::operator[](const int index)
	{
		if (index >= 0 && index < sizeValue) {
			return vector[index];
		}
		//throw std::out_of_range("Index out of range '[]'");
		std::cout << "Index out of range '[]'" << std::endl;
	}

	template<typename T>
	void MyVector<T>::resizeVector()
	{
		capacityValue *= 1.5;
		T* newVector = new T[capacityValue];
		for (int i = 0; i < sizeValue; i++) {
			newVector[i] = vector[i];
		}
		delete[] vector;
		vector = std::move(newVector);
	}

	template<typename T>
	void MyVector<T>::resize(int quantity)
	{
		capacityValue = quantity;
		resizeVector();
		for (int i = sizeValue; i < quantity; i++) {
			vector[i] = T();
		}
		sizeValue = quantity;
	}

	template<typename T>
	void MyVector<T>::resize(int quantity, T value)
	{
		capacityValue = quantity;
		resizeVector();
		for (int i = sizeValue; i < quantity; i++) {
			vector[i] = value;
		}
		sizeValue = quantity;
	}

	template<typename T>
	void MyVector<T>::reserve(int quantity)
	{
		capacityValue = quantity;
		T* newVector = new T[capacityValue];
		for (int i = 0; i < sizeValue; i++) {
			newVector[i] = vector[i];
		}
		delete[] vector;
		vector = std::move(newVector);
	}

	template<typename T>
	T& MyVector<T>::at(int index)
	{
		if (index >= 0 && index < sizeValue) {
			return vector[index];
		}
		std::cout << "Index out of range 'at()'" << std::endl;
	}

	template<typename T>
	void MyVector<T>::push_back(T value)
	{
		if (sizeValue == capacityValue) {
			resizeVector();
		}
		vector[sizeValue] = value;
		sizeValue++;
	}

	template<typename T>
	void MyVector<T>::pop_back()
	{
		if (sizeValue <= 0) {
			std::cout << "Index out of range 'pop_back()'" << std::endl;
		}
		else {
			sizeValue--;
			vector[sizeValue] = T();
		}
	}

	template<typename T>
	void MyVector<T>::emplace_back()
	{
		if (sizeValue == capacityValue) {
			resizeVector();
		}
		vector[sizeValue] = T();
		sizeValue++;
	}

	template<typename T>
	void MyVector<T>::info()
	{
		std::cout << "{ ";
		for (int i = 0; i < sizeValue; i++) {
			if (i + 1 != sizeValue)
				std::cout << vector[i] << ", ";
			else
				std::cout << vector[i];
		}
		std::cout << " }" << std::endl;
	}

	template<typename T>
	void MyVector<T>::clear()
	{
		delete[] vector;
		capacityValue = 4;
		sizeValue = 0;
		vector = new T[capacityValue];
	}

	template<typename T>
	void MyVector<T>::insert(iterator& it, T value)
	{
		sizeValue++;
		int offsetIter = it.iter - vector;
		if (capacityValue < sizeValue)
			resizeVector();
		for (int i = sizeValue; i > offsetIter; i--) {
			vector[i] = vector[i - 1];
		}
		vector[offsetIter] = value;
	}

	template<typename T>
	void MyVector<T>::erase(iterator& it)
	{
		sizeValue--;
		int offsetIter = it.iter - vector;
		for (int i = offsetIter; i < sizeValue; i++) {
			vector[i] = vector[i + 1];
		}
	}
}

#endif