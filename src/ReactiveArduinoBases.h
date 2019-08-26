/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEARDUINOBASES_h
#define _REACTIVEARDUINOBASES_h

using ReactiveCallback = void(*)();

template <typename T>
using ReactiveAction = void(*)(T);

template <typename T>
using ReactiveFunction = T(*)(T);

template <typename T>
using ReactiveCompound = T(*)(T, T);

template <typename Torig, typename Tdest>
using ReactiveMap = Tdest(*)(Torig);

template <typename T>
using ReactivePredicate = bool(*)(T);

template <typename T> class IObserver;
template <typename T> class Observable;
template <typename T1, typename T2> class Operator;

template <typename T>
class IObserver
{
public:
	virtual void OnNext(T value) = 0;
	virtual void OnComplete() = 0;

protected:
	virtual ~IObserver() = default;
};

template <typename T>
class IObservable
{
public:
	virtual void Suscribe(IObserver<T> &observer) = 0;

protected:
	virtual ~IObservable() = default;
};

template <typename T>
class IResetable
{
public:
	virtual void Reset() = 0;
	virtual ~IResetable() = default;

protected:
	bool _isComplete = false;
};
#endif