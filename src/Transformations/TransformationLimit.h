/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVETRANSFORMATIONLIMIT_h
#define _REACTIVETRANSFORMATIONLIMIT_h

template <typename T>
class TransformationLimit : public Operator<T, T>
{
public:
	TransformationLimit<T>(T lowerLimit, T upperLimit);

	void OnNext(T value) override;

private:
	T _upperLimit = T();
	T _lowerLimit = T();
};

template <typename T>
TransformationLimit<T>::TransformationLimit(T lowerLimit, T upperLimit)
{
	_lowerLimit = lowerLimit;
	_upperLimit = upperLimit;
}

template <typename T>
void TransformationLimit<T>::OnNext(T value)
{
	this->_childObservers.OnNext(value < _lowerLimit ? _lowerLimit : value > _upperLimit ? _upperLimit : value);
}

#endif