  /*
  =====================================================
  Maze Runner 2 !!!!!!
  =====================================================

  */
  #include <stdbool.h>
  #include <AFMotor.h>

  //AF_DCMotor motor(2);

  AF_DCMotor motor(3, MOTOR12_8KHZ);  //left motor
  AF_DCMotor motor2(4, MOTOR12_1KHZ);  //right motor








  void setup() {

    Serial.begin(9600);
    Serial.println("Motor Test!");

    //set pin analog pin to input
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);

    //set motor speed
    motor.setSpeed(200);
    motor2.setSpeed(200);

    Serial.begin(9600); // Starts the serial communication

    delay(2000);

  }



  void loop() {

    //if sensor value < 100 sensor is on (white surface)
    //if sensor value > 1000 || 500 sensor in off (black surface)

    /*
    Sensor 1: furthest Right -> analogPin 0
    Sensor 2: Middle Right   -> analogPin 1
    Sensor 3: Middle Left    -> analogPin 2
    Sensor 4: Furthest Left  -> analogPin 3
    */

    Serial.println("=============================================");
    Serial.print("Sensor0: "); Serial.println(analogRead(0));
    Serial.print("Sensor1: "); Serial.println(analogRead(1));
    Serial.print("Sensor2: "); Serial.println(analogRead(2));
    Serial.print("Sensor3: "); Serial.println(analogRead(3));
    Serial.println("=============================================");
    Serial.print("bool Right"); Serial.println(junctionRight());
    Serial.print("bool Left"); Serial.println(junctionLeft());
    delay(1000);
    




if(straightLine() == true)
  {
    forward();
  }
  else if (outOfBoundToRight() == true)
  {
      leftTurn();
     
  }
  else if (outOfBoundToLeft() == true)
  {
      rightTurn();     
  }

else if(foundJunction() == true)
{
  enterJunction();
}
else if(endOfLine() == true)
{
  turnAround();
}
else if(tJunction() == true)
{
  enterRightJunction();
}
else
{
  turnAround();
}














    

  }  //end loop()




  //============================Sensing============================

  bool junctionRight(){
    
    // 1/true == RIGHT
    // 0/FALSE == LEFT
      if( (analogRead(0)>500) && (analogRead(1)>500) && (analogRead(2)>500) && (analogRead(3)<100) )
      {   //right junction detected
      
      return true;
      }
      else
      {
        return false;
      }
  }

bool junctionLeft(){
  if(   (analogRead(3)>500) && (analogRead(1)>500) && (analogRead(2)>500) && (analogRead(0)<100) )
  {  //left junction detected   
    return true; 
  }
  else
  {
    return false;
  }
}

bool foundJunction(){
  if(junctionLeft() == true || junctionRight() == true)
  {
    return true;
  }
  else
  {
    return false;
  }
}


  bool straightLine(){

    if( (analogRead(1) && analogRead(2) > 500) && ((analogRead(0) && analogRead(3) < 100)) ){

      return true;
    }else{
      return false;
    }

  }

  bool outOfBoundToLeft(){  
    if ( (analogRead(3)&&analogRead(2) < 100) && (analogRead(0)&&analogRead(1) > 500)  ){

      return true;
    } else{
      return false;
    }
  }

  bool outOfBoundToRight(){
    if( (analogRead(0)&&analogRead(1) < 100) && (analogRead(2)&&analogRead(3) > 500) ){

      return true;
    } else{
      return false;
    }
  }

  bool endOfLine(){
    if ( (analogRead(0) && analogRead(1) && analogRead(2) && analogRead(3)) <100 ){    //all sensor ON (white surface)
      return true;
    } else {
      return false;
    }

  }

  bool tJunction(){

    if ( (analogRead(0) && analogRead(1) && analogRead(2) && analogRead(3)) > 500 ){    //all sensor OFF (Black surface)
      return true;
    } else {
      return false;
    }

  }



  //============================Sensing============================

//============================Entering Junction============================

  void enterLeftJunction()
  {
    while(!straightLine())
    {
      leftTurn();
    }   
  }

  void enterRightJunction(){
    while(!straightLine())
    {
      rightTurn();
    }    
  }

  //============================Entering Junction============================




  //============================Decision============================    
  //============================Decision============================






  //============================Movement============================

  void forward(){

    motor.run(FORWARD);  //left motor
    motor2.run(FORWARD);  //right motor

  }

  void backward(){
    motor.run(BACKWARD);  //left motor
    motor2.run(BACKWARD);  //right motor
  }

  void stopMotor(){
    motor.run(RELEASE);  //left motor
    motor2.run(RELEASE);  //right motor
  }

  void leftTurn(){

    motor.run(RELEASE);  //left motor
    motor2.run(FORWARD);  //right motor

  }

  void rightTurn(){

    motor.run(FORWARD);  //left motor
    motor2.run(RELEASE);  //right motor

  }

  void turnAround(){

    while( !straightLine() ){
      motor.run(BACKWARD);  //left motor
      motor2.run(FORWARD);  //right motor
    }
    stopMotor();
  }

void move()
{

  if(straightLine() == true)
  {
    forward();
  }
  else if (outOfBoundToRight() == true)
  {
    leftTurn();
  }
  else if (outOfBoundToLeft() == true)
  {
    rightTurn();
  }

}

void enterJunction()
{
  if(foundJunction() == true && junctionRight() == true)
  {
    enterRightJunction();
  }
  else if(foundJunction() == true && junctionLeft() == true)
  {
    enterLeftJunction();
  }
}

  //============================Movement============================


  


