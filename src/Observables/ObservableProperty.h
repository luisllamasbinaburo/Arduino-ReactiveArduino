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
	void Suscribe(IObserver<T> &) override;
	void Finish();
	void Reset() override;

private:
	IObserver<T> *_observer;
	bool _complete = false;
};

template <typename T>
void ObservableProperty<T>::operator=(const T& value)
{
	if (this->_complete) return;
	if (this->_observer != nullptr) this->_observer->OnNext(value);
}

template <typename T>
ObservableProperty<T>::ObservableProperty()
{
}

template <typename T>
void ObservableProperty<T>::Suscribe(IObserver<T> &observer)
{
	this->_observer = &observer;
}

template<typename T>
void ObservableProperty<T>::Finish()
{
	if (_complete) return;

	if (this->_observer != nullptr) this->_observer->OnComplete();
	this->_complete = true;
}

template<typename T>
void ObservableProperty<T>::Reset()
{
	this->_complete = false;
}

#endif