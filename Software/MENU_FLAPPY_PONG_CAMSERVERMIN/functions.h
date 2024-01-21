#include "SSD1306.h"
////////////////////////
#include "esp_camera.h"
#include <WiFi.h>
#include "esp_timer.h"
#include "img_converters.h"
#include "Arduino.h"
#include "fb_gfx.h"
#include "soc/soc.h" //disable brownout problems
#include "soc/rtc_cntl_reg.h"  //disable brownout problems
#include "esp_http_server.h"
///////////////////////////////////////
#define SCREEN_SDA 15
#define SCREEN_SCL 14

SSD1306  display(0x3c, SCREEN_SDA, SCREEN_SCL);

////////////////////////////////////////////////////////////////////////

// Replace with your network credentials

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* ssid     = "ESP32-Access-Point";
const char* password = "123456789";

#define PART_BOUNDARY "123456789000000000000987654321"


#define CAMERA_MODEL_AI_THINKER


#if defined(CAMERA_MODEL_AI_THINKER)
  #define PWDN_GPIO_NUM     32
  #define RESET_GPIO_NUM    -1
  #define XCLK_GPIO_NUM      0
  #define SIOD_GPIO_NUM     26
  #define SIOC_GPIO_NUM     27
  #define Y9_GPIO_NUM       35
  #define Y8_GPIO_NUM       34
  #define Y7_GPIO_NUM       39
  #define Y6_GPIO_NUM       36
  #define Y5_GPIO_NUM       21
  #define Y4_GPIO_NUM       19
  #define Y3_GPIO_NUM       18
  #define Y2_GPIO_NUM        5
  #define VSYNC_GPIO_NUM    25
  #define HREF_GPIO_NUM     23
  #define PCLK_GPIO_NUM     22
#else
  #error "Camera model not selected"
#endif

static const char* _STREAM_CONTENT_TYPE = "multipart/x-mixed-replace;boundary=" PART_BOUNDARY;
static const char* _STREAM_BOUNDARY = "\r\n--" PART_BOUNDARY "\r\n";
static const char* _STREAM_PART = "Content-Type: image/jpeg\r\nContent-Length: %u\r\n\r\n";

httpd_handle_t stream_httpd = NULL;

//////////////////////////////////////////////////////////////////////////////////////////////////

#define DEMO_DURATION 3000
typedef void (*Demo)(void);

float zidx[4];
int prazan[4];
int razmak=32;
int sirinaProlaza=30;


int score=0;
int stis=0;
float fx=30.00;
float fy=22.00;
int smjer=0;
unsigned long trenutno=0;

int igra=0;
int frame=0;
int sviraj=0;
unsigned long ton=0;
///////////////////////////////////////////////////////////////////////////////
bool game_over, win;

uint8_t player_score, mcu_score;
uint8_t ball_x = 53, ball_y = 26;
uint8_t ball_dir_x = 1, ball_dir_y = 1;

unsigned long ball_update;
unsigned long paddle_update;

const uint8_t MCU_X = 12;
uint8_t mcu_y = 16;

const uint8_t PLAYER_X = 115;
uint8_t player_y = 16;
//////////////////////////////////////////////////////////////////////////////
#define UP_BUTTON 13
#define DOWN_BUTTON 12
 
const unsigned long PADDLE_RATE = 64;
const unsigned long BALL_RATE = 32;
const uint8_t PADDLE_HEIGHT = 12;
const uint8_t SCORE_LIMIT = 9;
/////////////////////////////////////////////////////////////////////////



























