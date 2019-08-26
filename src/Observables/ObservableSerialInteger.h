/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEOBSERVABLESERIALINTEGER_h
#define _REACTIVEOBSERVABLESERIALINTEGER_h


template <>
class ObservableSerial<int> : public Observable<int>
{
public:
	ObservableSerial(char separator = '\n');
	void Suscribe(IObserver<int> &observer) override;
	void Receive();

private:
	int _data = 0;
	char _separator;
	bool _isNegative = false;
	IObserver<int>* _childObserver;
};

ObservableSerial<int>::ObservableSerial(char separator)
{
	_separator = separator;
}

void ObservableSerial<int>::Suscribe(IObserver<int> &observer)
{
	_childObserver = &observer;
}

void ObservableSerial<int>::Receive()
{
	if (_childObserver != nullptr)
	{
		
		while (Serial.available())
		{
			char newChar = Serial.read();

			if (newChar >= '0' && newChar <= '9')
				_data = (_data * 10) + (newChar - '0');

			else if (newChar == '-')
				_isNegative = true;

			else if (newChar == _separator)
			{
				_data = _isNegative ? -_data : _data;
				if (_childObserver != nullptr) _childObserver->OnNext(_data);

				_data = 0;
				_isNegative = false;
			}
		}
	}
}

//
//template <typename T>
//class ObservableSerialInteger : public Observable<T>
//{
//public:
//	ObservableSerialInteger(char separator = '\n');
//	void Suscribe(IObserver<T> &observer) override;
//	void Receive();
//
//private:
//	T _data = 0;
//	char _separator;
//	bool _isNegative = false;
//	IObserver<T>* _childObserver;
//};
//
//template <typename T>
//ObservableSerialInteger<T>::ObservableSerialInteger(char separator)
//{
//	_separator = separator;
//}
//
//template <typename T>
//void ObservableSerialInteger <T>::Suscribe(IObserver<T> &observer)
//{
//	_childObserver = &observer;
//}
//
//template <typename T>
//void ObservableSerialInteger <T>::Receive()
//{
//	if (_childObserver != nullptr)
//	{
//		
//		while (Serial.available())
//		{
//			char newChar = Serial.read();
//
//			if (newChar >= '0' && newChar <= '9')
//				_data = (_data * 10) + (newChar - '0');
//
//			else if (newChar == '-')
//				_isNegative = true;
//
//			else if (newChar == _separator)
//			{
//				_data = _isNegative ? -_data : _data;
//				if (_childObserver != nullptr) _childObserver->OnNext(_data);
//
//				_data = 0;
//				_isNegative = false;
//			}
//		}
//	}
//}

#endif