#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET    -1 
#define SCREEN_ADDRESS 0x3C

#define BOUTON_DROIT 13
int bouton_droit = HIGH;

#define BOUTON_GAUCHE 14
int bouton_gauche = HIGH;

#define BOUTON_A 32
#define BOUTON_B 33
int bouton_b = HIGH;
int bouton_a = HIGH;

const int buzzerPin = 4; 

int disp = 1;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// logo pas plein
const uint8_t epd_bitmap_spaceinvader [] = {
  0x00, 0xff, 0xff, 0x00, 0x03, 0xe0, 0x07, 0xc0, 0x0f, 0x00, 0x00, 0xf0, 0x1c, 0x00, 0x00, 0x38, 
  0x38, 0x00, 0x00, 0x1c, 0x30, 0x00, 0x00, 0x0c, 0x60, 0x00, 0x00, 0x06, 0xe0, 0x00, 0x00, 0x06, 
  0xc0, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x01, 
  0x80, 0x04, 0x10, 0x01, 0x80, 0x02, 0x20, 0x01, 0x80, 0x07, 0xf0, 0x01, 0x80, 0x0d, 0xd8, 0x01, 
  0x80, 0x1f, 0xfc, 0x01, 0x80, 0x17, 0xf4, 0x01, 0x80, 0x14, 0x14, 0x01, 0x80, 0x14, 0x14, 0x01, 
  0x80, 0x03, 0x60, 0x01, 0xc0, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x03, 
  0xe0, 0x00, 0x00, 0x06, 0x60, 0x00, 0x00, 0x06, 0x30, 0x00, 0x00, 0x0c, 0x38, 0x00, 0x00, 0x1c, 
  0x1c, 0x00, 0x00, 0x38, 0x0f, 0x00, 0x00, 0xf0, 0x03, 0xe0, 0x07, 0xc0, 0x01, 0xff, 0xff, 0x80
};

// logo plein
const uint8_t epd_bitmap_spaceinvader2 [] = {
  0x00, 0xff, 0xff, 0x00, 0x03, 0xff, 0xff, 0xc0, 0x0f, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xff, 0xf8, 
  0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 0x7f, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xfe, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xfb, 0xef, 0xff, 0xff, 0xfd, 0xdf, 0xff, 0xff, 0xf8, 0x0f, 0xff, 0xff, 0xf2, 0x27, 0xff, 
  0xff, 0xe0, 0x03, 0xff, 0xff, 0xe8, 0x0b, 0xff, 0xff, 0xeb, 0xeb, 0xff, 0xff, 0xeb, 0xeb, 0xff, 
  0xff, 0xfc, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xfe, 0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 
  0x1f, 0xff, 0xff, 0xf8, 0x0f, 0xff, 0xff, 0xf0, 0x03, 0xff, 0xff, 0xc0, 0x01, 0xff, 0xff, 0x80
};

//logo pong pas plein
const uint8_t epd_bitmap_pong [] = {
  0x00, 0xff, 0xff, 0x00, 0x03, 0xe0, 0x07, 0xc0, 0x0f, 0x00, 0x00, 0xf0, 0x1c, 0x00, 0x00, 0x38, 
  0x38, 0x00, 0x00, 0x1c, 0x30, 0x00, 0x00, 0x0c, 0x60, 0x00, 0x00, 0x06, 0xe0, 0x00, 0x00, 0x06, 
  0xc0, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x01, 
  0x83, 0xc0, 0x00, 0x41, 0x82, 0x60, 0x00, 0x41, 0x82, 0x60, 0x00, 0x41, 0x83, 0xc0, 0x00, 0x41, 
  0x82, 0x1c, 0xdc, 0x41, 0x82, 0x15, 0x54, 0x01, 0x82, 0x15, 0x54, 0x01, 0x82, 0x1d, 0x5c, 0x41, 
  0x80, 0x00, 0x04, 0x01, 0xc0, 0x00, 0x04, 0x03, 0xc0, 0x00, 0x0c, 0x03, 0xc0, 0x00, 0x00, 0x03, 
  0xe0, 0x00, 0x00, 0x06, 0x60, 0x00, 0x00, 0x06, 0x30, 0x00, 0x00, 0x0c, 0x38, 0x00, 0x00, 0x1c, 
  0x1c, 0x00, 0x00, 0x38, 0x0f, 0x00, 0x00, 0xf0, 0x03, 0xe0, 0x07, 0xc0, 0x01, 0xff, 0xff, 0x80
};

