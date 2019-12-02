//driver for the moteur CC//

#ifndef MOTEUR_CC_H
#define MOTEUR_CC_H

void initMoteurCC (void);

void enableMoteurCC(void);

void disableMoteurCC(void);

void setBoardSpeed (int relativeSpeed) ;

void setBoardOrientation (int orientation);

void navigate (int speed, int orientation);

void movePlateau (float rm);

#endif
