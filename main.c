//Colin Wilkins and Trenton Sanders
//April 16, 2014
//EE 3280, Dr. Bolding
//HW 2 - The Little Doctor

#include <device.h>
#include <stdlib.h>
#include <stdio.h>

void crosshair(int, int, int);  //Draws the crosshair
void blast(int, int, int, int); //Draws blast explosion, destroys stars
void color(int);    //Determines blast charge light
int distance(int, int, int, int); //Returns distancce b/w two points
void cornerScreen1(int);   //Player 1's score display
void cornerScreen2(int);   //Player 2's score display

//Global variabkes so functions change values
int coordx [200]={0};           //star x coordinate
int coordy [200]={0};           //star y coordinate
int score1=0;   //Score for p1
int score2=0;   //Score for p2

int main()
{
    //Variables to be sent
    int xcenter = 66;           //Starting x coord for crosshair
    int ycenter = 66;           //Starting y coord for crosshair
    int blast_status = 0;       //Blast status to be sent
    uint16 send;                //A combination of the above
    
    //Variables to be retrieved
    int other_blast_status =0;  //p2 blast status
    int other_xCenter = 66;     //p2 x coord
    int other_yCenter =66;      //p2 y coord
    uint16 receive;             //A combination of the above

    
    //Other
    int other_old_xCenter = 0;  //Previous p2 cursor locations that allow drawing "movement"
    int other_old_yCenter = 0;  
    uint32 slowtwinkle = 0;     //Used for twinkling
    int randstar = 0;
    int timer = 0;              //Used for counting loop cycles
    int power = 1;              //Blast size
    

    
    // Initialize LCD
    GLCD_Start();  
    Com_Block_Start();          //Starts the slave module

    // clear LCD to black color
    GLCD_Clear(GLCD_BLACK);

    int i;
    for (i = 0;i<200;i++)
    {
        int x = (rand()%124)+4;
        int y = (rand()%124)+4;
        
        coordx[i] = x;
        coordy[i] = y;
    }

    //start w/ red light
    Blast_Red_Write(0);
    
while(1){   //Inf loop

    if(slowtwinkle%4==0) //every ten loops
        randstar = rand()%200; //Assign new star to twinkle
    slowtwinkle++;//Increment every loop
   
    //Draw stars    
    for(i=0;i<200;i++){  
        if(i%5 == 0)
            GLCD_Pixel(coordx[i], coordy[i], GLCD_WHITE);
        if(i%5 == 1)
            GLCD_Pixel(coordx[i], coordy[i], GLCD_ORANGE);
        if(i%5 == 2)
            GLCD_Pixel(coordx[i], coordy[i], GLCD_WHITE);
        if(i%5 == 3)
            GLCD_Pixel(coordx[i], coordy[i], GLCD_GOLD);
        if(i%5 == 4)
            GLCD_Pixel(coordx[i], coordy[i], GLCD_WHITE);        
        
        //Make stars twinkle
        if((i < randstar)&&(randstar < i+20)) {
            GLCD_Pixel(coordx[randstar], coordy[randstar], GLCD_BLACK);
        }
    }
    
    if(Com_Block_GetRxBufferSize() >= 1)    //If there is data, then it will execute
    {
        receive = Com_Block_ReadRxData();
        other_xCenter = receive & 127;                  //get first 7 bits - xcoord
        other_yCenter = receive & 16256;                //get next 7 bits - ycoord
        other_yCenter = other_yCenter >> 7;             //shift to get ycoord bits
        other_blast_status = receive & 49152;           //get last 2 bits - blast status
        other_blast_status = other_blast_status >> 14;  //shift to get blast status bits
    }

   
    //Draw other player, redraw old crosshair black if moved
    if((other_old_xCenter != other_xCenter) || (other_old_yCenter != other_yCenter)){
        crosshair(other_old_xCenter,other_old_yCenter, GLCD_BLACK);
    }
        crosshair(other_xCenter, other_yCenter, GLCD_BLUE);
        other_old_xCenter = other_xCenter;
        other_old_yCenter = other_yCenter;
    
    //Draw yourself
    crosshair(xcenter, ycenter, GLCD_ORANGE);
    
    blast_status = 0;   //Default blast status to no blast
        
    //Move cursor
    //Crosshair doesn't move past points 112 and 20 (collide with screen edge)
    //Right
    if(!Move_Right_Read()){
        if(ycenter < 112){  //Edge collision
            crosshair(xcenter,ycenter,GLCD_BLACK);  //Delete old cursor
            ycenter++;  //Move
        }
            crosshair(xcenter,ycenter,GLCD_ORANGE); //Draw new location
    }

    //Left
    if(!Move_Left_Read()){
        if(ycenter > 20){
            crosshair(xcenter,ycenter,GLCD_BLACK);
            ycenter--;
        }
            crosshair(xcenter,ycenter,GLCD_ORANGE);
    }
    
    //Up
    if(!Move_Up_Read()){
        if(xcenter > 20){
            crosshair(xcenter,ycenter,GLCD_BLACK);
            xcenter--;
        }
            crosshair(xcenter,ycenter,GLCD_ORANGE);        
    }
    
    //Down
    if(!Move_Down_Read()){
        if(xcenter < 112){
            crosshair(xcenter,ycenter,GLCD_BLACK);
            xcenter++;
        }
            crosshair(xcenter,ycenter,GLCD_ORANGE);       
    }
   
    //Fire explosions
    //My explosion
    if(!Blast_Read()){
        blast_status = power;       //Sets status to proper explosion size
        blast(xcenter,ycenter,power,0);
        power = 0;  //Just fired
        color(power); //Update LED light
    }
    
    //P2 explosion
    if(other_blast_status)
    {
        blast(other_xCenter, other_yCenter, other_blast_status,1); //What a mouthful
    }
    
    //Blast charge-up
    if((timer%100 == 0) && (power < 2)){ //Increment every 100 cycles, not past 2
        power++; 
        color(power); //Update LED
        }
    timer++;
    
    //Send data
    if(Com_Block_ReadTxStatus() & Com_Block_STS_TX_FIFO_NOT_FULL)
    {
        send = blast_status;
        send = send << 7;
        send += ycenter;
        send = send << 7;
        send += xcenter;
        Com_Block_WriteTxData(send);
    }
    
    //Win condition
    if((score1+score2)>199) {   //When all stars destroyed
        cornerScreen1(score1);  //P1's score
        cornerScreen2(score2);  //P2's score
        while(1);   //End game
    }
  }
}

