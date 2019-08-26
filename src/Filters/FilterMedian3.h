/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEFILTERMEDIAN3_h
#define _REACTIVEFILTERMEDIAN3_h

template <typename T>
class FilterMedian3 : public Operator<T, T>
{
public:
	FilterMedian3<T>();
	T AddValue(T value);
	T GetFiltered();

	void OnNext(T value) override;

private:
	const int _windowSize = 3;
	T _items[3];
	T* _accessor;
	int _count;

	void addToBuffer(T value);
	void incCounter();

	static T getMedian3(T a, T b, T c);
};

template <typename T>
FilterMedian3<T>::FilterMedian3()
{
	_accessor = _items;
	_count = 0;
}

template<typename T>
T FilterMedian3<T>::AddValue(const T value)
{
	addToBuffer(value);
	incCounter();

	return GetFiltered();
}

template<typename T>
T FilterMedian3<T>::GetFiltered()
{
	return getMedian3(_items[0], _items[1], _items[2]);
}

template<typename T>
void FilterMedian3<T>::addToBuffer(const T value)
{
	*_accessor = value;

	++_accessor;
	if (_accessor >= _items + _windowSize)
		_accessor = _items;

}

template<typename T>
void FilterMedian3<T>::incCounter()
{
	if (_count < _windowSize)
		++_count;
}

template <typename T>
T FilterMedian3<T>::getMedian3(T a, T b, T c)
{
	if ((a <= b) && (a <= c))
		return (b <= c) ? b : c;
	if ((b <= a) && (b <= c))
		return (a <= c) ? a : c;
	return (a <= b) ? a : b;
}

template <typename T>
void FilterMedian3<T>::OnNext(T value)
{
	AddValue(value);

	if (_count < _windowSize) return;
	if (this->_childObserver != nullptr) this->_childObserver->OnNext(GetFiltered());
}
#endif