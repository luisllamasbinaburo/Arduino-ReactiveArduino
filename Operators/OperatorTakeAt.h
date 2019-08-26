/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEOPERATORTAKEAT_h
#define _REACTIVEOPERATORTAKEAT_h

template <typename T>
class OperatorTakeAt : public Operator<T, T>
{
public:
	OperatorTakeAt(size_t N);

	void OnNext(T value) override;

private:
	size_t index = 0;
	size_t element_index = 0;
	bool _completed = false;
};

template <typename T>
OperatorTakeAt<T>::OperatorTakeAt(size_t N)
{
	element_index = N;
}

template <typename T>
void OperatorTakeAt<T>::OnNext(T value)
{
	if (this->_completed) return;

	if (this->index == this->element_index)
	{
		if (this->_childObserver != nullptr) this->_childObserver->OnNext(value);
		if (this->_childObserver != nullptr) this->_childObserver->OnComplete();
		this->_completed = true;
	}

	this->index++;
}

#endif