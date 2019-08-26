/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEOBSERVABLEANALOGINPUT_h
#define _REACTIVEOBSERVABLEANALOGINPUT_h

template <typename T>
class ObservableAnalogInput : public Observable<T>
{
public:
	ObservableAnalogInput(uint8_t pin, uint8_t pinMode = INPUT);
	void Suscribe(IObserver<T> &observer) override;
	void Next();

private:
	uint8_t _pin;

	IObserver<T>* _childObserver;
};

template <typename T>
ObservableAnalogInput<T>::ObservableAnalogInput(uint8_t pin, uint8_t mode)
{
	this->_pin = pin;
	pinMode(pin, mode);
}

template <typename T>
void ObservableAnalogInput<T>::Suscribe(IObserver<T> &observer)
{
	_childObserver = &observer;
}

template <typename T>
void ObservableAnalogInput<T>::Next()
{
	if (_childObserver != nullptr) _childObserver->OnNext(analogRead(this->_pin));
}

#endif