/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEFILTERMEDIAN5_h
#define _REACTIVEFILTERMEDIAN5_h

template <typename T>
class FilterMedian5 : public Operator<T, T>
{
public:
	FilterMedian5<T>();
	T AddValue(T value);
	T GetFiltered();

	void OnNext(T value) override;

private:
	const int _windowSize = 5;
	T _items[5];
	T* _accessor;
	int _count;

	void addToBuffer(T value);
	void incCounter();

	static T getMedian5(T a, T b, T c, T d, T e);
};

template <typename T>
FilterMedian5<T>::FilterMedian5()
{
	_accessor = _items;
	_count = 0;
}

template<typename T>
T FilterMedian5<T>::AddValue(const T value)
{
	addToBuffer(value);
	incCounter();

	return GetFiltered();
}

template<typename T>
T FilterMedian5<T>::GetFiltered()
{
	return getMedian5(_items[0], _items[1], _items[2], _items[3], _items[4]);
}

template<typename T>
void FilterMedian5<T>::addToBuffer(const T value)
{
	*_accessor = value;

	++_accessor;
	if (_accessor >= _items + _windowSize)
		_accessor = _items;

}

template<typename T>
void FilterMedian5<T>::incCounter()
{
	if (_count < _windowSize)
		++_count;
}

template <typename T>
T FilterMedian5<T>::getMedian5(T a, T b, T c, T d, T e)
{
	return b < a ? d < c ? b < d ? a < e ? a < d ? e < d ? e : d
		: c < a ? c : a
		: e < d ? a < d ? a : d
		: c < e ? c : e
		: c < e ? b < c ? a < c ? a : c
		: e < b ? e : b
		: b < e ? a < e ? a : e
		: c < b ? c : b
		: b < c ? a < e ? a < c ? e < c ? e : c
		: d < a ? d : a
		: e < c ? a < c ? a : c
		: d < e ? d : e
		: d < e ? b < d ? a < d ? a : d
		: e < b ? e : b
		: b < e ? a < e ? a : e
		: d < b ? d : b
		: d < c ? a < d ? b < e ? b < d ? e < d ? e : d
		: c < b ? c : b
		: e < d ? b < d ? b : d
		: c < e ? c : e
		: c < e ? a < c ? b < c ? b : c
		: e < a ? e : a
		: a < e ? b < e ? b : e
		: c < a ? c : a
		: a < c ? b < e ? b < c ? e < c ? e : c
		: d < b ? d : b
		: e < c ? b < c ? b : c
		: d < e ? d : e
		: d < e ? a < d ? b < d ? b : d
		: e < a ? e : a
		: a < e ? b < e ? b : e
		: d < a ? d : a;
}

template <typename T>
void FilterMedian5<T>::OnNext(T value)
{
	AddValue(value);

	if (_count < _windowSize) return;
	if (this->_childObserver != nullptr) this->_childObserver->OnNext(GetFiltered());
}
#endif