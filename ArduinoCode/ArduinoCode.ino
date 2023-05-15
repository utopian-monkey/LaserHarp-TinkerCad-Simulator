

void setup() {
 
  for (int i=2; i<=6; i++)
  {
    pinMode (i, INPUT);
  }
  pinMode (7,OUTPUT);   // pin 8 for speaker output
  Serial.begin(9600);  
}

  int m,n,o,p,q;      // pin 2,3,4,5,6 are taking input from laser sensors
  int c[8]={956, 851, 758, 716, 638, 568, 506, 478};    //defining semi time periods for various notes
int note7 = 0x64;
int note6 = 0x66;
int note5 = 0x68;
int note4 = 0x70;
int note3 = 0x71;
int note2 = 0x40;
int note1 = 0x47;
int note8 = 0x63;

  int d0=0;
  int d1=1;
  int s=7;
  int dis=8;
int cmd0=0;
  int pitch0=0;
  int velocity0=0;
int cmd00=0;
  int pitch00=0;
  int velocity00=0;
int prevnote=note1;

void loop() {

  m=digitalRead(2);
  n=digitalRead(3);
  o=digitalRead(4);
  p=digitalRead(5);
  q=digitalRead(6);
  
  if (m==d0 && n==d1 && o==d1 && p==d1 && q==d1)
  {
    noteOff(0x80,prevnote,0x00);
    noteOn(0x90, note1, 0x7F);
    prevnote=note1;
    sound(0);
  }
  else if (m==d0 && n==d0 && o==d1 && p==d1 && q==d1)
  {
    sound(1);
    noteOff(0x80,prevnote,0x00);
    noteOn(0x90, note2, 0x7F);
    prevnote=note2;
  }
  else if (m==d1 && n==d0 && o==d1 && p==d1 && q==d1)
  {
    sound(2);
    noteOff(0x80,prevnote,0x00);
    noteOn(0x90, note3, 0x7F);
    prevnote=note3;
  }
  else if (m==d1 && n==d0 && o==d0 && p==d1 && q==d1)
  {
    sound(3);
    noteOff(0x80,prevnote,0x00);
    noteOn(0x90, note4, 0x7F);
    prevnote=note4;
  }
  else if (m==d1 && n==d1 && o==d0 && p==d1 && q==d1)
  {
    sound(4);
    noteOff(0x80,prevnote,0x00);
    noteOn(0x90, note5, 0x7F);
    prevnote=note5;
  }
  else if (m==d1 && n==d1 && o==d0 && p==d0 && q==d1)
  {
    sound(5);
    noteOff(0x80,prevnote,0x00);
    noteOn(0x90, note6, 0x7F);
    prevnote=note6;
  }
  else if (m==d1 && n==d1 && o==d1 && p==d0 && q==d1)
  {
    sound(6);
    noteOff(0x80,prevnote,0x00);
    noteOn(0x90, note7, 0x7F);
    prevnote=note7;
  }
  else if (m==d1 && n==d1 && o==d1 && p==d0 && q==d0)
  {
    noteOff(0x80,prevnote,0x00);
    sound(7);
    noteOn(0x90, note8, 0x7F);
    prevnote=note8;
  }
}

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void sound(int z)
{
  int x,y;

  x=readUltrasonicDistance(dis,dis);
  y= c[z]+c[z+1]*(x-162)*0.0000518;

  for(int i=0;i<100;i++)
  {
    digitalWrite(s,HIGH);
    delayMicroseconds(y);
    digitalWrite(s,LOW);
    delayMicroseconds(y);
  }
  delay(100);
}
void noteOn(int cmd, int pitch, int velocity) 
{
  
  if(cmd!=cmd0||pitch!=pitch0||velocity!=velocity0)
  {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
  }
   cmd0=cmd;
   pitch0=pitch;
  velocity0=velocity;
    
}
void noteOff(int cmd, int pitch, int velocity) 
{
  
  if(cmd!=cmd00||pitch!=pitch00||velocity!=velocity00)
  {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
  }
   cmd00=cmd;
   pitch00=pitch;
  velocity00=velocity;
    
}
