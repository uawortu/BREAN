#include <U8g2lib.h>
#include "images.h"
#include "fontovi.h"
#include "functions.h"




U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, SCREEN_SCL, SCREEN_SDA);



void FLAPPY1(void);
void PONG1(void);
void CAMERA1(void);
void YOUTUBE1(void);
void WIFI1(void);




void (*FUNCTION[])(void) = {
  FLAPPY1,
  PONG1,
  CAMERA1,
  YOUTUBE1,
  WIFI1
};


const unsigned char FACE [] PROGMEM ={
 0xdd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x6d,0xab,0xaa,
 0x1a,0x6b,0xb5,0xfd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xdf,0xaa,0x56,0x55,
 0x55,0xb5,0xf6,0xff,0xaf,0xdd,0xff,0xff,0xff,0xff,0xff,0xff,0xf6,0xff,0xbd,
 0xaa,0xaa,0x2a,0x5d,0x6d,0xfb,0xf7,0xfd,0xff,0xff,0xff,0xff,0xdf,0x7f,0xb7,
 0x6b,0xab,0x92,0xea,0xeb,0xdf,0xd6,0x7e,0xff,0xff,0xff,0xff,0xff,0xfd,0xdf,
 0x7f,0xdf,0x2a,0xa5,0x94,0xbd,0xb5,0xfd,0xdb,0xd7,0xfe,0xff,0xff,0xdf,0xff,
 0xf6,0xed,0xb5,0x55,0x2a,0x65,0xf7,0x6e,0xb7,0x6e,0xbd,0xdb,0xfd,0xbf,0xf7,
 0xef,0xff,0xbf,0x6f,0xd7,0x52,0x59,0xad,0xd5,0xee,0x5b,0x6b,0xed,0x6f,0xf7,
 0xff,0xfb,0xbf,0xf6,0xfa,0xba,0x4a,0x52,0x7b,0x7f,0xbb,0xd6,0x4a,0x5b,0xfd,
 0xff,0xff,0x7e,0xeb,0xaf,0xaf,0x57,0x95,0xaa,0xd6,0xaa,0xef,0xbb,0x54,0xb2,
 0xab,0x7e,0xfb,0xff,0xff,0xfa,0xfe,0x7a,0xab,0x4a,0xad,0xed,0x7a,0x6f,0x93,
 0x44,0xea,0xeb,0xdf,0x6f,0xbb,0xdf,0xab,0xaf,0xaa,0x54,0x5b,0xdb,0xdf,0xbb,
 0x2a,0x55,0x55,0xbd,0xf7,0xfe,0xef,0x76,0x7f,0xf5,0xad,0xaa,0xb6,0xb6,0xea,
 0xee,0x4a,0x88,0xa8,0xf6,0xbe,0xab,0xba,0xdd,0xea,0xaf,0xaa,0xaa,0xd5,0xaa,
 0xda,0xbf,0xaa,0x52,0x4a,0xad,0xfb,0xfd,0xd7,0xb6,0x57,0xb5,0xdb,0xaa,0x55,
 0x55,0xab,0xa2,0x05,0x85,0x54,0xd5,0xae,0x57,0xba,0x55,0x5d,0x6b,0xb5,0xaa,
 0xaa,0xfe,0xff,0x7f,0x69,0x28,0x21,0x75,0x7f,0xd5,0x4a,0xaa,0xd2,0xd6,0xae,
 0x55,0x55,0x91,0xfa,0xff,0x96,0x22,0x4a,0xd5,0xab,0x2a,0x95,0x90,0x2a,0xa9,
 0x55,0x95,0x57,0x4a,0x02,0x92,0x2a,0x49,0xa9,0x7a,0xff,0xaa,0x20,0x45,0x40,
 0x4a,0xaa,0xaa,0xbf,0x52,0x55,0x24,0x51,0x12,0x52,0xed,0xab,0x4a,0x0a,0x10,
 0x0a,0x90,0x44,0x54,0xef,0x8a,0x0a,0x09,0x84,0x54,0xa5,0xb6,0xbf,0x15,0xa0,
 0x84,0xa0,0x4a,0x29,0x29,0xff,0xb6,0x22,0xa2,0x2a,0xaa,0x54,0xfb,0x6f,0x49,
 0x05,0x20,0x04,0x20,0x52,0x55,0xff,0x55,0x4d,0x08,0x52,0x78,0xdb,0xdd,0xbf,
 0x12,0x90,0x04,0x51,0x95,0x84,0xa0,0xff,0xaf,0xaa,0xa5,0x54,0xe7,0x76,0xff,
 0xef,0x85,0x04,0x50,0x84,0x54,0x55,0x4a,0xdf,0x7f,0x55,0xaa,0xfb,0xbb,0xdb,
 0xf5,0xbf,0x2a,0x20,0x05,0xa9,0xaa,0x92,0xa4,0xf7,0xdf,0xff,0xff,0xff,0xfe,
 0xbe,0xff,0x7b,0x0b,0x09,0x50,0x52,0x95,0x14,0x11,0xff,0xfb,0xdf,0xff,0xdf,
 0xaf,0xeb,0xfe,0xdf,0x55,0xa0,0x8a,0x2a,0xa9,0xa2,0x44,0xff,0xff,0xff,0xbd,
 0xfb,0xfd,0xfe,0xbf,0x7f,0x2f,0x0a,0x55,0xff,0x42,0x4a,0x90,0xff,0xff,0xff,
 0xff,0x7f,0xd7,0xb7,0xf7,0xdb,0x55,0x41,0x00,0xd0,0x1f,0x10,0x01,0xbb,0xff,
 0xef,0xff,0xdf,0x7f,0xfd,0xfe,0xff,0xbb,0x10,0xb5,0x04,0x74,0x45,0x54,0xff,
 0xfb,0xfb,0xef,0xfd,0xfa,0xaf,0xff,0xbf,0x6e,0x0b,0x2a,0x50,0x81,0x02,0x01,
 0xef,0xff,0xfe,0xfb,0xaf,0xef,0xff,0xfd,0xff,0xdb,0xaa,0x28,0x01,0x48,0x28,
 0x48,0xfb,0xff,0xff,0xff,0xfb,0xaa,0xfe,0xef,0x6f,0x57,0x55,0x25,0x04,0x00,
 0x82,0x04,0xff,0xde,0xff,0x7f,0x2f,0x01,0x6d,0xfb,0xfa,0xba,0x56,0xa5,0x20,
 0x29,0x10,0x50,0xbf,0xff,0x7f,0xff,0xab,0x48,0xd8,0xde,0xaf,0xd7,0xed,0x2e,
 0x05,0x00,0x81,0x04,0xed,0xf7,0xff,0xef,0x55,0x20,0xa1,0x55,0xb5,0x74,0x5f,
 0xb5,0x90,0x44,0x08,0x20,0xff,0x7d,0xf7,0xff,0x95,0x0a,0x44,0x55,0x55,0x55,
 0xf5,0xeb,0x27,0x10,0xa2,0x0a,0xb5,0xdf,0xff,0x7f,0xab,0x20,0x11,0x52,0x4a,
 0x42,0x02,0x5d,0xad,0x82,0x08,0x20,0xff,0xf6,0x7d,0xf7,0x55,0x5f,0x45,0x8a,
 0x24,0x09,0x50,0xb5,0xad,0x2a,0xd5,0x0a,0xd5,0xff,0xdf,0xff,0x55,0xed,0x5d,
 0x50,0x11,0x20,0x81,0xda,0x76,0x55,0x55,0x91,0xbf,0x5a,0xf7,0xdf,0xff,0xff,
 0xff,0x07,0x84,0x04,0x48,0x7c,0xdb,0xbb,0xb5,0x0a,0xea,0xef,0xfd,0x7a,0xef,
 0x7f,0xf7,0xbf,0x22,0x00,0xa2,0xea,0x6d,0x6d,0xab,0x22,0x55,0x7d,0xef,0xdf,
 0xfb,0xf6,0xff,0xfd,0x95,0xa4,0x28,0x5d,0xdf,0xd6,0x6e,0x95,0xba,0xab,0xbb,
 0xf6,0xdf,0xdf,0xde,0xef,0xbf,0x15,0x25,0xf7,0x6a,0xbb,0x55,0x09,0x55,0xed,
 0xee,0xbf,0x6a,0x75,0xfb,0x7e,0xeb,0xab,0x48,0xdf,0xdf,0x56,0xad,0x42,0x6a,
 0xbb,0x5d,0xd5,0x56,0xad,0xd7,0xf7,0xbf,0x5e,0x81,0xba,0x6a,0xbb,0x55,0x95,
 0xd5,0xd6,0x52,0xa9,0x54,0x55,0xad,0x5a,0xf5,0xbb,0x96,0xd6,0xdd,0x6d,0x55,
 0x02,0xaa,0xaa,0x8a,0x44,0xa9,0x52,0x69,0x6d,0x55,0xd5,0xb5,0x6c,0x6b,0x5b,
 0xab,0x44,0xaa,0x5a,0x24,0x10,0x42,0x54,0x95,0xaa,0xaa,0xb6,0x56,0xdb,0xb6,
 0xd6,0x5a,0x91,0x55,0x55,0x81,0x4a,0x94,0x2a,0x25,0x11,0x49,0xa9,0xd5,0x6a,
 0x6d,0x35,0x25,0x42,0xaa,0x55,0x28,0x80,0x22,0x55,0x4a,0x4a,0x04,0x92,0xaa,
 0x5a,0xab,0xad,0x4a,0x49,0x55,0x55,0x65,0xfb,0xff,0x8a,0xa4,0x20,0x51,0x49,
 0xaa,0xaa,0xaa,0xd2,0x92,0x00,0x6a,0x55,0xdd,0xff,0xfe,0xff,0x0b,0x15,0x04,
 0x80,0x54,0x55,0x55,0x2d,0x25,0x2a,0x55,0xa9,0x76,0xff,0xbf,0xff,0xff,0x42,
 0x51,0x12,0x52,0x55,0x25,0x49,0x88,0x40,0xaa,0xea,0xfd,0xb5,0xff,0xff,0xff,
 0xff,0x06,0x40,0x40,0x55,0x4a,0x92,0x22,0x10,0xaa,0xaa,0xae,0xff,0xfb,0xff,
 0xfe,0xff,0xff,0x12,0x0a,0x2a,0x91,0x24,0x04,0x04,0xaa,0xaa,0x7b,0x6d,0xaf,
 0xaa,0xef,0xff,0xbb,0x07,0x40,0x40,0x04,0x49,0x11,0x41,0x92,0xda,0xee,0xfb,
 0xfd,0xff,0x7b,0xfb,0xff,0x5a,0x00,0x2a,0xa1,0x10,0x04,0x10,0xaa,0x54,0x5b,
 0xad,0xab,0xaa,0xde,0xae,0xee,0xff,0x92,0x00,0x08,0x42,0x00,0x04,0x92,0xea,
 0x6a,0x7b,0xff,0xff,0xeb,0xfd,0xbb,0x56,0x01,0x48,0x21,0x14,0x41,0x00,0xaa,
 0x2a,0xdd,0xd6,0xaa,0xaa,0x5a,0xab,0xee,0x6d,0x95,0x02,0x84,0x00,0x08,0x00,
 0x92,0x54,0x53,0xad,0xda,0xb6,0x6d,0xfd,0x5d,0x5b,0x25,0x28,0x21,0x52,0x00,
 0x49,0x2a,0xa5,0x54,0xab,0xb5,0x55,0xdb,0x96,0xea,0x56,0x49,0x01,0x08,0x00,
 0x42,0x00,0xa5,0x2a,0x55,0xaa,0xaa,0x6a,0x55,0xb5,0x56,0x29,0x15,0xa4,0x40,
 0x25,0x00,0x00,0xaa,0x54,0xa5,0x52,0x55,0x55,0x55,0xab,0xaa,0x52,0xa2,0x00,
 0x0a,0x00,0x10,0x00 };



