//#pragma var_model(mem)
//#pragma zp_reserve(0x91, 0x99, 0xa0, 0xa1, 0xa2, 0xc0, 0xc5, 0xc6, 0xcb, 0xcc )

#include <6502.h>
#include <c64.h>
#include <c64-print.h>
#include <stdio.h>
#include <conio.h>


#define RAND_MAX 24
#define UP = (char)(87)
#define LEFT = (char)(65)
#define RIGHT = (char)(68)
#define DOWN = (char)(83)

char *fruit = "*";
int i, j, gameover = 0;
int height = 24;
int width = 39;
int x, y, fruit_x, fruit_y;
unsigned int seed = 12345;

// Show the currently pressed key
int main(void) {
    VICII->MEMORY = toD018(DEFAULT_SCREEN, DEFAULT_FONT_MIXED);
    clrscr();
    rand_init();
    drawFruit();
    //draw();
    char ch = GETIN();
//    for(i=0;i<255;i++){printf("%d\n", rand_asm());}
    for(;;){
    //clrscr();
    //sleep();
    //fruits();
    }
}

void rand_init(){
    asm{
        lda #$FF
        sta $D40E
        sta $D40F
        lda #$80
        sta $D412
    }
}

int rand_asm(){
    int num;
    asm{
        lda $D41B
        sta num
    }
    return num;
}

void drawFruit()
{

    fruit_x = rand_asm();
    while(fruit_x <= 2 || fruit_x >= width-2){
        fruit_x = rand_asm();
    }

    fruit_y = rand_asm();
    while (fruit_y <= 2 || fruit_y >= height-2){
        fruit_y = rand_asm();
    }

    print_str_at(fruit, "15");
}

void draw(){
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (i == x && j == y && x == fruit_x && y == fruit_y){
                printf("0");
                fruit();
            }
            else if (i == fruit_x && j == fruit_y)
                printf("*"); //fruit
            else
                printf(" ");
        }
        printf("\n");

    }
}

void drawInit(){
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (i == 0 || j == 0){
                printf(" ");
            }
            else if (i == 1 || i == height - 1 || j == 1 || j == width - 1) {
                printf("#");
            }
            else
            {
                if (i == x && j == y)
                    printf("0"); //snake
                else if (i == fruit_x && j == fruit_y)
                    printf("*"); //fruit
                else
                    printf(" ");
            }
        }
        printf("\n");

    }
}

void sleep(){
    for (int i; i<100; i++){for (int j; j<25; j++){}}
    return;
}

// GETIN. Read byte from default input. (If not keyboard, must call OPEN and CHKIN beforehands.)
// Return: next byte in buffer or 0 if buffer is empty.
char GETIN() {
    char ch;
    asm {
        jsr $ffe4
        sta ch
    }
    return ch;
}