int motorA_BOT = 2;
int motorA_TOP = 3;
int motorB_BOT = 5; //used to be 4
int motorB_TOP = 4; //used to be 5
int distance_front = A0;
int distance_left = A1;
int distance_right = A2;

int photoMiddle = A5; //middle should be left
int photoLeft = A3; //right should be middle
int photoRight = A4;
int extraCredit = 0;
int distancewalls;
int done = 0;
//motorA is left
//motorB is right
void setup() 
{
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode (motorA_BOT, OUTPUT);
  pinMode (motorA_TOP, OUTPUT);
  pinMode (motorB_BOT, OUTPUT); 
  pinMode (motorB_TOP, OUTPUT);
  pinMode (distance_front, INPUT);
  pinMode (distance_left, INPUT);
  pinMode (distance_right, INPUT);
  pinMode (photoMiddle, INPUT);
  pinMode (photoLeft, INPUT);
  pinMode (photoRight, INPUT);
   
}
void loop() {
  // put your main code here, to run repeatedly:
        digitalWrite (motorA_BOT, LOW);
        digitalWrite (motorA_TOP, LOW);
        digitalWrite (motorB_BOT, LOW);
        digitalWrite (motorB_TOP, LOW);
        delay(100);
  int distanceFront = analogRead(A0);
  int distanceLeft = analogRead(A1);
  int distanceRight = analogRead(A2);

  int middlePhoto = analogRead(A5);
  int leftPhoto = analogRead(A3);
  int rightPhoto = analogRead(A4);

  if(done==1)
  {
        digitalWrite (motorA_BOT, LOW);
        digitalWrite (motorA_TOP, LOW);
        digitalWrite (motorB_BOT, LOW);
        digitalWrite (motorB_TOP, LOW);
        delay(10000);
  }
  
  //Serial.println("Left Photoresistor");
  Serial.println(leftPhoto);
  //Serial.println("Middle Photoresistor");
  Serial.println(middlePhoto);
  //Serial.println("Right Photoresistor");
  Serial.println(rightPhoto);
  //Serial.println("Distance");
  //Serial.println(distanceFront);
  
  
  //digitalWrite (motorA_BOT, HIGH); //Right goes backwards
  //digitalWrite (motorA_TOP, HIGH); //Right goes forward
  //digitalWrite (motorB_BOT, HIGH); //Left goes backwards
  //digitalWrite (motorB_TOP, HIGH); //Left goes forwards
 


  if (distanceFront>400) //obstacle in the way
  {  
        Serial.println ("There's obstacle: STOP");
        digitalWrite (motorA_BOT, LOW);
        digitalWrite (motorA_TOP, LOW);
        digitalWrite (motorB_BOT, LOW);
        digitalWrite (motorB_TOP, LOW);
        delay(50);
        extraCredit=1;
  }
  else if(middlePhoto <=500 && leftPhoto >500 && rightPhoto >500) //regular going on tape
  {
        //middlePhoto = BLACK leftPhoto && rightPhoto = WHITE
        Serial.println("Going Forward on tape");
        digitalWrite (motorA_BOT, LOW);
        digitalWrite (motorA_TOP, HIGH);
        digitalWrite (motorB_BOT, LOW);
        digitalWrite (motorB_TOP, HIGH);
        delay(35); //was 20
  }
  else if(rightPhoto <=500 && middlePhoto <=500) //Sharp RIGHT TURN
  {
        digitalWrite (motorA_BOT, LOW);
        digitalWrite (motorA_TOP, LOW);
        digitalWrite (motorB_BOT, LOW);
        digitalWrite (motorB_TOP, HIGH); //HIGH
        Serial.println("SHARP RIGHT");
        delay(60);
        digitalWrite (motorA_BOT, HIGH); //HIGH
        digitalWrite (motorA_TOP, LOW);
        digitalWrite (motorB_BOT, LOW);
        digitalWrite (motorB_TOP, LOW);
        delay(40);
        
  }
  else if(rightPhoto <=500 && middlePhoto >500) //turning right to stay on black tape
  {
        digitalWrite (motorA_BOT, LOW);
        digitalWrite (motorA_TOP, LOW);
        digitalWrite (motorB_BOT, LOW);
        digitalWrite (motorB_TOP, HIGH);
        Serial.println("kinda RIGHT");
        delay(40);
        digitalWrite (motorA_BOT, HIGH);
        digitalWrite (motorA_TOP, LOW);
        digitalWrite (motorB_BOT, LOW);
        digitalWrite (motorB_TOP, LOW);
        delay(25);
        
  }
  else if(leftPhoto <=500 && middlePhoto<500) //turning left to stay on black tape
  {
        digitalWrite (motorA_BOT, LOW);
        digitalWrite (motorA_TOP, HIGH); //HIGH
        digitalWrite (motorB_BOT, LOW);
        digitalWrite (motorB_TOP, LOW);
        Serial.println("SHARP lefT");
        delay(60);
        digitalWrite (motorA_BOT, LOW);
        digitalWrite (motorA_TOP, LOW);
        digitalWrite (motorB_BOT, HIGH); //HIGH
        digitalWrite (motorB_TOP, LOW);
        delay(40);
  }
  else if(leftPhoto <=500 && middlePhoto>500) //turning left to stay on black tape
  {
        digitalWrite (motorA_BOT, LOW);
        digitalWrite (motorA_TOP, HIGH);
        digitalWrite (motorB_BOT, LOW);
        digitalWrite (motorB_TOP, LOW);
        Serial.println("kinda left");
        delay(40);
        digitalWrite (motorA_BOT, LOW);
        digitalWrite (motorA_TOP, LOW);
        digitalWrite (motorB_BOT, HIGH);
        digitalWrite (motorB_TOP, LOW);
        delay(25);
  }
  else if(middlePhoto>500 && leftPhoto>500 && rightPhoto>500)
  {
        digitalWrite (motorA_BOT, HIGH);
        digitalWrite (motorA_TOP, LOW);
        digitalWrite (motorB_BOT, HIGH);
        digitalWrite (motorB_TOP, LOW);
        delay(30);
        Serial.println("kinda left");
   
  }
     
  

  
  
  if(middlePhoto>=500 && leftPhoto>=500 && rightPhoto>=500 && extraCredit==1) //extra credit white portion
  {
    extraCredit=2;
    Serial.println("BONUS CREDIT MODE");
  }
  if(extraCredit==2)
  {
        digitalWrite (motorA_BOT, LOW);
        digitalWrite (motorA_TOP, LOW);
        digitalWrite (motorB_BOT, LOW);
        digitalWrite (motorB_TOP, LOW);
        delay(100);
    Serial.println("Inside extracredit loop");
            
            // middlePhoto && left && right = RED, STOP
                    distancewalls = distanceLeft-distanceRight;
        if(middlePhoto<500 || leftPhoto<500 || rightPhoto<500) //stopping at red
        {
           Serial.println("Senses Red: STOP, BONUS CREDIT");
           digitalWrite (motorA_BOT, LOW);
           digitalWrite (motorA_TOP, LOW);
           digitalWrite (motorB_BOT, LOW);
           digitalWrite (motorB_TOP, LOW);
           done = 1;
              
        }  
        else if(distancewalls < -100) //turns 
        {
        digitalWrite (motorA_BOT, LOW);
        digitalWrite (motorA_TOP, HIGH);
        digitalWrite (motorB_BOT, LOW);
        digitalWrite (motorB_TOP, LOW);
        Serial.println("SHARP lefT");
        delay(70);
        digitalWrite (motorA_BOT, LOW);
        digitalWrite (motorA_TOP, LOW);
        digitalWrite (motorB_BOT, HIGH);
        digitalWrite (motorB_TOP, LOW);
        delay(25);
        }
        else if(distancewalls > 100)
        {
        digitalWrite (motorA_BOT, LOW);
        digitalWrite (motorA_TOP, LOW);
        digitalWrite (motorB_BOT, LOW);
        digitalWrite (motorB_TOP, HIGH);
        Serial.println("SHARP RIGHT");
        delay(70);
        digitalWrite (motorA_BOT, HIGH);
        digitalWrite (motorA_TOP, LOW);
        digitalWrite (motorB_BOT, LOW);
        digitalWrite (motorB_TOP, LOW);
        delay(25);
        }
        else
        {
          digitalWrite (motorA_BOT, LOW);
          digitalWrite (motorA_TOP, HIGH);
          digitalWrite (motorB_BOT, LOW);
          digitalWrite (motorB_TOP, HIGH);
          delay(70);
        }
  //digitalWrite (motorA_BOT, HIGH); //Right goes backwards
  //digitalWrite (motorA_TOP, HIGH); //Right goes forward
  //digitalWrite (motorB_BOT, HIGH); //Left goes backwards
  //digitalWrite (motorB_TOP, HIGH); //Left goes forwards
        
    
  }


        }
        
  
  
