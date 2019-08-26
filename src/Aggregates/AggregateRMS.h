/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEAGGREGATERMS_h
#define _REACTIVEAGGREGATERMS_h

template <typename T>
class AggregateRMS : public Operator<T, T>
{
public:
	AggregateRMS();

	void OnNext(T value) override;

private:
	T _sumSqr = T();
	size_t _count = 0;
};

template <typename T>
AggregateRMS<T>::AggregateRMS()
{
}

template <typename T>
void AggregateRMS<T>::OnNext(T value)
{
	this->_sumSqr += value * value;
	this->_count++;
	if (this->_childObserver != nullptr) this->_childObserver->OnNext(sqrt(this->_sumSqr / this->_count));
}

#endif