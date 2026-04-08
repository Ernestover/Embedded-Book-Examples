/*
 * Hello World — Blinking LED
 * Board: NUCLEO-L476RG
 *
 * The embedded equivalent of Hello World. Blinks the onboard LED
 * using bare metal register access — no HAL or vendor libraries.
 * Directly manipulates the GPIO output register (ODR) and uses a
 * software delay loop to control the blink rate.
 *
 * Reference: Programming Embedded Systems — Michael Barr
 */

#include "main.h"

void delay(volatile uint32_t count_ms) {
  #define CYCLES_PER_MS 1000 /*Number of decrement-and-test cycles.*/
  unsigned long nCycles = count_ms * CYCLES_PER_MS;
  while (nCycles--);
}

int main(void)
{

  // 1. enable clock for GPIO Port A
  // RCC->AHB23NR register, bit 0 = GPIOAEN
  RCC->AHB2ENR |= (1U << 0);

  // 2. configure PA5 as general purpose output 
  // MODER register: 2 bits per pin
  // PA5 = bits [11:10] -> set to 01 (output)
  GPIOA->MODER &= ~(3U << 10); // clear bits 11:10
  GPIOA->MODER |= (1U << 10); // SET BITS 11:10 TO 01 

  // 3. Blink loop
  while (1)
  {
    GPIOA->ODR |= (1U << 5); // PA5 HIGH -> LED ON
    delay(500);
    GPIOA->ODR &= ~(1U << 5); // PA5 LOW -> LED OFF
    delay(500);
  }
  return 0;
}
