#pragma
#include <initializer_list>


namespace myStd
{
	template<typename T>
	class Forward_list
	{
	public:
		Forward_list() : sizeValue(0), head(nullptr), tail(nullptr) {};
		Forward_list(std::initializer_list<T> initList);
		Forward_list(const Forward_list& other);
		~Forward_list() { clear(); };

		T& at(int index);
		void push_back(T value);
		void push_front(T value);
		void pop_back();
		void pop_front();
		void info();
		void clear();
		void insert(const int index, T value);
		void erase(int index);
		int size() { return sizeValue; };

		T& operator[](const int index);
		const Forward_list<T>& operator=(const Forward_list<T>& other);
		const Forward_list<T>& operator=(Forward_list<T>&& other);

	private:
		template<typename T>
		class Node
		{
		public:
			Node(T data = T(), Node* pNext = nullptr) : data(data), pNext(pNext) {};
			~Node() {};

			Node* pNext;
			T data;
		};

		int sizeValue;
		Node<T>* head;
		Node<T>* tail;

	public:
		class iterator
		{
		public:
			iterator() : iter(nullptr) {};
			iterator(Node<T>* ptr) : iter(ptr) {};
			~iterator() {}

			T& operator*() {
				return iter->data;
			}

			iterator& operator++() {
				iter = iter->pNext;
				return *this;
			}

			iterator& operator++(int) {
				iter = iter->pNext;
				return *this;
			}

			iterator& operator+=(T value) {
				for (int i = 0; i < value; i++) {
					iter = iter->pNext;
				}
				return *this;
			}

			iterator& operator+(T value) {
				iterator temp = *this;
				for (int i = 0; i < value; i++) {
					temp = temp.iter->pNext;
				}
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
			Node<T>* iter;
		};

		class const_iterator
		{
		public:
			const_iterator() : citer(nullptr) {};
			const_iterator(Node<T>* ptr) : citer(ptr) {};
			~const_iterator() {};

			const T& operator*() {
				return citer->data;
			}

			const_iterator& operator++(int) {
				citer = citer->pNext;
				return *this;
			}

			const_iterator& operator++() {
				citer = citer->pNext;
				return *this;
			}

			const_iterator& operator+=(T value) {
				for (int i = 0; i < value; i++) {
					citer = citer->pNext;
				}
				return *this;
			}

			const_iterator& operator+(T value) {
				const_iterator temp = *this;
				for (int i = 0; i < value; i++) {
					temp = temp.citer->pNext;
				}
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
			Node<T>* citer;
		};

		class reverse_iterator
		{
		public:
			reverse_iterator() : riter(nullptr) {};
			reverse_iterator(Node<T>* ptr) : riter(ptr) {};
			~reverse_iterator() {};

			T& operator*() {
				return riter->data;
			}

			reverse_iterator& operator++(int) {
				riter = riter->pLast;
				return *this;
			}

			reverse_iterator& operator++() {
				riter = riter->pLast;
				return *this;
			}

			reverse_iterator& operator+=(T value) {
				for (int i = 0; i < value; i++) {
					riter = riter->pNext;
				}
				return *this;
			}

			reverse_iterator& operator+(T value) {
				reverse_iterator temp = *this;
				for (int i = 0; i < value; i++) {
					temp = temp.riter->pNext;
				}
				return temp;
			}

			bool operator==(const reverse_iterator& other) const {
				if (riter == other.riter)
					return true;
				return false;
			}

			bool operator!=(const reverse_iterator& other) const {
				if (riter != other.riter)
					return true;
				return false;
			}

		private:
			Node<T>* riter;
		};

		iterator begin() { return head; };
		iterator end() { return tail; };
		const iterator cbegin() const { return head; };
		const iterator cend() const { return tail; };
		iterator rbegin() { return tail; };
		iterator rend() { return head; };
	};

	template<typename T>
	Forward_list<T>::Forward_list(std::initializer_list<T> initList) : sizeValue(initList.size())
	{
		head = new Node<T>;
		Node<T>* current = head;
		Node<T>* next = nullptr;
		int count = 0;
		for (const T& value : initList) {
			count++;
			current->data = value;
			if (count != initList.size()) {
				next = new Node<T>;
				current->pNext = next;
				current = next;
			}
			else {
				current->pNext = nullptr;
				tail = current;
			}
		}
	}

	template<typename T>
	Forward_list<T>::Forward_list(const Forward_list& other) : sizeValue(other.sizeValue)
	{
		head = new Node<T>;
		Node<T>* current = head;
		Node<T>* last = nullptr;
		Node<T>* otherCurrent = other.head;
		for (int i = 0; i < sizeValue; i++)
		{
			current->data = otherCurrent->data;
			otherCurrent = otherCurrent->pNext;
			last = current;
			current = current->pNext;
			if (i != sizeValue - 1) {
				current = new Node<T>;
				last->pNext = current;
				tail = current;
			}
		}
	}

