//driver for the girouette//

#ifndef CODEUR_INCR_H
#define CODEUR_INCR_H

	static int RESETVALUE = 0x011B; // 0x02D0 - 0x01B5

	void initTimerCodeur (void);
	void enableTimer3 (void);
	int getAngleGirouette(void);
	void setupCodeur(void);

#endif
