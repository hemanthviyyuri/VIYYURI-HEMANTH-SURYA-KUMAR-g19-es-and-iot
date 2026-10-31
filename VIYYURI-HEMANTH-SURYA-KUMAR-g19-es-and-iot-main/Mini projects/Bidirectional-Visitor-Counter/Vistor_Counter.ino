int visitors = 0;
int lastPIR = 0;
int PIR1_active = 0;
int PIR2_active = 0;
int pir1;
int pir2;
int pendingTime = 0;
int timeout = 3000;
int IDLE = 0;
int ENTRY_PENDING = 1;
int EXIT_PENDING = 2;
void lcd_pulse()
{
    PORTB |= (1 << PB3);
    _delay_ms(1);
    PORTB &= ~(1 << PB3);
    _delay_ms(1);
}
void lcd_nibble(int data)
{
    PORTD &= ~0x3C;
    if (data & 0x01)
        PORTD |= (1 << PD5);
    if (data & 0x02)
        PORTD |= (1 << PD4);
    if (data & 0x04)
        PORTD |= (1 << PD3);
    if (data & 0x08)
        PORTD |= (1 << PD2);
    lcd_pulse();
}
void lcd_cmd(unsigned char cmd)
{
    PORTB &= ~(1 << PB4);
    lcd_nibble(cmd >> 4);
    lcd_nibble(cmd & 0x0F);
    _delay_ms(2);
}
void lcd_data(unsigned char data)
{
    PORTB |= (1 << PB4);
    lcd_nibble(data >> 4);
    lcd_nibble(data & 0x0F);
    _delay_ms(2);
}
void lcd_string(const char *str)
{
    while (*str != '\0')
    {
        lcd_data(*str);
        str++;
    }
}
void lcd_initialise()
{
    _delay_ms(50);
    PORTB &= ~(1 << PB4);
    lcd_nibble(0x03);
    _delay_ms(5);
    lcd_nibble(0x03);
    _delay_ms(2);
    lcd_nibble(0x03);
    _delay_ms(2);
    lcd_nibble(0x02);
    _delay_ms(2);
    lcd_cmd(0x28);
    lcd_cmd(0x06);
    lcd_cmd(0x0C);
    lcd_cmd(0x01);
    _delay_ms(5);
}
void lcd_number(int number)
{
    char digits[5];
    int i = 0;
    if (number == 0)
    {
        lcd_data('0');
        return;
    }
    while (number > 0 && i < 5)
    {
        digits[i] = '0' + (number % 10);
        number = number / 10;
        i++;
    }
    while (i > 0)
    {
        i--;
        lcd_data(digits[i]);
    }
}
void DisplayMsg(const char *line1, const char *line2)
{
    lcd_cmd(0x01);
    lcd_cmd(0x80);
    lcd_string(line1);
    lcd_cmd(0xC0);
    lcd_string(line2);
}
void PlayBuzzer()
{
    PORTD |= (1 << PD7);
    _delay_ms(600);
    PORTD &= ~(1 << PD7);
}
void DisplayVisitors()
{
    lcd_cmd(0x01);
    lcd_cmd(0x80);
    lcd_string("Visitor count");
    lcd_cmd(0xC0);
    lcd_string("Visitors: ");
    lcd_number(visitors);
}
void UpdateVisitorsCounter(int change)
{
    visitors = visitors + change;
    if (visitors < 0)
        visitors = 0;
    PlayBuzzer();
    DisplayVisitors();
}
void gpioInit()
{
    DDRB &= ~((1 << PB0) | (1 << PB1));
    DDRB |= (1 << PB3) | (1 << PB4);
    DDRD |= 0xBC;
    PORTD &= ~(1 << PD7);
}
int main()
{
    gpioInit();
    lcd_initialise();
    DisplayMsg("Visitor counter", "Welcome");
    while (1)
    {
        pir1 = (PINB & (1 << PB0)) ? 1 : 0;
        pir2 = (PINB & (1 << PB1)) ? 1 : 0;
        int event1 = 0;
        int event2 = 0;
        if (pir1 == 1 && PIR1_active == 0)
            event1 = 1;
        if (pir2 == 1 && PIR2_active == 0)
            event2 = 1;
        PIR1_active = pir1;
        PIR2_active = pir2;
        if (event1 == 1 && event2 == 1)
        {
            lastPIR = IDLE;
            pendingTime = 0;
        }
        else
        {
            if (lastPIR == IDLE)
            {
                if (event1 == 1)
                {
                    lastPIR = ENTRY_PENDING;
                    pendingTime = 0;
                    DisplayMsg("Gate 1 detected",
                               "Waiting Gate 2");
                }
                else if (event2 == 1)
                {
                    if (visitors > 0)
                    {
                        lastPIR = EXIT_PENDING;
                        pendingTime = 0;

                        DisplayMsg("Gate 2 detected",
                                   "Waiting Gate 1");
                    }
                    else
                    {
                        DisplayMsg("No more visitors",
                                   "Count remains 0");
                    }
                }
            }
            else if (lastPIR == ENTRY_PENDING)
            {
                if (event2 == 1)
                {
                    visitors++;
                    lastPIR = IDLE;
                    pendingTime = 0;
                    PlayBuzzer();
                    DisplayVisitors();
                }
                else
                {
                    pendingTime = pendingTime + 10;
                }
            }
            else if (lastPIR == EXIT_PENDING)
            {
                if (event1 == 1)
                {
                    if (visitors > 0)
                        visitors--;

                    lastPIR = IDLE;
                    pendingTime = 0;

                    PlayBuzzer();
                    DisplayVisitors();
                }
                else
                {
                    pendingTime = pendingTime + 10;
                }
            }
            if (lastPIR != IDLE &&
                pendingTime >= timeout)
            {
                lastPIR = IDLE;
                pendingTime = 0;
                DisplayMsg("Crossing cancelled",
                           "Try again");
            }
        }
        _delay_ms(10);
    }
    return 0;
}
