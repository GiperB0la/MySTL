#pragma


namespace myStd
{
	// auto_ptr
	template<typename T>
	class Auto_ptr
	{
	public:
		Auto_ptr() : pointer(nullptr) {};
		Auto_ptr(T* pointer) : pointer(pointer) {};
		Auto_ptr(Auto_ptr& other) : pointer(other.pointer) {
			other.pointer = nullptr;
		};
		Auto_ptr(Auto_ptr&& other) noexcept : pointer(other.pointer) {
			other.pointer = nullptr;
		};
		~Auto_ptr() { delete pointer; };

		Auto_ptr<T>& operator=(Auto_ptr& other) {
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
	class Unique_ptr
	{
	public:
		Unique_ptr() : pointer(nullptr) {};
		Unique_ptr(T* pointer) : pointer(pointer) {};
		Unique_ptr(Unique_ptr&& other) : pointer(other.pointer) {
			other.pointer = nullptr;
		};
		~Unique_ptr() { delete pointer; }

		Unique_ptr<T>& operator=(Unique_ptr<T>&& other) {
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
		void swap(Unique_ptr<T>& other) {
			T* temp = pointer;
			pointer = other.pointer;
			other.pointer = temp;
		}

	private:
		T* pointer;
	};

	// shared_ptr
	template<typename T>
	class Shared_ptr
	{
	public:
		Shared_ptr() : pointer(nullptr), count(new int(1)) {};
		Shared_ptr(T* pointer) : pointer(pointer), count(new int(1)) {};
		Shared_ptr(const Shared_ptr& other) noexcept : pointer(other.pointer), count(other.count) {
			(*count)++;
		};
		Shared_ptr(Shared_ptr&& other) : pointer(other.pointer), count(other.count) {
			other.pointer = nullptr;
			other.count = nullptr;
		};
		~Shared_ptr() { cleanup(); }

		const Shared_ptr<T>& operator=(Shared_ptr<T>&& other) noexcept {
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
		void swap(Shared_ptr<T>& other) {
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