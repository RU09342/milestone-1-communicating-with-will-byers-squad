#include "msp430g2553.h"

//For Addressable RGB LED strip, the strip comes in this Thursday

//P1.2 Data Out; and P1.4 Serial Clock Out;
#define NPIXELS 5       //Number of LEDS in the string
#define NBYTES 20       //Number of pixels times 4 (3 color bytes and a flag byte)

//Define WDT settings for loop delay
//Interval mode, Clear Count, ACLK source, ~64cyc interval
#define WDT_ON WDTPW+WDTTMSEL+WDTCNTCL+WDTSSEL+WDTIS1+WDTIS0

typedef unsigned char byte;

typedef struct {
    byte f; //flag
    byte b; //blue
    byte g; //green
    byte r; //red
} pixel;

#define NHUES 128
#define NHUEBYTES 512
static const byte huebytes[NHUEBYTES] = {
        0xfcu, 0x0u, 0x0u, 0xffu,
        0xfcu, 0x0u, 0xbu, 0xffu,
        0xfcu, 0x0u, 0x17u, 0xffu,
        0xfcu, 0x0u, 0x23u, 0xffu,
        0xfcu, 0x0u, 0x2fu, 0xffu,
        0xfcu, 0x0u, 0x3bu, 0xffu,
        0xf8u, 0x0u, 0x47u, 0xffu,
        0xf8u, 0x0u, 0x53u, 0xffu,
        0xf8u, 0x0u, 0x5fu, 0xffu,
        0xf8u, 0x0u, 0x6bu, 0xffu,
        0xf8u, 0x0u, 0x77u, 0xffu,
        0xf4u, 0x0u, 0x83u, 0xffu,
        0xf4u, 0x0u, 0x8fu, 0xffu,
        0xf4u, 0x0u, 0x9bu, 0xffu,
        0xf4u, 0x0u, 0xa7u, 0xffu,
        0xf4u, 0x0u, 0xb3u, 0xffu,
        0xf4u, 0x0u, 0xbfu, 0xffu,
        0xf0u, 0x0u, 0xcbu, 0xffu,
        0xf0u, 0x0u, 0xd7u, 0xffu,
        0xf0u, 0x0u, 0xe3u, 0xffu,
        0xf0u, 0x0u, 0xefu, 0xffu,
        0xf0u, 0x0u, 0xfbu, 0xffu,
        0xf0u, 0x0u, 0xffu, 0xf7u,
        0xf0u, 0x0u, 0xffu, 0xebu,
        0xf0u, 0x0u, 0xffu, 0xdfu,
        0xf0u, 0x0u, 0xffu, 0xd3u,
        0xf0u, 0x0u, 0xffu, 0xc7u,
        0xf1u, 0x0u, 0xffu, 0xbbu,
        0xf1u, 0x0u, 0xffu, 0xafu,
        0xf1u, 0x0u, 0xffu, 0xa3u,
        0xf1u, 0x0u, 0xffu, 0x97u,
        0xf1u, 0x0u, 0xffu, 0x8bu,
        0xf2u, 0x0u, 0xffu, 0x7fu,
        0xf2u, 0x0u, 0xffu, 0x73u,
        0xf2u, 0x0u, 0xffu, 0x67u,
        0xf2u, 0x0u, 0xffu, 0x5bu,
        0xf2u, 0x0u, 0xffu, 0x4fu,
        0xf2u, 0x0u, 0xffu, 0x43u,
        0xf3u, 0x0u, 0xffu, 0x37u,
        0xf3u, 0x0u, 0xffu, 0x2bu,
        0xf3u, 0x0u, 0xffu, 0x1fu,
        0xf3u, 0x0u, 0xffu, 0x13u,
        0xf3u, 0x0u, 0xffu, 0x7u,
        0xf3u, 0x3u, 0xffu, 0x0u,
        0xf3u, 0xfu, 0xffu, 0x0u,
        0xf3u, 0x1bu, 0xffu, 0x0u,
        0xf3u, 0x27u, 0xffu, 0x0u,
        0xf3u, 0x33u, 0xffu, 0x0u,
        0xf3u, 0x3fu, 0xffu, 0x0u,
        0xe3u, 0x4bu, 0xffu, 0x0u,
        0xe3u, 0x57u, 0xffu, 0x0u,
        0xe3u, 0x63u, 0xffu, 0x0u,
        0xe3u, 0x6fu, 0xffu, 0x0u,
        0xe3u, 0x7bu, 0xffu, 0x0u,
        0xd3u, 0x87u, 0xffu, 0x0u,
        0xd3u, 0x93u, 0xffu, 0x0u,
        0xd3u, 0x9fu, 0xffu, 0x0u,
        0xd3u, 0xabu, 0xffu, 0x0u,
        0xd3u, 0xb7u, 0xffu, 0x0u,
        0xc3u, 0xc3u, 0xffu, 0x0u,
        0xc3u, 0xcfu, 0xffu, 0x0u,
        0xc3u, 0xdbu, 0xffu, 0x0u,
        0xc3u, 0xe7u, 0xffu, 0x0u,
        0xc3u, 0xf3u, 0xffu, 0x0u,
        0xc3u, 0xffu, 0xffu, 0x0u,
        0xc3u, 0xffu, 0xf3u, 0x0u,
        0xc3u, 0xffu, 0xe7u, 0x0u,
        0xc3u, 0xffu, 0xdbu, 0x0u,
        0xc3u, 0xffu, 0xcfu, 0x0u,
        0xc3u, 0xffu, 0xc3u, 0x0u,
        0xc7u, 0xffu, 0xb7u, 0x0u,
        0xc7u, 0xffu, 0xabu, 0x0u,
        0xc7u, 0xffu, 0x9fu, 0x0u,
        0xc7u, 0xffu, 0x93u, 0x0u,
        0xc7u, 0xffu, 0x87u, 0x0u,
        0xcbu, 0xffu, 0x7bu, 0x0u,
        0xcbu, 0xffu, 0x6fu, 0x0u,
        0xcbu, 0xffu, 0x63u, 0x0u,
        0xcbu, 0xffu, 0x57u, 0x0u,
        0xcbu, 0xffu, 0x4bu, 0x0u,
        0xcfu, 0xffu, 0x3fu, 0x0u,
        0xcfu, 0xffu, 0x33u, 0x0u,
        0xcfu, 0xffu, 0x27u, 0x0u,
        0xcfu, 0xffu, 0x1bu, 0x0u,
        0xcfu, 0xffu, 0xfu, 0x0u,
        0xcfu, 0xffu, 0x3u, 0x0u,
        0xcfu, 0xffu, 0x0u, 0x7u,
        0xcfu, 0xffu, 0x0u, 0x13u,
        0xcfu, 0xffu, 0x0u, 0x1fu,
        0xcfu, 0xffu, 0x0u, 0x2bu,
        0xcfu, 0xffu, 0x0u, 0x37u,
        0xceu, 0xffu, 0x0u, 0x43u,
        0xceu, 0xffu, 0x0u, 0x4fu,
        0xceu, 0xffu, 0x0u, 0x5bu,
        0xceu, 0xffu, 0x0u, 0x67u,
        0xceu, 0xffu, 0x0u, 0x73u,
        0xceu, 0xffu, 0x0u, 0x7fu,
        0xcdu, 0xffu, 0x0u, 0x8bu,
        0xcdu, 0xffu, 0x0u, 0x97u,
        0xcdu, 0xffu, 0x0u, 0xa3u,
        0xcdu, 0xffu, 0x0u, 0xafu,
        0xcdu, 0xffu, 0x0u, 0xbbu,
        0xccu, 0xffu, 0x0u, 0xc7u,
        0xccu, 0xffu, 0x0u, 0xd3u,
        0xccu, 0xffu, 0x0u, 0xdfu,
        0xccu, 0xffu, 0x0u, 0xebu,
        0xccu, 0xffu, 0x0u, 0xf7u,
        0xccu, 0xfbu, 0x0u, 0xffu,
        0xccu, 0xefu, 0x0u, 0xffu,
        0xccu, 0xe3u, 0x0u, 0xffu,
        0xccu, 0xd7u, 0x0u, 0xffu,
        0xccu, 0xcbu, 0x0u, 0xffu,
        0xdcu, 0xbfu, 0x0u, 0xffu,
        0xdcu, 0xb3u, 0x0u, 0xffu,
        0xdcu, 0xa7u, 0x0u, 0xffu,
        0xdcu, 0x9bu, 0x0u, 0xffu,
        0xdcu, 0x8fu, 0x0u, 0xffu,
        0xdcu, 0x83u, 0x0u, 0xffu,
        0xecu, 0x77u, 0x0u, 0xffu,
        0xecu, 0x6bu, 0x0u, 0xffu,
        0xecu, 0x5fu, 0x0u, 0xffu,
        0xecu, 0x53u, 0x0u, 0xffu,
        0xecu, 0x47u, 0x0u, 0xffu,
        0xfcu, 0x3bu, 0x0u, 0xffu,
        0xfcu, 0x2fu, 0x0u, 0xffu,
        0xfcu, 0x23u, 0x0u, 0xffu,
        0xfcu, 0x17u, 0x0u, 0xffu,
        0xfcu, 0xbu, 0x0u, 0xffu
};

