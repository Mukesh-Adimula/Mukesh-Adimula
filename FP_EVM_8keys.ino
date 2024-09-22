#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
int getFingerprintIDez();
SoftwareSerial mySerial(9, 10);
const int key1=A0; 
const int key2=A1; 
const int key3=A2; 
const int key4=A3; 
const int resl=A4; 
const int strt=8; 
const int stp=12; 
const int vrk=13; 
const int buzz=11; 
int   count1=0;
int   count2=0;
int   count3=0;
int   count4=0;
int   a[100];
int   i=0;
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
int   flag=0;
int   voted=0;
int   admin=0;
int   auth=0;
void setup()  
{
  lcd.begin(20, 4);
  lcd.setCursor(0,0);
  lcd.print("      WELCOME       ");
  lcd.setCursor(0,1);
  lcd.print("ENTER ADMIN FINGER  ");
  lcd.setCursor(0,2);
  lcd.print("&PRESS START KEY    ");
  lcd.setCursor(0,3);
  lcd.print("                    ");      
  Serial.begin(9600);
  Serial.println("fingertest");
  pinMode(key1,INPUT); 
  pinMode(key2,INPUT); 
  pinMode(key3,INPUT); 
  pinMode(key4,INPUT);
  pinMode(resl,INPUT);  
  pinMode(strt,INPUT); 
  pinMode(stp,INPUT); 
  pinMode(vrk,INPUT);       
  pinMode(buzz,OUTPUT); 
  digitalWrite(key1, HIGH); 
  digitalWrite(key2, HIGH); 
  digitalWrite(key3, HIGH); 
  digitalWrite(key4, HIGH); 
  digitalWrite(resl, HIGH); 
  digitalWrite(strt, HIGH); 
  digitalWrite(stp, HIGH); 
  digitalWrite(vrk, HIGH);       
  digitalWrite(buzz, LOW); 
  finger.begin(57600);
  for(i=0;i<100;i++)
  {
  a[i]=0;  
  }
  i=0;
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1);
  }
  Serial.println("Waiting for valid finger...");

evm_strt:
 if(digitalRead(strt)==HIGH)
  {
    goto evm_strt;
  }
  admin=1;
  delay(2000);
  getFingerprintIDez();
  delay(50);   
  if(auth==0)
  {
      digitalWrite(buzz, HIGH);   
  lcd.setCursor(0,0);
  lcd.print("ADMIN AUTHORIZATION ");
  lcd.setCursor(0,1);
  lcd.print("FAILED,PLEASE TRY   ");
  lcd.setCursor(0,2);
  lcd.print("AGAIN TO START EVM  ");
  lcd.setCursor(0,3);
  lcd.print("                    ");  
  Serial.println("admin fail");     
  delay(5000);
      digitalWrite(buzz, LOW); 
  lcd.setCursor(0,0);
  lcd.print("      WELCOME       ");
  lcd.setCursor(0,1);
  lcd.print("ENTER ADMIN FINGER  ");
  lcd.setCursor(0,2);
  lcd.print("&PRESS START KEY    ");
  lcd.setCursor(0,3);
  lcd.print("                    ");      
  goto evm_strt;     
  }  
  admin=0;
  auth=0;
  lcd.setCursor(0,0);
  lcd.print(" WELCOME  TO EVM    ");
  lcd.setCursor(0,1);
  lcd.print("ENTER FINGERPRINT&  ");
  lcd.setCursor(0,2);
  lcd.print("PRESS SCAN KEY TO   ");
  lcd.setCursor(0,3);
  lcd.print("VOTE YOUR CONTENDER ");    
  Serial.println("admin success");  
}

