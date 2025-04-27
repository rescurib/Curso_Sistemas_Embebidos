#include "app.h"
#include <stdint.h>
#include <stdbool.h>
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal.h"  // Para HAL_GetTick()

#define APP_INTERVALO_2_MS     2
#define APP_MAX_OBSERVERS      8

typedef void (*task_callback_t)(void);

static task_callback_t observers[APP_MAX_OBSERVERS];
static uint8_t observer_count = 0;
static uint32_t last_tick = 0;

static uint16_t g_SW1_state = 0;

// Función de registro privada
static void registrar_observador(task_callback_t callback) {
    if (observer_count < APP_MAX_OBSERVERS) {
        observers[observer_count++] = callback;
    }
}

static void app_init(void);
static bool sw_1_debounce(void);
static void led_1_toggle(void);

// Punto de entrada publico hacia nuestra applicación
void app_main(void) 
{
    static uint8_t initialized = 0;
    if (!initialized) 
    {
        app_init();
        initialized = 1;
    }

    uint32_t now = HAL_GetTick();
    if ((now - last_tick) >= APP_INTERVALO_2_MS) 
    {
        last_tick = now;
        if (sw_1_debounce() )
        {
            for (uint8_t i = 0; i < observer_count; ++i) {
                if (observers[i]) 
                {
                    observers[i]();
                }
            }
        }
    }
}

// Internal init — place to register all observers
static void app_init(void) 
{
    registrar_observador(led_1_toggle);
}

static bool sw_1_debounce(void)
{
    g_SW1_state = (g_SW1_state<<1) | !HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) | 0xe000;
    if(g_SW1_state==0xf000) return true;
    return false;
}

static void led_1_toggle(void)
{
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_12);
}


