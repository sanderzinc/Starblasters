/*******************************************************************************
* File Name: GLCD.c  
* Version 0.3
*
*  Description:
*    This file contains all the API for the SparkFun Color Graphics
*    Arduino Shield board which uses a Nokia 6100 LCD.
*
* Note:  This code has been tested with the Philips PCF8833 controller, but not
*        the EPSON S115D10 controller as of release 0.3.
*
*        Code has been optimized for a 32-bit processor such as the Cortex
*        M0 or M3.
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
#include "cytypes.h"
#include "GLCD.h"
#include "GLCD_SPIM_SCB.h"
#include "GLCD_Reset.h"
#include "cyfitter.h"

#if (GLCD_SPIM_TYPE == GLCD_SPIM_SCB_TYPE)
#include "GLCD_SPIM_SCB_SPI_UART.h"
#endif

uint8 GLCD_driver;
				
static int32 GLCD_x_offset = 0;
static int32 GLCD_y_offset = 0;

/*******************************************************************************
* Function Name: GLCD_Command
********************************************************************************
*
* Summary:
*  This function sends a command to the LCD controller.  
*
* Parameters:  
*  cmdData:  This is the command to be sent to the LCD controller  
*
* Return: 
*  None 
*  
*******************************************************************************/
void GLCD_Command(uint32 cmdData)
{
#if (GLCD_SPIM_TYPE == GLCD_SPIM_UDB_TYPE)
  while((GLCD_SPIM_SCB_ReadTxStatus() & (GLCD_SPIM_SCB_STS_SPI_DONE | GLCD_SPIM_SCB_STS_SPI_IDLE) )== 0);
  GLCD_SPIM_SCB_WriteTxData((uint16)cmdData);
#endif

#if (GLCD_SPIM_TYPE == GLCD_SPIM_SCB_TYPE)
    GLCD_SPIM_SCB_SpiUartWriteTxData(cmdData);
#endif
}

/*******************************************************************************
* Function Name: GLCD_Data
********************************************************************************
*
* Summary:
*  This function sends raw data to the controller.  The 9th bit is set to signal
*  the controller that it information is data and not a command.
*
* Parameters:  
*  rawData:  The data to be sent to the controller. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void GLCD_Data(uint32 rawData)
{	
#if (GLCD_SPIM_TYPE == GLCD_SPIM_UDB_TYPE)
    uint16 data16;
    data16 = (uint16)rawData | 0x0100;
	
    while((GLCD_SPIM_SCB_ReadTxStatus() & (GLCD_SPIM_SCB_STS_SPI_DONE | GLCD_SPIM_SCB_STS_SPI_IDLE) )== 0);
    GLCD_SPIM_SCB_WriteTxData(data16);
#endif

#if (GLCD_SPIM_TYPE == GLCD_SPIM_SCB_TYPE)

    rawData = rawData | 0x00000100;
    GLCD_SPIM_SCB_SpiUartWriteTxData(rawData);
#endif

}

/*******************************************************************************
* Function Name: GLCD_Start
********************************************************************************
*
* Summary:
*  This function initializes the SPI interface and the LCD controller.  
*
* Parameters:  
*  None:   
*
* Return: 
*  None 
*  
*******************************************************************************/
void GLCD_Start(void)
{
	
	GLCD_SPIM_SCB_Start();
#if (GLCD_SPIM_TYPE == GLCD_SPIM_SCB_TYPE)
    GLCD_SPIM_SCB_SpiSetActiveSlaveSelect(3u);
#endif

	CyDelayUs(20);			            /* 20us delay    */
	GLCD_Reset_Write(0x00);	/* Display Reset */
	CyDelay(200);			            /* 200ms delay   */
	GLCD_Reset_Write(0xFF);	/* Release Reset */
	CyDelay(200);			            /* 200ms delay   */
	
#if(GLCD_Controller == GLCD_EPSON)
	GLCD_Command(GLCD_DISCTL);	/*  Display control (0xCA)         */
	GLCD_Data(0x0C);		/* 12 = 1100 - CL dividing ratio [don't divide] switching period 8H (default) */
	GLCD_Data(0x20);		/* nlines/4 - 1 = 132/4 - 1 = 32 duty              */
	GLCD_Data(0x00);		/* No inversely highlighted lines                  */
	
	GLCD_Command(GLCD_COMSCN);	  /* common scanning direction     */
	GLCD_Data(0x01);		                  /* 1->68, 132<-69 scan direction */
	
	GLCD_Command(GLCD_OSCON);	  /* internal oscialltor ON        */
	GLCD_Command(GLCD_SLEEPOUT);  /* sleep out                     */    
	
	GLCD_Command(GLCD_PWRCTR);	  /* Power ctrl                    */
	GLCD_Data(0x0F);	                      /* everything on, no external reference  resistors  */
	
	GLCD_Command(GLCD_DINVON);	  /* invert display mode           */
	
	GLCD_Command(GLCD_DATCTL);	  /* data control                  */
	GLCD_Data(0x03);		/* Inverse page address, reverse rotation column address, column scan-direction	*/
	GLCD_Data(0x00);		                  /* normal RGB arrangement                 */
	GLCD_Data(0x02);		                  /* 16-bit Grayscale Type A (12-bit color) */
	
	GLCD_Command(GLCD_SETCONST);	/* Electronic volume, this is the contrast/brightness        */
	GLCD_Data(GLCD_CONST_DEFAULT);  /* Volume (contrast) setting - fine tuning, original (0-63)  */
	GLCD_Data(3);			                    /* Internal resistor ratio - coarse adjustment (0-7)         */
	
	GLCD_Command(GLCD_NOP);	        /* nop */

	CyDelay(100);

	GLCD_Command(GLCD_DISPON);	     /*  Display on */
#endif

#if(GLCD_Controller == GLCD_PHILIPS) /* Driver is Philips */

	GLCD_Command(GLCD_SLEEPOUT);	 /* Sleep Out          */
	GLCD_Command(GLCD_BSTRON);       /* Booster voltage on */
	GLCD_Command(GLCD_DISPON);		 /* Display on         */
	
	/* 12-bit color pixel format:  */
	GLCD_Command(GLCD_COLMOD);		 /* Color interface format     */
	GLCD_Data(0x03);			                 /* 0b011 is 12-bit/pixel mode */
	
	GLCD_Command(GLCD_MADCTL);		 /* Memory Access Control      */
	GLCD_Command(GLCD_SETCONST);     /* Set Contrast               */          
	GLCD_Data(GLCD_CONST_DEFAULT);
	
	GLCD_Command(GLCD_NOP);	
#endif

  	GLCD_Contrast(60);                           /* Set default contrast  */
  	GLCD_Clear(GLCD_BLACK);          /* Clear screen to black */
}

