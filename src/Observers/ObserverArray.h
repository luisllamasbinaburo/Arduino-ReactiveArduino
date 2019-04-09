/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _OBSERVERTOARRAY_h
#define _OBSERVERTOARRAY_h

template <typename T>
class ObserverArray : public IObserver<T>
{
public:
	ObserverArray(T *array, size_t length);

	void OnNext(T value);
	void OnComplete();
	size_t GetIndex();

private:
	T *_array;
	size_t _length;
	size_t _index;
};

template <typename T>
inline ObserverArray<T>::ObserverArray(T *array, size_t length)
{
	this->_array = array;
	this->_length = length;
	this->_index = 0;
}

template <typename T>
inline void ObserverArray<T>::OnNext(T value)
{
	if (this->_index >= this->_length) return;

	this->_array[this->_index] = value;
	this->_index++;
}

template <typename T>
inline void ObserverArray<T>::OnComplete()
{
}

template<typename T>
inline size_t ObserverArray<T>::GetIndex()
{
	return this->_index;
}
#endif

