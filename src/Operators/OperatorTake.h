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
	size_t index = 0;
	size_t num_elements = 0;
	bool _completed = false;
};

template <typename T>
OperatorTake<T>::OperatorTake(size_t N)
{
	this->num_elements = N;
}

template <typename T>
void OperatorTake<T>::OnNext(T value)
{
	if (this->_completed) return;

	if (this->index < this->num_elements)
	{
		if (this->_childObserver != nullptr) this->_childObserver->OnNext(value);
	}
	else
	{
		if (this->_childObserver != nullptr) this->_childObserver->OnComplete();
		this->_completed = true;
	}

	this->index++;
}

#endif