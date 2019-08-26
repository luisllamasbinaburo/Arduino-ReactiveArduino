/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEOBSERVABLESERIALDOUBLE_h
#define _REACTIVEOBSERVABLESERIALDOUBLE_h


template <>
class ObservableSerial<double> : public Observable<double>
{
public:
	ObservableSerial(char separator = '\n');
	void Suscribe(IObserver<double> &observer) override;
	void Receive();

private:
	char _separator;

	float _data = 0;
	int _dataReal = 0;
	int _dataDecimal = 0;
	int _dataPow = 1;
	bool _isDecimalStage = false;
	bool _isNegative = false;

	IObserver<double>* _childObserver;
};


ObservableSerial<double>::ObservableSerial(char separator)
{
	_separator = separator;
}

void ObservableSerial<double>::Suscribe(IObserver<double> &observer)
{
	_childObserver = &observer;
}

void ObservableSerial<double>::Receive()
{
	while (Serial.available())
	{
		char newChar = Serial.read();

		if (newChar == '-')
			_isNegative = true;

		else if (newChar == '.')
			_isDecimalStage = true;

		else if (newChar >= '0' && newChar <= '9')
		{
			if (_isDecimalStage == false)
				_dataReal = (_dataReal * 10) + (newChar - '0');
			else
			{
				_dataDecimal = (_dataDecimal * 10) + (newChar - '0');
				_dataPow *= 10;
			}
		}
		else if (newChar == _separator)
		{
			_data = (double)_dataReal + (double)_dataDecimal / _dataPow;
			_data = _isNegative ? -_data : _data;

			if (_childObserver != nullptr) _childObserver->OnNext(_data);

			_dataReal = 0;
			_dataDecimal = 0;
			_dataPow = 1;
			_isNegative = false;
			_isDecimalStage = false;
		}
	}
}
#endif