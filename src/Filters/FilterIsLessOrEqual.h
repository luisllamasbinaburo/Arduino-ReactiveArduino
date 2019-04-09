/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _AGGREGATEISLESSOREQUAL_h
#define _AGGREGATEISLESSOREQUAL_h

template <typename T>
class FilterIsLessOrEqual : public Operator<T, bool>
{
public:
	FilterIsLessOrEqual<T>(T value);
	void OnNext(T value);

private:
	T _value;
};

template<typename T>
FilterIsLessOrEqual<T>::FilterIsLessOrEqual(T value)
{
	_value = value;
}

template <typename T>
void FilterIsLessOrEqual<T>::OnNext(T value)
{
	if (this->_childObserver != nullptr) this->_childObserver->OnNext(value <= _value);
}
#endif

