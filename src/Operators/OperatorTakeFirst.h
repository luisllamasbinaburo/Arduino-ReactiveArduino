/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEOPERATORTAKEFIRST_h
#define _REACTIVEOPERATORTAKEFIRST_h

template <typename T>
class OperatorTakeFirst : public Operator<T, T>
{
public:
	OperatorTakeFirst();

	void OnNext(T value) override;

private:
	bool _completed = false;
};

template <typename T>
OperatorTakeFirst<T>::OperatorTakeFirst()
{
}

template <typename T>
void OperatorTakeFirst<T>::OnNext(T value)
{
	if (this->_completed) return;

	if (this->_childObserver != nullptr) this->_childObserver->OnNext(value);
	this->_completed = true;
}

#endif