/*******************************************************************************
* Function Name: GLCD_Stop
********************************************************************************
*
* Summary:
*  This function clears the LCD to black and turns off the display.  
*
* Parameters:  
*   None:   
*
* Return: 
*  None 
*  
*******************************************************************************/
void GLCD_Stop(void)
{
   GLCD_Clear(GLCD_BLACK);
   GLCD_Command(GLCD_DISPOFF);
}

/*******************************************************************************
* Function Name: GLCD_Clear
********************************************************************************
*
* Summary:
*  Clear the display.  
*
* Parameters:  
*  color: Color to clear display with. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void GLCD_Clear(int32 color)
{
    int32 i;

	GLCD_Command(GLCD_PAGEADDR);
	GLCD_Data(GLCD_MINX);
	GLCD_Data(GLCD_MAXX);

	GLCD_Command(GLCD_COLADDR);
	GLCD_Data(GLCD_MINY);
	GLCD_Data(GLCD_MAXY);

	GLCD_Command(GLCD_RAMWR);


	for( i=0; i < (GLCD_MAXX*GLCD_MAXY)/2; i++)
	{
		GLCD_Data((color>>4)&0x00FF);
		GLCD_Data(((color&0x0F)<<4)|(color>>8));
		GLCD_Data(color&0x0FF);
	}

	GLCD_x_offset = 0;
	GLCD_y_offset = 0;
}


/*******************************************************************************
* Function Name: GLCD_Contrast
********************************************************************************
*
* Summary:
*  Set color contrast  
*
* Parameters:  
*  setting: Contrast value.  
*
* Return: 
*  None 
*  
*******************************************************************************/
void GLCD_Contrast(int32 setting)
{
    setting &= GLCD_CONST_MASK;	                /* Mask off contrast value */
    GLCD_Command(GLCD_SETCONST);	/* Set Contrast            */
    GLCD_Data(setting);	                    

#if(GLCD_Controller == GLCD_EPSON)  /* Only required for Epson */
    GLCD_Data(3);			
#endif

}

