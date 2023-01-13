/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

// will print 0 1 2 3 5 7  (moving average of 0 2 4 6 8 10)

#include "ReactiveArduinoLib.h"
using namespace Reactive;

auto obs = FromRangeDefer<int>(0, 10, 2);
auto filter = MovingAverage<int>(4);
auto observer = ToSerial<int>();

void setup()
{
	Serial.begin(115200);
	while (!Serial) delay(1);

	obs >> filter >> observer;

	delay(5000);
}

void loop() 
{	
	obs.Next();
}

