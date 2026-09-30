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
	_array = array;
	_length = length;
	_index = 0;
}

template <typename T>
void ObserverCircularBuffer<T>::OnNext(T value)
{
	_array[_index] = value;

	_index++;
	if (_index >= _length) _index = 0;
}

template <typename T>
void ObserverCircularBuffer<T>::OnComplete()
{
}
template<typename T>
size_t ObserverCircularBuffer<T>::GetIndex()
{
	return _index;
}

#endif