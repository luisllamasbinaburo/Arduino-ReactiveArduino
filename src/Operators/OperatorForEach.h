/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEOPERATORFOREACH_h
#define _REACTIVEOPERATORFOREACH_h

template <typename T>
class OperatorForEach : public Operator<T, T>
{
public:
	OperatorForEach(ReactiveAction<T> action);

	void OnNext(T value) override;
	void OnComplete() override;

private:
	ReactiveAction<T> _doAction;
};

template <typename T>
OperatorForEach<T>::OperatorForEach(ReactiveAction<T> action)
{
	_doAction = action;
}

template <typename T>
void OperatorForEach<T>::OnNext(T value)
{
	_doAction(value);

	if (this->_childObserver != nullptr) this->_childObserver->OnNext(value);
}

template <typename T>
inline void OperatorForEach<T>::OnComplete()
{
}

#endif