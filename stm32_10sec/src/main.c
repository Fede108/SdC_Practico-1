#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/timer.h>
#include <stdio.h> 
#include <libopencm3/stm32/common/usart_common_all.h>
#include <libopencm3/stm32/f1/gpio.h>


#define ITERATIONS 60000000

#define FREQCLK 24

#define UART USART2
#define UART_PORT GPIOA
#define UART_TX_PIN GPIO2
#define UART_RX_PIN GPIO3
#define UART_BAUDRATE 9600
#define UART_DATABITS 8
#define UART_BUFFER_SIZE 64


void systemInit(void);
void configure_timer(void);
void configure_usart(void);
void send_uart(uint32_t time);

void configure_timer(void)
{
    // Habilitar reloj para TIM2
    rcc_periph_clock_enable(RCC_TIM2);

    timer_set_prescaler(TIM2, FREQCLK - 1); // 72 MHz / 72 = 1 MHz (1 tick = 1 µs)
    timer_set_period(TIM2, 0xFFFF);    // Máximo período
    timer_enable_counter(TIM2);
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
    snprintf(buffer, sizeof(buffer), "Frecuencia: %02d [Mhz], Tiempo de ejecucion: %02u [S]",FREQCLK, time);
    for (char* p = buffer; *p != '\0'; p++)
    {
        usart_send_blocking(UART, *p);
    }
}


void systemInit(void)
{
    
    if(FREQCLK == 72){
        rcc_clock_setup_pll(&rcc_hse_configs[RCC_CLOCK_HSE8_72MHZ]);
    }
    else{
        rcc_clock_setup_pll(&rcc_hse_configs[RCC_CLOCK_HSE8_24MHZ]);
    }
   
}


int main(void)
{
    systemInit();
    configure_timer();
    configure_usart();
    volatile uint32_t sum = 0;
    volatile uint32_t i;
    //Bucle que tarda aprox 10 segundos, asumiendo 4 ciclos por iteración.
    for ( int j = 0; j < ITERATIONS; j++) {
        sum += i;
    }
    
    uint32_t timer_value = timer_get_counter(TIM2);
    uint32_t time        = timer_value / 1000;

    timer_disable_counter(TIM2);
    send_uart(time);
    
    return 0;
    while (1)
    {
    }
    
}
