//queen.Tea Copyright 2015
//Init LCD
#define VERSION 3002
#define PROCNAME "Fan Monitor"
#define DEBUG 0
#define MSGDELAY 5000
#define DOTDELAY 100
#define FANTIMEOUT 1000
#define LCDHEIGHT 2
#define LCDWIDTH 16
#define fanC 3

#include <FreqMeasure.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd( 7,6,5, 4, 3, 2);

int Calc = 0;
double sum=0;
int count=0;
int startT=0;

/* ***************** TYPEDEF Structures ****************** */

typedef struct{
  char fantype;
  unsigned int fandiv; }fanspec;

//sensor dividers
fanspec fanspace[3]={{0,1},{1,2},{2,4}};

typedef struct{
  char fan;
  int type;
  int triggerpin;
  int rpm;
}fandef;

//set the fans being measured.
fandef fans[fanC]={{0,2,13,0},{1,2,12,0},{2,2,11,0}};


/* ********************* Main Code ******************* */

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  LCDinit();
  initMessages();
  serialInTest(DEBUG);
  fanInit();
  }

void loop() {
if (DEBUG){ Serial.println("Starting Main Loop\r\nrunning calc");}

checkRPM(75);
printLCD();
delay(1000);

if (DEBUG){ Serial.println("End Main Loop");}
}


/* ************************** MESSAGES *********************** */
void serialInTest(bool test) {
  if (test) {
  Serial.println("Unit in debug mode\r\n");
  delay(MSGDELAY/2);
  } else { 
    Serial.println("Unit running in normal mode!\r\n");
  }
}

void initMessages() {
  startT = millis();
  Serial.print(PROCNAME);
  Serial.print(" Rev ");
  Serial.print(VERSION, DEC);
  Serial.println("\r\nCopyright queen.Tea 2015\r\nStarting...\r\n");

  lcd.setCursor(2,0);
  lcd.print(PROCNAME);
  lcd.setCursor(3,1);
  lcd.print("Rev ");
  lcd.print(VERSION, DEC);
  delay(MSGDELAY);
  
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Copyright 2015");
  lcd.setCursor(3,1);
  lcd.print("queen.Tea");
  delay(MSGDELAY);
  lcd.clear();
  /*short boot fan info*/
  
  Serial.println("RPM Monitor Info\r\nFan Setups:\r\nFan Hall Sensor Types:\r\n 0:Mono Pole\r\n 1:Bi Pole\r\n 2:Quad Pole\r\n");
  for (int x = 0; x<fanC ;x++){
    lcd.setCursor(1,0);
    lcd.print("Fan Count: ");
    lcd.print(x+1, DEC);
    lcd.print("/");
    lcd.print(fanC, DEC);
    Serial.print("Fan ");
    Serial.print(x+1,DEC); 
    Serial.print(": Sensor Type: ");
    Serial.print(fans[x].type);
    Serial.print(" Trigger Pin: ");
    Serial.println(fans[x].triggerpin);
    lcd.setCursor (0,1);
    lcd.print("Type: ");
    lcd.print(fans[x].type);
    LCDalignRight(String("Pin: ") + String(fans[x].triggerpin,DEC),1);
    delay(MSGDELAY/2);
    lcd.clear();
    delay(250);
   lcd.clear();
  }
  /* Long Boot 
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Fan Count:");
  lcd.setCursor(14,0);
  lcd.print(fanC, DEC);
  delay(MSGDELAY);

  lcd.clear();
  Serial.println("RPM Monitor Info\r\nFan Setups:\r\nFan Hall Sensor Types:\r\n 0:Mono Pole\r\n 1:Bi Pole\r\n 2:Quad Pole\r\n");
  for (int x = 0; x<fanC ;x++){
    lcd.print("Fan ");
    lcd.print(x+1,DEC); 
    lcd.print("  Type: ");
    lcd.print(fans[x].type);
    Serial.print("Fan ");
    Serial.print(x+1,DEC); 
    Serial.print(": Sensor Type: ");
    Serial.print(fans[x].type);
    lcd.setCursor(0,1);
    lcd.print("Trigger Pin: ");
    lcd.print(fans[x].triggerpin);
    Serial.print(" Trigger Pin: ");
    Serial.println(fans[x].triggerpin);
    delay(MSGDELAY/2);
    lcd.clear();
    delay(250);
   lcd.clear();
  }*/
  Serial.print("\r\nStarting Monitor");
  Serial.println("\r\n");
    lcd.setCursor(4,0);
  lcd.print("Monitor"); 
  lcd.setCursor(4,1);
  lcd.print("Starting"); 
  delay(MSGDELAY/2);
}