/*******************************************************************************
* Function Name: GLCD_SwapColors
********************************************************************************
*
* Summary:
*   Swaps colors between Epson and Philips mode.  
*
* Parameters:  
*  prtValue:  The value  
*
* Return: 
*  None 
*  Added by Steve Sparks @ Big Nerd Ranch.
*  This swaps the Epson RGB order into the Philips RGB order. (Or, vice versa, I suppose.)
*******************************************************************************/
int32 GLCD_SwapColors(int32 in)
{
    return ((in & 0x000F)<<8)|(in & 0x00F0)|((in & 0x0F00)>>8);
}
/*******************************************************************************
* Function Name: GLCD_Pixel
********************************************************************************
*
* Summary:
*  Draw Pixel  
*
* Parameters:  
*  x,y:    Location to draw the pixel
*  color:  Color of the pixel
*
* Return: 
*  None 
*******************************************************************************/
void GLCD_Pixel(int32 x, int32 y, int32 color)
{
    y =	(GLCD_COL_HEIGHT - 1) - y;
    x = (GLCD_ROW_LENGTH - 1) - x;

#if (GLCD_Controller == GLCD_EPSON) /* EPSON     */
	GLCD_Command(GLCD_PAGEADDR);    /* Set page  */
	GLCD_Data(x);
	GLCD_Data(GLCD_ENDPAGE);

	GLCD_Command(GLCD_COLADDR);     /* Set column */
	GLCD_Data(y);
	GLCD_Data(GLCD_ENDCOL);

	GLCD_Command(GLCD_RAMWR);       /* Write color data */
	GLCD_Data((color>>4)&0x00FF);
	GLCD_Data(((color&0x0F)<<4)|(color>>8));
	GLCD_Data(color&0x0FF);
#endif

#if (GLCD_Controller == GLCD_PHILIPS) /* PHILIPS   */
	GLCD_Command(GLCD_PAGEADDR);      /* Set page  */
	GLCD_Data((uint8)x);
	GLCD_Data((uint8)x);

	GLCD_Command(GLCD_COLADDR);       /* Set column */
	GLCD_Data((uint8)y);
	GLCD_Data((uint8)y);

	GLCD_Command(GLCD_RAMWR);         /* Write color data */
	GLCD_Data((uint8)((color>>4)&0x00FF));
	GLCD_Data((uint8)(((color&0x0F)<<4)|0x00));
#endif
}

