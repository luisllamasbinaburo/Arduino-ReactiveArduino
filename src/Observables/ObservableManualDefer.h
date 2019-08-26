/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEOBSERVABLEMANUAL_h
#define _REACTIVEOBSERVABLEMANUAL_h

template <typename T>
class ObservableManualDefer : public Observable<T>
{
public:
	ObservableManualDefer();
	void Suscribe(IObserver<T> &observer) override;
	void Next();
	void Reset() override;
	void Complete();

private:
	IObserver<T>* _childObserver;
};

template <typename T>
ObservableManualDefer<T>::ObservableManualDefer()
{
}

template <typename T>
void ObservableManualDefer<T>::Suscribe(IObserver<T> &observer)
{
	_childObserver = &observer;
}

template <typename T>
void ObservableManualDefer<T>::Next()
{
	if (_childObserver != nullptr) _childObserver->OnNext({});
}

template <typename T>
void ObservableManualDefer<T>::Complete()
{
	if (_childObserver != nullptr) _childObserver->OnComplete();
}

template <typename T>
void ObservableManualDefer<T>::Reset()
{
}

#endif