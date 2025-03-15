#pragma
#include <initializer_list>


namespace myStd
{
	template<typename T>
	class Vector
	{
	public:
		Vector() : capacityValue(4), sizeValue(0) { Vector = new T[capacityValue]; }
		Vector(int sizeValue) : capacityValue(sizeValue), sizeValue(sizeValue) { 
			Vector = new T[capacityValue]; 
			for (int i = 0; i < sizeValue; ++i) {
				Vector[i] = T();
			}
		}
		Vector(const Vector& other);
		Vector(Vector&& other);
		Vector(std::initializer_list<T> initList);
		~Vector() { delete[] Vector; }

		const Vector<T>& operator=(const Vector<T>& other);
		const Vector<T>& operator=(Vector<T>&& other) noexcept;
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
			friend Vector;
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

		iterator begin() { return iterator(Vector); }
		iterator end() { return iterator(Vector + sizeValue); }

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

		const_iterator cbegin() const { return const_iterator(Vector); }
		const_iterator cend() const { return const_iterator(Vector + sizeValue); }

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

		reverse_iterator rbegin() { return reverse_iterator(Vector + sizeValue - 1); }
		reverse_iterator rend() { return reverse_iterator(Vector + 1); }

		void insert(iterator& it, T value);
		void erase(iterator& it);

	private:
		T* Vector;
		int sizeValue;
		int capacityValue;
		void resizeVector();
	};

	template<typename T>
	Vector<T>::Vector(const Vector& other) : capacityValue(other.capacityValue), sizeValue(other.sizeValue)
	{
		Vector = new T[capacityValue];
		for (int i = 0; i < sizeValue; i++) {
			Vector[i] = other.Vector[i];
		}
	}

	template<typename T>
	Vector<T>::Vector(Vector&& other) : capacityValue(other.capacityValue), sizeValue(other.sizeValue)
	{
		Vector = other.Vector;
		other.Vector = nullptr;
		other.sizeValue = 0;
		other.capacityValue = 0;
	}

	template<typename T>
	Vector<T>::Vector(std::initializer_list<T> initList) : capacityValue(initList.size() + 4), sizeValue(initList.size())
	{
		Vector = new T[capacityValue];
		int i = 0;
		for (const T& value : initList) {
			Vector[i++] = value;
		}
	}

	template<typename T>
	const Vector<T>& Vector<T>::operator=(const Vector<T>& other)
	{
		if (this != &other) {
			delete[] Vector;
			capacityValue = other.capacityValue;
			sizeValue = other.sizeValue;

			Vector = new T[capacityValue];
			for (int i = 0; i < sizeValue; i++) {
				Vector[i] = other.Vector[i];
			}
		}

		return *this;
	}

	template<typename T>
	const Vector<T>& Vector<T>::operator=(Vector<T>&& other) noexcept
	{
		if (this != &other) {
			delete[] Vector;
			sizeValue = other.sizeValue;
			capacityValue = other.capacityValue;
			Vector = other.Vector;
			other.Vector = nullptr;
			other.sizeValue = 0;
			other.capacityValue = 0;
		}

		return *this;
	}

	template<typename T>
	T& Vector<T>::operator[](const int index)
	{
		if (index >= 0 && index < sizeValue) {
			return Vector[index];
		}
		//throw std::out_of_range("Index out of range '[]'");
		std::cout << "Index out of range '[]'" << std::endl;
	}

	template<typename T>
	void Vector<T>::resizeVector()
	{
		capacityValue *= 1.5;
		T* newVector = new T[capacityValue];
		for (int i = 0; i < sizeValue; i++) {
			newVector[i] = Vector[i];
		}
		delete[] Vector;
		Vector = std::move(newVector);
	}

	template<typename T>
	void Vector<T>::resize(int quantity)
	{
		capacityValue = quantity;
		resizeVector();
		for (int i = sizeValue; i < quantity; i++) {
			Vector[i] = T();
		}
		sizeValue = quantity;
	}

	template<typename T>
	void Vector<T>::resize(int quantity, T value)
	{
		capacityValue = quantity;
		resizeVector();
		for (int i = sizeValue; i < quantity; i++) {
			Vector[i] = value;
		}
		sizeValue = quantity;
	}

	template<typename T>
	void Vector<T>::reserve(int quantity)
	{
		capacityValue = quantity;
		T* newVector = new T[capacityValue];
		for (int i = 0; i < sizeValue; i++) {
			newVector[i] = Vector[i];
		}
		delete[] Vector;
		Vector = std::move(newVector);
	}

	template<typename T>
	T& Vector<T>::at(int index)
	{
		if (index >= 0 && index < sizeValue) {
			return Vector[index];
		}
		std::cout << "Index out of range 'at()'" << std::endl;
	}

	template<typename T>
	void Vector<T>::push_back(T value)
	{
		if (sizeValue == capacityValue) {
			resizeVector();
		}
		Vector[sizeValue] = value;
		sizeValue++;
	}

	template<typename T>
	void Vector<T>::pop_back()
	{
		if (sizeValue <= 0) {
			std::cout << "Index out of range 'pop_back()'" << std::endl;
		}
		else {
			sizeValue--;
			Vector[sizeValue] = T();
		}
	}

	template<typename T>
	void Vector<T>::emplace_back()
	{
		if (sizeValue == capacityValue) {
			resizeVector();
		}
		Vector[sizeValue] = T();
		sizeValue++;
	}

	template<typename T>
	void Vector<T>::info()
	{
		std::cout << "{ ";
		for (int i = 0; i < sizeValue; i++) {
			if (i + 1 != sizeValue)
				std::cout << Vector[i] << ", ";
			else
				std::cout << Vector[i];
		}
		std::cout << " }" << std::endl;
	}

	template<typename T>
	void Vector<T>::clear()
	{
		delete[] Vector;
		capacityValue = 4;
		sizeValue = 0;
		Vector = new T[capacityValue];
	}

	template<typename T>
	void Vector<T>::insert(iterator& it, T value)
	{
		sizeValue++;
		int offsetIter = it.iter - Vector;
		if (capacityValue < sizeValue)
			resizeVector();
		for (int i = sizeValue; i > offsetIter; i--) {
			Vector[i] = Vector[i - 1];
		}
		Vector[offsetIter] = value;
	}

	template<typename T>
	void Vector<T>::erase(iterator& it)
	{
		sizeValue--;
		int offsetIter = it.iter - Vector;
		for (int i = offsetIter; i < sizeValue; i++) {
			Vector[i] = Vector[i + 1];
		}
	}
}