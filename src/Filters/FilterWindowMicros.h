// FilterWindowsMicros.h

#ifndef _REACTIVEFILTERWINDOWSMICROS_h
#define _REACTIVEFILTERWINDOWSMICROS_h

template <typename T>
class FilterWindowMicros : public Operator<T, T>
{
public:
	FilterWindowMicros<T>(unsigned long interval);
	void OnNext(T value) override;

private:
	bool _started = false;
	unsigned long _interval;
	unsigned long _lastTrigger = 0;
};

template<typename T>
FilterWindowMicros<T>::FilterWindowMicros(const unsigned long interval)
{
	_interval = interval;
}

template <typename T>
void FilterWindowMicros<T>::OnNext(T value)
{
	if (!_started)
	{
		_lastTrigger = micros();
		_started = true;
	}
	if (_started && static_cast<unsigned long>(micros() - _lastTrigger) <= _interval)
	{
		if (this->_childObserver != nullptr) this->_childObserver->OnNext(value);
	}
}

#endif