	template<typename T>
	T& Forward_list<T>::operator[](const int index)
	{
		if(index >= 0 && index < sizeValue) {
			int n = 0;
			Node<T>* current = head;
			while (n != index) {
				n++;
				current = current->pNext;
			}
			return current->data;
		}
		else {
			std::cout << "Index out of range '[]'" << std::endl;
		}
	}

	template<typename T>
	const Forward_list<T>& Forward_list<T>::operator=(const Forward_list<T>& other)
	{
		if (this != &other) {
			sizeValue = other.sizeValue;
			head = new Node<T>;
			Node<T>* current = head;
			Node<T>* last = nullptr;
			Node<T>* otherCurrent = other.head;
			for (int i = 0; i < sizeValue; i++)
			{
				current->data = otherCurrent->data;
				otherCurrent = otherCurrent->pNext;
				last = current;
				current = current->pNext;
				if (i != sizeValue - 1) {
					current = new Node<T>;
					last->pNext = current;
				}
			}
		}

		return *this;
	}

	template<typename T>
	const Forward_list<T>& Forward_list<T>::operator=(Forward_list<T>&& other)
	{
		if (this != &other) {
			sizeValue = other.sizeValue;
			head = other.head;
			tail = other.tail;
			other.sizeValue = 0;
			other.head = nullptr;
			other.tail = nullptr;
		}
		return *this;
	}

	template<typename T>
	T& Forward_list<T>::at(int index)
	{
		if (index >= 0 && index < sizeValue) {
			int n = 0;
			Node<T>* current = head;
			while (n != index) {
				n++;
				current = current->pNext;
			}
			return current->data;
		}
		else {
			std::cout << "Index out of range 'at()'" << std::endl;
		}
	}

	template<typename T>
	void Forward_list<T>::push_back(T value)
	{
		if (head == nullptr) {
			head = new Node<T>(value);
			tail = head;
		}
		else {
			Node<T>* newN = new Node<T>(value);
			tail->pNext = newN;
			tail = newN;
		}
		sizeValue++;
	}

	template<typename T>
	void Forward_list<T>::push_front(T value)
	{
		if (head == nullptr) {
			head = new Node<T>(value);
		}
		else {
			Node<T>* current = head;
			Node<T>* newHead = new Node<T>(value, current);
			head = newHead;
		}
		sizeValue++;
	}

	template<typename T>
	void Forward_list<T>::pop_back()
	{
		Node<T>* current = head;
		Node<T>* temp = current;
		while (current != tail) {
			temp = current;
			current = current->pNext;
		}
		temp->pNext = nullptr;
		delete current;
		sizeValue--;
		tail = temp;
		if (sizeValue == 0)
			head->pNext = nullptr;
	}

	template<typename T>
	void Forward_list<T>::pop_front()
	{
		Node<T>* temp = head;
		head = head->pNext;
		delete temp;
		sizeValue--;
		if (sizeValue == 0)
			head->pNext = nullptr;
	}

	template<typename T>
	void Forward_list<T>::info()
	{
		if (head == nullptr) return;

		Node<T>* current = head;
		std::cout << "{ ";
		while (current != tail) {
			std::cout << current->data << ", ";
			current = current->pNext;
		}
		if (sizeValue != 0)
			std::cout << current->data;
		std::cout << " }" << std::endl;
	}

	template<typename T>
	void Forward_list<T>::clear()
	{
		sizeValue = 0;
		Node<T>* current = head;
		Node<T>* temp = current;
		while (current != tail) {
			temp = current;
			current = current->pNext;
			delete temp;
		}
		delete tail;
		head = tail = nullptr;
	}

	template<typename T>
	void Forward_list<T>::insert(const int index, T value)
	{
		if (index < 0 || index >= sizeValue) { std::cout << "Index out of range 'insert()'" << std::endl; return; }

		if (index == 0) {
			push_front(value);
		}

		else if (index == sizeValue - 1) {
			push_back(value);
		}

		else {
			Node<T>* temp = nullptr;
			Node<T>* last = nullptr;
			Node<T>* current = head;
			for (int i = 0; i < sizeValue; i++) {
				if (i == index) {
					temp = current;
					current = new Node<T>;
					current->data = value;
					current->pNext = temp;
					last->pNext = current;
					sizeValue++;
					break;
				}
				last = current;
				current = current->pNext;
			}
		}
	}

	template<typename T>
	void Forward_list<T>::erase(int index)
	{
		if (head == nullptr) return;

		if (index >= 0 && index < sizeValue) {
			if (index == 0) {
				pop_front();
			}
			else if (index == sizeValue - 1) {
				pop_back();
			}
			else {
				Node<T>* temp = nullptr;
				Node<T>* last = nullptr;
				Node<T>* current = head;
				for (int i = 0; i < sizeValue; i++) {
					if (i == index) {
						last->pNext = current->pNext;
						delete current;
						break;
					}
					last = current;
					current = current->pNext;
				}
			}
		}
		else {
			std::cout << "Index out of range 'insert()'" << std::endl;
		}
	}
}