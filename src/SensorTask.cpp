/*
 * SensorTask.cpp
 *
 *  Created on: Jul 27, 2023
 *      Author: tobeh
 */


#include "SensorTask.h"
#include "lis3dh.h"
#include "../template/stm32facade.h"
#include "digitalinout.h"
using namespace Platform::BSP;

SensorTask::SensorTask(const char *const name, uint16_t stackDepth,
		osPriority priority, bool immidiateStart, osMessageQId _SensorMessageId) :
		PeriodicTaskBase(name, stackDepth, priority, 10, immidiateStart)
		,sensorMessageId(_SensorMessageId){
}

void SensorTask::m_task(){
	//GPIO Taster
	//Todo: pruefen ob pin passt.
	Platform::BSP::DigitalIn taster(Platform::BSP::STM32Facade::BaseBoard49);

	//LIS3DH beschleunigungssensorSpi(Platform::BSP::STM32Facade::instance(Platform::BSP::STM32Facade::SPI_Peripheral::UseSPI2), Platform::BSP::STM32Facade::BaseBoard28);
	int16_t x_ruhe;
	int16_t y_ruhe;
	int16_t z_ruhe;

	int16_t x;
	int16_t y;
	int16_t z;

	struct{
		int16_t x;
		int16_t y;
		int16_t z;
	}values;

	while(1){
		if(!taster.get()){
			//Setzen des Ruhepunkts
			//beschleunigungssensorSpi.raw(x_ruhe, y_ruhe, z_ruhe);
		}
		//if(beschleunigungssensorSpi.raw(x,y,z)){
			//Werte in RElation zum Ruhepunkt setzen und skallieren
			x=(x-x_ruhe)/20;
			y=(y-y_ruhe)/20;
			z=(z-z_ruhe)/20;

			values.x = x;
			values.y = y;
			values.z = z;
			//Daten an SD-Task senden
			//osMessagePut(sensorMessageId, values, 0);
		//}
	}
}



