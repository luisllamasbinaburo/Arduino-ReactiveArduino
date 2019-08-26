/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVETRANSFORMATIONSPLIT_h
#define _REACTIVETRANSFORMATIONSPLIT_h

template <typename T>
class TransformationSplit : public Operator<T, T>
{
public:
	ReactiveFunction<T> _function;

	TransformationSplit(char separator = ',');

	void OnNext(T value) override;

private:
	String _buffer = "";
	char _separator = ',';
};

template <typename T>
TransformationSplit<T>::TransformationSplit(char separator)
{
	_separator = separator;
}

template <typename T>
void TransformationSplit<T>::OnNext(T value)
{
	size_t counter = 0;
	size_t lastIndex = 0;
	_buffer = value;
	for (size_t index = 0; index < _buffer.length(); index++) {
		if (_buffer.substring(index, index + 1) == ",") 
		{
			if (this->_childObserver != nullptr) this->_childObserver->OnNext(_buffer.substring(lastIndex, index));
			lastIndex = index + 1;
			counter++;
		}

		if (index == _buffer.length() - 1)
		{
			if (this->_childObserver != nullptr) this->_childObserver->OnNext(_buffer.substring(lastIndex, _buffer.length()));
			if (this->_childObserver != nullptr) this->_childObserver->OnComplete();
		}
	}
}
#endif