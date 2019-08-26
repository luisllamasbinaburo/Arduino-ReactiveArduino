/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVETRANSFORMATIONREDUCE_h
#define _REACTIVETRANSFORMATIONREDUCE_h

template <typename T>
class TransformationReduce : public Operator<T, T>
{
public:
	ReactiveCompound<T> _function;

	TransformationReduce<T>(ReactiveCompound<T> function);

	void OnNext(T value) override;

private:
	T _rst = T();

};

template <typename T>
TransformationReduce<T>::TransformationReduce(ReactiveCompound<T> function)
{
	this->_function = function;
}

template <typename T>
void TransformationReduce<T>::OnNext(T value)
{
	this->_rst = this->_function(this->_rst, value);
	if (this->_childObserver != nullptr) this->_childObserver->OnNext(this->_rst);
}
#endif
