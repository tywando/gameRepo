#include <Adafruit_CircuitPlayground.h> //include CircuitPlayground Library
#include <AsyncDelay.h> //include AsyncDelay Library

volatile bool leftFlag = false; // flag for left button ISR
volatile bool rightFlag = false; // flag for right button ISR
volatile bool switchFlag = false; // flag for switch ISR
volatile bool gameFlag = false; // flag for starting and ending game

float pitchValues[4] = {261.63, 440, 523.25, 659.26}; //array with four tones that will be played
int colorValues[6] = {255, 0, 100, 50, 150, 200}; //array with 6 different values that will be used in color wheel
int color; //variable that is used to compare old and new color values
int note; //variable that is used to compare old and new tone values
int score = 0; //variable that keeps track of game score

void setup(void) {
  CircuitPlayground.begin(); //intialize CPX
  Serial.begin(9600); //starts serial monitor and tells it how fast to send bits
  attachInterrupt(4, left, RISING); //left button ISR
  attachInterrupt(5, right, RISING); //right button ISR
  attachInterrupt(7, flick, CHANGE); //switch ISR
  randomSeed(CircuitPlayground.lightSensor()); //create random sequence based on value of light sensor for randoms in loop
  while(!Serial); //wait to start game until serial monitor is oppen
  Serial.println("Start Game"); //print Start Game 
}

void loop() {
if (switchFlag == false) { //this plays normal mode of game 

if(gameFlag == false) { //gameFlag is checked to see if the game can run 
    
    int randNumber = random(6); //random number up to 6 for LED color 
    int randTone = random(4); //random number up to 4 for tone array. 

   for(int i = 0; i < 10; i++) { //for loop used to turn on all LEDs
    CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(colorValues[randNumber])); //turn on LEDs to color based on random number chosen from array
    }

    CircuitPlayground.playTone(pitchValues[randTone], 500); //play tone for 500 milliseconds based on random number chosen from array

    int oldColor = color; //store old color value 
    color = randNumber; //set color equal to the number chosen by random 
    int oldNote = note; //store old tone value 
    note = randTone; //set note equal to the number chosen by random 
    delay(500); //keep lights on for 500 milliseconds
    CircuitPlayground.clearPixels(); //turn off LEDs
    delay(2000); //wait 2000 milliseconds for response from inputs

 if(oldColor == color && leftFlag == true) { //if the previous color and new color are the same and the left button is pressed
  Serial.print("Score:"); //prints Score:
  Serial.println(++score); //prints out value of score and increments each time due to how many points you win
  leftFlag = false; //set left button flag back to false so game can continue
 }

 if(oldColor != color && leftFlag == true) { //if the previous color and new color are not the same and the left button is pressed
  Serial.println("Game Over"); //print Game Over beacuse player pressed button at wrong time
  leftFlag = false; //set left button flag back to false so game can continue once player starts again
  gameFlag = true; //this stops the game by setting the game flag to true
  score = 0; //resets score for nex time the player starts the game
 }

 if(oldNote == note && rightFlag == true) {  //if the previous tone and new tone are the same and the right button is pressed
  Serial.print("Score:"); //prints Score:
  Serial.println(++score); //prints out value of score and increments each time due to how many points you win
  rightFlag = false; //set right button flag back to false so game can continue
 }

 if(oldNote != note && rightFlag == true) { //if the previous tone and new tone are not the same and the right button is pressed
  Serial.println("Game Over"); //print Game Over beacuse player pressed button at wrong time
  rightFlag = false; //set right button flag back to false so game can continue once player starts again
  gameFlag = true; //this stops the game by setting the game flag to true
  score = 0; //resets score for nex time the player starts the game
 }
}

if (rightFlag == true && leftFlag == true) { //if both buttons have been pressed down when game isn't playing
    delay(1000); //wait for one second to allow time for game to begin
    gameFlag = false; //start new game by setting game flag back to false
    leftFlag = false; //set left button flag back to false so game can continue
    rightFlag = false; //set right button flag back to false so game can continue
    Serial.println("Start Game"); //print Start Game 
  }
}

else { //this plays hard mode of game 

 if(gameFlag == false) { //gameFlag is checked to see if the game can run 
    
    int randNumber = random(6); //random number up to 6 for LED color 
    int randTone = random(4); //random number up to 4 for tone array. 

   for(int i = 0; i < 10; i++) { //for loop used to turn on all LEDs
    CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(colorValues[randNumber])); //turn on LEDs to color based on random number chosen from array
    }

    CircuitPlayground.playTone(pitchValues[randTone], 100); //play tone for 500 milliseconds based on random number chosen from array

    int oldColor = color; //store old color value 
    color = randNumber; //set color equal to the number chosen by random 
    int oldNote = note; //store old tone value 
    note = randTone; //set note equal to the number chosen by random 
    delay(100); //keep lights on for 100 milliseconds
    CircuitPlayground.clearPixels(); //turn off LEDs
    delay(1250); //wait 1250 milliseconds for response from inputs

 if(oldColor == color && leftFlag == true) { //if the previous color and new color are the same and the left button is pressed
  Serial.print("Score:"); //prints Score:
  Serial.println(++score); //prints out value of score and increments each time due to how many points you win
  leftFlag = false; //set left button flag back to false so game can continue
 }

 if(oldColor != color && leftFlag == true) { //if the previous color and new color are not the same and the left button is pressed
  Serial.println("Game Over"); //print Game Over beacuse player pressed button at wrong time
  leftFlag = false; //set left button flag back to false so game can continue once player starts again
  gameFlag = true; //this stops the game by setting the game flag to true
  score = 0; //resets score for nex time the player starts the game
 }

 if(oldNote == note && rightFlag == true) {  //if the previous tone and new tone are the same and the right button is pressed
  Serial.print("Score:"); //prints Score:
  Serial.println(++score); //prints out value of score and increments each time due to how many points you win
  rightFlag = false; //set right button flag back to false so game can continue
 }

 if(oldNote != note && rightFlag == true) { //if the previous tone and new tone are not the same and the right button is pressed
  Serial.println("Game Over"); //print Game Over beacuse player pressed button at wrong time
  rightFlag = false; //set right button flag back to false so game can continue once player starts again
  gameFlag = true; //this stops the game by setting the game flag to true
  score = 0; //resets score for nex time the player starts the game
 }
}

if (rightFlag == true && leftFlag == true) { //if both buttons have been pressed down when game isn't playing
    delay(1000); //wait for one second to allow time for game to begin
    gameFlag = false; //start new game by setting game flag back to false
    leftFlag = false; //set left button flag back to false so game can continue
    rightFlag = false; //set right button flag back to false so game can continue
    Serial.println("Start Game"); //print Start Game 
  }
}
}

void left() { //left button ISR function 
  leftFlag = true; //triggers if statements in loop
}

void right() { //right button ISR function 
  rightFlag = true; //triggers if statements in loop
}

void flick() { //switch ISR function
  delay(1000); //use delay to debounce and give time to switch between normal and hard mode
  score = 0; //each time you change modes the score will reset
   if(switchFlag == true){ 
    switchFlag = false; //this plays normal mode 
  } else{
    switchFlag = true; //this plays hard mode
  }
}