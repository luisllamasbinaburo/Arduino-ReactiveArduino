/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEOBSERVABLEINTERVALMICROS_h
#define _REACTIVEOBSERVABLEINTERVALMICROS_h

template <typename T>
class ObservableIntervalMicros : public Observable<unsigned long>
{
public:
	ObservableIntervalMicros(unsigned long microsInterval, unsigned long delay = 0);
	void Subscribe(IObserver<T> &observer) override;
	void UnSubscribe(IObserver<T> &observer) override;

	void Start();
	void Reset() override;
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

	ObserverList<T> _childObservers;
};

template <typename T>
ObservableIntervalMicros<T>::ObservableIntervalMicros(unsigned long interval, unsigned long delay)
{
	_isActive = true;
	_delay = delay;
	_offset = delay;
	_interval = interval;
	_startTime = micros();
}

template <typename T>
void ObservableIntervalMicros<T>::Subscribe(IObserver<T> &observer)
{
	this->_childObservers.Add(&observer);
}

template <typename T>
void ObservableIntervalMicros<T>::UnSubscribe(IObserver<T> &observer)
{
	this->_childObservers.Remove(&observer);
}

template <typename T>
void ObservableIntervalMicros<T>::Update()
{
	if (_isActive == false) return;

	auto elapsed = static_cast<unsigned long>(micros() - _startTime);
	if (elapsed >= _interval + _offset)
	{
		this->_childObservers.OnNext(elapsed);
		_startTime = micros();
		_offset = 0;
	}
}

template <typename T>
void ObservableIntervalMicros<T>::Reset()
{
	_isActive = true;
	_offset = _delay;
	_startTime = micros();
}


template <typename T>
void ObservableIntervalMicros<T>::Start()
{
	Reset();
	_isActive = true;
}

template <typename T>
void ObservableIntervalMicros<T>::Stop()
{
	_isActive = false;
}

template <typename T>
void ObservableIntervalMicros<T>::SetInterval(unsigned long interval)
{
	_interval = interval;
}

template <typename T>
unsigned long ObservableIntervalMicros<T>::GetStartTime()
{
	return _startTime;
}

template <typename T>
unsigned long ObservableIntervalMicros<T>::GetElapsedTime()
{
	return micros() - _startTime;
}

template <typename T>
unsigned long ObservableIntervalMicros<T>::GetRemainingTime()
{
	return _interval - micros() + _startTime;
}

template <typename T>
bool ObservableIntervalMicros<T>::IsActive() const
{
	return _isActive;
}

#endif