#ifndef _VAR_SETTINGS_H
#define _VAR_SETTINGS_H

// 设置参数


// 滴的最长时长，单位毫秒
int s_u_time = 110;
// 防止抖动的忽略时间，少于这个时间的按压会忽略。单位：毫秒
int s_shake_time = 30;
// 播放电码的单位时长
int s_play_u_time = 120;
// 蜂鸣器频率
int s_bee_freq = 1800;
// 电键类型
// true 手动建
// false 自动键
bool s_key_type = false;
// 按键方向
// true 左嘀，右嗒； false 反向
bool s_auto_key_type = false;
// 是否自动发送
bool s_auto_send = false;
// 自动发送电码的间隔时长
int s_auto_send_time = 2000;
// 字母间隔时长
int s_split_time = 300;

// 是否启用触摸电键
bool s_touch_key = true;

// 触摸阈值
int s_touch_val = 1;


// 字母，单词间隔时间变量
unsigned long cs_time = 0;

// 检查空格标识
bool flag_space = false;
// 空格次数
bool flag_space_times = true;
// 是否检查发送
bool flag_send = false;
// 单词敲击的记录开始符号
bool flag_rcd = false;




#endif