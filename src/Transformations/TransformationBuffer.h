/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVETRANSFORMATIONBUFFER_h
#define _REACTIVETRANSFORMATIONBUFFER_h

template <typename T>
class TransformationBuffer : public Operator<T, T>
{
public:
	TransformationBuffer();

	void OnNext(T value);
	void OnComplete();

	void Reset();
private:
	String _buffer = "";
};

template <typename T>
TransformationBuffer<T>::TransformationBuffer()
{
}

template <typename T>
void TransformationBuffer<T>::Reset()
{
	_buffer = "";
}

template <typename T>
void TransformationBuffer<T>::OnNext(T value)
{
	_buffer = _buffer + String(value);

	if (this->_childObserver != nullptr) this->_childObserver->OnNext(_buffer);
}

template <typename T>
inline void TransformationBuffer<T>::OnComplete()
{
	if (this->_childObserver != nullptr) this->_childObserver->OnComplete();
}
#endif
