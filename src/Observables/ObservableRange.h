/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEOBSERVABLERANGE_h
#define _REACTIVEOBSERVABLERANGE_h

template <typename T> class Observable;

template <typename T>
class ObservableRange : public Observable<T>
{
public:
	ObservableRange(T start, T end, T step = 1);
	void Suscribe(IObserver<T> &observer) override;
	void Run();
	void Reset() override;

private:
	T _start;
	T _end;
	T _step;

	IObserver<T>* _childObserver;
};

template <typename T>
ObservableRange<T>::ObservableRange(T start, T end, T step)
{
	this->_start = start;
	this->_end = end;
	this->_step = step;
}

template <typename T>
void ObservableRange<T>::Suscribe(IObserver<T> &observer)
{
	_childObserver = &observer;
	Run();
}

template<typename T>
void ObservableRange<T>::Run()
{
	for (auto i = _start; i <= _end; i += _step)
		_childObserver->OnNext(i);

	_childObserver->OnComplete();
}

template<typename T>
void ObservableRange<T>::Reset()
{
	Run();
}

#endif