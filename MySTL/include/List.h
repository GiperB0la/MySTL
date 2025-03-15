#pragma
#include <initializer_list>


namespace myStd
{
	template<typename T>
	class List
	{
	public:
		List() : sizeValue(0), head(nullptr), tail(nullptr) {};
		List(std::initializer_list<T> initList);
		List(const List& other);
		~List() { clear(); };

		T& at(const int index);
		void push_back(T value);
		void push_front(T value);
		void pop_back();
		void pop_front();
		void info();
		void clear();
		void reverse();
		void insert(const int index, T value);
		void erase(const int index);
		void remove(T value);
		void assign(int size);
		void assign(int size, T value);
		int size() { return sizeValue; };

		T& operator[](const int index);
		const List<T>& operator=(const List<T>& other);
		const List<T>& operator=(List<T>&& other);

	private:
		template<typename T>
		class Node
		{
		public:
			Node(T data = T(), Node* pNext = nullptr, Node* pLast = nullptr) : data(data), pNext(pNext), pLast(pLast) {};
			~Node() {};

			Node* pNext;
			Node* pLast;
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
			~iterator() {};

			T& operator*() {
				return iter->data;
			}

			iterator& operator++(int) {
				iter = iter->pNext;
				return *this;
			}

			iterator& operator++() {
				iter = iter->pNext;
				return *this;
			}

			iterator& operator--(T) {
				iter = iter->pLast;
				return *this;
			}

			iterator& operator--() {
				iter = iter->pLast;
				return *this;
			}

			iterator& operator+=(T value) {
				for (int i = 0; i < value; i++) {
					iter = iter->pNext;
				}
				return *this;
			}

