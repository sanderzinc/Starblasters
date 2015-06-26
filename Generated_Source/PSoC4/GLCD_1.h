
/*******************************************************************************
* File Name: GLCD_1.h  
* Version 0.3
*
*  Description:
*    This file contains all the API function prototypes for the SparkFun Color 
*    Graphics Arduino Shield board which uses a Nokia 6100 LCD.
*
* Note:  This code has been tested with the Philips PCF8833 controller, but not
*        the EPSON S115D10 controller as of release 0.3.
*******************************************************************************
* The following firmware was developed by Cypress Semiconductor
* This work is licensed under a Creative Commons Attribution 3.0 Unported License.
*
* http://creativecommons.org/licenses/by/3.0/deed.en_US
* 
* You are free to:
* -To Share — to copy, distribute and transmit the work 
* -To Remix — to adapt the work 
* -To make commercial use of the work
*
* Much of this code was ported from the LCD_driver code by Mark Sproul
* and Peter DavenPort.  Also the tutorial by James P. Lynch
* on how the controller works was invaluable.
********************************************************************************/


#define GLCD_1_Controller     1
#define GLCD_1_PHILIPS         1u
#define GLCD_1_EPSON           0u

#define GLCD_1_SPIM            SPIM_SCB
#define GLCD_1_SPIM_TYPE       1
#define GLCD_1_SPIM_UDB_TYPE    0u 
#define GLCD_1_SPIM_SCB_TYPE    1u 


/*******************************************************
*				Function Prototypes                    
********************************************************/


void GLCD_1_Start(void);
void GLCD_1_Stop(void);
void GLCD_1_Clear(int32 color);
void GLCD_1_Contrast(int32 setting);

void GLCD_1_Pixel(int32 x, int32 y, int32 color );
void GLCD_1_DrawCircle (int32 x, int32 y, int32 radius, int32 color);

void GLCD_1_PrintChar(uint8 c, int32 x, int32 y, int32 fColor, int32 bColor);
void GLCD_1_PrintString(char *pString, int32 x, int32 y, int32 fColor, int32 bColor);

void GLCD_1_DrawLine(int32 x0, int32 y0, int32 x1, int32 y1, int32 color);
void GLCD_1_DrawRect(int32 x0, int32 y0, int32 x1, int32 y1, int32 fill, int32 color);

/* Low level commands used by the normal commands.  */
void  GLCD_1_Command(uint32 datacmd);
void  GLCD_1_Data(uint32 datadt);
int32 GLCD_1_SwapColors(int32 in);
void  GLCD_1_On(void);
void  GLCD_1_Off(void);


const uint8 GLCD_1_FONT8x16[97][16];


/********************************************************************
*                                                                  
*					LCD Dimension Definitions                       
*                                                                  
*********************************************************************/
#define GLCD_1_ROW_LENGTH  132
#define GLCD_1_COL_HEIGHT  132
#define GLCD_1_ENDPAGE     132
#define GLCD_1_ENDCOL      130

#define GLCD_1_MINX        0u
#define GLCD_1_MAXX        131u
#define GLCD_1_MINY        0u
#define GLCD_1_MAXY        131u




#if (GLCD_1_Controller == GLCD_1_EPSON)
#define GLCD_1_DISPON       0xAF	/* Display on         */
#define GLCD_1_DISPOFF      0xAE	/* Display off        */
#define GLCD_1_SLEEPIN      0x95	/* Sleep in           */
#define GLCD_1_SLEEPOUT     0x94	/* Sleep out          */
#define GLCD_1_DINVOFF      0xA6	/* Normal display     */
#define GLCD_1_DINVON       0xA7	/* Inverse display    */
#define GLCD_1_PAGEADDR     0x75	/* Page address set   */
#define GLCD_1_COLADDR      0x15	/* Column address set */
#define GLCD_1_RAMWR        0x5C	/* Writing to memory  */
#define GLCD_1_SETCONST     0x81	/* Electronic volume control (Contrast) */
#define GLCD_1_NOP          0x25	/* No op              */

#define	GLCD_1_CONST_MASK	   0x3F	/* Contrast Mask      */
#define	GLCD_1_CONST_DEFAULT 0x20	/* Default Contrast   */
#endif

#if (GLCD_1_Controller == GLCD_1_PHILIPS)
#define GLCD_1_DISPON      0x29	/* Display on            */
#define GLCD_1_DISPOFF     0x28	/* Display off           */
#define GLCD_1_SLEEPIN     0x10	/* Sleep in              */ 
#define	GLCD_1_SLEEPOUT	 0x11	/* Sleep out             */
#define	GLCD_1_DINVOFF	 0x20	/* Display inversion off */
#define GLCD_1_DINVON      0x21	/* Display inversion ona */
#define GLCD_1_PAGEADDR    0x2B	/* Page address set      */
#define GLCD_1_COLADDR     0x2A	/* Column address set    */
#define GLCD_1_RAMWR       0x2C	/* Memory write          */
#define	GLCD_1_SETCONST	 0x25	/* Set contrast          */
#define	GLCD_1_NOP  		 0x00	/* No operation          */
 
