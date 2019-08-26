/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEOBSERVERANALOGOUTPUT_h
#define _REACTIVEOBSERVERANALOGOUTPUT_h

template <typename T>
class ObserverAnalogOutput : public IObserver<T>
{
public:
	ObserverAnalogOutput(uint8_t pin);

	void OnNext(T value) override;
	void OnComplete() override;

private:
	uint8_t _pin;
};

template <typename T>
ObserverAnalogOutput<T>::ObserverAnalogOutput(uint8_t pin)
{
	this->_pin = pin;
	pinMode(pin, OUTPUT);
}


template <typename T>
void ObserverAnalogOutput<T>::OnNext(T value)
{
	analogWrite(value);
}

template <typename T>
void ObserverAnalogOutput<T>::OnComplete()
{
}

#endif