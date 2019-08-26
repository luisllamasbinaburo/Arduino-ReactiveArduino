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
	void Suscribe(IObserver<T> &observer) override;
	void Next();
	void Reset() override;

private:
	T *_array;
	size_t _index;
	size_t _length;

	IObserver<T>* _childObserver;
};

template <typename T>
ObservableArrayDefer<T>::ObservableArrayDefer(T *array, size_t length)
{
	this->_index = 0;
	this->_array = array;
	this->_length = length;
}

template <typename T>
void ObservableArrayDefer<T>::Suscribe(IObserver<T> &observer)
{
	_childObserver = &observer;
}

template <typename T>
void ObservableArrayDefer<T>::Next()
{
	if (_index >= this->_length) return;

	if (_childObserver != nullptr) _childObserver->OnNext(_array[_index]);
	_index++;

	if(_index >= this->_length)
		if(_childObserver != nullptr) _childObserver->OnComplete();
}

template <typename T>
void ObservableArrayDefer<T>::Reset()
{
	_index = 0;
}

#endif