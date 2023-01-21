/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEOPERATORNORESET_h
#define _REACTIVEOPERATORNORESET_h

template <typename T>
class OperatorNoReset : public Operator<T, T>
{
public:
	OperatorNoReset();

	void OnNext(T value) override;
	void OnComplete() override;
	void Reset() override;
};

template <typename T>
OperatorNoReset<T>::OperatorNoReset()
{
}

template <typename T>
void OperatorNoReset<T>::OnNext(T value)
{
	this->_childObservers.OnNext(value);
}

template <typename T>
void OperatorNoReset<T>::OnComplete()
{
	this->_childObservers.OnComplete();
}

template<typename T>
inline void OperatorNoReset<T>::Reset()
{
	this->_childObservers.OnComplete();
}

#endif