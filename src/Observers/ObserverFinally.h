/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEOBSERVERFINALLY_h
#define _REACTIVEOBSERVERFINALLY_h

template <typename T>
class ObserverFinally : public IObserver<T>
{
public:
	ObserverFinally(ReactiveCallback action);

	void OnNext(T value) override;
	void OnComplete() override;

private:
	ReactiveCallback _action;
};

template <typename T>
ObserverFinally<T>::ObserverFinally(ReactiveCallback action)
{
	_action = action;
}

template <typename T>
void ObserverFinally<T>::OnNext(T value)
{

}

template <typename T>
void ObserverFinally<T>::OnComplete()
{
	_action();
}

#endif