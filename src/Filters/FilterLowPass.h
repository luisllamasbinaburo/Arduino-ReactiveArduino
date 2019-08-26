/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEFILTERLOWPASS_h
#define _REACTIVEFILTERLOWPASS_h

template <typename T>
class FilterLowPass : public Operator<T, T>
{
public:
	FilterLowPass<T>(double alpha);
	void OnNext(T value) override;

private:
	double _alpha;
	T _lowPassFilter = T();
};

template<typename T>
FilterLowPass<T>::FilterLowPass(const double alpha)
{
	_alpha = alpha;
}

template <typename T>
void FilterLowPass<T>::OnNext(T value)
{
	_lowPassFilter = static_cast<T>(_alpha * value + (1 - _alpha) * _lowPassFilter);

	if (this->_childObserver != nullptr) this->_childObserver->OnNext(_lowPassFilter);
}

#endif