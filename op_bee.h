// ESP8266蜂鸣器控制
#ifndef _OP_BEE_H
#define _OP_BEE_H

void bee(bool s)
{
	s? ledcWriteTone(0, s_bee_freq): ledcWriteTone(0, 0);
}

#endif