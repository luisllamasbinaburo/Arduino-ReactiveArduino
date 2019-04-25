/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEAGGREGATEANY_h
#define _REACTIVEAGGREGATEANY_h

template <typename T>
class AggregateAny : public Operator<T, bool>
{
public:
	ReactivePredicate<T> _condition;

	AggregateAny(ReactivePredicate<T> condition);

	void OnNext(T value);

private:
	bool _state = false;
};

template <typename T>
AggregateAny<T>::AggregateAny(ReactivePredicate<T> condition)
{
	this->_condition = condition;
}

template <typename T>
void AggregateAny<T>::OnNext(T value)
{
	if (this->_condition(value)) this->_state = true;

	this->_childObserver->OnNext(this->_state);
}


#endif