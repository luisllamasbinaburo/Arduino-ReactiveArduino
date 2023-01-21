/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVETRANSFORMATIONJOIN_h
#define _REACTIVETRANSFORMATIONJOIN_h

template <typename T>
class TransformationJoin: public Operator<T, T>
{
public:
	TransformationJoin(char separator = ',');

	void OnNext(T value) override;
	void OnComplete() override;

private:
	bool _isFirst = true;
	String _buffer = "";
	String _separator = ",";
};

template <typename T>
TransformationJoin<T>::TransformationJoin(char separator)
{
	_separator = String(separator);
}

template <typename T>
void TransformationJoin<T>::OnNext(T value)
{
	if (_isFirst)
	{
		_buffer = String(value);
		_isFirst = false;
	}
	else
	{
		_buffer = _buffer + _separator + String(value);
	}

	this->_childObservers.OnNext(_buffer);
}

template <typename T>
void TransformationJoin<T>::OnComplete()
{
	this->_childObservers.OnComplete();
}
#endif
