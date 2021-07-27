/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEOBSERVABLETIMERMILLIS_h
#define _REACTIVEOBSERVABLETIMERMILLIS_h

template <typename T>
class ObservableTimerMillis : public Observable<unsigned long>
{
public:
	ObservableTimerMillis(unsigned long microsInterval, unsigned long delay = 0);
	void Suscribe(IObserver<T> &observer) override;

	void Start();
	void Reset() override;
	void Stop();
	void Update();

	void SetInterval(unsigned long interval);

	unsigned long GetStartTime() const;
	unsigned long GetElapsedTime() const;
	unsigned long GetRemainingTime() const;

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
ObservableTimerMillis<T>::ObservableTimerMillis(unsigned long interval, unsigned long delay)
{
	this->_isActive = true;
	this->_delay = delay;
	this->_offset = delay;
	this->_interval = interval;
	this->_startTime = millis();
}

template <typename T>
void ObservableTimerMillis<T>::Suscribe(IObserver<T> &observer)
{
	_childObserver = &observer;
}

template <typename T>
void ObservableTimerMillis<T>::Update()
{
	if (_isActive == false) return;

	auto elapsed = static_cast<unsigned long>(millis() - _startTime);
	if (elapsed >= _interval + _offset)
	{
		if (_childObserver != nullptr) _childObserver->OnNext(elapsed);
			_offset = 0;
	}
}

template <typename T>
void ObservableTimerMillis<T>::Reset()
{
	this->_isActive = true;
	this->_offset = this->_delay;
	this->_startTime = millis();
}


template <typename T>
void ObservableTimerMillis<T>::Start()
{
	Reset();
	_isActive = true;
}

template <typename T>
void ObservableTimerMillis<T>::Stop()
{
	_isActive = false;
}

template <typename T>
void ObservableTimerMillis<T>::SetInterval(unsigned long interval)
{
	_interval = interval;
}

template <typename T>
unsigned long ObservableTimerMillis<T>::GetStartTime() const
{
	return _startTime;
}

template <typename T>
unsigned long ObservableTimerMillis<T>::GetElapsedTime() const
{
	return millis() - _startTime;
}

template <typename T>
unsigned long ObservableTimerMillis<T>::GetRemainingTime() const
{
	return _interval - millis() + _startTime;
}

template <typename T>
bool ObservableTimerMillis<T>::IsActive() const
{
	return _isActive;
}

#endif
