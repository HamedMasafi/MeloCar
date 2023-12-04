#include "pitches.h"
#include "themes.h"
#define melodyPin 8
//Mario main theme melody


void setup2(void)
{
   pinMode(melodyPin, OUTPUT);//buzzer
   pinMode(13, OUTPUT);//led indicator when singing a note
pinMode(2, INPUT_PULLUP); //Button 1 with internal pull up
pinMode(3, INPUT_PULLUP); //Button 2 with internal pull up
pinMode(4, INPUT_PULLUP); //Button 3 with internal pull up
pinMode(5, INPUT_PULLUP); //Button 4 with internal pull up
pinMode(6, INPUT_PULLUP); //Button 4 with internal pull up
Serial.begin(9600);
}
// void loop2()
// {

//     if (digitalRead(2)==0)
//       { Serial.println("Selected -> 'Super Mario Main Theme' ");   sing(1);  }
//     if (digitalRead(3)==0)
//       { Serial.println("Selected -> 'Super Mario underworld' ");   sing(2);  }
//     if (digitalRead(4)==0)
//       { Serial.println("Selected -> 'Pirates Theme' ");            sing(3);  }
//     if (digitalRead(5)==0)
//       { Serial.println("Selected -> 'CrazyFrog Theme' ");          sing(4);  }
//     if (digitalRead(6)==0)
//       { Serial.println("Selected -> 'Titanic Theme' ");            sing(5);  }

// }












void buzz(int targetPin, long frequency, long length) {
 // digitalWrite(13,HIGH);
  long delayValue = 1000000/frequency/2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length/ 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to 
  //// get the total number of cycles to produce
  for (long i=0; i < numCycles; i++){ // for the calculated length of time...
    digitalWrite(targetPin,HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin,LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
//  digitalWrite(13,LOW);
}





void play_melody(int *melody, int *tempo, int melody_size){
     int size = melody_size;

     for (int thisNote = 0; thisNote < size; thisNote++) {

       // to calculate the note duration, take one second
       // divided by the note type.
       //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
       int noteDuration = 1000/tempo[thisNote];

       buzz(melodyPin, melody[thisNote],noteDuration);

       // to distinguish the notes, set a minimum time between them.
       // the note's duration + 30% seems to work well:
       int pauseBetweenNotes = noteDuration * 1.30;
       delay(pauseBetweenNotes);

       // stop the tone playing:
       buzz(melodyPin, 0,noteDuration);
    }
  
  }



  
void sing(int s){

   // iterate over the notes of the melody:
   int song = s;
   if(song==1){
     play_melody(mario_note, mario_duration, sizeof(mario_note)/sizeof(int));
   }else if(song==2){
     play_melody(MarioUW_note, MarioUW_duration, sizeof(MarioUW_note)/sizeof(int));
   }else if(song==3){
     play_melody(Pirates_note, Pirates_duration, sizeof(Pirates_note)/sizeof(int));
   }else if(song==4){
     play_melody(CrazyFrog_note, CrazyFrog_duration, sizeof(CrazyFrog_note)/sizeof(int));
   }else{
     play_melody(Titanic_note, Titanic_duration, sizeof(Titanic_note)/sizeof(int));
  }
  
}
