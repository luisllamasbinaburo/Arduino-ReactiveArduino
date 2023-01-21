/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEOPERATORIF_h
#define _REACTIVEOPERATORIF_h


template <typename T>
class OperatorIf : public Operator<T, T>
{
public:
	OperatorIf(ReactivePredicate<T> condition, ReactiveAction<T> action);

	void OnNext(T value) override;

private:
	ReactivePredicate<T> _condition;
	ReactiveAction<T> _action;
};

template <typename T>
OperatorIf<T>::OperatorIf(ReactivePredicate<T> condition, ReactiveAction<T> action)
{
	_condition = condition;
	_action = action;
}

template <typename T>
void OperatorIf<T>::OnNext(T value)
{
	if (_condition(value)) _action(value);
	this->_childObservers.OnNext(value);
}

#endif