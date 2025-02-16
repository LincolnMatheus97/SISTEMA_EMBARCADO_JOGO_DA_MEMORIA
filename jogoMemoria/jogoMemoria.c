#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "inc/matriz_led.h"
#include "inc/display_oled.h"
#include "inc/buzzer.h"
#include "inc/logica_jogo.h"

// Função principal
int main()
{
    // Inicializa as entradas e saídas do Pico SDK
    stdio_init_all();

    // Inicializa a matriz de LEDs'
    npInit(LED_PIN);
    npClear();
    npWrite();

    // Inicializa ADC para leitura do Joystick.
    adc_init();
    adc_gpio_init(JOY_X_PIN);
    adc_gpio_init(JOY_Y_PIN);

    // Inicializa botão A e B
    gpio_init(BT_B_PIN);
    gpio_set_dir(BT_B_PIN, GPIO_IN);
    gpio_pull_up(BT_B_PIN);
    gpio_init(BT_A_PIN);
    gpio_set_dir(BT_A_PIN, GPIO_IN);
    gpio_pull_up(BT_A_PIN);

    // Inicializa display OLED
    inicializacaoDisplay();

    // Inicializa o buzzer
    pwm_init_buzzer(BUZZER_PIN);

    // Inicializa o jogo
    inicializarJogo();

    while (true)
    {   
        // Movimentar o Joystick
        movimentarJoystick();
        
        npClear();

        // Exibir LEDs acertados
        for (int i = 0; i < LED_COUNT; i++)
        {
            if (acertos[i])
            {
                npSetLED(i, 0, 1, 0);
            }
        }
        
        // Exibir posição atual do LED branco
        npSetLED(pegarIndiceLED(led_x, led_y), 1, 1, 1);
        npWrite();

        // Verificar se o jogador acertou a sequência de LEDs
        if (debounceBotao(BT_B_PIN))
        {
            verificarJogada();
        }

        sleep_ms(100);
    }
}