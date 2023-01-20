/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEOBSERVABLEARRAYDEFER_h
#define _REACTIVEOBSERVABLEARRAYDEFER_h

template <typename T>
class ObservableArrayDefer : public Observable<T>
{
public:
	ObservableArrayDefer(T *array, size_t length);
	void Subscribe(IObserver<T> &observer) override;
	void UnSubscribe(IObserver<T> &observer) override;
	void Next();
	void Reset() override;

private:
	T *_array;
	size_t _index;
	size_t _length;

	ObserverList<T> _childObservers;
};

template <typename T>
ObservableArrayDefer<T>::ObservableArrayDefer(T *array, size_t length)
{
	this->_index = 0;
	this->_array = array;
	this->_length = length;
}

template <typename T>
void ObservableArrayDefer<T>::Subscribe(IObserver<T> &observer)
{
	this->_childObservers.Add(&observer);
}

template <typename T>
void ObservableArrayDefer<T>::UnSubscribe(IObserver<T> &observer)
{
	this->_childObservers.Remove(&observer);
}

template <typename T>
void ObservableArrayDefer<T>::Next()
{
	if (_index >= this->_length) return;

	T value = _array[_index];
	this->_childObservers.Each([value](IObserver<T>* o) { o->OnNext(value); });
	_index++;

	if(_index >= this->_length)
		this->_childObservers.Each([](IObserver<T>* o) { o->OnComplete(); });
}

template <typename T>
void ObservableArrayDefer<T>::Reset()
{
	_index = 0;
}

#endif