// 'pong_plein', 32x32px
const uint8_t epd_bitmap_pong2 [] = {
  0x00, 0xff, 0xff, 0x00, 0x03, 0xff, 0xff, 0xc0, 0x0f, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xff, 0xf8, 
  0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 0x7f, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xfe, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xfc, 0x3f, 0xff, 0xbf, 0xfd, 0x9f, 0xff, 0xbf, 0xfd, 0x9f, 0xff, 0xbf, 0xfc, 0x3f, 0xff, 0xbf, 
  0xfd, 0xe3, 0x23, 0xbf, 0xfd, 0xea, 0xab, 0xff, 0xfd, 0xea, 0xab, 0xff, 0xfd, 0xe2, 0xa3, 0xbf, 
  0xff, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xfe, 0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 
  0x1f, 0xff, 0xff, 0xf8, 0x0f, 0xff, 0xff, 0xf0, 0x03, 0xff, 0xff, 0xc0, 0x01, 0xff, 0xff, 0x80
};

const uint8_t epd_bitmap_pongLogo [] = {
  0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe3, 0x80, 
  0x00, 0x00, 0x00, 0x00, 0x07, 0xe1, 0xc7, 0x81, 0xdc, 0x0f, 0x60, 0x07, 0xe1, 0xcf, 0xc1, 0xff, 
  0x1f, 0xe0, 0x07, 0xe1, 0xdc, 0xe1, 0xe7, 0x39, 0xe0, 0x07, 0xe3, 0x98, 0x71, 0xc3, 0x38, 0xe0, 
  0x07, 0xff, 0xb8, 0x71, 0xc3, 0xb0, 0xe0, 0x07, 0xff, 0x38, 0x71, 0xc3, 0xb0, 0xe0, 0x07, 0xe0, 
  0x38, 0x71, 0xc3, 0xf0, 0xe0, 0x07, 0xe0, 0x38, 0x71, 0xc3, 0xb0, 0xe0, 0x00, 0xe0, 0x18, 0x71, 
  0xc3, 0xb8, 0xe0, 0x00, 0xe0, 0x1c, 0xe1, 0xc3, 0xb8, 0xe0, 0x00, 0xe0, 0x0f, 0xe1, 0xc3, 0x9f, 
  0xe0, 0x07, 0xe0, 0x07, 0x81, 0xc3, 0x8f, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x10, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xc0, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x1f, 0x80, 0x00
};

int choix = 0;
bool AB_Pressed = false;
bool LR_Pressed = false;
float nombreAleatoire = 0;

bool inGame_Pong = false;
bool coolDown_Pong = true;
int pong_bar_y1 = 10;
int pong_bar_y2 = 25;

int pong_bar_y1b = 10;
int pong_bar_y2b = 25;

int ball_x = 63;
int ball_y = 31;

int dx = 1;
int dy = -1;

int pong_score_p = 0;
int pong_score_a = 0;

int pong_win = 0;
bool pong_wait = false;

bool pong_barInter(int by, int pby1, int pby2) {
  if (by >= pby1 && by <= pby2) {
    return true;
  }
  return false;
}

void setup() {
  Serial.begin(115200);

  // Initialisation de l'écran
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("Échec de l'initialisation de l'écran OLED"));
    for(;;);
  }
  
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(35, 20);
  
  display.println(F("TGC"));

  display.display();
  
  pinMode(buzzerPin, OUTPUT);
  pinMode(BOUTON_DROIT, INPUT_PULLUP);
  pinMode(BOUTON_A, INPUT_PULLUP);
  pinMode(BOUTON_B, INPUT_PULLUP);

  tone(buzzerPin, 440); 
  delay(200);

  tone(buzzerPin, 523); 
  delay(200);

  tone(buzzerPin, 659); 
  delay(500);

  noTone(buzzerPin);
  delay(500);
}

void menu() {
  display.clearDisplay();
  display.setTextSize(1);             
  display.setCursor(5, 5);
  display.println(F("TGC One"));

  display.drawLine(0, 17, 127, 17, SSD1306_WHITE);

  if (choix == 0) {
    display.drawBitmap(27, 25, epd_bitmap_spaceinvader2, 32, 32, SSD1306_WHITE);
    display.drawBitmap(69, 25, epd_bitmap_pong, 32, 32, SSD1306_WHITE);
  } else {
    display.drawBitmap(27, 25, epd_bitmap_spaceinvader, 32, 32, SSD1306_WHITE);
    display.drawBitmap(69, 25, epd_bitmap_pong2, 32, 32, SSD1306_WHITE);
  }
  display.display();

  bouton_droit = digitalRead(BOUTON_DROIT);
  bouton_gauche = digitalRead(BOUTON_GAUCHE);
  if (bouton_droit == LOW) {
    choix = 1;
  }

  if (bouton_gauche == LOW) {
    choix = 0;
  }

  bouton_b = digitalRead(BOUTON_B);
  if (bouton_b == LOW) {
    if (!AB_Pressed) {
      //Serial.println("B");
      AB_Pressed = true;
    }
  }

  bouton_a = digitalRead(BOUTON_A);
  if (bouton_a == LOW) {
    if (!AB_Pressed) {
      //Serial.println("A");
      AB_Pressed = true;

      if (choix == 1) {
        disp = 2;
      }
    }
  }

  if (bouton_b == HIGH && bouton_a == HIGH) {
    AB_Pressed = false;
  }
}

