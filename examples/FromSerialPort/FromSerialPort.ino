/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/
 
// Write 10,20,30 in serial port and
// recieve 20.00 + 40.00 + 60.00

auto observable = Reactive::FromSerialString();

void setup()
{
	Serial.begin(9600);
	while (!Serial) delay(1);

	observable
		>> Reactive::Split<String>(',')
		>> Reactive::Distinct<String>()
		>> Reactive::ParseFloat()
		>> Reactive::Map<float, String>([](float x) {return String(x * 2); })
		>> Reactive::Join<String>('+')
		>> Reactive::Last<String>()
		>> Reactive::ToSerial<String>();
}

void loop()
{
	observable.Recieve();
}
