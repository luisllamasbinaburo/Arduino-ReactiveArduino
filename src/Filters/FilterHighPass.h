/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEFILTERHIGHPASS_h
#define _REACTIVEFILTERHIGHPASS_h

template <typename T>
class FilterHighPass : public Operator<T, T>
{
public:
	FilterHighPass<T>(double alpha);
	void OnNext(T value) override;

private:
	double _alpha;
	T _lowPassFilter = T();
	T _highPassFilter = T();
};

template<typename T>
FilterHighPass<T>::FilterHighPass(const double alpha)
{
	this->_alpha = alpha;
}

template <typename T>
void FilterHighPass<T>::OnNext(T value)
{
	this->_lowPassFilter = static_cast<T>(this->_alpha * value + (1 - this->_alpha) * this->_lowPassFilter);

	if (this->_childObserver != nullptr) this->_childObserver->OnNext(value - this->_lowPassFilter);
}

#endif