/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/
 
#include "ReactiveArduinoLib.h"
using namespace Reactive;

int values[] = { 0, 1, 4, 6, 2, 5, 7, 3, 5, 8 };
int valuesLength = sizeof(values) / sizeof(values[0]);

void setup()
{
	Serial.begin(115200);
	while (!Serial) delay(1);
}

void loop()
{
	FromArray(values, valuesLength)
	.Cast<float>()
	.Median5()
	.MovingAverage(4)
	.DoAndFinally(
		[](float x) { Serial.println(x); },
		[]() { Serial.println("No more items"); }
	);

	delay(2000);
}