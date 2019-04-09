/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _FILTERLIMIT_h
#define _FILTERLIMIT_h

template <typename T>
class FilterUpperLimit : public Operator<T, T>
{
public:
	FilterUpperLimit<T>(T upperLimit);

	void OnNext(T value);

private:
	T _upperLimit;
};

template <typename T>
FilterUpperLimit<T>::FilterUpperLimit(T upperLimit)
{
	_upperLimit = upperLimit;
}

template <typename T>
inline void FilterUpperLimit<T>::OnNext(T value)
{
	this->_childObserver->OnNext(value > _upperLimit ? _upperLimit : value);
}



template <typename T>
class FilterLowerLimit : public Operator<T, T>
{
public:
	FilterLowerLimit<T>(T lowerLimit);

	void OnNext(T value);

private:
	T _lowerLimit;
};

template <typename T>
FilterLowerLimit<T>::FilterLowerLimit(T lowerLimit)
{
	_lowerLimit = lowerLimit;
}

template <typename T>
inline void FilterLowerLimit<T>::OnNext(T value)
{
	this->_childObserver->OnNext(value < _lowerLimit ? _lowerLimit : value);
}


template <typename T>
class FilterLimit : public Operator<T, T>
{
public:
	FilterLimit<T>(T lowerLimit, T upperLimit);

	void OnNext(T value);

private:
	T _upperLimit;
	T _lowerLimit;
};

template <typename T>
FilterLimit<T>::FilterLimit(T lowerLimit, T upperLimit)
{
	_lowerLimit = lowerLimit;
	_upperLimit = upperLimit;
}

template <typename T>
inline void FilterLimit<T>::OnNext(T value)
{
	this->_childObserver->OnNext(value < _lowerLimit ? _lowerLimit : value > _upperLimit ? _upperLimit : value);
}

#endif

