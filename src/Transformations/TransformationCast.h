/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVETRANSFORMATIONCAST_h
#define _REACTIVETRANSFORMATIONCAST_h

template <typename Torig, typename Tdest>
class TransformationCast : public Operator<Torig, Tdest>
{
public:
	TransformationCast<Torig, Tdest>();

	void OnNext(Torig value) override;
};

template <typename Torig, typename Tdest>
TransformationCast<Torig, Tdest>::TransformationCast()
{
}

template<typename Torig, typename Tdest>
void TransformationCast<Torig, Tdest>::OnNext(Torig value)
{
	this->_childObserver->OnNext((Tdest)(value));
}
#endif