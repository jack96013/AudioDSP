/*
 * @Author       : TZU-CHIEH, HSU
 * @Mail         : j.k96013@gmail.com
 * @Department   : ECIE Lab, NTUT
 * @Date         : 2024-06-27 16:07:52
 * @LastEditTime : 2024-06-30 22:58:58
 * @Description  : Bluetooth auido
 */

#include "BluetoothAudio.h"



BluetoothAudio::BluetoothAudio()
{
    //ctor
    this->runTimer = SoftTimer();
}


void BluetoothAudio::init()
{
	receiver.begin(&Serial2,200);

    // at.on(ATNotificationEvent::type, [](const Event *env) {
	// 	auto notification = (const ATNotificationEvent *)env;
	// 	Serial.printf("AT Notfication: \"%s\"\n", notification->content.c_str());
	// });

	// Serial.println("checking the connection:");

	// at.execute("AT")
	// 	->onSuccess([&](const String &result) {
	// 		bool echo = result.startsWith("OK");
	// 		Serial.print("Modem successfully respond and AT Echo is ");
	// 		Serial.println(echo ? "on, i'm going to turn it off!" : "off.");
	// 		if (echo) {
	// 			this->at.execute("ATE0")->freeOnFinish();
	// 		}
	// 	})
	// 	->onFail([](const std::exception &e) {
	// 		Serial.printf("Modem respond with error");
	// 	})
	// 	// ->freeOnFinish();

	
}

void BluetoothAudio::loop()
{
    // at.communicate();
    serial_relay();
	if (runTimer.hasTimedOut())
	{
		runTimer.reset();
		_run();
	}
}

void BluetoothAudio::_run()
{
    
}

void BluetoothAudio::serial_relay()
{

  char val;
  // 若收到「序列埠監控視窗」的資料，則送到藍牙模組
  if (Serial.available())
  {
    val = Serial.read();
    Serial2.print(val);
  }

  // 若收到藍牙模組的資料，則送到「序列埠監控視窗」
  if (Serial2.available())
  {
    val = Serial2.read();
    Serial.print(val);
  }
}

void BluetoothAudio::parseCommand()
{
	
}
