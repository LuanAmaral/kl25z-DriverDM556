/*
 * DM556.cpp
 *
 *  Created on: 9 de dez de 2020
 *      Author: servidor-pd
 */

#include <DM556.h>

//DM556::DM556(GPIO_Type* _pulPort, uint32_t _pulPin, GPIO_Type* _dirPort, uint32_t _dirPin, GPIO_Type* _enaPort, uint32_t _enaPin) {
//	// TODO Auto-generated constructor stub
//	pulPort = _pulPort;
//	pulPin  = _pulPin;
//	dirPort = _dirPort;
//	dirPin  = _dirPin;
//	enaPort = _enaPort;
//	enaPin  = _enaPin;
//
//	gpio_pin_config_t output ={kGPIO_DigitalOutput,1,};
//
//	GPIO_PinInit(pulPort, pulPin, &output);
//	GPIO_PinInit(dirPort, dirPin, &output);
//	GPIO_PinInit(enaPort, enaPin, &output);
//
//}

DM556::DM556(GPIO_Type* _pulPort, uint32_t _pulPin, GPIO_Type* _dirPort, uint32_t _dirPin) {
	// TODO Auto-generated constructor stub
	pulPort = _pulPort;
	pulPin  = _pulPin;
	dirPort = _dirPort;
	dirPin  = _dirPin;
	enaPin  = 0;

	gpio_pin_config_t output ={kGPIO_DigitalOutput,1,};

	GPIO_PinInit(pulPort, pulPin, &output);
	GPIO_PinInit(dirPort, dirPin, &output);
}

DM556::~DM556() {
	// TODO Auto-generated destructor stub
}


void DM556::set_configurations(int _angPorPulso){
    angPorPulse = _angPorPulso;
}

void DM556::spin(float angle){
	if(angle < 0){
		inverse_spin(angle);
		return;;
	}
	direct_spin(angle);
}

void DM556::direct_spin(int angle){
	if(enaPin != 0){
		GPIO_ClearPinsOutput(enaPort, 1u<<enaPin);
	}
	GPIO_ClearPinsOutput(dirPort, 1u<<dirPin);
	int pulse = (int)(angle / angPorPulse );
	printf("\n\r%d", angle);
	for(int i =0; i< 2*pulse; i++){
		GPIO_TogglePinsOutput(pulPort, 1u<<pulPin);
		delay((uint32_t)3); //us
	}
	if(enaPin != 0){
		GPIO_SetPinsOutput(enaPort, 1u<<enaPin);
	}

}

void DM556::inverse_spin(float angle){
	if(enaPin != 0){
		GPIO_ClearPinsOutput(enaPort, 1u<<enaPin);
	}
	GPIO_ClearPinsOutput(dirPort, 1u<<dirPin);
	int pulse = (int)(angle / angPorPulse );
	for(int i =0; i< 2*pulse; i++){
		GPIO_TogglePinsOutput(pulPort, 1u<<pulPin);
		delay((uint32_t)3); //us
	}
	if(enaPin != 0){
		GPIO_SetPinsOutput(enaPort, 1u<<enaPin);
	}
}

void DM556::delay(uint32_t usec){
	PIT_SetTimerPeriod(PIT,kPIT_Chnl_1 , USEC_TO_COUNT(usec,CLOCK_GetBusClkFreq()));
	PIT_StartTimer(PIT, kPIT_Chnl_1);
	while(PIT_GetStatusFlags(PIT, kPIT_Chnl_1) != kPIT_TimerFlag);
	PIT_StopTimer(PIT, kPIT_Chnl_1);
	PIT_ClearStatusFlags(PIT, kPIT_Chnl_1 , kPIT_TimerFlag);
}
































