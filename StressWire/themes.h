/*
 * The themes given below were converted from the piano sheet music 
 * First Code by : B.Aswinth Raj
 * Editted by : Sina From sisoog.com
 * Dated: 15-06-2017
 * Website: CircuitDigest.com
 */

//##############**" Super mario main **##############//
int mario_note[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7, 
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0, 

  NOTE_C7, 0, 0, NOTE_G6, 
  0, 0, NOTE_E6, 0, 
  0, NOTE_A6, 0, NOTE_B6, 
  0, NOTE_AS6, NOTE_A6, 0, 

  NOTE_G6, NOTE_E7, NOTE_G7, 
  NOTE_A7, 0, NOTE_F7, NOTE_G7, 
  0, NOTE_E7, 0,NOTE_C7, 
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6, 
  0, 0, NOTE_E6, 0, 
  0, NOTE_A6, 0, NOTE_B6, 
  0, NOTE_AS6, NOTE_A6, 0, 

  NOTE_G6, NOTE_E7, NOTE_G7, 
  NOTE_A7, 0, NOTE_F7, NOTE_G7, 
  0, NOTE_E7, 0,NOTE_C7, 
  NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
int mario_duration[] = {
  12, 12, 12, 12, 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12, 

  12, 12, 12, 12,
  12, 12, 12, 12, 
  12, 12, 12, 12, 
  12, 12, 12, 12, 

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};


//##############**"End of super mario main**##############//


//##############**"Mario underworld" **##############//
int MarioUW_note[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,NOTE_AS3, NOTE_AS4, 0, 0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_AS3, NOTE_AS4, 0,0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,NOTE_DS3, NOTE_DS4, 0, 0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4, NOTE_DS4, NOTE_GS3, NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,  NOTE_AS3, NOTE_A3, NOTE_GS3,0, 0, 0
};
int MarioUW_duration[] = {
 12, 12, 12, 12,12, 12, 6,3,
 12, 12, 12, 12, 12, 12, 6, 3,
 12, 12, 12, 12, 12, 12, 6,
 3, 12, 12, 12, 12,
 12, 12, 6, 6, 18, 18, 18,
 6, 6, 6, 6,6, 6,
 18, 18, 18, 18, 18, 18, 10, 10, 10,
 10, 10, 10, 3, 3, 3
};
//###########End of Mario underworld#############//



//##############**"HE IS A PIRATE" Theme song of Pirates of caribbean**##############//
int Pirates_note[] = {
NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4,
NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, 
NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4,  
NOTE_A3, NOTE_C4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_F4, 
NOTE_F4, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_C4, NOTE_D4,
0, NOTE_A3, NOTE_C4, NOTE_B3, NOTE_D4, NOTE_B3, NOTE_E4, NOTE_F4,
NOTE_F4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4,
NOTE_D4, 0, 0, NOTE_A3, NOTE_C4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_F4,
NOTE_G4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_G4,
NOTE_A4, NOTE_D4, 0, NOTE_D4, NOTE_E3, NOTE_F4, NOTE_F4, NOTE_G4, NOTE_A4, 
NOTE_D4, 0, NOTE_D4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_F4, NOTE_D4
};
int Pirates_duration[] = {
4,8,4,8,4,8,8,8,8,4,8,4,8,4,8,8,8,8,4,8,4,8,
4,8,8,8,8,4,4,8,8,4,4,8,8,4,4,8,8,
8,4,8,8,8,4,4,8,8,4,4,8,8,4,4,8,4,
4,8,8,8,8,4,4,8,8,4,4,8,8,4,4,8,8,
8,4,8,8,8,4,4,4,8,4,8,8,8,4,4,8,8
};
//###########End of He is a Pirate song#############//


//##############**"Crazy Frog" song of Crazy frog album**##############//
int CrazyFrog_note[] = {
  NOTE_D4, 0, NOTE_F4, NOTE_D4, 0, NOTE_D4, NOTE_G4, NOTE_D4, NOTE_C4,
  NOTE_D4, 0, NOTE_A4, NOTE_D4, 0, NOTE_D4, NOTE_AS4, NOTE_A4, NOTE_F4,
  NOTE_D4, NOTE_A4, NOTE_D5, NOTE_D4, NOTE_C4, 0, NOTE_C4, NOTE_A3, NOTE_E4, NOTE_D4,
  0,NOTE_D4,NOTE_D4
};
int CrazyFrog_duration[] = {
  8, 8, 6, 16, 16, 16, 8, 8, 8, 
  8, 8, 6, 16, 16, 16, 8, 8, 8,
  8, 8, 8, 16, 16, 16, 16, 8, 8, 2,
  8,4,4
};
//###########End of Crazy Frog#############//






//##############**"Titanic" **##############//
int Titanic_note[] = {
NOTE_E4, NOTE_B4, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_B4, NOTE_E4, NOTE_E4, NOTE_B4, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_B4, NOTE_E4, NOTE_E4, NOTE_B4, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_B4, NOTE_E4,
NOTE_E4, NOTE_B4, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_D5, NOTE_E4, NOTE_B4, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_B4, NOTE_E4, NOTE_E4, NOTE_B4, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_B4, NOTE_F5,
NOTE_E4, NOTE_B4, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_B4, NOTE_E4,
NOTE_E4, NOTE_B4, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_D5, NOTE_E5, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_B3, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_B3, NOTE_E4,
NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4


};
int Titanic_duration[] = {
8,8,8,8,8,8,4,8,8,8,8,8,8,4,8,8,8,8,8,8,4,8,8,8,8,4,4,8,8,8,8,8,8,4,8,8,8,8,8,8,4,8,8,8,8,8,8,1,
8,8,8,8,4,4,4,8,4,4,8,8,8,8,4,8,8,4,8,4,8,8,4,8,4,1



};
//###########End of Titanic#############//
