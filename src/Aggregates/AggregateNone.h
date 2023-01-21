/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEAGGREGATENONE_h
#define _REACTIVEAGGREGATENONE_h

template <typename T>
class AggregateNone : public Operator<T, bool>
{
public:
	ReactivePredicate<T> _condition;

	AggregateNone(ReactivePredicate<T> condition);

	void OnNext(T value) override;

private:
	bool _state = true;
};

template <typename T>
AggregateNone<T>::AggregateNone(ReactivePredicate<T> condition)
{
	_condition = condition;
}

template <typename T>
void AggregateNone<T>::OnNext(T value)
{
	if (!_condition(value)) _state = false;

	this->_childObservers.OnNext(_state);
}

#endif