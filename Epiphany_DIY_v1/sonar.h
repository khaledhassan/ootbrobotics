/*
 * sonar.h
 *
 * Created: 9/7/2011 4:17:11 AM
 *  Author: Tim
 */ 


#ifndef SONAR_H_
#define SONAR_H_

#include <avr/io.h>
#include <asf.h>

#define numberOfSonar	2

struct Sonar
	{
		PORT_t		*sonarPort;
		uint8_t		sonarPin;
		uint16_t	rawTime; 
	}sonar[numberOfSonar],*currentSonarPtr;


void sonarAssignment(PORT_t *port, uint8_t pin, uint8_t sonarNumber);
void sonarInit();
void sonarEnable(struct Sonar *_sonar);
void disableAllSonar(void);



#endif /* SONAR_H_ */