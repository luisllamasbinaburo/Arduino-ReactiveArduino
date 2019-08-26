/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _TOPROPERTY_h
#define _TOPROPERTY_h

template <typename T>
class ObserverProperty : public IObserver<T>
{
public:
	ObserverProperty(T & property);

	void OnNext(T value) override;
	void OnComplete() override;

private:
	T * _property;
};

template <typename T>
ObserverProperty<T>::ObserverProperty(T &property)
{
	this->_property = &property;
}

template <typename T>
void ObserverProperty<T>::OnNext(T value)
{
	*(this->_property) = value;
}

template <typename T>
void ObserverProperty<T>::OnComplete()
{
}

#endif