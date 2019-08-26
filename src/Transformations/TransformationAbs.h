/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVETRANSFORMATIONABS_h
#define _REACTIVETRANSFORMATIONABS_h

template <typename T>
class TransformationAbs : public Operator<T, T>
{
public:
	TransformationAbs<T>();

	void OnNext(T value) override;
};

template <typename T>
TransformationAbs<T>::TransformationAbs()
{
}

template <typename T>
void TransformationAbs<T>::OnNext(T value)
{
	this->_childObserver->OnNext(value >= 0 ? value : -value);
}

#endif