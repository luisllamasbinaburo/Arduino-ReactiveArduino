/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEOBSERVABLEPROPERTY_h
#define _REACTIVEOBSERVABLEPROPERTY_h

template <typename T>
class ObservableProperty : public Observable<T>
{
public:
	void operator = (const T&);
	ObservableProperty();
	void Subscribe(IObserver<T> &) override;
	void UnSubscribe(IObserver<T> &) override;
	void Finish();
	void Reset() override;

private:
	ObserverList<T> _observers;
	
	bool _complete = false;
};

template <typename T>
void ObservableProperty<T>::operator=(const T& value)
{
	if (this->_complete) return;
	_observers.Fire(value);
}

template <typename T>
ObservableProperty<T>::ObservableProperty()
{
}

template <typename T>
void ObservableProperty<T>::Subscribe(IObserver<T> &observer)
{
	_observers.Add(&observer);
}

template <typename T>
void ObservableProperty<T>::UnSubscribe(IObserver<T> &observer)
{
	_observers.Remove(&observer);
}

template<typename T>
void ObservableProperty<T>::Finish()
{
	if (_complete) return;

	_observers.Complete();
	this->_complete = true;
}

template<typename T>
void ObservableProperty<T>::Reset()
{
	this->_complete = false;
}

#endif