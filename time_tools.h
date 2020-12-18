#ifndef _TIME_TOOLS_H
#define _TIME_TOOLS_H


int tt(bool s) {
	if(s) {
		cs_time = millis();
		return 0;
	}
	else {
		return millis() - cs_time;
	}
}


#endif