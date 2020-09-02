int leftblack; // stores the value of whatever black colour the robot is calibrate to
int leftwhite; // stores value of whatever the white colour the robot is to calibrate to
int rightblack; // stores the value of whatever black colour the robot is calibrate to
int rightwhite; // stores value of whatever the white colour the robot is to calibrate to

int count = 0;

const int lefttol = 100; e// +/- tolerance for left photoresistor
const int righttol = 100; // +/- tolerance for right photoresistor

int leftcolour; // for calibrating photoresistor/debugging ~ shows current value on left photoresistor
int rightcolour; // for cailbrating photoresistor/debugging  ~ shows current value on right photoresistor

// pin variable declarations: 

const int light = 4; // indicator light
const int button = 5; // the start button

const int right2 = 7;
const int right1 = 8; // right1 and right2 are the 2 inputs for the right motor's h-bridge
const int left1 = 9; 
const int left2 = 10; // left1 and left2 are the 2 inputs for the left motor's h-bridge

const int leftr = A0; // leftr and rightr are the 2 input pins for the left and right photoresistor
const int rightr = A1;  

void setup() { // this code only runs once

      Serial.begin(9600); // for debugging using console

      // initialize the indicator LED
      pinMode(light,OUTPUT);
      digitalWrite (light, LOW);
      // initialize start button as an input
      pinMode(button,INPUT);
      
      // right motor ~ declares output pins left1,left2
      pinMode(left1,OUTPUT);
      pinMode(left2,OUTPUT);
      
      // left motor ~ declares output pins right1,right2
      pinMode(right1,OUTPUT);
      pinMode(right2,OUTPUT);
     
      // initialize left photoresistor as an input
      pinMode(leftr,INPUT);
      // initialize right photoresistor as an input
      pinMode(rightr,INPUT);    
      
      //Bot doesn't start scanning black colour until the push button is pressed
      while (digitalRead (button) == LOW) {
          delay(1); // puts the robot on a infinite delay loop to prevent it from moving
      }

      // LED blinks once to indicate scan complete
      digitalWrite (light, HIGH);
      delay (500);
      digitalWrite (light, LOW);
      delay (500);
    
      //  Bot reads the colour white and intializes it into the colour variable
      leftwhite = analogRead (leftr);
      Serial.println("left white value:");
      Serial.println(leftwhite);

      //Bot doesn't start scanning second white colour until the push button is pressed
      while (digitalRead (button) == LOW) {
          delay(1); // puts the robot on a infinite delay loop to prevent it from moving
      }

      // LED blinks once to indicate scan complete
      digitalWrite (light, HIGH);
      delay (500);
      digitalWrite (light, LOW);
      delay (500);

      //  Bot reads the colour white and intializes it into the colour variable
      rightwhite = analogRead (rightr);
      Serial.println("right white value:");
      Serial.println(rightwhite);
      
      // after the 3 scans, the next button press will allow the robot to move
      while (digitalRead (button) == LOW) {
          delay(1);
      }
}

// all the movement functions:

void forwards (){ // bot moves forwards
    //right motor
    digitalWrite(right1,HIGH);
    digitalWrite(right2,LOW);
   
    //left motor
    digitalWrite (left1, LOW);
    digitalWrite (left2, HIGH);
}


void left (){ //bot turns left
    //right motor
    //while (analogRead (leftr) <= (leftwhite + lefttol) && analogRead (leftr) >= (leftwhite - lefttol)){
    digitalWrite (right1, HIGH);
    digitalWrite (right2, LOW);
  
    //left motor
    digitalWrite (left1, HIGH);
    digitalWrite (left2, LOW); 
    //}
}

void right () { // bot turns right
    //while (analogRead (rightr) <= (rightwhite + righttol) && analogRead (rightr) >= (rightwhite - righttol)){
      //right motor
    digitalWrite (right1, LOW );
    digitalWrite (right2, HIGH);
  
    //left motor
    digitalWrite (left1, LOW );
    digitalWrite (left2, HIGH );
    //}
}

void nogo (){ // bot brakes
    //right motor
    digitalWrite (right1, HIGH );
    digitalWrite (right2, HIGH);
  
    //left motor
    digitalWrite (left1, HIGH);
    digitalWrite (left2, HIGH); 
}

void loop() { // this part of the code repeats indefinitely

      // if the right photoresistor sense white, it turns right 
    if (analogRead (rightr) <= (rightwhite + righttol) && analogRead (rightr) >= (rightwhite - righttol)) {
        //while (analogRead (rightr) <= (rightwhite + righttol) && analogRead (rightr) >= (rightwhite - righttol)) {
             rightcolour = analogRead (rightr); // for debug
             Serial.println(rightcolour); // for debug
             Serial.println("turn right"); // for debug
             right (); // turns bot right
             delay (50);
             nogo ();
             delay (200);
             count += 1;

             if (count > 50)
            {
              forwards (); // moves bot forwards
              delay (200);
              nogo ();
              delay (30);
              count = 0;
            }
        //} 
    }
  
    // if the left photoresistor sense white, it turns left
    else if (analogRead (leftr) <= (leftwhite + lefttol) && analogRead (leftr) >= (leftwhite - lefttol)) { 
        //while (analogRead (leftr) <= (leftwhite + lefttol) && analogRead (leftr) >= (leftwhite - lefttol)) { 
            leftcolour = analogRead (leftr); // for debug
            Serial.println(leftcolour); // for debug
            Serial.println("turn left"); // for debug
            left(); // turns bot left
            delay (50);
            nogo ();
            delay (200);
            count += 1;

            if (count > 50)
            {
              forwards (); // moves bot forwards
              delay (200);
              nogo ();
              delay (30);
              count = 0;
            }
        //}   
    }

    if the right photoresistor senses black, it brakes
    if (analogRead (rightr) <= (rightblack + 30) && analogRead (rightr) >= (rightblack - 30)){
         while (analogRead (rightr) <= (rightblack + 30) && analogRead (rightr) >= (rightblack - 30)){
              rightcolour = analogRead (rightr); // for debug
              Serial.println(rightcolour); // for debug
              Serial.println("brake right"); // for debug
              nogo (); // brakes bot
              delay (500);
         }         
    }
  
    // if the left photoresistor senses black, it brakes
    if (analogRead (leftr) <= (leftblack + 30) && analogRead (leftr) >= (leftblack - 30) ){
         while (analogRead (leftr) <= (leftblack + 30) && analogRead (leftr) >= (leftblack - 30) ){
              leftcolour = analogRead (leftr);  // for debug
              Serial.println(leftcolour); // for debug
              Serial.println("brake left"); // for debug
              nogo (); // brakes bot
              delay (500);
         }             
    }
  
    else{
        // bot moves forwards while nothing is detected
         leftcolour = analogRead (leftr);  // for debug
         rightcolour = analogRead (rightr);  // for debug
         Serial.println(leftcolour);  // for debug
         Serial.println(rightcolour);  // for debug
         Serial.println("forward");  // for debug
         
         forwards (); // moves bot forwards
         delay (40);
         nogo ();
         delay (50);

         count = 0;
    }
 
}
