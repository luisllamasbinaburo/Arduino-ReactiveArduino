/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#include "ReactiveArduinoLib.h"
// Write 10,20,30 in serial port and
// receive 20.00 + 40.00 + 60.00 + 20 + 40 + 60 + ...

auto obsString = Reactive::Property<String>();

void setup()
{
	Serial.begin(115200);
	while (!Serial) delay(1);

	obsString
		.Split(',')
		.Distinct()
		.ParseFloat()
		.Select<String>([](float x) {return String(x * 2); })
		.Join('+')
		.Last()
		.ToSerial();
}

void loop()
{		
	obsString = "10,20,30";
	delay(2500);
}