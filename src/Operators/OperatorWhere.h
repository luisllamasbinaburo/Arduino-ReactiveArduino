/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEOPERATORWHERE_h
#define _REACTIVEOPERATORWHERE_h

template <typename T>
class OperatorWhere : public Operator<T, T>
{
public:
	ReactivePredicate<T> _condition;

	OperatorWhere(ReactivePredicate<T> condition);

	void OnNext(T value) override;

private:

};

template <typename T>
OperatorWhere<T>::OperatorWhere(ReactivePredicate<T> condition)
{
	this->_condition = condition;
}

template <typename T>
void OperatorWhere<T>::OnNext(T value)
{
		if (_condition(value))
			this->_childObservers.OnNext(value);
}

#endif