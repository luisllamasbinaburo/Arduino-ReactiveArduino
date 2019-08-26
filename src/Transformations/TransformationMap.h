/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVETRANSFORMATIONMAP_h
#define _REACTIVETRANSFORMATIONMAP_h

template <typename Torig, typename Tdest>
class TransformationMap : public Operator<Torig, Tdest>
{
public:
	ReactiveMap<Torig, Tdest> _map;

	TransformationMap<Torig, Tdest>(ReactiveMap<Torig, Tdest> map);

	void OnNext(Torig value) override;
};

template <typename Torig, typename Tdest>
TransformationMap<Torig, Tdest>::TransformationMap(ReactiveMap<Torig, Tdest> map)
{
	this->_map = map;
}

template<typename Torig, typename Tdest>
void TransformationMap<Torig, Tdest>::OnNext(Torig value)
{
	Tdest newValue = (Tdest)(this->_map(value));

	if (this->_childObserver != nullptr) this->_childObserver->OnNext(newValue);
}
#endif