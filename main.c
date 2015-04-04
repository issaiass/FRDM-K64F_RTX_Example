/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions
#include "MK64F12.h"                    // Device header

void LED_Initialize(void);                  // Intialize the LED
void Blink(void const *arg);                // Blink function

osThreadDef(Blink, osPriorityNormal, 1, 0); // Define the blink task

/*
 * main: initialize and start the system
 */
int main (void) {
  osKernelInitialize ();                    // initialize CMSIS-RTOS
	SystemInit();                             // Initialize system core functions
  LED_Initialize();                         // GPIOB Pin 21 Setup
  osThreadCreate(osThread (Blink), NULL);   // Thread creation of blink a led
	osKernelStart ();                         // start thread execution 
}

void LED_Initialize(void) {
  SIM->SCGC5     |=   1 <<  10 ;            // Enable Port B Clock
  PORTB->PCR[21] |=  (1 <<   8);            // PTB21 is GPIO pin
	PTB->PDOR      &= ~(1 <<  21);            // PTB21 = Low Level
  PTB->PDDR      |=   1 <<  21 ;            // PTB21 = Set As Output
}

void Blink(void const *arg) {
	while(1) {
		osDelay(1000);                          // Delay 1 sec
    PTB->PTOR    |=   1 << 21;              // Toogle PTB21
	}
}
