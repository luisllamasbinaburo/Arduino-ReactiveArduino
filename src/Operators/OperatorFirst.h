/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEOPERATORFIRST_h
#define _REACTIVEOPERATORFIRST_h

template <typename T>
class OperatorFirst : public Operator<T, T>
{
public:
	OperatorFirst();

	void OnNext(T value) override;
	void OnComplete() override;


private:
	T _first = T();
	bool _any = false;

};

template <typename T>
OperatorFirst<T>::OperatorFirst()
{
}

template <typename T>
void OperatorFirst<T>::OnNext(T value)
{
	if(!_any) 
		this->_first = value;

	this->_any = true;
}

template <typename T>
void OperatorFirst<T>::OnComplete()
{
	if (_any)
		if (this->_childObserver != nullptr) this->_childObserver->OnNext(_first);
}

#endif