pixel *HUELUT = (pixel *) huebytes; //Point to the HUE lookup table data cast as pixels.

//Create a frame buffer
pixel framebuffer[NPIXELS];     //Array stores pixel values for next display update

//FUNCTION PROTOTYPES
void setup(void);  //setup peripherals

void rainbowsmooth(byte);   //Creates a smooth rainbow frame

void outputframe(void); //Update display

void setpixel_RGB(byte,byte, byte, byte); //Set the value of the nth pixel
void setpixel_LUT(byte, byte, pixel*);  //Set the value of the nth pixel using a color preset

byte makeflag(byte, byte, byte); //Construct the flag byte

void spi_byte(byte);    //send a single byte to the string
void spi_ctlpixel(void);        //output an empty pixel

unsigned int loopcount = 0;

int main(void) {

    setup(); //initialize peripheralsl


    while(1){
        rainbowsmooth(loopcount);   //put a frame in the frame buffer
        outputframe();  //Send the buffer to the string

        WDTCTL = WDT_ON;    //Start the watch dog timer in interval mode.
        IE1 |= WDTIE;       // Enable WDT interrupt
        _BIS_SR(CPUOFF+GIE);    //Stop execution, enter low power mode. (will wakeup via WDT interrupt for next frame)

        loopcount++;
        if(loopcount>=NHUES) loopcount = 0;
    }

}


