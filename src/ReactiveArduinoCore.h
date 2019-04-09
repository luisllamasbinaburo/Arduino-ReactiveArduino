/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEARDUINOCORE_h
#define _REACTIVEARDUINOCORE_h

#include "ReactiveArduinoBases.h"

template <typename T>
class Observable : IObservable<T>, IResetable<T>
{
public:
	virtual void Suscribe(IObserver<T> &observer) = 0;

	void operator >> (IObserver<T> & obs)
	{
		Suscribe(obs);
	}
	
	template <typename Torig, typename Tdest>
	Observable<Tdest>& operator >> (Operator<Torig, Tdest>& op)
	{
		return Compound(*this, op);
	}

	template <typename Torig, typename Tdest>
	Observable<Tdest> &Compound(Observable<Torig> &obs, Operator<Torig, Tdest> &op)
	{
		op._parentObservable = this;
		return op;
	}

	virtual void Reset()
	{
	}
};


template <typename Torig, typename Tdest>
class Operator : public  IObserver<Torig>, public  Observable<Tdest>
{
public:
	Observable<Torig>* _parentObservable;
	IObserver<Tdest>* _childObserver;

	void Suscribe(IObserver<Tdest> & observer);

	virtual void OnNext(Torig value);
	virtual void OnComplete();

	void Reset();
private:
};
template <typename Torig, typename Tdest>
void Operator<Torig, Tdest>::Suscribe(IObserver<Tdest> &observer)
{
	this->_childObserver = &observer;
	_parentObservable->Suscribe(*this);
}


template <typename Torig, typename Tdest>
inline void Operator<Torig, Tdest>::OnNext(Torig value)
{
	//if (this->_childObserver != nullptr) this->_childObserver->OnNext(value);
	//if (this->_childObserver != nullptr) this->_childObserver->OnNext((Tdest)value);
}

template <typename Torig, typename Tdest>
inline void Operator<Torig, Tdest>::OnComplete()
{
	if (this->_childObserver != nullptr) this->_childObserver->OnComplete();
}

template<typename Torig, typename Tdest>
inline void Operator<Torig, Tdest>::Reset()
{
	if(_parentObservable != nullptr) _parentObservable->Reset();
}
#endif

