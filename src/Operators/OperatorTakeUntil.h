/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEOPERATORTAKEUNTIL_h
#define _REACTIVEOPERATORTAKEUNTIL_h

template <typename T>
class OperatorTakeUntil : public Operator<T, T>
{
public:
	ReactivePredicate<T> _condition;

	OperatorTakeUntil(ReactivePredicate<T> condition);

	void OnNext(T value) override;

private:
	bool _completed = false;
};

template <typename T>
OperatorTakeUntil<T>::OperatorTakeUntil(ReactivePredicate<T> condition)
{
	this->_condition = condition;
}

template <typename T>
void OperatorTakeUntil<T>::OnNext(T value)
{
	if (this->_completed) return;

	if (!this->_condition(value))
		if (this->_childObserver != nullptr) this->_childObserver->OnNext(value);
	else
	{
		this->_completed = true;
		if (this->_childObserver != nullptr) this->_childObserver->OnComplete();
	}
}

#endif