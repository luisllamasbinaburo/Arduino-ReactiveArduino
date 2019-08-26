/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEOPERATORREPEAT_h
#define _REACTIVEOPERATORREPEAT_h

template <typename T>
class OperatorRepeat : public Operator<T, T>
{
public:
	OperatorRepeat(size_t N);

	void OnNext(T value) override;
	void OnComplete() override;

private:
	size_t _repetition;
};

template <typename T>
OperatorRepeat<T>::OperatorRepeat(size_t N)
{
	this->_repetition = N;
}

template <typename T>
void OperatorRepeat<T>::OnNext(T value)
{
	if (this->_childObserver != nullptr) this->_childObserver->OnNext(value);
}

template <typename T>
void OperatorRepeat<T>::OnComplete()
{
	this->_repetition--;
	if (this->_repetition > 0)
	{
		if (this->_parentObservable != nullptr) this->_parentObservable->Reset();
	}
	else
	{
		if (this->_childObserver != nullptr) this->_childObserver->OnComplete();
	}
}

#endif