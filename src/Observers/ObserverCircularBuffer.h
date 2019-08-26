#ifndef _REACTIVEOBSERVERCIRCULARBUFFER_h
#define _REACTIVEOBSERVERCIRCULARBUFFER_h

template <typename T>
class ObserverCircularBuffer : public IObserver<T>
{
public:
	ObserverCircularBuffer(T *array, size_t length);

	void OnNext(T value) override;
	void OnComplete() override;
	size_t GetIndex();

private:
	T *_array;
	size_t _length;
	size_t _index;
};

template <typename T>
ObserverCircularBuffer<T>::ObserverCircularBuffer(T *array, size_t length)
{
	this->_array = array;
	this->_length = length;
	this->_index = 0;
}

template <typename T>
void ObserverCircularBuffer<T>::OnNext(T value)
{
	this->_array[this->_index] = value;

	this->_index++;
	if (this->_index >= this->_length) this->_index = 0;
}

template <typename T>
void ObserverCircularBuffer<T>::OnComplete()
{
}
template<typename T>
size_t ObserverCircularBuffer<T>::GetIndex()
{
	return this->_index;
}

#endif