void loop()                     // run over and over again
{
home:  
  if(digitalRead(stp)==LOW)
  {
  admin=1;
  delay(2000);
  getFingerprintIDez();
  delay(50);   
  if(auth==0)
  {
     digitalWrite(buzz, HIGH);    
  lcd.setCursor(0,0);
  lcd.print("ADMIN AUTHORIZATION ");
  lcd.setCursor(0,1);
  lcd.print("FAILED,PLEASE TRY   ");
  lcd.setCursor(0,2);
  lcd.print(" AGAIN TO STOP THE  ");
  lcd.setCursor(0,3);
  lcd.print("     POLLING        ");   
  delay(5000);
      digitalWrite(buzz, LOW); 
  lcd.setCursor(0,0);
  lcd.print(" WELCOME  TO EVM    ");
  lcd.setCursor(0,1);
  lcd.print("ENTER FINGERPRINT&  ");
  lcd.setCursor(0,2);
  lcd.print("PRESS SCAN KEY TO   ");
  lcd.setCursor(0,3);
  lcd.print("VOTE YOUR CONTENDER ");       
  goto home;     
  }
  lcd.setCursor(0,0);
  lcd.print("EVM POLLING STOPPED ");
  lcd.setCursor(0,1);
  lcd.print("NO MORE VOTING,PLS  ");
  lcd.setCursor(0,2);
  lcd.print("ENTER ADMIN FINGER  ");
  lcd.setCursor(0,3);
  lcd.print("TO DISPLAY RESULTS  ");  
  admin=0;
  auth=0;
evm_rsl:  
  if(digitalRead(resl)==HIGH)
  {
    goto evm_rsl;
  }
  admin=1;
  delay(2000);
  getFingerprintIDez();
  delay(50);   
  if(auth==0)
  {
     digitalWrite(buzz, HIGH);    
  lcd.setCursor(0,0);
  lcd.print("ADMIN AUTHORIZATION ");
  lcd.setCursor(0,1);
  lcd.print("FAILED,PLEASE TRY   ");
  lcd.setCursor(0,2);
  lcd.print(" AGAIN DISPLAY THE  ");
  lcd.setCursor(0,3);
  lcd.print("     RESULTS        ");   
  delay(5000);
      digitalWrite(buzz, LOW); 
  lcd.setCursor(0,0);
  lcd.print("EVM POLLING STOPPED ");
  lcd.setCursor(0,1);
  lcd.print("NO MORE VOTING,PLS  ");
  lcd.setCursor(0,2);
  lcd.print("ENTER ADMIN FINGER  ");
  lcd.setCursor(0,3);
  lcd.print("TO DISPLAY RESULTS  ");      
  goto evm_rsl;     
  }
  lcd.setCursor(0,0);
  lcd.print("AUTHORIZATION DONE  ");
  lcd.setCursor(0,1);
  lcd.print("THE FINAL RESULTS:  ");  
  lcd.setCursor(0,2);
  lcd.print("TRS:        BJP:    ");   
  lcd.setCursor(0,3);
  lcd.print("TDP:       CONG:    "); 
  lcd.setCursor(4,2);        
  lcd.print(count1);  
  lcd.setCursor(16,2);        
  lcd.print(count2); 
  lcd.setCursor(4,3);        
  lcd.print(count3);
  lcd.setCursor(16,3);        
  lcd.print(count4);   
  while(1);
  } 
  if(digitalRead(vrk)==HIGH)
  {
    goto home;
  }  
  getFingerprintIDez();
  delay(50);            //don't ned to run this at full speed.
  if(flag==1)
  {
    flag=0;
    delay(1000);
    goto home;
  }
  else
  {
    if(voted==0)
    {
    digitalWrite(buzz, HIGH);     
  lcd.setCursor(0,0);
  lcd.print("FINGERPRINT IS  NOT ");
  lcd.setCursor(0,1);
  lcd.print("  REGISTERED OR     ");
  lcd.setCursor(0,2);
  lcd.print(" IDENTIFIED,PLS TRY ");  
  lcd.setCursor(0,3);
  lcd.print("AGAIN/ CONSULT ADMIN");      
  delay(5000);
    digitalWrite(buzz,LOW); 
    }
  lcd.setCursor(0,0);
  lcd.print(" WELCOME  TO EVM    ");
  lcd.setCursor(0,1);
  lcd.print("ENTER FINGERPRINT&  ");
  lcd.setCursor(0,2);
  lcd.print("PRESS SCAN KEY TO   ");
  lcd.setCursor(0,3);
  lcd.print("VOTE YOUR CONTENDER ");    
  voted=0;
  goto home;    
  }  
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

 p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
      lcd.setCursor(0,0);
  lcd.print("found finger"); 
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
//  lcd.setCursor(0,0);
//  lcd.print("SORRY FINGERPRNT");  
//  lcd.setCursor(0,1);
//  lcd.print("MATCH NOT FOUND"); 
  delay(2000);
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
 
    lcd.setCursor(0,0);
  lcd.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 
 // goto kb;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
 // lcd.setCursor(0,0);
 // lcd.print(finger.fingerID);  
  delay(1000);
  i=finger.fingerID;
  if(admin==1)
  {
    if(i==1)
    {
      auth=1;
      goto xit;
    }
    else
    {
      auth=0;
      goto xit;
    }
  }
  if((a[i])==1)
  {
  lcd.setCursor(0,0);
  lcd.print("  ALERT,YOUR VOTE   "); 
  lcd.setCursor(0,1);
  lcd.print("  ALREADY  COUNTED  ");     
  lcd.setCursor(0,2);
  lcd.print("PLEASE CONSULT ADMIN"); 
  lcd.setCursor(0,3);
  lcd.print("  FOR ANY DISPUTES  "); 
  digitalWrite(buzz, HIGH); 
  voted=1;
  delay(5000);
  lcd.setCursor(0,0);
  lcd.print(" WELCOME  TO EVM    ");
  lcd.setCursor(0,1);
  lcd.print("ENTER FINGERPRINT&  ");
  lcd.setCursor(0,2);
  lcd.print("PRESS SCAN KEY TO   ");
  lcd.setCursor(0,3);
  lcd.print("VOTE YOUR CONTENDER ");    
  digitalWrite(buzz, LOW); 
  }
  else
  {
  a[i]=1;
  goto kb;
  }
 xit: 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID; 
  while(1)
{
kb:
  lcd.setCursor(0,0);
  lcd.print("AUTHENTICATION DONE "); 
  lcd.setCursor(0,1);
  lcd.print(" VOTER ID IS VALID  "); 
  lcd.setCursor(0,2);
  lcd.print("   VOTE FOR YOUR    "); 
  lcd.setCursor(0,3);
  lcd.print("    CONTESTANT      "); 
  
  if(digitalRead(key1)==LOW)
  {
  count1=count1+1;
  lcd.setCursor(0,0);
  lcd.print("     THANK YOU!     "); 
  lcd.setCursor(0,1);
  lcd.print(" YOUR VOTE HAS BEEN ");   
  lcd.setCursor(0,2);
  lcd.print("       POLLED       "); 
  lcd.setCursor(0,3);
  lcd.print("    SUCCESSFULLY    ");     
  delay(3000);
  lcd.setCursor(0,0);
  lcd.print(" WELCOME  TO EVM    ");
  lcd.setCursor(0,1);
  lcd.print("ENTER FINGERPRINT&  ");
  lcd.setCursor(0,2);
  lcd.print("PRESS SCAN KEY TO   ");
  lcd.setCursor(0,3);
  lcd.print("VOTE YOUR CONTENDER ");  
  flag=1;
  break;
} 
  if(digitalRead(key2)==LOW)
  {
  count2=count2+1;
  lcd.setCursor(0,0);
  lcd.print("     THANK YOU!     "); 
  lcd.setCursor(0,1);
  lcd.print(" YOUR VOTE HAS BEEN ");   
  lcd.setCursor(0,2);
  lcd.print("       POLLED       "); 
  lcd.setCursor(0,3);
  lcd.print("    SUCCESSFULLY    ");     
  delay(3000);
  lcd.setCursor(0,0);
  lcd.print(" WELCOME  TO EVM    ");
  lcd.setCursor(0,1);
  lcd.print("ENTER FINGERPRINT&  ");
  lcd.setCursor(0,2);
  lcd.print("PRESS SCAN KEY TO   ");
  lcd.setCursor(0,3);
  lcd.print("VOTE YOUR CONTENDER ");  
  flag=1;  
  break;
}
  if(digitalRead(key3)==LOW)
  {
  count3=count3+1;
  lcd.setCursor(0,0);
  lcd.print("     THANK YOU!     "); 
  lcd.setCursor(0,1);
  lcd.print(" YOUR VOTE HAS BEEN ");   
  lcd.setCursor(0,2);
  lcd.print("       POLLED       "); 
  lcd.setCursor(0,3);
  lcd.print("    SUCCESSFULLY    ");     
  delay(3000);
  lcd.setCursor(0,0);
  lcd.print(" WELCOME  TO EVM    ");
  lcd.setCursor(0,1);
  lcd.print("ENTER FINGERPRINT&  ");
  lcd.setCursor(0,2);
  lcd.print("PRESS SCAN KEY TO   ");
  lcd.setCursor(0,3);
  lcd.print("VOTE YOUR CONTENDER ");  
  flag=1;  
  break;
}
  if(digitalRead(key4)==LOW)
  {
  count4=count4+1;
  lcd.setCursor(0,0);
  lcd.print("     THANK YOU!     "); 
  lcd.setCursor(0,1);
  lcd.print(" YOUR VOTE HAS BEEN ");   
  lcd.setCursor(0,2);
  lcd.print("       POLLED       "); 
  lcd.setCursor(0,3);
  lcd.print("    SUCCESSFULLY    ");     
  delay(3000);
  lcd.setCursor(0,0);
  lcd.print(" WELCOME  TO EVM    ");
  lcd.setCursor(0,1);
  lcd.print("ENTER FINGERPRINT&  ");
  lcd.setCursor(0,2);
  lcd.print("PRESS SCAN KEY TO   ");
  lcd.setCursor(0,3);
  lcd.print("VOTE YOUR CONTENDER ");  
  flag=1;  
  break;
}
}
}