void crosshair(int xcoord, int ycoord, int color){
    //Two lines, intersect at coordinates
    GLCD_DrawLine(xcoord,ycoord-15,xcoord,ycoord+15,color);
    GLCD_DrawLine(xcoord-15,ycoord,xcoord+15,ycoord,color);
    //Two circles
    GLCD_DrawCircle(xcoord,ycoord,10,color);
    GLCD_DrawCircle(xcoord,ycoord,5,color);
}

void blast(int xmiddle, int ymiddle, int power, int player){
    if(power){ //Don't fire if power == 0
        int j;
        for(j = 0; j<(power*20); j++){//Explosion alternates between green and orange
            GLCD_DrawCircle(xmiddle, ymiddle, j, GLCD_GREEN);
            j++;
            GLCD_DrawCircle(xmiddle, ymiddle, j, GLCD_ORANGE);
        }
        for(j = 0; j<(power*20)+1; j++){//Delete explosion
            GLCD_DrawCircle(xmiddle, ymiddle, j, GLCD_BLACK);
        }
        //Delete hit stars
        for(j=0;j<200;++j){
            if( //Check coordinates of all stars
                ((distance(coordx[j],xmiddle,coordy[j],ymiddle))<(((power*20)+1)*((power*20)+1)))    //If radius^2 < distance, star not hit
                && ((coordx[j]!=0)&&(coordy[j]!=0)))   //Stars at (0,0) already destroyed
                {
                    GLCD_Pixel(coordx[j],coordy[j],GLCD_BLACK); //Catches stars explosion doesn't draw over
                    coordx[j]=0;
                    coordy[j]=0;
                    if(player)  //Player=1 for p2, 0 for p1
                        ++score2;
                    else ++score1;
                }
        }
    }
}

void color(int level)
{
    if(level == 0){ //Red on
        Blast_Red_Write(0);
        Blast_Blue_Write(1);
        Blast_Green_Write(1);
    }
    if(level == 1){ //Blue on
        Blast_Red_Write(1);
        Blast_Blue_Write(0);
        Blast_Green_Write(1);
    }
    if(level == 2){ //Green on
        Blast_Red_Write(1);
        Blast_Blue_Write(1);
        Blast_Green_Write(0);
    }
}

void cornerScreen1(score)
{
    char scoreStr[20];
    sprintf(scoreStr, "%d Stars", (200-score));
    GLCD_DrawRect(0,20,50,110,1,GLCD_ORANGE); //Draw splash screen
    GLCD_PrintString(scoreStr,15,30,GLCD_BLACK,GLCD_ORANGE);
}

void cornerScreen2(score)
{
    char scoreStr[20];
    sprintf(scoreStr, "%d Stars", (200-score));
    GLCD_DrawRect(132,20,82,110,1,GLCD_BLUE); //Draw splash screen
    GLCD_PrintString(scoreStr,97,30,GLCD_BLACK,GLCD_BLUE);
}

inline int distance(x1,y1,x2,y2)
{
    return (((x1-y1)*(x1-y1))+((x2-y2)*(x2-y2)));
}