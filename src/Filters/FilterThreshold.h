/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _FILTERTHRESHOLD_h
#define _FILTERTHRESHOLD_h

template <typename T>
class FilterThreshold : public Operator<T, bool>
{
public:
	FilterThreshold<T>(T threshold) : FilterThreshold<T>(threshold, threshold, false) {}
	FilterThreshold<T>(T threshold, bool state) : FilterThreshold<T>(threshold, threshold, state) {}
	FilterThreshold<T>(T lowThreshold, T highThreshold) : FilterThreshold<T>(lowThreshold, highThreshold, false) {}
	FilterThreshold<T>(T lowThreshold, T highThreshold, bool state);

	void OnNext(T value);
	//void OnComplete();

private:
	T FallThreshold;
	T RiseThreshold;
	bool _state;
};

template<typename T>
FilterThreshold<T>::FilterThreshold(T threshold1, T threshold2, bool state)
{
	FallThreshold = threshold1 <= threshold2 ? threshold1 : threshold2;
	RiseThreshold = threshold1 > threshold2 ? threshold1 : threshold2;
	_state = state;
}

template <typename T>
void FilterThreshold<T>::OnNext(T value)
{
	if (_state == false && value > RiseThreshold)
	{
		_state = true;
		if (this->_childObserver != nullptr) this->_childObserver->OnNext(_state);
	}

	if (_state == true && value < FallThreshold)
	{
		_state = false;
		if (this->_childObserver != nullptr) this->_childObserver->OnNext(_state);
	}
}
#endif

