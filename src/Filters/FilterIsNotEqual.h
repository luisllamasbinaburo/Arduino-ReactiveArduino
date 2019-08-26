/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEFILTERISNOTEQUAL_h
#define _REACTIVEFILTERISNOTEQUAL_h

template <typename T>
class FilterIsNotEqual : public Operator<T, T>
{
public:
	FilterIsNotEqual<T>(T value);
	void OnNext(T value) override;

private:
	T _value = T();
};

template<typename T>
FilterIsNotEqual<T>::FilterIsNotEqual(T value)
{
	_value = value;
}

template <typename T>
void FilterIsNotEqual<T>::OnNext(T value)
{
	if (value != this->_value)
		if (this->_childObserver != nullptr) this->_childObserver->OnNext(value);
}

#endif