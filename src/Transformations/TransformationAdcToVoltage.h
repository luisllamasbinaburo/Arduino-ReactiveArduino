/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVETRANSFORMATIONADCTOVOLTAGE_h
#define _REACTIVETRANSFORMATIONADCTOVOLTAGE_h

template <typename T>
class TransformationAdcToVoltage : public Operator<T, float>
{
public:
	TransformationAdcToVoltage<T>(float input_max = 1023.0f, float output_max = 5.0f);

	void OnNext(T value) override;

private:
	float _input_max = 0.0f;
	float _output_max = 0.0f;
};

template <typename T>
TransformationAdcToVoltage<T>::TransformationAdcToVoltage(float input_max, float output_max)
{
	_input_max = input_max;
	_output_max = output_max;
}


template <typename T>
void TransformationAdcToVoltage<T>::OnNext(T value)
{
	this->_childObservers.OnNext((static_cast<float>(value) * _output_max) / _input_max);
}

#endif