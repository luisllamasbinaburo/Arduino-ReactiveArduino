/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVETRANSFORMATIONLIMITLOWER_h
#define _REACTIVETRANSFORMATIONLIMITLOWER_h

template <typename T>
class TransformationLowerLimit : public Operator<T, T>
{
public:
	TransformationLowerLimit<T>(T lowerLimit);

	void OnNext(T value) override;

private:
	T _lowerLimit = T();
};

template <typename T>
TransformationLowerLimit<T>::TransformationLowerLimit(T lowerLimit)
{
	_lowerLimit = lowerLimit;
}

template <typename T>
void TransformationLowerLimit<T>::OnNext(T value)
{
	this->_childObserver->OnNext(value < _lowerLimit ? _lowerLimit : value);
}

#endif