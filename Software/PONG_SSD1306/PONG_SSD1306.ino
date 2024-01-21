/*
  A simple Pong game.
  https://notabug.org/Maverick/WokwiPong
  
  Based on Arduino Pong by eholk
  https://github.com/eholk/Arduino-Pong
*/



#include "SSD1306.h"

#define UP_BUTTON 4
#define DOWN_BUTTON 12
 
const unsigned long PADDLE_RATE = 64;
const unsigned long BALL_RATE = 32;
const uint8_t PADDLE_HEIGHT = 10;
const uint8_t SCORE_LIMIT = 9;

SSD1306  display(0x3c, 21, 22);

bool game_over, win;

int player_score, mcu_score;
uint8_t ball_x = 53, ball_y = 26;
uint8_t ball_dir_x = 1, ball_dir_y = 1;

unsigned long ball_update;
unsigned long paddle_update;

const uint8_t MCU_X = 12;
uint8_t mcu_y = 16;

const uint8_t PLAYER_X = 115;
uint8_t player_y = 16;

void setup() 
{
    display.init();

    
    display.display();
    unsigned long start = millis();

    pinMode(UP_BUTTON, INPUT_PULLUP);
    pinMode(DOWN_BUTTON, INPUT_PULLUP);

    display.clear();
    drawCourt();

    while(millis() - start < 2000);

    display.display();

    ball_update = millis();
    paddle_update = ball_update;
    display.flipScreenVertically();
}


void loop(){

gamechpong();

}
void gamechpong() 
{
    bool update_needed = false;
    unsigned long time = millis();

    static bool up_state = false;
    static bool down_state = false;
    
    up_state |= (digitalRead(UP_BUTTON) == LOW);
    down_state |= (digitalRead(DOWN_BUTTON) == LOW);

    if(time > ball_update) 
    {
        uint8_t new_x = ball_x + ball_dir_x;
        uint8_t new_y = ball_y + ball_dir_y;

        // Check if we hit the vertical walls
        if(new_x == 0 || new_x == 127) 
        {
            ball_dir_x = -ball_dir_x;
            new_x += ball_dir_x + ball_dir_x;

            if (new_x < 64)
            {
                //player_scoreTone();
                player_score++;
            }
            else
            {
                //mcu_scoreTone();
                mcu_score++;
            }

            if (player_score == SCORE_LIMIT || mcu_score == SCORE_LIMIT)
            {
                win = player_score > mcu_score;
                game_over = true;
            }
        }

        // Check if we hit the horizontal walls.
        if(new_y == 0 || new_y == 53) 
        {
            //wallTone();
            ball_dir_y = -ball_dir_y;
            new_y += ball_dir_y + ball_dir_y;
        }

        // Check if we hit the CPU paddle
        if(new_x == MCU_X && new_y >= mcu_y && new_y <= mcu_y + PADDLE_HEIGHT) 
        {
            //mcuPaddleTone();
            ball_dir_x = -ball_dir_x;
            new_x += ball_dir_x + ball_dir_x;
        }

        // Check if we hit the player paddle
        if(new_x == PLAYER_X && new_y >= player_y && new_y <= player_y + PADDLE_HEIGHT)
        {
            //playerPaddleTone();
            ball_dir_x = -ball_dir_x;
            new_x += ball_dir_x + ball_dir_x;
        }

        //display.setPixel(ball_x, ball_y, BLACK);
        display.setColor(BLACK);
        display.setPixel(ball_x, ball_y);
        display.setColor(WHITE);
        //display.setPixel(new_x, new_y, WHITE);
        display.setPixel(new_x, new_y);
        ball_x = new_x;
        ball_y = new_y;

        ball_update += BALL_RATE;

        update_needed = true;
    }

    if(time > paddle_update) 
    {
        paddle_update += PADDLE_RATE;

        // CPU paddle
        //display.drawFastVLine(MCU_X, mcu_y, PADDLE_HEIGHT, BLACK);
        display.setColor(BLACK);
        display.drawVerticalLine(MCU_X, mcu_y, PADDLE_HEIGHT);
        const uint8_t half_paddle = PADDLE_HEIGHT >> 1;

        if(mcu_y + half_paddle > ball_y)
        {
            int8_t dir = ball_x > MCU_X ? -1 : 1;
            mcu_y += dir;
        }

        if(mcu_y + half_paddle < ball_y)
        {
            int8_t dir = ball_x > MCU_X ? 1 : -1;
            mcu_y += dir;
        }

        if(mcu_y < 1) 
        {
            mcu_y = 1;
        }

        if(mcu_y + PADDLE_HEIGHT > 53)
        {
            mcu_y = 53 - PADDLE_HEIGHT;
        }

        // Player paddle
        display.setColor(WHITE);
        display.drawVerticalLine(MCU_X, mcu_y, PADDLE_HEIGHT);
        //display.drawFastVLine(MCU_X, mcu_y, PADDLE_HEIGHT, WHITE);
        display.setColor(BLACK);
        display.drawVerticalLine(PLAYER_X, player_y, PADDLE_HEIGHT);
        //display.drawFastVLine(PLAYER_X, player_y, PADDLE_HEIGHT, BLACK);

        if(up_state) 
        {
            player_y -= 1;
        }

        if(down_state) 
        {
            player_y += 1;
        }

        up_state = down_state = false;

        if(player_y < 1) 
        {
            player_y = 1;
        }

        if(player_y + PADDLE_HEIGHT > 53) 
        {
            player_y = 53 - PADDLE_HEIGHT;
        }
        
        //display.drawFastVLine(PLAYER_X, player_y, PADDLE_HEIGHT, WHITE);
        display.setColor(WHITE);
        display.drawVerticalLine(PLAYER_X, player_y, PADDLE_HEIGHT);

        update_needed = true;
    }

    if(update_needed)
    {
        if (game_over)
        {
            const char* text = win ? "YOU WIN!!" : "YOU LOSE!";
            display.clear();
            display.drawString(40,28,text);
            //display.setCursor(40, 28);
            //display.print(text);
            display.display();

            delay(5000);

            display.clear();
            ball_x = 53;
            ball_y = 26;
            ball_dir_x = 1;
            ball_dir_y = 1;
            mcu_y = 16;
            player_y = 16;
            mcu_score = 0;
            player_score = 0;
            game_over = false;
            drawCourt();
        }
        
        //display.setColor(WHITE);
        display.drawString(0,54,String(mcu_score));
        //display.setCursor(0, 56);
        //display.print(mcu_score);
        display.drawString(122,54,String(player_score));
        //display.setCursor(122, 56);
        //display.print(player_score);
        display.display();
    }
}


void drawCourt() 
{   display.setColor(WHITE);
    display.drawRect(0, 0, 127, 55);
}