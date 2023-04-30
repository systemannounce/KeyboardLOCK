#include <reg51.h>

#define ROWS 4
#define COLS 4

// 定义行和列的端口
sbit ROW1 = P1^0;
sbit ROW2 = P1^1;
sbit ROW3 = P1^2;
sbit ROW4 = P1^3;
sbit COL1 = P1^4;
sbit COL2 = P1^5;
sbit COL3 = P1^6;
sbit COL4 = P1^7;

// 定义键盘映射
unsigned char keymap[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};


// 初始化键盘函数
void init_keyboard() {
    // 将行设置为输出，列设置为输入
    ROW1 = ROW2 = ROW3 = ROW4 = 0;
    COL1 = COL2 = COL3 = COL4 = 1;
}

// 扫描键盘函数
unsigned char scan_keyboard() {
    unsigned char row, col;

    // 扫描每一行
    for (row = 0; row < ROWS; row++) {
        // 将当前行设置为低电平
        switch (row) {
            case 0: ROW1 = 0; break;
            case 1: ROW2 = 0; break;
            case 2: ROW3 = 0; break;
            case 3: ROW4 = 0; break;
        }

        // 检查每一列是否有按键按下
        for (col = 0; col < COLS; col++) {
            switch (col) {
                case 0: if (COL1 == 0) return keymap[row][col]; break;
                case 1: if (COL2 == 0) return keymap[row][col]; break;
                case 2: if (COL3 == 0) return keymap[row][col]; break;
                case 3: if (COL4 == 0) return keymap[row][col]; break;
            }
        }

        // 将当前行恢复为高电平
        switch (row) {
            case 0: ROW1 = 1; break;
            case 1: ROW2 = 1; break;
            case 2: ROW3 = 1; break;
            case 3: ROW4 = 1; break;
        }
    }

    // 没有按键按下
    return 0;
}


// void main() {
//     unsigned char key;

//     // 初始化键盘
//     init_keyboard();

//     while (1) {
//         // 扫描键盘
//         key = scan_keyboard();
//         if (key != 0) {
//             // 在此处处理按键事件
//             // ...
//         }
//     }
// }