void pong() {
  bouton_a = digitalRead(BOUTON_A);
  bouton_b = digitalRead(BOUTON_B);
  display.clearDisplay();
  if (!inGame_Pong) {
    display.setTextSize(1);             
    display.setCursor(18, 50);
    display.drawBitmap(35, 18, epd_bitmap_pongLogo, 56, 19, SSD1306_WHITE);
    display.println(F("Press A to play"));
  
    display.display();
  
    if (bouton_a == LOW) {
      if (!AB_Pressed) {
        //Serial.println("A");
        AB_Pressed = true;
        inGame_Pong = true;
        nombreAleatoire = 0.7 + ((float)esp_random() / UINT32_MAX) * (0.9 - 0.7);
        ball_x = 63;
        ball_y = 31;
        dx = 1;
        dy = -1;
        pong_bar_y1 = 10;
        pong_bar_y2 = 25;
        pong_bar_y1b = 117;
        pong_bar_y2b = 118;
        pong_score_p = 0;
        pong_score_a = 0;
        coolDown_Pong = true;
        pong_win = 0;
      }
    }
    
    if (bouton_b == HIGH && bouton_a == HIGH) {
      AB_Pressed = false;
    }
  }
  else {
    if (coolDown_Pong) {
      display.setTextSize(2);             
      display.setCursor(60, 30);
      display.println(F("3"));
      display.display();
      display.clearDisplay();
      display.setTextSize(2);             
      display.setCursor(60, 30);
      tone(buzzerPin, 440); 
      delay(100);
      noTone(buzzerPin);
      delay(900);
      display.println(F("2"));
      display.display();
      display.clearDisplay();
      display.setTextSize(2);             
      display.setCursor(60, 30);
      tone(buzzerPin, 440); 
      delay(100);
      noTone(buzzerPin);
      delay(900);
      display.println(F("1"));
      display.display();
      display.clearDisplay();
      display.setTextSize(2);             
      display.setCursor(55, 30);
      tone(buzzerPin, 440); 
      delay(100);
      noTone(buzzerPin);
      delay(900);
      display.println(F("GO"));
      display.display();
      display.clearDisplay();
      tone(buzzerPin, 440); 
      delay(1000);
      noTone(buzzerPin);
      
      coolDown_Pong = false;
    }

    if (pong_win == 1) {
      display.setTextSize(1);             
      display.setCursor(30, 20);
      display.println("Player win!");

      display.setCursor(55, 40);
      display.println(pong_score_p);
      display.setCursor(60, 40);
      display.print("-");
      display.print(pong_score_a);
      display.display();

      ball_x = 0;
      ball_y = 0;

      tone(buzzerPin,440);
      delay(100);
      tone(buzzerPin,523);
      delay(100);
      tone(buzzerPin,659);
      delay(100);
      tone(buzzerPin,880);
      delay(100);
      tone(buzzerPin,659);
      delay(100);
      tone(buzzerPin,880);
      delay(1000);
      noTone(buzzerPin);

      pong_wait = true;
      AB_Pressed = false;
      while (pong_wait) {
        bouton_a = digitalRead(BOUTON_A);
        if (bouton_a == LOW) {
          if (!AB_Pressed) {
            //Serial.println("A");
            AB_Pressed = true;
            inGame_Pong = false;
            pong_win == 0;
            pong_wait = false;
          }
        }
        delay(100);
      }
    } else if (pong_win == 2) {
      display.setTextSize(1);             
      display.setCursor(30, 20);
      display.println("The AI win!");

      display.setCursor(55, 40);
      display.println(pong_score_p);
      display.setCursor(60, 40);
      display.print("-");
      display.print(pong_score_a);
      display.display();

      ball_x = 0;
      ball_y = 0;

      tone(buzzerPin,440);
      delay(100);
      tone(buzzerPin,523);
      delay(100);
      tone(buzzerPin,659);
      delay(100);
      tone(buzzerPin,880);
      delay(100);
      tone(buzzerPin,659);
      delay(100);
      tone(buzzerPin,880);
      delay(1000);
      noTone(buzzerPin);

      pong_wait = true;
      AB_Pressed = false;
      while (pong_wait) {
        bouton_a = digitalRead(BOUTON_A);
        if (bouton_a == LOW) {
          if (!AB_Pressed) {
            //Serial.println("A");
            AB_Pressed = true;
            inGame_Pong = false;
            pong_win == 0;
            pong_wait = false;
          }
        }
        delay(100);
      }
    }

    if (pong_score_p >= 3) {
      pong_win = 1; 
    }

    if (pong_score_a >= 3) {
      pong_win = 2;
    }

    ball_x += dx,
    ball_y += dy;

    if (ball_y > 63) {
      dy = -dy;
    }

    if (ball_y < 1) {
      dy = -dy;
    }

    if (ball_x > 127) {
      dx = -dx;
      pong_score_p += 1;
      display.setTextSize(1);             
      display.setCursor(20, 20);
      display.println("Player striked!");
      display.setCursor(55, 40);
      display.println(pong_score_p);
      display.setCursor(60, 40);
      display.print("-");
      display.print(pong_score_a);
      display.display();
      tone(buzzerPin, 440);
      delay(500);
      noTone(buzzerPin);
      delay(1000);
      
      ball_x = 63;
      ball_y = 31;
      dx = 1;
      dy = -1;
      pong_bar_y1 = 10;
      pong_bar_y2 = 25;
      pong_bar_y1b = 117;
      pong_bar_y2b = 118;
      nombreAleatoire = 0.7 + ((float)esp_random() / UINT32_MAX) * (0.9 - 0.7);

      display.clearDisplay();
    }

    if (ball_x < 1) {
      dx = -dx;
      pong_score_a += 1;
      display.setTextSize(1);             
      display.setCursor(20, 20);
      display.println("The AI striked!");
      display.setCursor(55, 40);
      display.println(pong_score_p);
      display.setCursor(60, 40);
      display.print("-");
      display.print(pong_score_a);
      display.display();
      tone(buzzerPin, 440);
      delay(500);
      noTone(buzzerPin);
      delay(1000);
      
      ball_x = 63;
      ball_y = 31;
      dx = 1;
      dy = -1;
      pong_bar_y1 = 10;
      pong_bar_y2 = 25;
      pong_bar_y1b = 117;
      pong_bar_y2b = 118;
      nombreAleatoire = 0.7 + ((float)esp_random() / UINT32_MAX) * (0.9 - 0.7);

      display.clearDisplay();
    }

    display.drawLine(10, pong_bar_y1, 10, pong_bar_y2, SSD1306_WHITE); // x0, y0, x1, y1

    display.drawPixel(ball_x, ball_y, SSD1306_WHITE);

    if (ball_x == 10 && pong_barInter(ball_y, pong_bar_y1, pong_bar_y2)) {
      dx = -dx;
      tone(buzzerPin, 659);
      delay(20);
      noTone(buzzerPin);
    }

    if (ball_x == 117 && pong_barInter(ball_y, pong_bar_y1b, pong_bar_y2b)) {
      dx = -dx;
      tone(buzzerPin, 659);
      delay(20);
      noTone(buzzerPin);
    }

    display.drawLine(117, pong_bar_y1b, 117, pong_bar_y2b, SSD1306_WHITE);

    if (pong_bar_y1b+round((pong_bar_y2b*nombreAleatoire + pong_bar_y1b*nombreAleatoire)/2) > pong_bar_y1b+ball_y) {
      pong_bar_y2b -= 1;
      pong_bar_y1b -= 1;

      if (pong_bar_y2b > 63) {
        pong_bar_y1b = 64-15;
        pong_bar_y2b = 64;    
      }
    } else {
      pong_bar_y2b += 1;
      pong_bar_y1b += 1;

      if (pong_bar_y1b < 1) {
        pong_bar_y1b = 0;
        pong_bar_y2b = 15;  
      }
    }

    bouton_droit = digitalRead(BOUTON_DROIT);
    bouton_gauche = digitalRead(BOUTON_GAUCHE);

    if (bouton_droit == LOW) {
      if (pong_bar_y2 > 64) {
        pong_bar_y1 = 64-15;
        pong_bar_y2 = 64;    
      } else {
        pong_bar_y2 = pong_bar_y2 + 1;
        pong_bar_y1 = pong_bar_y1 + 1;
      }
    }

    if (bouton_gauche == LOW) {
      if (pong_bar_y1 < 0) {
        pong_bar_y1 = 0;
        pong_bar_y2 = 15;  
      }
      else {
        pong_bar_y2 = pong_bar_y2 - 1;
        pong_bar_y1 = pong_bar_y1 - 1;
      }
      //delay(10);
    }

    display.setTextSize(1);             
    display.setCursor(0, 1);
    display.println(pong_score_p);

    display.setTextSize(1);             
    display.setCursor(122, 1);
    display.println(pong_score_a);

    // système pour revenir au menu pong et au menu original
    
    display.display(); 
  }
}

void loop() {
  switch (disp) {
    case 1:
      menu();
      break;
    case 2:
      pong();
      break;
  }
}
