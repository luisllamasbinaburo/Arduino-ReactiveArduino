/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEFILTERDEBOUNCEMICROS_h
#define _REACTIVEFILTERDEBOUNCEMICROS_h

template <typename T>
class FilterDebounceMicros : public Operator<T, T>
{
public:
	FilterDebounceMicros<T>(unsigned long interval);
	void OnNext(T value) override;

private:
	unsigned long _previousMicros;
	unsigned long _intervalMicros;
};

template<typename T>
FilterDebounceMicros<T>::FilterDebounceMicros(const unsigned long interval)
{
	this->_previousMicros = micros();
	this->_intervalMicros = interval;
}

template <typename T>
void FilterDebounceMicros<T>::OnNext(T value)
{
	if (micros() - this->_previousMicros >= this->_intervalMicros)
	{
		this->_previousMicros = micros();
		if (this->_childObserver != nullptr) this->_childObserver->OnNext(value);
	}
}

#endif