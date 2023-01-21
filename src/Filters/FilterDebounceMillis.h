/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEFILTERDEBOUNCEMILLIS_h
#define _REACTIVEFILTERDEBOUNCEMILLIS_h

template <typename T>
class FilterDebounceMillis : public Operator<T, T>
{
public:
	FilterDebounceMillis<T>(unsigned long interval);
	void OnNext(T value) override;

private:
	unsigned long _previousMillis;
	unsigned long _intervalMillis;
};

template<typename T>
FilterDebounceMillis<T>::FilterDebounceMillis(unsigned long interval)
{
	_previousMillis = millis();
	_intervalMillis = interval;
}

template <typename T>
void FilterDebounceMillis<T>::OnNext(T value)
{
	if (millis() - _previousMillis >= _intervalMillis)
	{
		_previousMillis = millis();
		this->_childObservers.OnNext(value);
	}
}

#endif