const unsigned char bitmap_scrollbar_background [] PROGMEM = {
  0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 
  0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 
  0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 
  0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 
  0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 
  0x00, 0x40, 0x00, 0x00, };


const unsigned char FLAPPY[] PROGMEM =   {
  0x80,0x0f,0x00,0x70,0x12,0x00,0x08,0x21,0x00,0x04,0x51,0x00,0x02,0x51,0x00,
 0x3e,0x42,0x00,0x41,0xfc,0x00,0x41,0x03,0x01,0x3e,0xfd,0x00,0x04,0x42,0x00,
 0x18,0x3c,0x00,0xe0,0x03,0x00}; 


const unsigned char PONG[] PROGMEM =   {
  0x00,0x00,0x00,0x02,0x00,0x00,0x02,0x00,0x00,0x1a,0x00,0x00,0x1a,0x00,0x00,
 0x02,0x40,0x00,0x02,0x40,0x00,0x00,0x40,0x00,0x00,0x40,0x00,0x00,0x40,0x00,
 0x00,0x40,0x00,0x00,0x00,0x00}; 

const unsigned char CAMERA[] PROGMEM =   {
0x00,0x00,0x00,0xc0,0x07,0x00,0x40,0x04,0x00,0xff,0xff,0x01,0x01,0x00,0x01,
 0xc1,0x67,0x01,0x41,0x64,0x01,0x41,0x04,0x01,0x41,0x04,0x01,0xc1,0x07,0x01,
 0x01,0x00,0x01,0xff,0xff,0x01}; 


