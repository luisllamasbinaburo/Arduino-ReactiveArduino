/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _AGGREGATEMIN_h
#define _AGGREGATEMIN_h

template <typename T>
class AggregateMin : public Operator<T, T>
{
public:
	AggregateMin();

	void OnNext(T value);

private:
	bool _any = false;
	T _min = false;
};

template <typename T>
AggregateMin<T>::AggregateMin()
{
}

template <typename T>
void AggregateMin <T>::OnNext(T value)
{
	if (!_any) _min = value;
	else _min = value < _min ? value : _min;
	_any = true;

	if(this->_childObserver != nullptr) this->_childObserver->OnNext(_min);

}
#endif

