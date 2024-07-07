/*
 * @Author       : TZU-CHIEH, HSU
 * @Mail         : j.k96013@gmail.com
 * @Department   : ECIE Lab, NTUT
 * @Date         : 2024-06-27 16:07:52
 * @LastEditTime : 2024-07-07 13:06:51
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
	receiver.begin(Serial2,200);
	receiver.setOnReceiveCallback(onReceive, this);

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

	Serial2.println("AT+TRACKINFO");
	Serial2.println("AT+TRACKSTAT");
	
	
	

	runTimer.setTimeOutTime(1000);
}

void BluetoothAudio::loop()
{
    // at.communicate();
    serial_relay();
	receiver.run();
	if (runTimer.hasTimedOut())
	{
		runTimer.reset();
		_run();
	}


}

String BluetoothAudio::getTrackTitle()
{
    return trackTitle;
}

String BluetoothAudio::getTrackArtist()
{
    return trackArtist;
}

String BluetoothAudio::getTrackAblum()
{
    return trackAblum;
}

int BluetoothAudio::getTrackTotalTime()
{
    return trackTotalTime;
}

int BluetoothAudio::getTrackElapsedTime()
{
    return trackElapsedTime;
}

float BluetoothAudio::getTrackProgress()
{
    return (float)trackElapsedTime / (float)trackTotalTime;
}

void BluetoothAudio::_run()
{
    Serial2.println("AT+TRACKINFO");
	Serial2.println("AT+TRACKSTAT");
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

}

void BluetoothAudio::parseCommand(String &response)
{
	// +TRACKSTAT=1,55395,195141
	// +PLAYSTAT=2
	// +TRACKINFO=Anne-Marie - 2002 [Official Video]Anne-Marie
	// 
	
	if (response.indexOf('+') != 0)
		return;

	int splitMarkIndex = response.indexOf('=');
	if (splitMarkIndex == -1)
		return;

	String header = response.substring(1, splitMarkIndex); 
	String data = response.substring(splitMarkIndex + 1);
		
	// Serial.print("Header = ");
	// Serial.println(header);
	// Serial.print("data = ");
	// Serial.println(data);
	
	
	if (header == "PLAYSTAT") {
		// Format: +PLAYSTAT=Param
		// Param:(0~4)
		// (0) Stopped
		// (1) Playing
		// (2) Paused
		// (3) Fast Forwarding
		// (4) Fast Rewinding

		playState = (BluetoothAudioPlayState)data.toInt();
    }
	else if (header == "TRACKSTAT") {
		// Format: +TRACKSTAT=Param1, Param2, Param3
		// Param1:(0~4), Media Player State
		// Param2:( Decimal ASCII), Elapsed time of current track in second
		// Param3:( Decimal ASCII), Total time of current track in second

		int firstComma = data.indexOf(',');
		int secondComma = data.indexOf(',', firstComma + 1);
		if (firstComma == -1 || secondComma == -1)
			return;
      	playState = (BluetoothAudioPlayState)data.substring(0, firstComma).toInt();;
		trackElapsedTime = data.substring(firstComma + 1, secondComma).toInt();;
		trackTotalTime = data.substring(secondComma + 1).toInt();

		// Serial.println("===== TRACKSTAT =====");
		// Serial.print("playState = ");
		// Serial.println((int)playState);
		// Serial.print("trackElapsedTime = ");
		// Serial.println(trackElapsedTime);
		// Serial.print("trackTotalTime = ");
		// Serial.println(trackTotalTime);
		// Serial.println("=================");
		
    }

	else if (header == "TRACKINFO")
	{
		// Format: +TRACKINFO=Param1 <FF> Param2 <FF> Param3
		// Param1: title
		// Param2: artist
		// Param3: ablum

		int firstSign = data.indexOf((char)0xFF);
		int secondSign = data.indexOf((char)0xFF, firstSign + 1);
		// Serial.print("First Sign = ");
		// Serial.println(firstSign);
		// Serial.print("Sec Sign = ");
		// Serial.println(secondSign);
		
		if (firstSign == -1)
			return;

		if (secondSign == -1)
		{
			secondSign = data.length();
		}
      	trackTitle = data.substring(0, firstSign);
		trackArtist = data.substring(firstSign + 1, secondSign);
		trackAblum = data.substring(secondSign + 1);
		// Serial.println("===== TITLE =====");
		// Serial.print("trackTitle = ");
		// Serial.println(trackTitle);
		// Serial.print("trackArtist = ");
		// Serial.println(trackArtist);
		// Serial.print("trackAblum = ");
		// Serial.println(trackAblum);
		// Serial.println("=================");
	}
}

void BluetoothAudio::onReceive(void *arg, String &payload)
{
	BluetoothAudio *_this = (BluetoothAudio *)arg;
	// Serial.print("RECV >> ");
	// Serial.println(payload);
	_this->parseCommand(payload);

}
