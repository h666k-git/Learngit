#include "AI8051u.h"

typedef unsigned char u8;
typedef unsigned int u16;

sbit BEEP_P50 = P5^0;

// 延时函数 (沿用你已验证的参数)
void DelayMs(unsigned int ms) {
    u16 i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 1200; j++); 
}

void main() {
    // 【已验证】关闭可能占用引脚的外设
    PWMB_BKR = 0x00; 
    PWMB_ENO = 0x00; 
    AUXR = 0x00;     

    // 【已验证】配置 P5.0 为强推挽输出
    P5M1 &= ~0x07; 
    P5M0 |= 0x07;  

    // 初始化引脚为高电平 (关闭蜂鸣器)
    BEEP_P50 = 1;

    while(1) {
        // === 救护车 "滴-嘟" 循环 ===
        
        // "滴" - 短促高音 (低电平触发)
        BEEP_P50 = 0;
        DelayMs(150);   // 发声时长
        BEEP_P50 = 1;
        DelayMs(80);    // 短间隔

        // "嘟" - 绵长低音 (低电平触发)
        BEEP_P50 = 0;
        DelayMs(300);   // 发声时长
        BEEP_P50 = 1;
        DelayMs(80);    // 短间隔

        // 组间停顿 (模拟真实救护车的节奏间隙)
        DelayMs(200);
    }
}