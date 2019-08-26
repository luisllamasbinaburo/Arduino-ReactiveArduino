/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEOPERATORLAST_h
#define _REACTIVEOPERATORLAST_h

template <typename T>
class OperatorLast : public Operator<T, T>
{
public:
	OperatorLast();

	void OnNext(T value) override;
	void OnComplete() override;

private:
	T _last = T();
	bool _any = false;
};

template <typename T>
OperatorLast<T>::OperatorLast()
{
}

template <typename T>
void OperatorLast<T>::OnNext(T value)
{
	this->_last = value;
	this->_any = true;
}

template <typename T>
void OperatorLast<T>::OnComplete()
{
	if (!this->_any) return;

	if (this->_childObserver != nullptr) this->_childObserver->OnNext(_last);
	if (this->_childObserver != nullptr) this->_childObserver->OnComplete();
}

#endif