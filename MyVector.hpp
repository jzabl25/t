/**
 * MyVector - a basic vector made with a dynamic array.
 */

#include <cstddef>
#include <new>
#include <stdexcept>

namespace CPSC131::MyVector
{
	template <typename T>
	class MyVector
	{
		public:
			static constexpr size_t DEFAULT_CAPACITY = 64;
			static constexpr size_t MINIMUM_CAPACITY = 8;

			MyVector(size_t capacity = MyVector::DEFAULT_CAPACITY)
			{
				capacity_ = capacity;
				if (capacity_ < MINIMUM_CAPACITY) {
					capacity_ = MINIMUM_CAPACITY;
				}
				elements_ = new T[capacity_];
			}

			MyVector(const MyVector& other)
			{
				size_ = other.size_;
				capacity_ = other.capacity_;
				elements_ = new T[capacity_];
				for (size_t i = 0; i < size_; i++) {
					elements_[i] = other.elements_[i];
				}
			}

			~MyVector()
			{
				delete[] elements_;
				elements_ = nullptr;
				size_ = 0;
				capacity_ = 0;
			}

			MyVector& operator=(const MyVector& rhs)
			{
				if (this == &rhs) {
					return *this;
				}

				T* newElements = new T[rhs.capacity_];
				for (size_t i = 0; i < rhs.size_; i++) {
					newElements[i] = rhs.elements_[i];
				}

				delete[] elements_;
				elements_ = newElements;
				size_ = rhs.size_;
				capacity_ = rhs.capacity_;
				return *this;
			}

			T& operator[](size_t index) const
			{
				return at(index);
			}

			T* elements()
			{
				return elements_;
			}

			size_t size() const
			{
				return size_;
			}

			size_t capacity() const
			{
				return capacity_;
			}

			bool empty() const
			{
				return size_ == 0;
			}

			T& at(size_t index) const
			{
				if (index >= size_) {
					throw std::out_of_range("MyVector index out of range");
				}
				return elements_[index];
			}

			void reserve(size_t capacity)
			{
				if (capacity < size_) {
					throw std::invalid_argument("Cannot reserve less than MyVector size");
				}
				if (capacity <= capacity_) {
					return;
				}
				reallocate(capacity);
			}

			T& set(size_t index, const T& element)
			{
				if (index >= size_) {
					throw std::out_of_range("MyVector index out of range");
				}
				elements_[index].~T();
				new (elements_ + index) T(element);
				return elements_[index];
			}

			T& push_back(const T& element)
			{
				if (size_ == capacity_) {
					reallocate(capacity_ * 2);
				}
				elements_[size_] = element;
				size_++;
				return elements_[size_ - 1];
			}

			T pop_back()
			{
				if (empty()) {
					throw std::underflow_error("Cannot pop_back an empty MyVector");
				}

				T removed = elements_[size_ - 1];
				elements_[size_ - 1].~T();
				new (elements_ + size_ - 1) T();
				size_--;
				shrinkIfNeeded();
				return removed;
			}

			T& insert(size_t index, const T& element)
			{
				if (index > size_) {
					throw std::out_of_range("MyVector insert index out of range");
				}
				if (size_ == capacity_) {
					reallocate(capacity_ * 2);
				}

				for (size_t i = size_; i > index; i--) {
					elements_[i] = elements_[i - 1];
				}
				elements_[index] = element;
				size_++;
				return elements_[index];
			}

			T erase(size_t index)
			{
				if (index >= size_) {
					throw std::out_of_range("MyVector erase index out of range");
				}

				T removed = elements_[index];
				elements_[index].~T();
				new (elements_ + index) T();
				for (size_t i = index; i + 1 < size_; i++) {
					elements_[i] = elements_[i + 1];
				}
				elements_[size_ - 1] = T();
				size_--;
				shrinkIfNeeded();
				return removed;
			}

			void clear()
			{
				for (size_t i = 0; i < size_; i++) {
					elements_[i].~T();
					new (elements_ + i) T();
				}
				size_ = 0;

				if (capacity_ != DEFAULT_CAPACITY) {
					reallocate(DEFAULT_CAPACITY);
				}
			}

		private:
			size_t size_ = 0;
			size_t capacity_ = 0;
			T* elements_ = nullptr;

			void reallocate(size_t newCapacity)
			{
				if (newCapacity < MINIMUM_CAPACITY) {
					newCapacity = MINIMUM_CAPACITY;
				}
				T* newElements = new T[newCapacity];
				for (size_t i = 0; i < size_; i++) {
					newElements[i] = elements_[i];
				}
				delete[] elements_;
				elements_ = newElements;
				capacity_ = newCapacity;
			}

			void shrinkIfNeeded()
			{
				if (size_ == 0) {
					if (capacity_ != MINIMUM_CAPACITY) {
						reallocate(MINIMUM_CAPACITY);
					}
					return;
				}

				if (capacity_ > MINIMUM_CAPACITY && size_ < capacity_ / 3) {
					size_t newCapacity = capacity_ / 2;
					if (newCapacity < MINIMUM_CAPACITY) {
						newCapacity = MINIMUM_CAPACITY;
					}
					reallocate(newCapacity);
				}
			}
	};
}
