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
	void Subscribe(IObserver<T> &observer) override;
	void UnSubscribe(IObserver<T> &observer) override;
	void Next();
	void Reset() override;

private:
	T _start;
	T _end;
	T _step;
	T _value;

	ObserverList<T> _childObservers;
};

template <typename T>
ObservableRangeDefer<T>::ObservableRangeDefer(T start, T end, T step)
{
	_start = start;
	_end = end;
	_step = step;
	_value = start;
}

template <typename T>
void ObservableRangeDefer<T>::Subscribe(IObserver<T> &observer)
{
	this->_childObservers.Add(&observer);
}

template <typename T>
void ObservableRangeDefer<T>::UnSubscribe(IObserver<T> &observer)
{
	this->_childObservers.Remove(&observer);
}

template <typename T>
void ObservableRangeDefer<T>::Next()
{
	if (_value > _end) return;

	T value = _value;
	this->_childObservers.OnNext(value);
	_value += _step;

	if(_value > _end)
		this->_childObservers.OnComplete();
}

template <typename T>
void ObservableRangeDefer<T>::Reset()
{
	_value = _start;
}

#endif