/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEOBSERVERSERIAL_h
#define _REACTIVEOBSERVERSERIAL_h

template <typename T>
class ObserverSerial : public IObserver<T>
{
public:


private:
	void OnNext(T value) override;
	void OnComplete() override;
};

template <typename T>
void ObserverSerial<T>::OnNext(T value)
{
	Serial.println((T)value);
}

template <typename T>
void ObserverSerial<T>::OnComplete()
{
}

#endif