/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEOBSERVABLERANGEDEFER_h
#define _REACTIVEOBSERVABLERANGEDEFER_h

template <typename T>
class ObservableRangeDefer : public Observable<T>
{
public:
	ObservableRangeDefer(T start, T end, T step = 1);
	void Suscribe(IObserver<T> &observer) override;
	void Next();
	void Reset() override;

private:
	T _start;
	T _end;
	T _step;
	T _value;

	IObserver<T>* _childObserver;
};

template <typename T>
ObservableRangeDefer<T>::ObservableRangeDefer(T start, T end, T step)
{
	this->_start = start;
	this->_end = end;
	this->_step = step;
	this->_value = start;
}

template <typename T>
void ObservableRangeDefer<T>::Suscribe(IObserver<T> &observer)
{
	_childObserver = &observer;
}

template <typename T>
void ObservableRangeDefer<T>::Next()
{
	if (_value > this->_end) return;

	if (_childObserver != nullptr) _childObserver->OnNext(_value);
	_value += _step;

	if(_value > this->_end)
		if (_childObserver != nullptr) _childObserver->OnComplete();
}

template <typename T>
void ObservableRangeDefer<T>::Reset()
{
	this->_value = this->_start;
}

#endif