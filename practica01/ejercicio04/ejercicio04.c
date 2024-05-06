/*
 * Copyright (c) 2006, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 */

/**
 * \file
 *         A very simple Contiki application showing how Contiki programs look
 * \author
 *         Adam Dunkels <adam@sics.se>
 */

#include "contiki.h"

#include "dev/button-sensor.h"
#include "dev/leds.h"

#include <stdio.h> /* For printf() */
/*---------------------------------------------------------------------------*/
PROCESS(hello_world_process, "Hello world process");
AUTOSTART_PROCESSES(&hello_world_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(hello_world_process, ev, data)
{
  PROCESS_BEGIN();

  leds_off(LEDS_ALL);

  SENSORS_ACTIVATE(button_sensor);
  static bool button_pressed = false;

  /* Initialize blue timer */
  static struct etimer blue_timer;
  etimer_set(&blue_timer, CLOCK_SECOND * 3);

  /* Initialize red timer */
  static struct etimer red_timer;
  etimer_set(&red_timer, CLOCK_SECOND * 5);

  /* Initialize green timer */
  static struct etimer green_timer;
  etimer_set(&green_timer, CLOCK_SECOND * 7);

  while(1) {
    /* Wait for any event */
    PROCESS_WAIT_EVENT();

    if (ev == sensors_event && data == &button_sensor) {
      printf("Button pressed\n");
      leds_off(LEDS_ALL);
      button_pressed = !button_pressed;
    }

    if(ev == PROCESS_EVENT_TIMER && data == &blue_timer) {
      if (button_pressed) {
        //leds_toggle(LEDS_BLUE); // no funciona
        leds_toggle(LEDS_ALL);
        leds_toggle(LEDS_RED);
        leds_toggle(LEDS_GREEN);
        printf("Blue\n");
      }
      etimer_reset(&blue_timer);
    }

    if(ev == PROCESS_EVENT_TIMER && data == &red_timer) {
      if (button_pressed) {
        leds_toggle(LEDS_RED);
        printf("Red\n");
      }
      etimer_reset(&red_timer);
    }

    if(ev == PROCESS_EVENT_TIMER && data == &green_timer) {
      if (button_pressed) {
        leds_toggle(LEDS_GREEN);
        printf("Green\n");
      }
      etimer_reset(&green_timer);
    }
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
