//#pragma var_model(mem)
//#pragma zp_reserve(0x91, 0x99, 0xa0, 0xa1, 0xa2, 0xc0, 0xc5, 0xc6, 0xcb, 0xcc )

#include <6502.h>
#include <c64.h>
#include <stdio.h>
#include <conio.h>

#define RAND_MAX 24
#define UP = (char)(87)
#define LEFT = (char)(65)
#define RIGHT = (char)(68)
#define DOWN = (char)(83)


int i, j, gameover = 0;
int height = 24;
int width = 39;
int x, y, fruitx, fruity;
unsigned int seed = 12345;

// Show the currently pressed key
int main(void) {
    VICII->MEMORY = toD018(DEFAULT_SCREEN, DEFAULT_FONT_MIXED);
    clrscr();
    rand_init();
    fruits();
    draw();
    char ch = GETIN();
//    for(i=0;i<255;i++){printf("%d\n", rand_asm());}
    for(;;){}
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

void fruits()
{
    x = 12;
    y = 12;
    fruitsx:
        fruitx = rand_asm();
        while(fruitx <= 2 || fruitx >= x-2){
            fruitx = rand_asm();
        }

    fruitsy:
        fruity = rand_asm();
        while (fruity <= 2 || fruity >= y-2){
            fruity = rand_asm();
        }
}

void draw(){
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
                else if (i == fruitx && j == fruity)
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