/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEOBSERVABLEARRAY_h
#define _REACTIVEOBSERVABLEARRAY_h

template <typename T>
class ObservableArray : public Observable<T>
{
public:
	ObservableArray(T *array, size_t length);
	void Subscribe(IObserver<T> &observer) override;
	void UnSubscribe(IObserver<T> &observer) override;
	
	void Run();
	void Reset() override;

private:
	T *_array;
	size_t _length;
	ObserverList<T> _childObservers;
};

template <typename T>
ObservableArray<T>::ObservableArray(T *array, size_t length)
{
	this->_array = array;
	this->_length = length;
}

template <typename T>
void ObservableArray<T>::Subscribe(IObserver<T> &observer)
{
	this->_childObservers.Add(&observer);
	Run();
}

template <typename T>
void ObservableArray<T>::UnSubscribe(IObserver<T> &observer)
{
	this->_childObservers.Remove(&observer);
}

template<typename T>
void ObservableArray<T>::Run()
{
	if (this->_childObserver == nullptr) return;
	for (size_t i = 0; i < this->_length; i++)
		this->_childObservers.Fire(_array[i]);

	this->_childObservers.Complete();
}

template<typename T>
void ObservableArray<T>::Reset()
{
	Run();
}

#endif