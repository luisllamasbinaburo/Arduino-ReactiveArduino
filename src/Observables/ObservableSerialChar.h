/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEOBSERVABLESERIALCHAR_h
#define _REACTIVEOBSERVABLESERIALCHAR_h

template <>
class ObservableSerial<char> : public Observable<char>
{
public:
	ObservableSerial();
	void Subscribe(IObserver<char> &observer) override;
	void UnSubscribe(IObserver<char> &observer) override;
	void Receive();

private:
	ObserverList<char> _childObservers;
};

ObservableSerial<char>::ObservableSerial()
{
}

void ObservableSerial<char>::Subscribe(IObserver<char> &observer)
{
	_childObservers.Add(&observer);
}

void ObservableSerial<char>::UnSubscribe(IObserver<char> &observer)
{
	_childObservers.Remove(&observer);
}

void ObservableSerial<char>::Receive()
{
	while(Serial.available())
		_childObservers.Fire((char)Serial.read());
}

#endif