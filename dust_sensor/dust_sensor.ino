#include <SoftwareSerial.h>

SoftwareSerial mySerial(10,11);
int incomeByte[7];
int data;
int z=0;
int sum;
unsigned long error;
char stop_1;
int count=0;
 
int speakerpin=12;

int blueTx=2;   //Tx (보내는핀 설정)at
int blueRx=3;   //Rx (받는핀 설정)

SoftwareSerial blueSerial(blueTx,blueRx);

 
void setup()
{
  Serial.begin(9600);
  mySerial.begin(2400);
  blueSerial.begin(9600);
}
 
void loop(){
  if(count<=2){
 mySerial.listen();
 
  if (mySerial.available()>0){
 
 //   data=Serial.write(mySerial.read());
 data=mySerial.read();

    if(data == 170){
      z=0;
      incomeByte[z]=data;
    }
    else{
      z++;
      incomeByte[z]=data;
    } 
    if(z==6)
    {
      sum=incomeByte[1]+ incomeByte[2]+ incomeByte[3] + incomeByte[4];
 /////////////////////////////////////////////////////////////////////////////////////////////////////

      ////////////////////////////////////////////////
      if(incomeByte[5]==sum && incomeByte[6]==255 )
      {
 
        // Serial.print("Data OK! |");
        for(int k=0;k<7;k++)
        {
          Serial.print(incomeByte[k]);
          Serial.print("|");
        } 
 
        Serial.print(" Vo=");
        float vo=(incomeByte[1]*256.0+incomeByte[2])/1024.0*5.00;
        Serial.print(vo,3);
        Serial.print("v | ");
        float c=vo*700;
       
        Serial.print(" PM2.5 = ");
        Serial.print(c,2);
        Serial.print("ug/m3 ");
        Serial.println();
        Serial.println(count);
           blueSerial.print(" Vo=");
  
        blueSerial.print(vo,3);
        blueSerial.print("v | ");

       
        blueSerial.print(" PM2.5 = ");
        blueSerial.print(c,2);
        blueSerial.print("ug/m3 ");
        blueSerial.println();
        blueSerial.println(count);
        /////////////////////////////////////////////////////////////////////////////////
        if ( 2>= count  && c>51){

  tone(speakerpin,500,1000);  //500: 음의 높낮이(주파수), 1000: 음의 지속시간(1초)
  delay(2000);
  count++; 
Serial.println(count);

        }
        else if(2>=count  &&c>101){
          tone(speakerpin,1000,500);  //500: 음의 높낮이(주파수), 1000: 음의 지속시간(1초)
  delay(1000); 
  count++;
  Serial.println(count);
        }
/////////////////////////////////////////////////////////////////////////////////////////

      }
/////////////////////////////////////////////////////////////////////////////////
      else{
        z=0;
        Serial.flush();
     
        for(int m=0;m<7;m++){
          incomeByte[m]=0;
        }
  
      }
      z=0;
     
    }
  }
  }
  
    if (count ==3){
     //blueSerial.print("click");
     
    blueSerial.listen();
   if(blueSerial.available()){
   
    stop_1=blueSerial.read() + '0';
    Serial.println(stop_1);
    if(stop_1=='1'){
      count=0;
      
    }
   
        
      }
     mySerial.listen();

   }
 
 

 
}