void drawCourt() 
{   display.setColor(WHITE);
    display.drawRect(0, 0, 127, 55);
}
/////////////////////////////////////////////////////////////////
static esp_err_t stream_handler(httpd_req_t *req){
  camera_fb_t * fb = NULL;
  esp_err_t res = ESP_OK;
  size_t _jpg_buf_len = 0;
  uint8_t * _jpg_buf = NULL;
  char * part_buf[64];

  res = httpd_resp_set_type(req, _STREAM_CONTENT_TYPE);
  if(res != ESP_OK){
    return res;
  }

  while(true){
    fb = esp_camera_fb_get();
    if (!fb) {
      Serial.println("Camera capture failed");
      res = ESP_FAIL;
    } else {
      if(fb->width > 400){
        if(fb->format != PIXFORMAT_JPEG){
          bool jpeg_converted = frame2jpg(fb, 80, &_jpg_buf, &_jpg_buf_len);
          esp_camera_fb_return(fb);
          fb = NULL;
          if(!jpeg_converted){
            Serial.println("JPEG compression failed");
            res = ESP_FAIL;
          }
        } else {
          _jpg_buf_len = fb->len;
          _jpg_buf = fb->buf;
        }
      }
    }
    if(res == ESP_OK){
      size_t hlen = snprintf((char *)part_buf, 64, _STREAM_PART, _jpg_buf_len);
      res = httpd_resp_send_chunk(req, (const char *)part_buf, hlen);
    }
    if(res == ESP_OK){
      res = httpd_resp_send_chunk(req, (const char *)_jpg_buf, _jpg_buf_len);
    }
    if(res == ESP_OK){
      res = httpd_resp_send_chunk(req, _STREAM_BOUNDARY, strlen(_STREAM_BOUNDARY));
    }
    if(fb){
      esp_camera_fb_return(fb);
      fb = NULL;
      _jpg_buf = NULL;
    } else if(_jpg_buf){
      free(_jpg_buf);
      _jpg_buf = NULL;
    }
    if(res != ESP_OK){
      break;
    }
    //Serial.printf("MJPG: %uB\n",(uint32_t)(_jpg_buf_len));
  }
  return res;
}
/////////////////////////////////////////////////////////////////
void startCameraServer(){
  httpd_config_t config = HTTPD_DEFAULT_CONFIG();
  config.server_port = 80;

  httpd_uri_t index_uri = {
    .uri       = "/",
    .method    = HTTP_GET,
    .handler   = stream_handler,
    .user_ctx  = NULL
  };
  
  //Serial.printf("Starting web server on port: '%d'\n", config.server_port);
  if (httpd_start(&stream_httpd, &config) == ESP_OK) {
    httpd_register_uri_handler(stream_httpd, &index_uri);
  }
}
/////////////////////////////////////////////////////////////////////

void gamechflap() {

   display.clear();

   if(igra==0)
   {
    display.setFont(ArialMT_Plain_16);
    //display.setFont(&FreeMonoBoldOblique12pt7b);
    display.drawString(0,4,"Flappy ");
    //display.setCursor(0,4);
    //display.print(Flappy );

   display.drawXbm(0, 0, 128, 64, pozadina);
   display.drawXbm(20, 32, 14, 9, ptica);

   display.setFont(ArialMT_Plain_10);
   display.drawString(0,44,"press to start");
  //  display.setFont(&FreeMonoBoldOblique12pt7b);
  //  display.setCursor(0,44);
  //  display.print(press to start);

   /////starts the game///////
    if(digitalRead(13)==0)
    igra=1;
    }

   if(igra==1)
   {
   display.setFont(ArialMT_Plain_10);
   //display.setFont(&FreeMonoBoldOblique12pt7b);
   display.drawString(3,0,String(score));
  //  display.setCursor(3,0);
  //  display.print(score);



   if(digitalRead(13)==0)
   {
    if(stis==0)
      {
        trenutno=millis();
        smjer=1;
        sviraj=1;
        stis=1;
        ton=millis();
       
        }
    
    }else{stis=0;}

   
    for(int j=0;j<4;j++){
       display.setColor(WHITE);
    display.fillRect(zidx[j],0,6,64);
     display.setColor(BLACK);
      display.fillRect(zidx[j],prazan[j],6,sirinaProlaza);
   
    }

  display.setColor(WHITE);
 //  display.fillCircle(fx, fy, 4); // igrac
  display.drawXbm(fx, fy, 14, 9, ptica);
  
    for(int j=0;j<4;j++)
    {
    zidx[j]=zidx[j]-0.01;
    if(zidx[j]<-7){
      score=score+1;
      
      
       digitalWrite(23,1);
      prazan[j]=random(8,32);
     
    zidx[j]=128;
    }
    }
  if((trenutno+185)<millis())
  smjer=0;

    if((ton+40)<millis())
  sviraj=0;

if(smjer==0)
 fy=fy+0.01;
else
 fy=fy-0.03;


 if(sviraj==1)
 digitalWrite(23,1);
 else
 digitalWrite(23,0);

if(fy>63 || fy<0){
igra=0;
fy=22;
score=0;
 digitalWrite(23,1);
  delay(500);
   digitalWrite(23,0); 
for(int i=0;i<4;i++)
  {
    zidx[i]=128+((i+1)*razmak);
    {prazan[i]=random(4,30);}
    }
}

for(int m=0;m<4;m++)
if(zidx[m]<=fx+7 && fx+7<=zidx[m]+6)
{
  
 
  if(fy<prazan[m] || fy+8>prazan[m]+sirinaProlaza){
  igra=0;
  fy=22;
  score=0;
  digitalWrite(23,1);
  delay(500);
   digitalWrite(23,0);
  for(int i=0;i<4;i++)
  {
    zidx[i]=128+((i+1)*razmak);
    {prazan[i]=random(8,32);}
    }
  }}
   display.drawRect(0,0,128,64);
   }
  
   display.display();

}



////////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////

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
////////////////////////////////////////////////////////////////////////////////////////////
void WIFIAP(){
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("Camera Stream Ready! Connect to the ESP32 AP and go to: http://");
  Serial.println(IP);
};