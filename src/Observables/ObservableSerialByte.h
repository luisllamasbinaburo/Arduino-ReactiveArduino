/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEOBSERVABLESERIALBYTE_h
#define _REACTIVEOBSERVABLESERIALBYTE_h

template <>
class ObservableSerial<byte> : public Observable<byte>
{
public:
	ObservableSerial();
	void Subscribe(IObserver<byte> &observer);
	void Receive();

private:
	IObserver<byte>* _childObserver;
};

ObservableSerial<byte>::ObservableSerial()
{
}

void ObservableSerial<byte>::Subscribe(IObserver<byte> &observer)
{
	_childObserver = &observer;
}

void ObservableSerial<byte>::Receive()
{
	while (Serial.available())
	{
		byte newChar = Serial.read();
		if (_childObserver != nullptr) _childObserver->OnNext(newChar);
	}
}

#endif