#define	GLCD_1_CONST_MASK	   0x7F	/* Contrast Mask         */
#define	GLCD_1_CONST_DEFAULT 0x30	/* Default Contrast      */

#endif

/* Command constants  */

/********************************************************************
*
*					EPSON Controller Definitions
*
*********************************************************************/

#define GLCD_1_COMSCN      0xBB	/* Common scan direction      */
#define GLCD_1_DISCTL      0xCA	/* Display control            */
#define GLCD_1_DATCTL      0xBC	/* Data scan direction, etc.  */
#define GLCD_1_RGBSET8     0xCE	/* 256-color position set     */
#define GLCD_1_RAMRD       0x5D	/* Reading from memory        */
#define GLCD_1_PTLIN       0xA8	/* Partial display in         */
#define GLCD_1_PTLOUT      0xA9	/* Partial display out        */
#define GLCD_1_RMWIN       0xE0	/* Read and modify write      */
#define GLCD_1_RMWOUT      0xEE	/* End                        */
#define GLCD_1_ASCSET      0xAA	/* Area scroll set            */
#define GLCD_1_SCSTART     0xAB	/* Scroll start set           */
#define GLCD_1_OSCON       0xD1	/* Internal oscillation on    */
#define GLCD_1_OSCOFF      0xD2	/* Internal osciallation off  */

#define GLCD_1_PWRCTR      0x20	/* Power control              */
#define GLCD_1_VOLUP       0xD6	/* Increment electronic control by 1 */
#define GLCD_1_VOLDOWN     0xD7	/* Decrement electronic control by 1 */
#define GLCD_1_TMPGRD      0x82	/* Temperature gradient set   */
#define GLCD_1_EPCTIN      0xCD	/* Control EEPROM             */
#define GLCD_1_EPCOUT      0xCC	/* Cancel EEPROM control      */
#define GLCD_1_EPMWR       0xFC	/* Write into EEPROM          */
#define GLCD_1_EPMRD       0xFD	/* Read from EEPROM           */
#define GLCD_1_EPSRRD1     0x7C	/* Read register 1            */
#define GLCD_1_EPSRRD2     0x7D	/* Read register 2            */

/********************************************************************
*
*			PHILLIPS Controller Definitions
*
*********************************************************************/

#define	GLCD_1_BSTRON		0x03	/* Booster voltage on              */
#define	GLCD_1_NORON		0x13	/* Normal display mode on          */
#define GLCD_1_RGBSET	    0x2D	/* Color set                       */
#define	GLCD_1_MADCTL		0x36	/* Memory data access control      */
#define	GLCD_1_COLMOD		0x3A	/* Interface pixel format          */
#define GLCD_1_DISCTR     0xB9	/* Super frame inversion           */
#define	GLCD_1_EC			0xC0	/* Internal or external oscillator */

/*******************************************************
*				12-Bit Color Definitions
********************************************************/

#define GLCD_1_BLACK		0x000
#define GLCD_1_NAVY 		0x008
#define GLCD_1_BLUE		0x00F
#define GLCD_1_TEAL 		0x088
#define GLCD_1_EMERALD	0x0C5
#define	GLCD_1_GREEN		0x0F0
#define GLCD_1_CYAN		0x0FF
#define GLCD_1_SLATE 		0x244
#define GLCD_1_INDIGO  	0x408
#define GLCD_1_TURQUOISE	0x4ED
#define GLCD_1_OLIVE 		0x682
#define GLCD_1_MAROON 	0x800
#define GLCD_1_PURPLE 	0x808
#define GLCD_1_GRAY 		0x888
#define GLCD_1_SKYBLUE	0x8CE
#define GLCD_1_BROWN		0xB22
#define GLCD_1_CRIMSON 	0xD13
#define GLCD_1_ORCHID 	0xD7D
#define GLCD_1_RED		0xF00
#define GLCD_1_MAGENTA	0xF0F
#define GLCD_1_ORANGE 	0xF40
#define GLCD_1_PINK		0xF6A
#define GLCD_1_CORAL 		0xF75
#define GLCD_1_SALMON 	0xF87
#define GLCD_1_GOLD 		0xFD0
#define GLCD_1_YELLOW		0xFF0
#define GLCD_1_WHITE		0xFFF



/*******************************************************
*                   Circle Definitions
********************************************************/
#define GLCD_1_FULLCIRCLE 1
#define GLCD_1_OPENSOUTH  2
#define GLCD_1_OPENNORTH  3
#define GLCD_1_OPENEAST   4
#define GLCD_1_OPENWEST   5
#define GLCD_1_OPENNORTHEAST 6
#define GLCD_1_OPENNORTHWEST 7
#define GLCD_1_OPENSOUTHEAST 8
#define GLCD_1_OPENSOUTHWEST 9
















//[] END OF FILE
