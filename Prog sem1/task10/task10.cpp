#include <iostream>
#include <exception>
#include <algorithm>

class MyException : public std::exception
{
	using base_t = std::exception;
public:
	MyException()
		: base_t("MyException")
	{}
};

template <class T>
class Deque
{
	T* m_data = nullptr;		// динамический массив
	size_t m_capacity = 0;		// размер массива
	size_t m_size = 0;			// размер контейнера
	size_t m_increment = 1024;	// количество приращения

public:
	Deque()
	{
	}

	Deque(const Deque<T>& rhs)
	{
		this->operator=(rhs);
	}

	virtual ~Deque()
	{
		if (m_data)
			delete[] m_data;
	}

	Deque<T>& operator=(const Deque& rhs)
	{
		size_t newSize = rhs.size();
		if (alloc(newSize))
		{
			copy(m_data, rhs.m_data, newSize);
			m_size = newSize;
		}
		return *this;
	}

	void clear()
	{
		m_size = 0;
	}

	void push_front(const T& v)
	{
		if (alloc(m_size + 1)) {
			for (size_t i = m_size; i > 0; --i) {
				m_data[i] = m_data[i - 1];
			}

			m_data[0] = v;
			m_size++;
		}
	}

	void push_back(const T& v)
	{
		if (alloc(m_size + 1)) {
			m_data[m_size++] = v;
		}
	}

	void pop_front()
	{
		if (!m_size)
			return;
		m_size--;
		copy(m_data, &m_data[1], m_size);
	}

	void pop_back()
	{
		if (m_size)
			m_size--;
	}

	size_t size() const
	{
		return m_size;
	}

	bool empty() const
	{
		return (m_size == 0);
	}

	T operator[](size_t i) const
	{
		if (i >= m_size)
			throw std::exception("index error.");
		return m_data[i];
	}

private:
	bool alloc(size_t newSize)
	{
		if (newSize > m_capacity) {
			m_capacity = newSize + m_increment;
			T* temp = new T[m_capacity];

			if (!temp)
				throw std::exception("allocate error.");

			copy(temp, m_data, m_size);
			std::swap(temp, m_data);
			if (temp)
				delete[] temp;
		}

		return m_capacity >= newSize;
	}

	static T* copy(T* dest, const T* src, size_t count)
	{
		if (count)
			memcpy(dest, src, sizeof(T) * count);
		return dest;
	}
};

int main()
{
	Deque<int> deq1;

	for (int v = 0; v < 100; ++v) {
		deq1.push_back(v);
	}

	Deque<int> deq2(deq1);

	for (size_t i = 0; i < 50; ++i) {
		deq2.pop_front();
	}

	Deque<int> deq3 = deq2;

	deq3.pop_back();

	std::cout << "deq1: ";

	for (size_t i = 0; i < deq1.size(); ++i)
	{
		std::cout << deq1[i] << " ";
	}

	std::cout << "\ndeq2: ";

	for (size_t i = 0; i < deq2.size(); ++i)
	{
		std::cout << deq2[i] << " ";
	}

	std::cout << "\ndeq3: ";

	for (size_t i = 0; i < deq3.size(); ++i)
	{
		std::cout << deq3[i] << " ";
	}

	std::cout << "\n\nsize1: " << deq1.size() << "\n";
	std::cout << "size2: " << deq2.size() << "\n";
	std::cout << "size3: " << deq3.size() << "\n";
}