const unsigned char YOUTUBE[] PROGMEM =   {
0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x00,0xf0,0x00,0x00,0xf0,0x03,0x00,
 0xf0,0x0f,0x00,0xf0,0x03,0x00,0xf0,0x00,0x00,0x30,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00}; 


const unsigned char WIFI[] PROGMEM =   {
0x00,0x00,0x00,0xf0,0x0f,0x00,0x08,0x10,0x00,0xe4,0x27,0x00,0x12,0x48,0x00,
 0xc9,0x93,0x00,0x24,0x24,0x00,0x90,0x09,0x00,0x80,0x01,0x00,0x80,0x01,0x00,
 0x80,0x01,0x00,0x00,0x00,0x00}; 

const unsigned char* bitmap_icons[5] = {
  FLAPPY,
  PONG,
  CAMERA,
  YOUTUBE,
  WIFI
};


const int NUM_ITEMS = 5; // number of items in the list and also the number of screenshots and screenshots with QR codes (other screens)
const int MAX_ITEM_LENGTH = 20; // maximum characters for the item name

char menu_items [NUM_ITEMS] [MAX_ITEM_LENGTH] = {  // array with item names
  { "FLAPPY" }, 
  { "PONG" }, 
  { "CAMERA" }, 
  { "YOUTUBE" }, 
  { "WI-FI" }
 };


