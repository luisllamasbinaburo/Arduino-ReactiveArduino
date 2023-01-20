/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEOPERATORDISTINCT_h
#define _REACTIVEOPERATORDISTINCT_h

template <typename T>
class OperatorDistinct : public Operator<T, T>
{
public:
	OperatorDistinct();

	void OnNext(T value) override;

private:
	T _last = T();
	bool _any = false;
};

template <typename T>
OperatorDistinct<T>::OperatorDistinct()
{
}

template <typename T>
void OperatorDistinct<T>::OnNext(T value)
{
	if (!_any || (_any && _last != value))
		this->_childObservers.Fire(value);

	_last = value;
	_any = true;
}

#endif