int sensorPin = A0;           // A0 is the input pin for the sensor
float sensorValue = 0;       // value coming from the sensor
int count = 0;               //count the heart beat
unsigned long starttime = 0;
int heartrate = 0;
boolean counted = false;    //change value when it cross threshold
int c=0;
int avg=0;
int flag=0;
int threshold=0;
int t1,t2=0,t3=0;        //values at t-to,to,t+to
int i;
void setup (void) {
      Serial.begin (9600);     // Start Serial Communication @ 9600
  }

void loop (){
starttime = millis();
if(flag==0){
  c=0;
  flag=1;
  while(millis()<starttime+3000){
    sensorValue = analogRead(sensorPin);
    t1=t2;
    t2=t3;
    t3=sensorValue;                              
    delay(5);
    if(t2>t1&&t2>t3){          //give maximum
      Serial.print("b ");
      threshold+=t2;                                
      i++;
    }
  }
  threshold=0.75*threshold/i;        //setting threshold value
  Serial.print ("threshold= ");
}
else{
while (millis()<starttime+10000)     
{
sensorValue = analogRead(sensorPin);
avg=sensorValue+avg;
c++;        
delay (10);
if(c>=10){
  avg=avg/10;                           //taking avg of 10values
if (avg > threshold && counted == false)        
{
count++;                                //count the heartbeat
digitalWrite (13,HIGH);
digitalWrite (13, LOW);
counted = true;
}
else if (avg < threshold)                 
{
counted = false;
digitalWrite (13, LOW);
}
c=0;
avg=0;
    }
  }
}                             //count will give heartbeat for 10sec
heartrate = count*6;          // heart beat for one min
Serial.print ("HR=");           
Serial.println (heartrate);     //print the heart beat
Serial.println ();
count = 0;
}  

We are taking input from sensor to Arduino from pin A0. We are running the code for 10sec. 
We are calculating the three values at time t-t0, t, t+t0 at every 5ms.
 Then we are calculating the peak by looking if it is greater t+t0 and t-t0. 
We are setting the threshold value by taking 75 percent of peak value. 
We set a flag (counted) to True if the sensor value is greater than the threshold and we increase the count by 1. 
And set the flag as False if the sensor value is less than the threshold. So this for only 10 sec. 
To calculate BPM (Beat per minute) we are multiplying the count of 6. 