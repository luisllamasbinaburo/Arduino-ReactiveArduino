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
	void Subscribe(IObserver<int> &observer) override;
	void UnSubscribe(IObserver<int> &observer) override;
	void Receive();

private:
	int _data = 0;
	char _separator;
	bool _isNegative = false;

	ObserverList<int> _childObservers;
};

inline ObservableSerial<int>::ObservableSerial(char separator)
{
	_separator = separator;
}

inline void ObservableSerial<int>::Subscribe(IObserver<int> &observer)
{
	_childObservers.Add(&observer);
}

inline void ObservableSerial<int>::UnSubscribe(IObserver<int> &observer)
{
	_childObservers.Remove(&observer);
}

inline void ObservableSerial<int>::Receive()
{
	if (!_childObservers.IsEmpty())
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
				_childObservers.Fire(_data);

				_data = 0;
				_isNegative = false;
			}
		}
	}
}
#endif