#include "msp430g2553.h"
//For Addressable RGB LED strip, confirmed working!
//P1.2 Data Out; and P1.4 Serial Clock Out;

#define NLEDS 1 //Number of LEDS in the string. 32 LEDs in this strip.
#define NBYTES 4 //Number of LEDs times 4 (3 color bytes and a flag byte)
typedef unsigned char byte;
typedef struct {
    byte f; //flag
    byte b; //blue
    byte g; //green
    byte r; //red
} LED;
#define NCOLORS 8 //Total number of RGB colors = 128 colors per LED
#define NCOLORBYTES 32 //Total number of cycled colors including flags.
static const byte COLORbytes[NCOLORBYTES] = {
        0xfcu, 0x0u, 0x0u, 0xffu, //red
        0xf3u, 0x0u, 0xffu, 0x0u, //green
        0xcfu, 0xffu, 0x0u, 0x0u, //blue
        0xc0u, 0xffu, 0xffu, 0xffu, //white
        0xc3u, 0xffu, 0xffu, 0x0u, //green-blue
        0xccu, 0xffu, 0x0u, 0xffu, //red-blue
        0xf0u, 0x0u, 0xffu, 0xffu, //red-green
        0xfeu, 0x0u, 0x15u, 0x5cu //rowan brown
};
LED *COLORLUT = (LED *) COLORbytes; //Point to the COLOR lookup table data cast as LEDs.
LED framebuffer[NLEDS];     //Create a frame buffer. Array stores LED values for next display update

void setup(void); //setup peripherals
void rainbowsmooth(byte); //Creates a smooth rainbow frame
void outputframe(void); //Update display
void setLED_RGB(byte,byte, byte, byte); //Set the value of the nth LED
void setLED_LUT(byte, byte, LED*); //Set the value of the nth LED using a color preset
byte makeflag(byte, byte, byte);//Construct the flag byte
void spi_byte(byte); //send a single byte to the string
void spi_ctlLED(void); //output an empty LED
unsigned int loopcount = 0;

int cyclecolor = 0;
int main(void) {
    setup(); //initialize peripherals
    //if ((P1IN & BIT3) == BIT3) {
    //    cyclecolor = 0;
    //    while(1) {
    //    }
    //}
    //if ((P1IN & BIT3) != BIT3) {
    while(cyclecolor < 1){
        rainbowsmooth(loopcount);   //put a frame in the frame buffer
        outputframe();  //Send the buffer to the string
        //Define WDT settings for loop delay. Interval mode, Clear Count, ACLK source, ~64cyc interval
        WDTCTL = WDTPW+WDTTMSEL+WDTCNTCL+WDTSSEL+WDTIS1+WDTIS0; //Start the watch dog timer in interval mode.

        IE1 |= WDTIE;       // Enable WDT interrupt
        _BIS_SR(CPUOFF+GIE);    //Stop execution, enter low power mode. (will wakeup via WDT interrupt for next frame)
        loopcount++;
        cyclecolor = 1;
        if(loopcount>=NCOLORS) loopcount = 0;
    }
    //}
}
//WDT Interrupt service routine. Resume the loop after a delay
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer (void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop the WDT
    IE1 &= ~WDTIE;              // Disable WDT interrupt
    _BIC_SR_IRQ(CPUOFF); //Resume active mode on return from interrupt
}
//Creates a still for a smooth rainbow scroll, good for relatively high update rates
void rainbowsmooth(byte offset){
    unsigned int n;
    for(n=0;n<NLEDS;n++){
        setLED_LUT(n, (n*4+offset)%NCOLORS, COLORLUT); //Cycle through the COLOR table
    }
}
//Displays the frame buffer on the string
void outputframe(void){
    unsigned int c;
    byte *framebytes = ( byte * ) framebuffer;
    spi_ctlLED();
    for(c=0;c<NBYTES;c++){
        spi_byte(framebytes[c]);
    }
    spi_ctlLED();
}
//SPI output an empty LED for control
void spi_ctlLED(void){
    int c;
    for(c=4;c>0;c--) {
        spi_byte(0x00);
    }
}
//SPI output of individual bytes
void spi_byte(byte data){
    IE2 |= UCA0TXIE;                          // Enable USCI0 TX interrupt
    if((IFG2&UCA0TXIFG)==0){        //Wait for SPI TX buffer to be ready
        _BIS_SR(CPUOFF+GIE);
    }
    UCA0TXBUF = ~data;          //Put data in transmit buffer, inverted because output stage also inverts
}
// Resume execution when TX buffer is ready for another character
#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCIA0TX_ISR(void)
{
    _BIC_SR_IRQ(CPUOFF);        //resume active mode
    IFG2 &= ~UCA0TXIFG;         //reset the TX flag
    IE2 &= UCA0TXIE;            //disable the TX interrupt
}
//make the color flag required for each LED
byte makeflag(byte red, byte green, byte blue) {
  byte flag = 0;

  flag = (red&0xC0)>>6;
  flag |= ((green&0xC0)>>4);
  flag |= ((blue&0xC0)>>2);
  return ~flag;
}
//Set a LED in the frame buffer by RGB value
void setLED_RGB(byte n,byte red,byte green,byte blue) {
    framebuffer[n].f = makeflag(red,green,blue);
    framebuffer[n].r = red;
    framebuffer[n].g = green;
    framebuffer[n].b = blue;
}
//Set a LED in the frame buffer by named color
void setLED_LUT(byte n, byte color, LED *LUT){
    framebuffer[n]=LUT[color];
}
//Setup Peripherals
void setup(void){
    WDTCTL = WDTPW + WDTHOLD;                // Stop watchdog timer
    //Setup ACLK
    BCSCTL3 |= LFXT1S_2;    //Set LFXT1 source to internal VLO
    BCSCTL1 |= DIVA_3;          //Set Aclk divider to 8 (~3Khz)
    //Setup Speed of Color Changes
    DCOCTL = CALDCO_16MHZ;  //Slow = DCO 16MHZ
    BCSCTL1 |= CALBC1_16MHZ;        //slow = SMCLK 16MHZ
    
    //Setup SMclock timer 
    P1SEL = BIT2 + BIT4;
    P1SEL2 = BIT2 + BIT4;
    P1REN = BIT3; //set up button to switch colors.
    P1OUT = BIT3;
    UCA0CTL0 |= UCCKPL + UCMSB + UCMST + UCSYNC; // 3-pin, 8-bit SPI master. Mode 0 Inverted from standard so the BJT external inversion/5V conversion will be right
    UCA0CTL1 |= UCSSEL_2; // SMCLK
    UCA0BR0 = 0xff; // 255
    UCA0BR1 = 0x00; // 0
    UCA0MCTL = 0; // No modulation
    UCA0CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
    IE2 |= UCA0TXIE; // Enable USCI0 TX interrupt
    spi_byte(0x00); //Send a zero byte to initialize output low.
}