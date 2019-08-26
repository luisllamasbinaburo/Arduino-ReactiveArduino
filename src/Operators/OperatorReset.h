/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEOPERATORRESET_h
#define _REACTIVEOPERATORRESET_h

template <typename T>
class OperatorReset : public Operator<T, T>
{
public:
	OperatorReset();

	void OnNext(T value) override;
	void OnComplete() override;
	void Reset() override;
};

template <typename T>
OperatorReset<T>::OperatorReset()
{
}

template <typename T>
void OperatorReset<T>::OnNext(T value)
{
	if (this->_childObserver != nullptr) this->_childObserver->OnNext(value);
}

template <typename T>
void OperatorReset<T>::OnComplete()
{
	if (this->_childObserver != nullptr) this->_childObserver->OnComplete();
}

template <typename T>
void OperatorReset<T>::Reset()
{
	if (this->_parentObservable != nullptr) this->_parentObservable->Reset();
}

#endif