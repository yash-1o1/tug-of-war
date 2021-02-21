/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>

/* Standard Includes */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/* Module Includes */
#include <LcdDriver/Crystalfontz128x128_ST7735.h>

#define BUFFER_SIZE 5

#define LEFT_BUTTON BIT1
#define RIGHT_BUTTON BIT4
#define S1 BIT1
#define S2 BIT5

#define LEFT_LED BIT0

#define RGBLED_RED BIT0
#define RGBLED_GREEN BIT1
#define RGBLED_BLUE BIT2

#define BLED_RED BIT6
#define BLED_GREEN BIT4
#define BLED_BLUE BIT6

#define PRESSED 0

void initialize();
void TurnOn_Launchpad_LED1();
void TurnOff_Launchpad_LED1();

void TurnOn_Launchpad_RGBLEDRED();
void TurnOff_Launchpad_RGBLEDRED();
void TurnOn_Launchpad_RGBLEDGREEN();
void TurnOff_Launchpad_RGBLEDGREEN();
void TurnOn_Launchpad_RGBLEDBLUE();
void TurnOff_Launchpad_RGBLEDBLUE();

void TurnOn_Launchpad_LEDRED();
void TurnOff_Launchpad_LEDRED();
void TurnOn_Launchpad_LEDGREEN();
void TurnOff_Launchpad_LEDGREEN();
void TurnOn_Launchpad_LEDBLUE();
void TurnOff_Launchpad_LEDBLUE();

char SwitchStatus_RIGHT();
char SwitchStatus_LEFT();
char SwitchStatus_UP();
char SwitchStatus_DOWN();
void TurnOn_Launchpad_RGBLEDRED();
void TurnOff_Launchpad_RGBLEDRED();

/** Initializes a graphics context used for drawing things to the screen */
Graphics_Context InitGraphics()
{
    Graphics_Context context;

    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);
    Graphics_initContext(&context, &g_sCrystalfontz128x128, &g_sCrystalfontz128x128_funcs);

    Graphics_setFont(&context, &g_sFontFixed6x8);

    Graphics_setForegroundColor(&context, GRAPHICS_COLOR_BLACK);
    Graphics_setBackgroundColor(&context, GRAPHICS_COLOR_WHITE);
    Graphics_clearDisplay(&context);

    return context;
}

int main(void)
{
    /* Stop Watchdog  */
    WDT_A_holdTimer();

    Graphics_Context context = InitGraphics();

    int left = 0;
    int right = 0;

    char buffer[BUFFER_SIZE];

    initialize();
    while (1)
    {
        // If the button is not pressed, keep the LED off
        if (SwitchStatus_UP() == PRESSED)
        {
            if (right > 0 && right < 40)
                right += 1;
            else if (right == 0)
                right += 1;
        }
        if (SwitchStatus_DOWN() == PRESSED)
        {
            if (right > 0 && right < 40)
                right -= 1;
            else if (right == 40)
                right -= 1;
        }
        if (SwitchStatus_RIGHT() == PRESSED)
        {
            if (left > 0 && left < 40)
                left += 1;
            else if (left == 0)
                left += 1;
        }
        if ( SwitchStatus_LEFT() == PRESSED)
        {
            if (left > 0 && left < 40)
                left -= 1;
            else if (left == 40)
                left -= 1;
        }

        TurnOnOff_LED(left, right);
        snprintf(buffer, BUFFER_SIZE, "%02d", left);
        Graphics_drawString(&context, (int8_t*) buffer, -1, 20, 20, true);

        snprintf(buffer, BUFFER_SIZE, "%02d", right);
        Graphics_drawString(&context, (int8_t*) buffer, -1, 100, 100, true);

    }
}

void initialize()
{
    WDT_A_hold(WDT_A_BASE);

    P1DIR |= LEFT_LED;
    P2DIR |= RGBLED_RED;
    P2DIR |= RGBLED_GREEN;
    P2DIR |= RGBLED_BLUE;
    P2DIR |= BLED_RED;
    P2DIR |= BLED_GREEN;
    P5DIR |= BLED_BLUE;

    P1DIR &= ~LEFT_BUTTON;
    P1REN |= LEFT_BUTTON;
    P1OUT |= LEFT_BUTTON;

    P1DIR &= ~RIGHT_BUTTON;
    P1REN |= RIGHT_BUTTON;
    P1OUT |= RIGHT_BUTTON;

    P5DIR &= ~S1;
    P5REN |= S1;
    P5OUT |= S1;

    P3DIR &= ~S2;
    P3REN |= S2;
    P3OUT |= S2;
}

