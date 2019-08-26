/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVETRANSFORMATIONTOGGLE_h
#define _REACTIVETRANSFORMATIONTOGGLE_h

template <typename T>
class TransformationToggle : public Operator<T, int>
{
public:
	TransformationToggle(int state = LOW);

	void OnNext(T value) override;

private:
	int _state = false;
};

template <typename T>
TransformationToggle<T>::TransformationToggle(int state)
{
	this->_state = false;
}

template <typename T>
void TransformationToggle<T>::OnNext(T value)
{
	this->_state = !this->_state;

	if (this->_childObserver != nullptr) this->_childObserver->OnNext(this->_state);
}
#endif