#pragma once
const int DEFAULT_CAPACITY = 16;

template <class T>
class CustomQueue {
private:
	int capacity;
	int size;
	int head;
	int tail;
	T* data;

	void raiseTail() {
		tail = (tail + 1) > capacity ? 0 : tail + 1;
	}

	void raiseHead() {
		head = (head + 1) > capacity ? 0 : head + 1;
	}

	void destroy() {
		if (data) {
			delete[] data;
		}
	}

public:
	CustomQueue(const int _capacity)
		: capacity(_capacity < 1 ? DEFAULT_CAPACITY : _capacity)
		, size(0)
		, head(0)
		, tail(0)
		, data(new T[capacity + 1])
	{

	}

	CustomQueue()
		: capacity(DEFAULT_CAPACITY)
		, size(0)
		, head(0)
		, tail(0)
		, data(new T[capacity + 1])
	{

	}

	CustomQueue(const CustomQueue& queue)
		: capacity(queue.capacity)
		, size(queue.size)
		, head(queue.head)
		, tail(queue.tail)
		, data(nullptr)
	{
		data = new T[capacity + 1];
		for (int i = 0; i < capacity + 1; ++i) {
			data[i] = queue.data[i];
		}
	}

	CustomQueue& operator =(const CustomQueue& queue)
	{
		if (&queue == this) {
			return *this;
		}

		capacity = queue.capacity;
		size = queue.size;
		head = queue.head;
		tail = queue.tail;

		delete[] data;

		data = new T[capacity + 1];
		for (int i = 0; i < capacity + 1; ++i) {
			data[i] = queue.data[i];
		}

		return *this;
	}

	CustomQueue& operator =(CustomQueue&& queue)
	{
		if (&queue == this) {
			return *this;
		}

		capacity = queue.capacity;
		size = queue.size;
		head = queue.head;
		tail = queue.tail;

		delete[] data;

		data = std::move(queue.data);

		queue.capacity = DEFAULT_CAPACITY;
		queue.size = 0;
		queue.head = 0;
		queue.tail = 0;
		queue.data = new T[queue.capacity + 1];

		return *this;
	}

	CustomQueue(CustomQueue&& queue)
		: capacity(queue.capacity)
		, size(queue.size)
		, head(queue.head)
		, tail(queue.tail)
		, data(std::move(queue.data))
	{
		queue.capacity = DEFAULT_CAPACITY;
		queue.size = 0;
		queue.head = 0;
		queue.tail = 0;
		queue.data = new T[queue.capacity + 1];
	}

	~CustomQueue() noexcept {
		destroy();
	}

	int getSize() const {
		return size;
	}

	int getCapacity() const {
		return capacity;
	}

	bool isEmpty() const {
		return size == 0;
	}

	bool isFull() const {
		return size == capacity;
	}

	bool push(const T item) {

		if (isFull()) {
			return false;
		}
		
		data[tail] = item;
		raiseTail();
		++size;

		return true;
	}

	T pop() {
		if (isEmpty()) {
			return NULL;
		}

		T result = data[head];
		raiseHead();
		--size;

		return result;
	}

	T peek() {
		if (isEmpty()) {
			return NULL;
		}

		return data[head];
	}

};