/*******************************************************************************
* Function Name: GLCD_DrawCircle
********************************************************************************
*
* Summary:
*  Draw a circle on the display given a start point and radius.  
*
*  This code uses Bresenham's Circle Algorithm. 
*
* Parameters:  
*  x0, y0: Center of circle
*  radius: Radius of circle
*  color:  Color of circle
*
* Return: 
*  None 
*  
*******************************************************************************/
void GLCD_DrawCircle (int32 x0, int32 y0, int32 radius, int32 color)
{
	int32 f = 1 - radius;
	int32 ddF_x = 0;
	int32 ddF_y = -2 * radius;
	int32 x = 0;
	int32 y = radius;

	GLCD_Pixel(x0, y0 + radius, color);
	GLCD_Pixel(x0, y0 - radius, color);
	GLCD_Pixel( x0 + radius, y0, color);
	GLCD_Pixel( x0 - radius, y0, color);

	while(x < y)
	{
		if(f >= 0)
		{
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x + 1;

		GLCD_Pixel(x0 + x, y0 + y, color);
		GLCD_Pixel(x0 - x, y0 + y, color);
		GLCD_Pixel( x0 + x, y0 - y, color);
		GLCD_Pixel( x0 - x, y0 - y, color);
		GLCD_Pixel( x0 + y, y0 + x, color);
		GLCD_Pixel( x0 - y, y0 + x, color);
		GLCD_Pixel( x0 + y, y0 - x, color);
		GLCD_Pixel( x0 - y, y0 - x, color);
	}
}

/*******************************************************************************
* Function Name: GLCD_PrintChar
********************************************************************************
*
* Summary:
*  Print a character on the display.  
*
* Parameters:  
*  c:       ASCII character to be printed
*  x,y:     Location where character will be printed.
*  fColor:  Foreground color
*  bColor:  Background color
*
* Return: 
*  None 
*  
*******************************************************************************/
void GLCD_PrintChar(uint8 c, int32 x, int32 y, int32 fColor, int32 bColor)
{
	y	=	(GLCD_COL_HEIGHT - 1) - y; /* make display "right" side up */
	x	=	(GLCD_ROW_LENGTH - 2) - x;

	int32             i,j;
	int32    nCols;
	int32    nRows;
	int32    nBytes;
	uint8    PixelRow;
	uint8    Mask;
	int32    Word0;
	int32    Word1;
	uint8   *pFont;
	uint8   *pChar;

	/* Get pointer to the beginning of the selected font table  */
	pFont = (uint8 *)GLCD_FONT8x16;
	
	/* Get the nColumns, nRows and nBytes.                      */
	nCols = *pFont;
	nRows = *(pFont + 1);
	nBytes = *(pFont + 2);
	
	/* Get pointer to the last byte of the desired character    */
	pChar = pFont + (nBytes * (c - 0x1F)) + nBytes - 1;

#if (GLCD_Controller == GLCD_EPSON)
	/* Row address set */
	GLCD_Command(GLCD_PAGEADDR);
	GLCD_Data(x);
	GLCD_Data((x + nRows - 1));
	/* Column address set */
	GLCD_Command(GLCD_COLADDR);
	GLCD_Data(y);
	GLCD_Data((y + nCols - 1));

	/* Write Memory */
	GLCD_Command(GLCD_RAMWR);
	/* Loop on each row, working backwards from the bottom to the top  */
	for (i = nRows - 1; i >= 0; i--) {
		/* Copy pixel row from font table and then decrement row       */
		PixelRow = *pChar++;
		/* Loop on each pixel in the row (left to right)               */
		/* Note: we do two pixels each loop                            */
		Mask = 0x80;
		for (j = 0; j < nCols; j += 2) 
		{
			/* If pixel bit set, use foreground color; else use the background color. */
			/* Now get the pixel color for two successive pixels                      */
			if ((PixelRow & Mask) == 0)
			{
				Word0 = bColor;
			}
			else
			{
				Word0 = fColor;
			}
			
			Mask = Mask >> 1;
			if ((PixelRow & Mask) == 0)
			{
				Word1 = bColor;
			}
			else
			{
				Word1 = fColor;
			}
			Mask = Mask >> 1;
			/* Use this information to output three data bytes  */
			GLCD_Data((uint8)((Word0 >> 4) & 0xFF));
			GLCD_Data((uint8)(((Word0 & 0xF) << 4) | ((Word1 >> 8) & 0xF)));
			GLCD_Data((uint8)(Word1 & 0xFF));
		}
	}
#endif

#if (GLCD_Controller == GLCD_PHILIPS)

	/* Set row address     */
	GLCD_Command(GLCD_PAGEADDR);
	GLCD_Data((uint8)x);
	GLCD_Data((uint8)(x + nRows - 1));
    /* Set column address  */
	GLCD_Command(GLCD_COLADDR);
	GLCD_Data((uint8)y);
	GLCD_Data((uint8)(y + nCols - 1));

	/* Write to display memory */
	GLCD_Command(GLCD_RAMWR);
	/* loop on each row, working backwards from the bottom to the top.  */
	pChar+=nBytes-1;  /* Stick pChar at the end of the row, need to reverse print on phillips */
	for (i = nRows - 1; i >= 0; i--) {
		/* copy pixel row from font table and then decrement row.  */
		PixelRow = *pChar--;
		/* Loop on each pixel in the row (left to right)  */
		/* Note: we do two pixels each loop               */
		Mask = 0x01;  
		for (j = 0; j < nCols; j += 2) 
		{
			/* If pixel bit set, use foreground color; else use the background color  */
			/* Get the pixel color for two successive pixels                          */
			if ((PixelRow & Mask) == 0)
				Word0 = bColor;
			else
				Word0 = fColor;
			Mask = Mask << 1; 
			if ((PixelRow & Mask) == 0)
				Word1 = bColor;
			else
				Word1 = fColor;
			Mask = Mask << 1; 
			/* use this information to output three data bytes */
			GLCD_Data((Word0 >> 4) & 0xFF);
			GLCD_Data(((Word0 & 0xF) << 4) | ((Word1 >> 8) & 0xF));
			GLCD_Data(Word1 & 0xFF);
		}
	}
#endif
}

/*******************************************************************************
* Function Name: GLCD_PrintString
********************************************************************************
*
* Summary:
*  Print a string horizontally on the display.  
*
* Parameters:  
*  pString:  Pointer to null terminated string to be displayed.
*  x,y:      Location where string is to be printed
*  fColor:   Forground Color
*  bColor:   Background Color
*
* Return: 
*  None 
*  
*******************************************************************************/
void GLCD_PrintString(char *pString, int32 x, int32 y, int32 fColor, int32 bColor)
{
	x = x + 16;
	y = y + 8;
    int32 originalY = y;

	/* Loop until null-terminator is found */
	while (*pString != 0x00) 
	{
		/* Draw the character        */
		GLCD_PrintChar(*pString++, x, y, fColor, bColor);
		/* Advance the y position    */
		y = y + 8;
		/* Bail out if y exceeds 131 */
		if (y > 131) 
		{
            x = x + 16;
            y = originalY;
        }
        if (x > 131) break;
	}
}

/*******************************************************************************
* Function Name: GLCD_DrawLine
********************************************************************************
*
* Summary:
*  Draw a line on the display.  
*
* Parameters:  
*  x0, y0:  The beginning endpoint
*  x1, y1:  The end endpoint.
*  color:   Color of the line.
*
* Return: 
*  None 
*  
*******************************************************************************/
void GLCD_DrawLine(int32 x0, int32 y0, int32 x1, int32 y1, int32 color)
{
	int32 dy = y1 - y0; /* Difference between y0 and y1 */
	int32 dx = x1 - x0; /* Difference between x0 and x1 */
	int32 stepx, stepy;

	if (dy < 0)
	{
		dy = -dy;
		stepy = -1;
	}
	else
	{
		stepy = 1;
	}

	if (dx < 0)
	{
		dx = -dx;
		stepx = -1;
	}
	else
	{
		stepx = 1;
	}

	dy <<= 1; /* dy is now 2*dy  */
	dx <<= 1; /* dx is now 2*dx  */
	GLCD_Pixel(x0, y0, color);

	if (dx > dy) 
	{
		int fraction = dy - (dx >> 1);
		while (x0 != x1)
		{
			if (fraction >= 0)
			{
				y0 += stepy;
				fraction -= dx;
			}
			x0 += stepx;
			fraction += dy;
			GLCD_Pixel(x0, y0, color);
		}
	}
	else
	{
		int fraction = dx - (dy >> 1);
		while (y0 != y1)
		{
			if (fraction >= 0)
			{
				x0 += stepx;
				fraction -= dy;
			}
			y0 += stepy;
			fraction += dx;
			GLCD_Pixel( x0, y0, color);
		}
	}
}

/*******************************************************************************
* Function Name: GLCD_DrawRect
********************************************************************************
*
* Summary:
*  Draw a rectangle, filled or not.  
*
* Parameters:  
*  x0, y0:  The upper lefthand corner.
*  x1, y1:  The lower right corner.
*  fill:    Non-Zero if retangle is to be filled.
*  color:   Color for rectangle, border and fill.
*
* Return: 
*  None 
*  
*******************************************************************************/
void GLCD_DrawRect(int32 x0, int32 y0, int32 x1, int32 y1, int32 fill, int32 color)
{	
     int xDiff;
	/* Check if the rectangle is to be filled    */
	if (fill != 0)
	{	
        /* Find the difference between the x vars */
		if(x0 > x1)
		{
			xDiff = x0 - x1; 
		}
		else
		{
			xDiff = x1 - x0;
		}
	
	    /* Fill it with lines  */
		while(xDiff >= 0)
		{
			GLCD_DrawLine(x0, y0, x0, y1, color);
		
			if(x0 > x1)
				x0--;
			else
				x0++;
		
			xDiff--;
		}

	}
	else 
	{
		/* Draw the four sides of the rectangle */
		GLCD_DrawLine(x0, y0, x1, y0, color);
		GLCD_DrawLine(x0, y1, x1, y1, color);
		GLCD_DrawLine(x0, y0, x0, y1, color);
		GLCD_DrawLine(x1, y0, x1, y1, color);
	}
}


/*******************************************************************************
* Function Name: GLCD_Off
********************************************************************************
*
* Summary:
*  Turn off display
*
* Parameters:  
*  None 
*
* Return: 
*  None 
*  
*******************************************************************************/
void GLCD_Off(void)		/* Turn off the display  */
{
    GLCD_Command(GLCD_DISPOFF);
}

/*******************************************************************************
* Function Name: GLCD_On
********************************************************************************
*
* Summary:
*  Turn on display
*
* Parameters:  
*  None 
*
* Return: 
*  None 
*  
*******************************************************************************/
void GLCD_On(void)		/* Turn on the display */
{
    GLCD_Command(GLCD_DISPON);
}



/* [] END OF FILE */
