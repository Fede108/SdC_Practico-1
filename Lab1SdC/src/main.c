#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/systick.h>
#include <stdio.h> 
#include <libopencm3/cm3/nvic.h>


#define ITERATIONS 30000000

uint32_t freqclk = 24;

#define UART USART2
#define UART_PORT GPIOA
#define UART_TX_PIN GPIO2
#define UART_RX_PIN GPIO3
#define UART_BAUDRATE 9600
#define UART_DATABITS 8
#define UART_BUFFER_SIZE 64


void systemInit(void);
void configure_usart(void);
void send_uart(uint32_t time);
void configure_systick(void);

volatile uint32_t ms_ticks = 0;

void configure_systick(){
    systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
    systick_set_reload((freqclk*1000) - 1);
    systick_interrupt_enable();
    systick_counter_enable();

}
void sys_tick_handler(void) {
    ms_ticks++;
}

void configure_usart(void)
{

    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_USART2);

    gpio_set_mode(UART_PORT, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, UART_TX_PIN | UART_RX_PIN);

    usart_set_baudrate(USART2, UART_BAUDRATE);
    usart_set_databits(USART2, UART_DATABITS);
    usart_set_stopbits(USART2, USART_STOPBITS_1);
    usart_set_mode(USART2, USART_MODE_TX);
    usart_set_parity(USART2, USART_PARITY_NONE);
    usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);

    usart_enable(USART2);
}

void send_uart(uint32_t time)
{
    char buffer[UART_BUFFER_SIZE];
    snprintf(buffer, sizeof(buffer), "Frecuencia: %02lu [Mhz], Tiempo de ejecucion: %02lu [ms]",freqclk, time);
    for (char* p = buffer; *p != '\0'; p++)
    {
        usart_send_blocking(UART, *p);
    }
}


void systemInit(void)
{
    
    if(freqclk == 64){
        rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_HSI_64MHZ]);
    }
    else if(freqclk == 48){
        rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_HSI_48MHZ]);
    }else{
        rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_HSI_24MHZ]);
    }
   
}


int main(void)
{
    systemInit();
    configure_usart();
    configure_systick();
    volatile float sum = 0;
    volatile float i = 1.5;
    //volatile uint32_t sum = 0;
    //volatile uint32_t i = 1;
    //Bucle que tarda aprox 10 segundos, asumiendo 4 ciclos por iteración.
    for ( int j = 0; j < ITERATIONS; j++) {
        sum += i;
        sum = 0;
    }
    
    send_uart(ms_ticks);
    
    return 0;
    while (1)
    {
    }
    
}
