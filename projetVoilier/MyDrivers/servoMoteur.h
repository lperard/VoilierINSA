//driver for the rf receiver//

#ifndef SERVO_MOTEUR_H
#define SERVO_MOTEUR_H

/*
@brief : config TIMER1
@param : none
@return : none
*/
void initServoMoteur (void);

void enableServoMoteur(void);

void disableServoMoteur(void);

void setSailAngle (int angle) ;

void setAngleFromGirouette (int angle);
#endif
