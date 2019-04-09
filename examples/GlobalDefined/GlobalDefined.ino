/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/
 
#include "ReactiveArduinoLib.h"

auto obs = Reactive::FromRangeDefer<int>(0, 10, 2);
auto filter = Reactive::MovingAverage<int>(4);
auto observer = Reactive::ToSerial<int>();

void setup()
{
	Serial.begin(9600);
	while (!Serial) delay(1);

	obs >> filter >> Reactive::ToSerial<int>();
}

void loop() 
{
	obs.Next();
}

