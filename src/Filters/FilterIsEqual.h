/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _AGGREGATEISEQUAL_h
#define _AGGREGATEISEQUAL_h

template <typename T>
class FilterIsEqual : public Operator<T, bool>
{
public:
	FilterIsEqual<T>(T value);
	void OnNext(T value);

private:
	T _value;
};

template<typename T>
FilterIsEqual<T>::FilterIsEqual(T value)
{
	_value = value;
}

template <typename T>
void FilterIsEqual<T>::OnNext(T value)
{
	if (this->_childObserver != nullptr) this->_childObserver->OnNext(value == _value);
}
#endif

