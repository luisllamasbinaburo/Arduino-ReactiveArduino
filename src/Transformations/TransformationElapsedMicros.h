/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVETRANSFORMATIONELAPEDMICROS_h
#define _REACTIVETRANSFORMATIONELAPEDMICROS_h

template <typename T>
class TransformationElapsedMicros : public Operator<T, unsigned long>
{
public:
	TransformationElapsedMicros();

	void OnNext(T value) override;

	void Reset() override;

private:
	unsigned long _starTime;
};

template <typename T>
TransformationElapsedMicros<T>::TransformationElapsedMicros()
{
	_starTime = micros();
}

template <typename T>
void TransformationElapsedMicros<T>::Reset()
{
	_starTime = micros();
}

template <typename T>
void TransformationElapsedMicros<T>::OnNext(T value)
{
	if (this->_childObserver != nullptr) this->_childObserver->OnNext(micros() - _starTime);
	_starTime = micros();
}

#endif