			iterator& operator-=(T value) {
				for (int i = 0; i < value; i++) {
					iter = iter->pLast;
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

			iterator& operator-(T value) {
				iterator temp = *this;
				for (int i = 0; i < value; i++) {
					temp = temp.iter->pLast;
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

			const_iterator& operator--(T) {
				citer = citer->pLast;
				return *this;
			}

			const_iterator& operator--() {
				citer = citer->pLast;
				return *this;
			}

			const_iterator& operator+=(T value) {
				for (int i = 0; i < value; i++) {
					citer = citer->pNext;
				}
				return *this;
			}

			const_iterator& operator-=(T value) {
				for (int i = 0; i < value; i++) {
					citer = citer->pLast;
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

			const_iterator& operator-(T value) {
				const_iterator temp = *this;
				for (int i = 0; i < value; i++) {
					temp = temp.citer->pLast;
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

			reverse_iterator& operator--(T) {
				riter = riter->pNext;
				return *this;
			}

			reverse_iterator& operator--() {
				riter = riter->pNext;
				return *this;
			}

			reverse_iterator& operator+=(T value) {
				for (int i = 0; i < value; i++) {
					riter = riter->pLast;
				}
				return *this;
			}

			reverse_iterator& operator-=(T value) {
				for (int i = 0; i < value; i++) {
					riter = riter->pNext;
				}
				return *this;
			}

			reverse_iterator& operator+(T value) {
				reverse_iterator temp = *this;
				for (int i = 0; i < value; i++) {
					temp = temp.riter->pLast;
				}
				return temp;
			}

			reverse_iterator& operator-(T value) {
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
	List<T>::List(std::initializer_list<T> initList) : sizeValue(initList.size())
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
				next->pLast = current;
				current = next;
			}
			else {
				current->pNext = nullptr;
				tail = current;
			}
		}
	}

	template<typename T>
	List<T>::List(const List& other) : sizeValue(other.sizeValue)
	{
		head = new Node<T>;
		Node<T>* next = nullptr;
		Node<T>* current = head;
		Node<T>* currentOther = other.head;
		while (currentOther->pNext != nullptr) {
			current->data = currentOther->data;
			next = new Node<T>;
			current->pNext = next;
			next->pLast = current;
			current = next;
			currentOther = currentOther->pNext;
		}
		current->data = currentOther->data;
	}

	template<typename T>
	T& List<T>::operator[](const int index)
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
			std::cout << "Index out of range '[]'" << std::endl;
		}
	}

	template<typename T>
	const List<T>& List<T>::operator=(const List<T>& other)
	{
		if (this != &other) {
			clear();
			sizeValue = other.sizeValue;

			head = new Node<T>;
			Node<T>* next = nullptr;
			Node<T>* current = head;
			Node<T>* currentOther = other.head;
			while (currentOther->pNext != nullptr) {
				current->data = currentOther->data;
				next = new Node<T>;
				current->pNext = next;
				next->pLast = current;
				current = next;
				currentOther = currentOther->pNext;
			}
			current->data = currentOther->data;
		}

		return *this;
	}

	template<typename T>
	const List<T>& List<T>::operator=(List<T>&& other)
	{
		if (this != &other) {
			clear();
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
	T& List<T>::at(const int index)
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
	void List<T>::push_back(T value)
	{
		if (head == nullptr) {
			head = new Node<T>(value);
			tail = head;
		}
		else {
			Node<T>* newN = new Node<T>(value);
			newN->pLast = tail;
			tail->pNext = newN;
			tail = newN;
		}
		sizeValue++;
	}

	template<typename T>
	void List<T>::push_front(T value)
	{
		if (head == nullptr) {
			head = new Node<T>(value);
		}
		else {
			Node<T>* current = head;
			Node<T>* newHead = new Node<T>(value, current);
			current->pLast = newHead;
			head = newHead;
		}
		sizeValue++;
	}

	template<typename T>
	void List<T>::pop_back()
	{
		if (head != nullptr) {
			if (sizeValue == 1) {
				clear();
				return;
			}
			Node<T>* n = tail->pLast;
			n->pNext = nullptr;
			delete tail;
			tail = n;
			sizeValue--;
		}
	}

	template<typename T>
	void List<T>::pop_front()
	{
		if (head != nullptr) {
			if (sizeValue == 1) {
				clear();
				return;
			}
			Node<T>* n = head->pNext;
			delete head;
			head = n;
			head->pLast = nullptr;
			sizeValue--;
		}
	}

	template<typename T>
	void List<T>::info()
	{
		if (head == nullptr) return;

		Node<T>* current = head;
		std::cout << "{ ";
		while (current->pNext != nullptr) {
			std::cout << current->data << ", ";
			current = current->pNext;
		}
		if (sizeValue != 0)
			std::cout << current->data;
		std::cout << " }" << std::endl;
	}

	template<typename T>
	void List<T>::clear()
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
	void List<T>::reverse()
	{
		if (head == nullptr) return;

		T* lst = new T[sizeValue];
		Node<T>* current = head;
		int i = 0;
		while (current != tail) {
			lst[i] = current->data;
			current = current->pNext;
			i++;
		}
		lst[i] = current->data;

		current = head;
		i = sizeValue - 1;
		while (current != tail) {
			current->data = lst[i];
			current = current->pNext;
			i--;
		}
		current->data = lst[i];

		delete[] lst;
	}

	template<typename T>
	void List<T>::insert(const int index, T value)
	{
		if (index < 0 || index >= sizeValue) { std::cout << "Index out of range 'insert()'" << std::endl; return; }

		if (index == 0) {
			push_front(value);
		}

		else if (index == sizeValue - 1) {
			push_back(value);
		}

		else {
			int i = 0;
			Node<T>* current = head;
			Node<T>* temp = nullptr;
			while (current->pNext != nullptr) {
				if (i == index) {
					temp = new Node<T>(value);
					temp->pNext = current;
					temp->pLast = current->pLast;
					current->pLast->pNext = temp;
					current->pLast = temp;
					break;
				}
				current = current->pNext;
				i++;
			}
			sizeValue++;
		}
	}

	template<typename T>
	void List<T>::erase(const int index)
	{
		if (index < 0 || index >= sizeValue) { std::cout << "Index out of range 'erase()'" << std::endl; return; }

		if (index == 0) {
			pop_front();
		}

		else if (index == sizeValue - 1) {
			pop_back();
		}

		else {
			int i = 0;
			Node<T>* current = head;
			Node<T>* temp = nullptr;
			while (current->pNext != nullptr) {
				if (i == index) {
					current->pNext->pLast = current->pLast;
					current->pLast->pNext = current->pNext;
					delete current;
					break;
				}
				current = current->pNext;
				i++;
			}
			sizeValue--;
		}
	}

	template<typename T>
	void List<T>::remove(T value)
	{
		Node<T>* current = head;
		Node<T>* temp = nullptr;
		while (true) {
			if (current->data == value) {
				if (current == head) {
					if (sizeValue == 1) {
						pop_front();
						return;
					}
					current = current->pNext;
					pop_front();
				}
				else if (current == tail) {
					pop_back();
					break;
				}
				else {
					current->pNext->pLast = current->pLast;
					current->pLast->pNext = current->pNext;
					temp = current;
					current = current->pNext;
					delete temp;
				}
			}
			else {
				if (current == tail)
					break;
				current = current->pNext;
			}
		}
	}

	template<typename T>
	void List<T>::assign(int size)
	{
		clear();
		sizeValue = size;
		head = new Node<T>;
		Node<T>* current = head;
		Node<T>* next = nullptr;
		int count = 0;
		while (count != sizeValue) {
			count++;
			current->data = T();
			if (count != sizeValue) {
				next = new Node<T>;
				current->pNext = next;
				next->pLast = current;
				current = next;
			}
			else {
				current->pNext = nullptr;
				tail = current;
			}
		}
	}

	template<typename T>
	void List<T>::assign(int size, T value)
	{
		clear();
		sizeValue = size;
		head = new Node<T>;
		Node<T>* current = head;
		Node<T>* next = nullptr;
		int count = 0;
		while (count != sizeValue) {
			count++;
			current->data = value;
			if (count != sizeValue) {
				next = new Node<T>;
				current->pNext = next;
				next->pLast = current;
				current = next;
			}
			else {
				current->pNext = nullptr;
				tail = current;
			}
		}
	}
}