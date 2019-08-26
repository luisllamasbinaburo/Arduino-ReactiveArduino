/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEAGGREGATEAVERAGE_h
#define _REACTIVEAGGREGATEAVERAGE_h

template <typename T>
class AggregateAverage : public Operator<T, T>
{
public:
	AggregateAverage();

	void OnNext(T value) override;

private:
	T _sum = T();
	size_t _count = 0;
};

template <typename T>
AggregateAverage<T>::AggregateAverage()
{
}

template <typename T>
void AggregateAverage<T>::OnNext(T value)
{
	this->_sum += value;
	this->_count++;
	if (this->_childObserver != nullptr) this->_childObserver->OnNext(this->_sum/ this->_count);
}

#endif