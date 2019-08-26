/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEFILTERSMRMS_h
#define _REACTIVEFILTERSMRMS_h

template <typename T>
class FilterMovingRMS : public Operator<T, T>
{
public:
	FilterMovingRMS<T>(size_t windowSize);
	void AddValue(T value);
	T GetFiltered();

	void OnNext(T value) override;

private:
	T* _items;
	T* _accessor;
	int _windowSize;
	int _count;
	T _sum = T();

	void addToBuffer(T value);
	void incCounter();
};

template <typename T>
FilterMovingRMS<T>::FilterMovingRMS(const size_t windowSize)
{
	_items = new T[windowSize];
	_accessor = _items;
	_windowSize = windowSize;
	_count = 0;
}

template<typename T>
void FilterMovingRMS<T>::AddValue(const T value)
{
	addToBuffer(value);
	incCounter();
}

template<typename T>
T FilterMovingRMS<T>::GetFiltered()
{
	_sum = 0;
	for (size_t index = 0; index < _count; index++)
	{
		_sum += _items[index] * _items[index];
	}
	return (sqrt(_sum / _count));
}

template<typename T>
void FilterMovingRMS<T>::addToBuffer(const T value)
{
	*_accessor = value;

	++_accessor;
	if (_accessor >= _items + _windowSize)
		_accessor = _items;

}

template<typename T>
void FilterMovingRMS<T>::incCounter()
{
	if (_count < _windowSize)
		++_count;
}

template <typename T>
void FilterMovingRMS<T>::OnNext(T value)
{
	AddValue(value);
	if (this->_childObserver != nullptr) this->_childObserver->OnNext(GetFiltered());
}

#endif