void TurnOn_Launchpad_LED1()
{
    P1OUT = P1OUT |  LEFT_LED;
}

void TurnOff_Launchpad_LED1()
{
    P1OUT = P1OUT & ~LEFT_LED;
}

void TurnOn_Launchpad_RGBLEDRED()
{
    P2OUT |= BLED_RED;
}

void TurnOff_Launchpad_RGBLEDRED()
{
    P2OUT = P2OUT & ~BLED_RED;
}

void TurnOn_Launchpad_RGBLEDGREEN()
{
    P2OUT |= BLED_GREEN;
}

void TurnOff_Launchpad_RGBLEDGREEN()
{
    P2OUT = P2OUT & ~BLED_GREEN;
}

void TurnOn_Launchpad_RGBLEDBLUE()
{
    P5OUT |= BLED_BLUE;
}

void TurnOff_Launchpad_RGBLEDBLUE()
{
    P5OUT &= ~BLED_BLUE;
}

void TurnOn_Launchpad_LEDRED()
{
    P2OUT |= RGBLED_RED;
}

void TurnOff_Launchpad_LEDRED()
{
    P2OUT = P2OUT & ~RGBLED_RED;
}

void TurnOn_Launchpad_LEDGREEN()
{
    P2OUT |= RGBLED_GREEN;
}

void TurnOff_Launchpad_LEDGREEN()
{
    P2OUT = P2OUT & ~RGBLED_GREEN;
}

void TurnOn_Launchpad_LEDBLUE()
{
    P2OUT |= RGBLED_BLUE;
}

void TurnOff_Launchpad_LEDBLUE()
{
    P2OUT = P2OUT & ~RGBLED_BLUE;
}

char SwitchStatus_LEFT()
{
    return (P1IN & LEFT_BUTTON);
}

char SwitchStatus_RIGHT()
{
    return (P1IN & RIGHT_BUTTON);
}

char SwitchStatus_UP()
{
    return (P5IN & S1);
}

char SwitchStatus_DOWN()
{
    return (P3IN & S2);
}

