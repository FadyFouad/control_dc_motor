
bool leftflage = false ;
bool rightflage = false ;
long DL = 0;
long DR = 0;
int lefttickscount = 0 ;
int righttickscount = 0 ;
int leftencoderval = 0;
int rightencoderval = 0;

unsigned int rpm_l;
unsigned int w_l;
unsigned long timeold_l;
unsigned int rpm_r;
unsigned int w_r;
unsigned long timeold_r;

int leftdes(){
  return (22.0/7.0)*7.0*(DL);  
}

int rightdes(){
  return (22.0/7.0)*7.0*(DR); 
}


int dl(){
//  return DL ;
  
  chatter.publish( &str_msg );
  return rpm_l;
}

int dr(){
//  return DR ;
  str_msg.data = rpm_r;
  chatter.publish( &str_msg );
  return rpm_r;
}


//void ticks(char type ,int* val,int* tickscount,long* D,bool* flage){
////        Serial.println(*val);
//    if(*val > 500 ){
//      *flage = true ;
//       
//    }else{
//      if(*flage == true){
//        *tickscount = *tickscount+1 ;
////        ticksprint(type);
//      }
//      if(*tickscount%20 == 0 && *flage == true){
//        *D = *D +  1;
////        *tickscount = 0;
////        roundprint(type);
//        
//      }
//      *flage = false ;
//  }
//}


void leftticks(){
    //    Serial.println(val);
    if(digitalRead(20) == 1 ){
      leftflage = true ;
    }else{
      if(leftflage == true){
        lefttickscount ++ ;

      }
      if(lefttickscount%20 == 0 && leftflage == true){
        DL ++;
        rpm_l =(lefttickscount)*30*1000/(millis() - timeold_l);
        str_msg.data = rpm_l;
        w_l = (2*3.14*rpm_l)/60 ;
        timeold_l = millis();
        lefttickscount = 0;
      }
      leftflage = false ;
  }
}

void rightticks(){
    //    Serial.println(val);
    if(digitalRead(21) == 1  ){
      rightflage = true ;
    }else{
      if(rightflage == true){
        righttickscount ++ ;
      }
      if(righttickscount%20 == 0 && rightflage == true){
        DR ++;
        rpm_r =(righttickscount)*30*1000/(millis() - timeold_r);
        str_msg.data = rpm_r;
        w_r = (2*3.14*rpm_r)/60 ;
        timeold_r = millis();
        righttickscount = 0;    
      }
      rightflage = false ;
  }
}


 void roundprint(char type){
  if (type == 'l'){
      Serial.print("left Round");Serial.print("  ");Serial.print(DL);
      Serial.println();
  
  }else if (type == 'r'){
     Serial.print("right Round");Serial.print("  ");Serial.print(DR);
     Serial.println();
    
  }
  }
  void ticksprint(char type){
  if (type == 'l'){
      Serial.print("left tick");Serial.print("  ");Serial.print(lefttickscount);
      Serial.println();
  
  }else if (type == 'r'){
     Serial.print("right tick");Serial.print("  ");Serial.print(righttickscount);
     Serial.println();
    
  }
  }


  