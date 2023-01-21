/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVETRANSFORMATIONBUFFER_h
#define _REACTIVETRANSFORMATIONBUFFER_h

template <typename T>
class TransformationStringBuffer : public Operator<T, T>
{
public:
	TransformationStringBuffer();

	void OnNext(T value) override;
	void OnComplete() override;

	void Reset() override;
private:
	String _buffer = "";
};

template <typename T>
TransformationStringBuffer <T>::TransformationStringBuffer()
{
}

template <typename T>
void TransformationStringBuffer <T>::Reset()
{
	_buffer = "";
}

template <typename T>
void TransformationStringBuffer <T>::OnNext(T value)
{
	_buffer = _buffer + String(value);

	this->_childObservers.OnNext(_buffer);
}

template <typename T>
void TransformationStringBuffer <T>::OnComplete()
{
	this->_childObservers.OnComplete();
}
#endif
