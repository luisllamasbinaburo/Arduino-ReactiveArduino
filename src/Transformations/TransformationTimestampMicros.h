/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVETRANSFORMATIONTIMESTAMPMICROS_h
#define _REACTIVETRANSFORMATIONTIMESTAMPMICROS_h

template <typename T>
class TransformationTimestampMicros : public Operator<T, unsigned long>
{
public:
	TransformationTimestampMicros();

	void OnNext(T value) override;

	void Reset() override;

private:
	unsigned long _starTime;
};

template <typename T>
TransformationTimestampMicros<T>::TransformationTimestampMicros()
{
	_starTime = micros();
}

template <typename T>
void TransformationTimestampMicros<T>::Reset()
{
	_starTime = micros();
}

template <typename T>
void TransformationTimestampMicros<T>::OnNext(T value)
{
	if (this->_childObserver != nullptr) this->_childObserver->OnNext(micros() - _starTime);
}
#endif