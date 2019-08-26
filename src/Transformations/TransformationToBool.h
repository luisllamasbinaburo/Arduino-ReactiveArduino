/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVETRANSFORMATIONTOBOOL_h
#define _REACTIVETRANSFORMATIONTOBOOL_h

template <typename T>
class TransformationToBool : public Operator<T, bool>
{
public:
	TransformationToBool<T>();

	void OnNext(T value) override;
};

template <typename T>
TransformationToBool<T>::TransformationToBool()
{
}

template <typename T>
void TransformationToBool<T>::OnNext(T value)
{
	this->_childObserver->OnNext(value != 0);
}

#endif