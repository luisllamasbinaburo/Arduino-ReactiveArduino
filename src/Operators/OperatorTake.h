/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEOPERATORTAKEN_h
#define _REACTIVEOPERATORTAKEN_h

template <typename T>
class OperatorTake : public Operator<T, T>
{
public:
	OperatorTake(size_t N);

	void OnNext(T value) override;

private:
	size_t _index = 0;
	size_t _num_elements = 0;
	bool _completed = false;
};

template <typename T>
OperatorTake<T>::OperatorTake(size_t N)
{
	_num_elements = N;
}

template <typename T>
void OperatorTake<T>::OnNext(T value)
{
	if (_completed) return;

	if (_index < _num_elements)
	{
		this->_childObservers.OnNext(value);
	}
	else
	{
		this->_childObservers.OnComplete();
		_completed = true;
	}

	_index++;
}

#endif