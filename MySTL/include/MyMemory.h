#ifndef MEMORY_H
#define MEMORY_H


namespace myStd
{
	// auto_ptr
	template<typename T>
	class MyAuto_ptr
	{
	public:
		MyAuto_ptr() : pointer(nullptr) {};
		MyAuto_ptr(T* pointer) : pointer(pointer) {};
		MyAuto_ptr(MyAuto_ptr& other) : pointer(other.pointer) {
			other.pointer = nullptr;
		};
		MyAuto_ptr(MyAuto_ptr&& other) noexcept : pointer(other.pointer) {
			other.pointer = nullptr;
		};
		~MyAuto_ptr() { delete pointer; };

		MyAuto_ptr<T>& operator=(MyAuto_ptr& other) {
			if (this != &other) {
				delete pointer;
				pointer = other.pointer;
				other.pointer = nullptr;
			}

			return *this;
		}
		T* operator->() {
			return pointer;
		}
		T& operator*() {
			return *pointer;
		}

		T* get() const {
			return pointer;
		}
		void reset() {
			delete pointer;
			pointer = nullptr;
		}
		void reset(T* ptr) {
			delete pointer;
			pointer = ptr;
		}
		T* release() {
			T* temp = pointer;
			pointer = nullptr;
			return temp;
		}

	private:
		T* pointer;
	};

	// unique_ptr
	template<typename T>
	class MyUnique_ptr
	{
	public:
		MyUnique_ptr() : pointer(nullptr) {};
		MyUnique_ptr(T* pointer) : pointer(pointer) {};
		MyUnique_ptr(MyUnique_ptr&& other) : pointer(other.pointer) {
			other.pointer = nullptr;
		};
		~MyUnique_ptr() { delete pointer; }

		MyUnique_ptr<T>& operator=(MyUnique_ptr<T>&& other) {
			if (this != &other) {
				delete pointer;
				pointer = other.pointer;
				other.pointer = nullptr;
			}

			return *this;
		}
		operator bool() {
			if (pointer != nullptr)
				return 1;
			return 0;
		}
		T* operator->() {
			return pointer;
		}
		T& operator*() {
			return *pointer;
		}

		T* get() const {
			return pointer;
		}
		void reset() {
			delete pointer;
			pointer = nullptr;
		}
		void reset(T* ptr) {
			delete pointer;
			pointer = ptr;
		}
		T* release() {
			T* temp = pointer;
			pointer = nullptr;
			return temp;
		}
		void swap(MyUnique_ptr<T>& other) {
			T* temp = pointer;
			pointer = other.pointer;
			other.pointer = temp;
		}

	private:
		T* pointer;
	};

	// shared_ptr
	template<typename T>
	class MyShared_ptr
	{
	public:
		MyShared_ptr() : pointer(nullptr), count(new int(1)) {};
		MyShared_ptr(T* pointer) : pointer(pointer), count(new int(1)) {};
		MyShared_ptr(const MyShared_ptr& other) noexcept : pointer(other.pointer), count(other.count) {
			(*count)++;
		};
		MyShared_ptr(MyShared_ptr&& other) : pointer(other.pointer), count(other.count) {
			other.pointer = nullptr;
			other.count = nullptr;
		};
		~MyShared_ptr() { cleanup(); }

		const MyShared_ptr<T>& operator=(MyShared_ptr<T>&& other) noexcept {
			if (this != &other) {
				cleanup();
				pointer = other.pointer;
				count = other.count;
				other.pointer = nullptr;
				other.count = nullptr;
			}

			return *this;
		}
		operator bool() {
			if (pointer != nullptr)
				return 1;
			return 0;
		}
		T* operator->() {
			return pointer;
		}
		T& operator*() {
			return *pointer;
		}

		T* get() const {
			return pointer;
		}
		void reset() {
			cleanup();
			pointer = nullptr;
			count = new int(1);
		}
		void reset(T* ptr) {
			cleanup();
			pointer = ptr;
			count = new int(1);
		}
		T* release() {
			T* temp = pointer;
			cleanup();
			return temp;
		}
		void swap(MyShared_ptr<T>& other) {
			T* tempPointer = pointer;
			T* tempCount = count;
			pointer = other.pointer;
			count = other.count;
			other.pointer = tempPointer;
			other.count = tempCount;
		}
		int use_count() {
			return *count;
		}
		bool unique() {
			if (*count == 1)
				return 1;
			return 0;
		}

	private:
		void cleanup() {
			if (count != nullptr && --(*count) == 0) {
				delete pointer;
				delete count;
			}
		}

		T* pointer;
		int* count;
	};
}

#endif