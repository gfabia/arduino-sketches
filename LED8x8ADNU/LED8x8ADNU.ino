// Sketch to display the text "ADNU", one character per quadrant, on an 8x8 led (bi-color) matrix 
// Author: Glenn G. Fabia

int ROW_pins[] = {13,12,11,10,17,16,15,14};
int COL_pins[] = {9,8,7,6,5,4,3,2};

int MAX_PINS = 8;

int A [4][4] = {{0,1,1,0},{1,0,0,1},{1,1,1,1},{1,0,0,1}};
int D [4][4] = {{1,1,1,0},{1,0,0,1},{1,0,0,1},{1,1,1,0}};
int N [4][4] = {{1,0,0,1},{1,1,0,1},{1,0,1,1},{1,0,0,1}};
int U [4][4] = {{1,0,0,1},{1,0,0,1},{1,0,0,1},{0,1,1,0}};

int count = 0;

int ADNU[8][8] = {{0,1,1,0,1,1,1,0},
                  {1,0,0,1,1,0,0,1},
                  {1,1,1,1,1,0,0,1},
                  {1,0,0,1,1,1,1,0},
                  {1,0,0,1,1,0,0,1},
                  {1,1,0,1,1,0,0,1},
                  {1,0,1,1,1,0,0,1},
                  {1,0,0,1,0,1,1,0}};

int refresh_rate = 30;
void setup() {
   for(int i = 0; i < MAX_PINS; i++) {
       pinMode(ROW_pins[i], OUTPUT);  
       pinMode(COL_pins[i], OUTPUT);  
   }
  Serial.begin(9600);
}
void loop() {

   int v = analogRead(A4);
   refresh_rate = map(v, 0, 1023, 0, 500);

   int displayTime = refresh_rate;
   if(count < displayTime) {
     drawLetter(A,0,0);
   } else if (count < displayTime*2) {
     drawLetter(D,0,4);
   } else if (count < displayTime*3) {
     drawLetter(N,4,0);
   } else if (count < displayTime*4) {
      drawLetter(U,4,4);
   } else if (count < displayTime*5) {
       drawADNU();
   } else if (count < displayTime*6) {
       drawAll();  
   } else {
       clearScreen();
   }
   count = (count + 1) % (displayTime * 7) ;
   Serial.println(refresh_rate);
}


void drawRandomPixel(){
     int col = rand() % MAX_PINS;
     int row = rand() % MAX_PINS;
     drawPixel(row, col);
}

void drawPixel(int row, int col){
       digitalWrite(ROW_pins[row], HIGH);  
       for(int i = 0; i < MAX_PINS; i++)
           digitalWrite(COL_pins[i], HIGH); 
       digitalWrite(COL_pins[col], LOW); 
           
}

void drawAll(){
   for(int i = 0; i < MAX_PINS; i++) {
       digitalWrite(ROW_pins[i], HIGH);  
       digitalWrite(COL_pins[i], LOW);  
   }
}

void drawADNU(){
    for(int r = 0; r < 8; r++){
        digitalWrite(ROW_pins[r], HIGH);
        for(int c = 0; c < 8; c++){
                digitalWrite(COL_pins[c], HIGH);
          
        }
        for(int c = 0; c < 8; c++){
            digitalWrite(COL_pins[c], !ADNU[r][c]);
        }
             
        delay(1); 
        digitalWrite(ROW_pins[r], LOW);
    }
}

void drawLetter(int letter[][4], int startRow, int startCol) {
     for(int r = 0; r <  4; r++){

        if(startRow + r < MAX_PINS)
          digitalWrite(ROW_pins[startRow + r], HIGH);
        for(int c = 0; c < 8; c++){
                digitalWrite(COL_pins[c], HIGH);
        }
         for(int c = 0; c < 4; c++){
              if(startCol + c < MAX_PINS) {
                     digitalWrite(COL_pins[startCol + c], !letter[r][c]);
              }
         }
        
        delay(1);
        digitalWrite(ROW_pins[startRow + r], LOW); 
     }
}

void clearScreen(){
   for(int i = 0; i < MAX_PINS; i++) {
       digitalWrite(ROW_pins[i], LOW);  
       digitalWrite(COL_pins[i], LOW);  
   }
}

