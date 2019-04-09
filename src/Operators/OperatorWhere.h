/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _OPERATORWHERE_h
#define _OPERATORWHERE_h

template <typename T>
class OperatorWhere : public Operator<T, T>
{
public:
	ReactiveCondition<T> _condition;

	OperatorWhere(ReactiveCondition<T> condition);

	void OnNext(T value);

private:

};

template <typename T>
OperatorWhere<T>::OperatorWhere(ReactiveCondition<T> condition)
{
	this->_condition = condition;
}

template <typename T>
void OperatorWhere<T>::OnNext(T value)
{
	if (this->_childObserver != nullptr)
		if (this->_condition(value))
			this->_childObserver->OnNext(value);
}
#endif