bool hasRun = false;


#define BUTTON_UP_PIN 2 // pin for UP button 
#define BUTTON_SELECT_PIN 13  // pin for SELECT button
#define BUTTON_DOWN_PIN 12 // pin for DOWN button

//#define DEMO_PIN 13 // pin for demo mode, use switch or wire to enable or disable demo mode, see more details below


int button_up_clicked = 0; // only perform action when button is clicked, and wait until another press
int button_select_clicked = 0; // same as above
int button_down_clicked = 0; // same as above

int item_selected = 0; // which item in the menu is selected

int item_sel_previous; // previous item - used in the menu screen to draw the item before the selected one
int item_sel_next; // next item - used in the menu screen to draw next item after the selected one

int current_screen = 0;   // 0 = menu, 1 = screenshot, 2 = qr

int demo_mode = 0; // when demo mode is set to 1, it automatically goes over all the screens, 0 = control menu with buttons
int demo_mode_state = 0; // demo mode state = which screen and menu item to display
int demo_mode_delay = 0; // demo mode delay = used to slow down the screen switching



void setup() {

Serial.begin(115200);


///////////////////////////////////////////////////////////////////////////
   display.init();

    //display.display();
    unsigned long start = millis();

    pinMode(UP_BUTTON, INPUT_PULLUP);
    pinMode(DOWN_BUTTON, INPUT_PULLUP);

    display.clear();
    //drawCourt();

    while(millis() - start < 2000);

    display.display();

    ball_update = millis();
    paddle_update = ball_update;
    display.flipScreenVertically();
////////////////////////////////////////////////////////////////


pinMode(13,INPUT_PULLUP); 
  //display.init();
  display.init();
  for(int i=0;i<4;i++)
  {
    zidx[i]=128+((i+1)*razmak);
    {prazan[i]=random(8,32);}
    }

////////////////////////////////////////////////////////////////////////////////////

 WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout detector
 
  Serial.setDebugOutput(false);
  
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG; 
  
  if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }
 // Camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }


////////////////////////////beginning of menu setup //////////////////////////////////////////

  u8g2.setColorIndex(1);  // set the color to white
  u8g2.begin();
  u8g2.setBitmapMode(1);
  u8g2.setFont(u8g2_font_7x13B_tf);
  //Wire.begin(SCREEN_SDA, SCREEN_SCL);
  // define pins for buttons
  // INPUT_PULLUP means the button is HIGH when not pressed, and LOW when pressed
  // since it´s connected between some pin and GND
  pinMode(BUTTON_UP_PIN, INPUT_PULLUP); // up button
  pinMode(BUTTON_SELECT_PIN, INPUT_PULLUP); // select button
  pinMode(BUTTON_DOWN_PIN, INPUT_PULLUP); // down button

  u8g2.clearBuffer();
  u8g2.drawXBMP( 0, 0, 128, 64,FACE);
  u8g2.sendBuffer();
  
 WIFIAP();
////////////////////////////end of menu setup //////////////////////////////////////////
}


