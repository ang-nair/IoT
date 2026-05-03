#include <Servo.h>

Servo h; 
int hp = 90; 
int hmax = 175;
int hmin = 5; 

Servo v; 
int vp = 90; 
int vmax = 100;
int vmin = 1;

int tl = A0; 
int tr = A3; 
int bl = A1; 
int br = A2; 

void setup() {
  Serial.begin(9600); 
  h.attach(2);
  v.attach(13);
  h.write(hp);
  v.write(vp);
  delay(2500);
}

void loop() {
  // Read left side normally
  int l_tl = analogRead(tl); 
  int l_bl = analogRead(bl); 

  // Read right side and subtract the 106 "ghost light" baseline
  int l_trRaw = analogRead(tr) - 106; 
  int l_tr = max(l_trRaw, 0); // max() prevents negative numbers
  
  int l_brRaw = analogRead(br) - 106; 
  int l_br = max(l_brRaw, 0);

  int dt = 150; 
  int tol = 40; 

  int avg_t = (l_tl + l_tr) / 2; 
  int avg_b = (l_bl + l_br) / 2; 
  int avg_l = (l_tl + l_bl) / 2; 
  int avg_r = (l_tr + l_br) / 2; 

  int dv = avg_t - avg_b; 
  int dh = avg_l - avg_r; 

  // --- DEBUG PRINTING ---
  Serial.print("Left Avg: "); Serial.print(avg_l);
  Serial.print(" | Right Avg: "); Serial.print(avg_r);
  Serial.print(" || dh: "); Serial.print(dh);
  Serial.print(" | H-Pos: "); Serial.println(hp);

  // --- Vertical Control ---
  if (abs(dv) > tol) {
    if (avg_t > avg_b) {
      vp++; 
      if (vp > vmax) vp = vmax;
    } else {
      vp--; 
      if (vp < vmin) vp = vmin;
    }
    v.write(vp);
  }

  // --- Horizontal Control ---
  if (abs(dh) > tol) {
    if (avg_l > avg_r) {
      hp--; 
      if (hp < hmin) hp = hmin;
    } else {
      hp++; 
      if (hp > hmax) hp = hmax;
    }
    h.write(hp);
  }

  delay(dt); 
}