void TurnOnOff_LED(int left, int right)
{
    if (left > right)
    {
        if (left == 00 && right == 00)
        {
            TurnOff_Launchpad_RGBLEDRED();
            TurnOff_Launchpad_RGBLEDBLUE();
            TurnOff_Launchpad_RGBLEDGREEN();
            TurnOff_Launchpad_LEDRED();
            TurnOff_Launchpad_LEDGREEN();
            TurnOff_Launchpad_LEDBLUE();
            TurnOn_Launchpad_LED1();
        }
        if (left - right < 10 )
        {
            TurnOff_Launchpad_RGBLEDRED();
            TurnOff_Launchpad_RGBLEDBLUE();
            TurnOff_Launchpad_RGBLEDGREEN();
            TurnOff_Launchpad_LEDRED();
            TurnOff_Launchpad_LEDGREEN();
            TurnOff_Launchpad_LEDBLUE();
            TurnOn_Launchpad_LED1();
        }
        if (left - right == 10 )
        {
            TurnOn_Launchpad_RGBLEDRED();
            TurnOff_Launchpad_RGBLEDBLUE();
            TurnOff_Launchpad_RGBLEDGREEN();
            TurnOff_Launchpad_LEDRED();
            TurnOff_Launchpad_LEDGREEN();
            TurnOff_Launchpad_LEDBLUE();
            TurnOn_Launchpad_LED1();
        }
        if (left - right > 10 && left - right < 20)
        {
            TurnOff_Launchpad_RGBLEDBLUE();
            TurnOn_Launchpad_RGBLEDRED();
            TurnOff_Launchpad_RGBLEDGREEN();
            TurnOff_Launchpad_LEDRED();
            TurnOff_Launchpad_LEDGREEN();
            TurnOff_Launchpad_LEDBLUE();
            TurnOff_Launchpad_LED1();
        }
        if (left - right == 20)
        {
            TurnOff_Launchpad_RGBLEDBLUE();
            TurnOn_Launchpad_RGBLEDRED();
            TurnOn_Launchpad_RGBLEDGREEN();
            TurnOff_Launchpad_LEDRED();
            TurnOff_Launchpad_LEDGREEN();
            TurnOff_Launchpad_LEDBLUE();
            TurnOff_Launchpad_LED1();
        }
        if (left - right > 20 && left - right < 30)
        {
            TurnOff_Launchpad_RGBLEDBLUE();
            TurnOff_Launchpad_RGBLEDRED();
            TurnOn_Launchpad_RGBLEDGREEN();
            TurnOff_Launchpad_LEDRED();
            TurnOff_Launchpad_LEDGREEN();
            TurnOff_Launchpad_LEDBLUE();
            TurnOff_Launchpad_LED1();
        }
        if (left - right == 30)
        {
            TurnOn_Launchpad_RGBLEDBLUE();
            TurnOff_Launchpad_RGBLEDRED();
            TurnOn_Launchpad_RGBLEDGREEN();
            TurnOff_Launchpad_LEDRED();
            TurnOff_Launchpad_LEDGREEN();
            TurnOff_Launchpad_LEDBLUE();
            TurnOff_Launchpad_LED1();
        }
        if (left - right > 30 && left - right <= 40)
        {
            TurnOn_Launchpad_RGBLEDBLUE();
            TurnOff_Launchpad_RGBLEDRED();
            TurnOff_Launchpad_RGBLEDGREEN();
            TurnOff_Launchpad_LEDRED();
            TurnOff_Launchpad_LEDGREEN();
            TurnOff_Launchpad_LEDBLUE();
            TurnOff_Launchpad_LED1();
        }
    }
    if (right > left)
    {
        if (left == 00 && right == 00)
        {
            TurnOff_Launchpad_RGBLEDRED();
            TurnOff_Launchpad_RGBLEDBLUE();
            TurnOff_Launchpad_RGBLEDGREEN();
            TurnOff_Launchpad_LEDRED();
            TurnOff_Launchpad_LEDGREEN();
            TurnOff_Launchpad_LEDBLUE();
            TurnOn_Launchpad_LED1();
        }
        if (right - left < 10 )
        {
            TurnOff_Launchpad_RGBLEDRED();
            TurnOff_Launchpad_RGBLEDBLUE();
            TurnOff_Launchpad_RGBLEDGREEN();
            TurnOff_Launchpad_LEDRED();
            TurnOff_Launchpad_LEDGREEN();
            TurnOff_Launchpad_LEDBLUE();
            TurnOn_Launchpad_LED1();
        }
        if (right - left == 10 )
        {
            TurnOff_Launchpad_RGBLEDRED();
            TurnOff_Launchpad_RGBLEDBLUE();
            TurnOff_Launchpad_RGBLEDGREEN();
            TurnOn_Launchpad_LEDRED();
            TurnOff_Launchpad_LEDGREEN();
            TurnOff_Launchpad_LEDBLUE();
            TurnOn_Launchpad_LED1();
        }
        if (right - left > 10 && right - left < 20)
        {
            TurnOff_Launchpad_RGBLEDBLUE();
            TurnOff_Launchpad_RGBLEDRED();
            TurnOff_Launchpad_RGBLEDGREEN();
            TurnOn_Launchpad_LEDRED();
            TurnOff_Launchpad_LEDGREEN();
            TurnOff_Launchpad_LEDBLUE();
            TurnOff_Launchpad_LED1();
        }
        if (right - left == 20)
        {
            TurnOff_Launchpad_RGBLEDBLUE();
            TurnOff_Launchpad_RGBLEDRED();
            TurnOff_Launchpad_RGBLEDGREEN();
            TurnOn_Launchpad_LEDRED();
            TurnOn_Launchpad_LEDGREEN();
            TurnOff_Launchpad_LEDBLUE();
            TurnOff_Launchpad_LED1();
        }
        if (right - left > 20 && right - left < 30)
        {
            TurnOff_Launchpad_RGBLEDBLUE();
            TurnOff_Launchpad_RGBLEDRED();
            TurnOff_Launchpad_RGBLEDGREEN();
            TurnOff_Launchpad_LEDRED();
            TurnOn_Launchpad_LEDGREEN();
            TurnOff_Launchpad_LEDBLUE();
            TurnOff_Launchpad_LED1();
        }
        if (right - left == 30)
        {
            TurnOff_Launchpad_RGBLEDBLUE();
            TurnOff_Launchpad_RGBLEDRED();
            TurnOff_Launchpad_RGBLEDGREEN();
            TurnOff_Launchpad_LEDRED();
            TurnOn_Launchpad_LEDGREEN();
            TurnOn_Launchpad_LEDBLUE();
            TurnOff_Launchpad_LED1();
        }
        if (right - left > 30 && right - left <= 40)
        {
            TurnOff_Launchpad_RGBLEDBLUE();
            TurnOff_Launchpad_RGBLEDRED();
            TurnOff_Launchpad_RGBLEDGREEN();
            TurnOff_Launchpad_LEDRED();
            TurnOff_Launchpad_LEDGREEN();
            TurnOn_Launchpad_LEDBLUE();
            TurnOff_Launchpad_LED1();
        }
    }
}