void loop() {


  if (current_screen == 0) { // MENU SCREEN

      // up and down buttons only work for the menu screen
      if ((digitalRead(BUTTON_UP_PIN) == LOW) && (button_up_clicked == 0)) { // up button clicked - jump to previous menu item
        item_selected = item_selected - 1; // select previous item
        button_up_clicked = 1; // set button to clicked to only perform the action once
        if (item_selected < 0) { // if first item was selected, jump to last item
          item_selected = NUM_ITEMS-1;
        }
      }
      else if ((digitalRead(BUTTON_DOWN_PIN) == LOW) && (button_down_clicked == 0)) { // down button clicked - jump to next menu item
        item_selected = item_selected + 1; // select next item
        button_down_clicked = 1; // set button to clicked to only perform the action once
        if (item_selected >= NUM_ITEMS) { // last item was selected, jump to first menu item
          item_selected = 0;
          }
      } 

      if ((digitalRead(BUTTON_UP_PIN) == HIGH) && (button_up_clicked == 1)) { // unclick 
        button_up_clicked = 0;
      }
      if ((digitalRead(BUTTON_DOWN_PIN) == HIGH) && (button_down_clicked == 1)) { // unclick
        button_down_clicked = 0;
      }

  }


  if ((digitalRead(BUTTON_SELECT_PIN) == LOW) && (button_select_clicked == 0)) { // select button clicked, jump between screens
     button_select_clicked = 1; // set button to clicked to only perform the action once
     if (current_screen == 0){

    //(*FUNCTION[item_selected])();
        current_screen = 1;
        } // menu items screen --> screenshots screen
     //else if (current_screen == 1) {current_screen = 2;} // screenshots screen --> qr codes screen
     
     else {current_screen = 0;} // qr codes screen --> menu items screen
  }
  if ((digitalRead(BUTTON_SELECT_PIN) == HIGH) && (button_select_clicked == 1)) { // unclick 
    button_select_clicked = 0;
  }

  // set correct values for the previous and next items
  item_sel_previous = item_selected - 1;
  if (item_sel_previous < 0) {item_sel_previous = NUM_ITEMS - 1;} // previous item would be below first = make it the last
  item_sel_next = item_selected + 1;  
  if (item_sel_next >= NUM_ITEMS) {item_sel_next = 0;} // next item would be after last = make it the first


  u8g2.clearBuffer(); // required for page drawing mode for u8g2 library
  // u8g2.firstPage();
  // do {
    if (current_screen == 0) { // MENU SCREEN
      //u8g2.firstPage();
       //do {
      // selected item background
      u8g2.drawRFrame(0, 22, 120, 20,7);

      // draw previous item as icon + label
      u8g2.setFont(u8g2_font_7x13B_tf);
      u8g2.drawStr(25, 17, menu_items[item_sel_previous]); 
      u8g2.drawXBMP( 4, 3, 17, 12, bitmap_icons[item_sel_previous]);          

      // draw selected item as icon + label in bold font
      u8g2.setFont(u8g2_font_7x13B_tf);  
      u8g2.drawStr(25, 38, menu_items[item_selected]);   
      u8g2.drawXBMP( 4, 25, 17, 12, bitmap_icons[item_selected]);     

      // draw next item as icon + label
      u8g2.setFont(u8g2_font_7x13B_tf);   
      u8g2.drawStr(25, 59, menu_items[item_sel_next]);   
      u8g2.drawXBMP( 4, 47, 17, 12, bitmap_icons[item_sel_next]);  

      //draw scrollbar background
      u8g2.drawXBMP(128-8, 0, 8, 64, bitmap_scrollbar_background);

      // draw scrollbar handle
      u8g2.drawBox(125, 64/NUM_ITEMS * item_selected, 3, 64/NUM_ITEMS); 

    } 


    while (current_screen == 1) { // SCREENSHOTS SCREEN
      (*FUNCTION[item_selected])();

    }
   
  u8g2.sendBuffer(); // send buffer from RAM to display controller

}
 


void FLAPPY1() {
 gamechflap();   
}

void PONG1() {
  gamechpong();  
}

void CAMERA1() {
  if(!hasRun){
  
  startCameraServer();  
  hasRun = true;
            }
}

void YOUTUBE1() {
  u8g2.clearBuffer();
  u8g2.drawXBMP( 0, 0, 128, 64,FACE);
  u8g2.sendBuffer();  
}

void WIFI1() {
  u8g2.clearBuffer();
  u8g2.drawXBMP( 0, 0, 128, 64,FACE);
  u8g2.sendBuffer();  
}