/* *************************** INIT Proc ****************************** */
void fanInit() {
  for (int x = 0; x<fanC; x++){ 
    pinMode(fans[x].triggerpin, OUTPUT);
    digitalWrite(fans[x].triggerpin, LOW);
  }
}

void LCDinit() {
  lcd.begin(LCDWIDTH, LCDHEIGHT); 
}


/* *********************Main Functions and Subs*********************** */

void LCDalignRight(String str, int r){
  if (str.length()>=LCDWIDTH){return;} else {
    lcdProc(str,LCDWIDTH-str.length(),r);
  }
}

void printLCD(){
  //int startP=0;
  int offset = 2;
  int rpmLast[]={0,0};
  int lblLast[]={0,1};
  String msg = "Fan";
  lcd.clear();
  for (int x=0; x < fanC;x++){
   // startP=lastP[0];
    if (DEBUG){ 
      Serial.print("x:");
      Serial.println(x);
      Serial.print("lblLast: ");
      Serial.print(lblLast[0]);
      Serial.print(" rpmLast: ");
      Serial.println(rpmLast[0]);
    }
    lblLast[0]=lcdProc(msg + String(x+1,DEC),lblLast[0],0)+offset;
    rpmLast[0]=lcdProc(String(fans[x].rpm,DEC),rpmLast[0],1)+offset;
   // startP=lastP[0]+2;
    if (DEBUG){ 
      Serial.print("lblLast: ");
      Serial.print(lblLast[0]);
      Serial.print("rpmLast: ");
      Serial.println(rpmLast[0]);
    }
  }
}

int lcdProc (String strIn, int offset,int r){
  int c = 0;
  if (strIn.length() <= 1) { lcd.setCursor(3+offset,r);
  c=3+offset;}
  else if (strIn.length() <= 2) { lcd.setCursor(2+offset,r);
  c=2+offset;}
  else if (strIn.length() <= 3) { lcd.setCursor(1+offset,r); 
  c=1+offset;}
  else { lcd.setCursor(0+offset,r); 
  c=offset;
  }
  lcd.print(strIn);
  return (strIn.length()+c);
}

void checkRPM(int n){
  if (DEBUG){Serial.println("checkRPM starting");}
  for (int x=0; x < fanC;x++){
    fans[x].rpm = getRPMbyHz(fans[x].triggerpin,fans[x].type,n);
    if (DEBUG && fans[x].rpm==0){fans[x].rpm=666;}
    if (DEBUG) {
      Serial.print("checkRPM - x: ");
      Serial.print(x,DEC);
      Serial.print(" fans.rpm: ");
      Serial.println(fans[x].rpm);
      }
    }
  if (DEBUG){Serial.println("checkRPM done\r\n");}
}

int getRPMbyHz(int trigPin, int divFac, int n) {
  sum = 0;
  count = 0;
  startT = millis();
  if (DEBUG) {
    Serial.print("getRPMbyHZ - t: ");
    Serial.print(startT);
    Serial.print(" trigPin: ");
    Serial.print(divFac);
    Serial.print(" sample size: ");
    Serial.println(n);
  }
  digitalWrite(trigPin, HIGH);
  FreqMeasure.begin();
    while(count < n){
      if (FreqMeasure.available()) {
        sum = sum + FreqMeasure.read();
        count++;
        startT = millis();
        } else if (millis() - startT > FANTIMEOUT) {
          if (DEBUG) {Serial.println("getRPMbyHz timed out");}
          digitalWrite(trigPin, LOW);
          return 0;
        }
    }
    float frequency = FreqMeasure.countToFrequency(sum / count);
    float rpm = frequency * 60.0 / divFac;
    
    if (DEBUG){   
      Serial.print("getRPMbyHz: Sum: ");
      Serial.print(sum);
      Serial.print(" Count: ");
      Serial.print(count);
      Serial.print(" f: ");
      Serial.print(frequency);
      Serial.print(" rpm: ");
      Serial.println(rpm); 
      Serial.println("Exiting getRPMbyHz\r\n");
      }
    sum = 0;
    count = 0;  
    digitalWrite(trigPin, LOW);
    return int(rpm);
  }