//WDT Interrupt service routine
//Resume the loop after a delay
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

    for(n=0;n<NPIXELS;n++){
        setpixel_LUT(n, (n*4+offset)%NHUES, HUELUT); //Cycle through the Hue table
    }
}


//Displays the frame buffer on the string
void outputframe(void){
    unsigned int c;

    byte *framebytes = ( byte * ) framebuffer;

    spi_ctlpixel();
    for(c=0;c<NBYTES;c++){
        spi_byte(framebytes[c]);
    }
    spi_ctlpixel();

}

//SPI output an empty pixel for control
void spi_ctlpixel(void){
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

//make the color flag required for each pixel
byte makeflag(byte red, byte green, byte blue) {
  byte flag = 0;

  flag = (red&0xC0)>>6;
  flag |= ((green&0xC0)>>4);
  flag |= ((blue&0xC0)>>2);
  return ~flag;
}

//Set a pixel in the frame buffer by RGB value
void setpixel_RGB(byte n,byte red,byte green,byte blue) {
    framebuffer[n].f = makeflag(red,green,blue);
    framebuffer[n].r = red;
    framebuffer[n].g = green;
    framebuffer[n].b = blue;
}

//Set a pixel in the frame buffer by named color
void setpixel_LUT(byte n, byte color, pixel *LUT){
    framebuffer[n]=LUT[color];
}

//Setup Peripherals
void setup(void){
    WDTCTL = WDTPW + WDTHOLD;                // Stop watchdog timer

    //Setup ACLK
    BCSCTL3 |= LFXT1S_2;    //Set LFXT1 source to internal VLO
    BCSCTL1 |= DIVA_3;          //Set Aclk divider to 8 (~3Khz)

    //Setup Main clocks
    DCOCTL = CALDCO_16MHZ;  //Set DCO 16MHZ
    BCSCTL1 |= CALBC1_16MHZ;        //set SMCLK 16MHZ

    //Setup USCI for SPI
    P1SEL = BIT2 + BIT4;
    P1SEL2 = BIT2 + BIT4;
    UCA0CTL0 |= UCCKPL + UCMSB + UCMST + UCSYNC;  // 3-pin, 8-bit SPI master. Mode 0 Inverted from standard so the BJT external inversion/5V conversion will be right

    UCA0CTL1 |= UCSSEL_2;                    // SMCLK
    UCA0BR0 = 0xff;                          // /255
    UCA0BR1 = 0x00;

    UCA0MCTL = 0;                             // No modulation
    UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
    IE2 |= UCA0TXIE;                          // Enable USCI0 TX interrupt
    spi_byte(0x00);                         //Send a zero byte to initialize output low.

}