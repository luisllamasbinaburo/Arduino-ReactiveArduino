/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEOBSERVABLEDIGITALINPUT_h
#define _REACTIVEOBSERVABLEDIGITALINPUT_h

template <typename T>
class ObservableDigitalInput : public Observable<T>
{
public:
	ObservableDigitalInput(uint8_t pin, uint8_t pinMode = INPUT);
	void Subscribe(IObserver<T> &observer) override;
	void UnSubscribe(IObserver<T> &observer) override;
	void Next();

private:
	uint8_t _pin;

	ObserverList<T> _childObservers;
};

template <typename T>
ObservableDigitalInput<T>::ObservableDigitalInput(uint8_t pin, uint8_t mode)
{
	this->_pin = pin;
	pinMode(pin, mode);
}

template <typename T>
void ObservableDigitalInput<T>::Subscribe(IObserver<T> &observer)
{
	this->_childObservers.Add(&observer);
}

template <typename T>
void ObservableDigitalInput<T>::UnSubscribe(IObserver<T> &observer)
{
	this->_childObservers.Remove(&observer);
}

template <typename T>
void ObservableDigitalInput<T>::Next()
{
	this->_childObservers.Fire(digitalRead(this->_pin));
}

#endif