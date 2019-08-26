/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEAGGREGATECOUNTDOWN_h
#define _REACTIVEAGGREGATECOUNTDOWN_h

template <typename T>
class AggregateCountdown : public Operator<T, int>
{
public:
	AggregateCountdown(int count);

	void OnNext(T value) override;

private:
	int _count = false;
};

template <typename T>
AggregateCountdown<T>::AggregateCountdown(int count)
{
	this->_count = count;
}

template <typename T>
void AggregateCountdown<T>::OnNext(T value)
{
	this->_count--;
	this->_childObserver->OnNext(_count);

	if (_count <= 0)
	{
		this->_childObserver->OnComplete();
	}
}

#endif