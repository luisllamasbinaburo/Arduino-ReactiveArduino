/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVETRANSFORMATIONFREQUENCY_h
#define _REACTIVETRANSFORMATIONFREQUENCY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

template <typename T>
class TransformationFrequency : public Operator<T, float>
{
public:
	TransformationFrequency();

	void OnNext(T value) override;

	void Reset() override;

private:
	unsigned long _starTime;
};

template <typename T>
TransformationFrequency<T>::TransformationFrequency()
{
	_starTime = millis();
}

template <typename T>
void TransformationFrequency<T>::Reset()
{
	_starTime = millis();
}

template <typename T>
void TransformationFrequency<T>::OnNext(T value)
{
	if (this->_childObserver != nullptr) this->_childObserver->OnNext(1000.0 / (millis() - _starTime));
	_starTime = millis();
}
#endif
