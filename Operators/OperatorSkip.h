/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEOPERATORSKIPN_h
#define _REACTIVEOPERATORSKIPN_h

template <typename T>
class OperatorSkip : public Operator<T, T>
{
public:
	OperatorSkip(size_t N);

	void OnNext(T value) override;

private:
	size_t index = 0;
	size_t num_elements = 0;
	bool _completed = false;
};

template <typename T>
OperatorSkip<T>::OperatorSkip(size_t N)
{
	num_elements = N;
}

template <typename T>
void OperatorSkip<T>::OnNext(T value)
{
	if (index >= num_elements)
		if (this->_childObserver != nullptr) this->_childObserver->OnNext(value);

	index++;
}

#endif