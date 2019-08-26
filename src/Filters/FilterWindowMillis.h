/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEFILTERWINDOWMILLIS_h
#define _REACTIVEFILTERWINDOWMILLIS_h

template <typename T>
class FilterWindowMillis : public Operator<T, T>
{
public:
	FilterWindowMillis<T>(unsigned long interval);
	void OnNext(T value) override;

private:
	bool _started = false;
	unsigned long _interval;
	unsigned long _lastTrigger = 0;
};

template<typename T>
FilterWindowMillis<T>::FilterWindowMillis(const unsigned long interval)
{
	_interval = interval;
}

template <typename T>
void FilterWindowMillis<T>::OnNext(T value)
{
	if (!_started)
	{
		_lastTrigger = millis();
		_started = true;
	}
	if (_started && static_cast<unsigned long>(millis() - _lastTrigger) <= _interval)
	{
		if (this->_childObserver != nullptr) this->_childObserver->OnNext(value);
	}
}

#endif