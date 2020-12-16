/*
 * DM556.h
 *
 *  Created on: 9 de dez de 2020
 *      Author: servidor-pd
 */

#ifndef DM556_H_
#define DM556_H_

#include "fsl_debug_console.h"
#include "MKL25Z4.h"
#include "fsl_gpio.h"
#include "fsl_pit.h"


#define HIGH 1
#define LOW  0

class DM556 {
public:
	DM556(GPIO_Type* _pulPort, uint32_t _pulPin, GPIO_Type* _dirPort, uint32_t _dirPin, GPIO_Type* _enaPort, uint32_t _enaPin);
	DM556(GPIO_Type* _pulPort, uint32_t _pulPin, GPIO_Type* _dirPort, uint32_t _dirPin);
	void set_configurations(int _angPorPulso);
	void direct_spin(int angle);
	void inverse_spin(float angle);
	void spin(float angle);

	virtual ~DM556();

private:
	  float angPorPulse = 1;
	  GPIO_Type* pulPort ;
	  uint32_t pulPin = 1;
	  GPIO_Type* dirPort ;
	  uint32_t dirPin = 2;
	  GPIO_Type* enaPort ;
	  uint32_t enaPin = 3;
	void   delay(uint32_t usec);
};

#endif /* DM556_H_ */
