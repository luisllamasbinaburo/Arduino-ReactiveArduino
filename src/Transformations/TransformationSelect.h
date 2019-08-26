/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVETRANSFORMATIONSELECT_h
#define _REACTIVETRANSFORMATIONSELECT_h

template <typename T>
class TransformationSelect : public Operator<T, T>
{
public:
	ReactiveFunction<T> _function;

	TransformationSelect<T>(ReactiveFunction<T> function);

	void OnNext(T value) override;
};

template <typename T>
TransformationSelect<T>::TransformationSelect(ReactiveFunction<T> function)
{
	this->_function = function;
}

template <typename T>
void TransformationSelect<T>::OnNext(T value)
{
	if (this->_childObserver != nullptr) this->_childObserver->OnNext(this->_function(value));
}
#endif