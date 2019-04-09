/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _ObservableTimerMicros_h
#define _ObservableTimerMicros_h

template <typename T>
class ObservableTimerMicros : public Observable<unsigned long>
{
public:
	ObservableTimerMicros(unsigned long microsInterval, unsigned long delay = 0);
	void Suscribe(IObserver<T> &observer);

	void Start();
	void Reset();
	void Stop();
	void Update();

	void SetInterval(unsigned long interval);

	unsigned long GetStartTime();
	unsigned long GetElapsedTime();
	unsigned long GetRemainingTime();

	bool IsActive() const;

private:
	bool _isActive;
	bool _isExpired;
	unsigned long _startTime;
	unsigned long _delay;
	unsigned long _offset;
	unsigned long _interval;

	IObserver<T>* _childObserver;
};

template <typename T>
inline ObservableTimerMicros<T>::ObservableTimerMicros(unsigned long interval, unsigned long delay = 0)
{
	this->__isActive = true;
	this->_delay = delay;
	this->_offset = delay;
	this->_interval = interval;
	this->_startTime = micros();
}

template <typename T>
void ObservableTimerMicros<T>::Suscribe(IObserver<T> &observer)
{
	_childObserver = &observer;
}

template <typename T>
void ObservableTimerMicros<T>::Update()
{
	if (_isActive == false) return false;

	auto elapsed = static_cast<unsigned long>(micros() - _startTime);
	if (elapsed >= _interval + _offset)
	{
		if (_childObserver != nullptr) _childObserver->OnNext(elapsed);
		_offset = 0;
	}
}

template <typename T>
void ObservableTimerMicros<T>::Reset()
{
	this->__isActive = true;
	this->_offset = delay;
	this->_startTime = micros();
}


template <typename T>
void ObservableTimerMicros<T>::Start()
{
	Reset();
	_isActive = true;
}

template <typename T>
void ObservableTimerMicros<T>::Stop()
{
	_isActive = false;
}

template <typename T>
void ObservableTimerMicros<T>::SetInterval(unsigned long interval)
{
	_interval = interval;
}

template <typename T>
unsigned long ObservableTimerMicros<T>::GetStartTime()
{
	return _startTime;
}

template <typename T>
unsigned long ObservableTimerMicros<T>::GetElapsedTime()
{
	return micros() - _startTime;
}

template <typename T>
unsigned long ObservableTimerMicros<T>::GetRemainingTime()
{
	return _interval - micros() + _startTime;
}

template <typename T>
bool ObservableTimerMicros<T>::IsActive() const
{
	return _isActive;
}
#endif