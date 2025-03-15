#pragma
#include <initializer_list>


namespace myStd
{
	template<typename T, int S>
	class Array
	{
	public:
		Array() : sizeValue(S) { mArray = new T[sizeValue]; }
		Array(const Array& other);
		Array(Array&& other);
		Array(std::initializer_list<T> initList);
		~Array() { delete[] mArray; }

		const Array<T, S>& operator=(const Array<T, S>& other);
		const Array<T, S>& operator=(Array<T, S>&& other) noexcept;
		T& operator[](const int index);

		int size() { return sizeValue; }
		T& at(int index);
		T& front() { return mArray[0]; }
		T& back() { return mArray[sizeValue - 1]; }
		bool empty();
		T* data() { return mArray; }

		void info();
		void clear();
		void fill(T value);

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

			iterator& operator+(T value) {
				iter += value;
				return *this;
			}

			iterator& operator-(T value) {
				iter -= value;
				return *this;
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

		iterator begin() { return iterator(mArray); }
		iterator end() { return iterator(mArray + sizeValue); }

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

			const_iterator& operator+(T value) {
				citer += value;
				return *this;
			}

			const_iterator& operator-(T value) {
				citer -= value;
				return *this;
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

		const_iterator cbegin() const { return const_iterator(mArray); }
		const_iterator cend() const { return const_iterator(mArray + sizeValue); }

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

			reverse_iterator& operator+(T value) {
				reverse_iter -= value;
				return *this;
			}

			reverse_iterator& operator-(T value) {
				reverse_iter += value;
				return *this;
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

		reverse_iterator rbegin() { return reverse_iterator(mArray + sizeValue - 1); }
		reverse_iterator rend() { return reverse_iterator(mArray + 1); }

	private:
		T* mArray;
		int sizeValue;
	};

	template<typename T, int S>
	Array<T, S>::Array(const Array& other) : sizeValue(other.sizeValue)
	{
		mArray = new T[sizeValue];
		for (int i = 0; i < sizeValue; i++) {
			mArray[i] = other.mArray[i];
		}
	}

	template<typename T, int S>
	Array<T, S>::Array(Array&& other) : sizeValue(other.sizeValue)
	{
		mArray = other.mArray;
		other.mArray = nullptr;
		other.sizeValue = 0;
	}

	template<typename T, int S>
	Array<T, S>::Array(std::initializer_list<T> initList) : sizeValue(initList.size())
	{
		mArray = new T[sizeValue];
		int i = 0;
		for (const T& value : initList) {
			mArray[i++] = value;
		}
	}

	template<typename T, int S>
	const Array<T, S>& Array<T, S>::operator=(const Array<T, S>& other)
	{
		if (this != &other) {
			delete[] mArray;
			sizeValue = other.sizeValue;

			mArray = new T[sizeValue];
			for (int i = 0; i < sizeValue; i++) {
				mArray[i] = other.mArray[i];
			}
		}

		return *this;
	}

	template<typename T, int S>
	const Array<T, S>& Array<T, S>::operator=(Array<T, S>&& other) noexcept
	{
		if (this != &other) {
			delete[] mArray;
			sizeValue = other.sizeValue;
			mArray = other.mArray;
			other.mArray = nullptr;
			other.sizeValue = 0;
		}

		return *this;
	}

	template<typename T, int S>
	T& Array<T, S>::operator[](const int index)
	{
		if (index >= 0 && index < sizeValue) {
			return mArray[index];
		}
		//throw std::out_of_range("Index out of range '[]'");
		std::cout << "Index out of range '[]'" << std::endl;
	}

	template<typename T, int S>
	T& Array<T, S>::at(int index)
	{
		if (index >= 0 && index < sizeValue) {
			return mArray[index];
		}
		//throw std::out_of_range("Index out of range 'at()'");
		std::cout << "Index out of range 'at()'" << std::endl;
	}

	template<typename T, int S>
	void Array<T, S>::clear()
	{
		for (int i = 0; i < sizeValue; i++) {
			mArray[i] = T();
		}
	}

	template<typename T, int S>
	bool Array<T, S>::empty()
	{
		for (int i = 0; i < sizeValue; i++) {
			if (mArray[i] != T())
				return 0;
		}
		return 1;
	}

	template<typename T, int S>
	void Array<T, S>::info()
	{
		std::cout << "{ ";
		for (int i = 0; i < sizeValue; i++) {
			if (i + 1 != sizeValue)
				std::cout << mArray[i] << ", ";
			else
				std::cout << mArray[i];
		}
		std::cout << " }" << std::endl;
	}

	template<typename T, int S>
	void Array<T, S>::fill(T value)
	{
		for (int i = 0; i < sizeValue; i++) {
			mArray[i] = value;
		}
	}
}