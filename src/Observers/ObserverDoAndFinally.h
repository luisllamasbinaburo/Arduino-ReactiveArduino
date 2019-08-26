/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEOBSERVERDOANDFINALLY_h
#define _REACTIVEOBSERVERDOANDFINALLY_h

template <typename T>
class ObserverDoAndFinally : public IObserver<T>
{
public:
	ObserverDoAndFinally(ReactiveAction<T> doAction, ReactiveCallback finallyAction);

	void OnNext(T value) override;
	void OnComplete() override;

private:
	ReactiveAction<T> _doAction;
	ReactiveCallback _finallyAction;
};

template <typename T>
ObserverDoAndFinally<T>::ObserverDoAndFinally(ReactiveAction<T> doAction, ReactiveCallback finallyAction)
{
	_doAction = doAction;
	_finallyAction = finallyAction;
}

template <typename T>
void ObserverDoAndFinally<T>::OnNext(T value)
{
	_doAction(value);
}

template <typename T>
void ObserverDoAndFinally<T>::OnComplete()
{
	_finallyAction();
}

#endif