#ifndef JOGO_MEMORIA_H // Include guard para evitar múltiplas inclusões
#define JOGO_MEMORIA_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "inc/matriz_led.h"
#include "inc/display_oled.h"
#include "inc/buzzer.h"

// Definição dos pinos do Joystick, Botões e tamanho Matriz de LEDs
#define JOY_X_PIN 26
#define JOY_Y_PIN 27
#define BT_A_PIN 5
#define BT_B_PIN 6
#define MATRIZ_LINHA 5
#define MATRIZ_COLUNA 5

// Função para debouncing dos botões.
bool debounceBotao(uint pin)
{   
    // Variável estática para armazenar o último tempo de pressionamento do botão.
    static uint32_t last_press = 0;
    uint32_t now = to_ms_since_boot(get_absolute_time());

    if (gpio_get(pin) == 0)
    {
        if (now - last_press > 300)
        {
            last_press = now;
            sleep_ms(50);
            return true;
        }
    }
    return false;
}

// Variáveis do jogo.
int led_x = 0, led_y = 0;          // Posição do LED selecionado
int sequencia[5];                  // Sequência de LEDs
int tamanho_sequencia = 1;         // Começamos com 3 LEDs
int indice_jogador = 0;            // Índice do jogador na sequência
int nivel = 1;                     // Nível do jogador
bool acertos[LED_COUNT] = {false}; // LEDs acertados
static uint16_t last_x_value = 0;  // Último valor do ADC_X
static uint16_t last_y_value = 0;  // Último valor do ADC_Y

// Movimentação do Joystick

void movimentarJoystick()
{
    adc_select_input(0);
    uint16_t x_value = adc_read();
    adc_select_input(1);
    uint16_t y_value = adc_read();

    // Só atualiza se houve uma mudança significativa  ( >200 unidades no ADC)
    if (abs((int)x_value - (int)last_x_value) > 200)
    {
        last_x_value = x_value;

        if (x_value > 4000 && led_y < MATRIZ_LINHA - 1)
            led_y++; // Baixo
        if (x_value < 1000 && led_y > 0)
            led_y--; // Cima
    }

    if (abs((int)y_value - (int)last_y_value) > 200)
    {
        last_y_value = y_value;

        if (y_value > 4000 && led_x < MATRIZ_COLUNA - 1)
            led_x++; // Direita
        if (y_value < 1000 && led_x > 0)
            led_x--; // Esquerda
    }
}

// Converte coordenadas (x, y) em um índice para a matriz de LEDs.
int pegarIndiceLED(int x, int y)
{
    x = 4 - x; // Inverte a coluna
    if (y % 2 == 0)
    {
        return y * 5 + x;
    }
    else
    {
        return y * 5 + (4 - x);
    }
}

// Gera uma sequência de LEDs aleatória.
void sequenciaAleatoria()
{
    for (int i = 0; i < tamanho_sequencia; i++)
    {
        int x = rand() % MATRIZ_COLUNA;
        int y = rand() % MATRIZ_LINHA;
        sequencia[i] = pegarIndiceLED(x, y);
    }
}

// Exibe a sequência de LEDs com Temporizadores de hardware.
void exibirSequencia()
{

    absolute_time_t tempo_atual = get_absolute_time();

    for (int i = 0; i < tamanho_sequencia; i++)
    {
        npClear();
        npSetLED(sequencia[i], 0, 0, 1);
        npWrite();

        while (absolute_time_diff_us(tempo_atual, get_absolute_time()) < 500000)
        {
        } // Espera 500ms sem bloquear
        tempo_atual = get_absolute_time();

        npClear();
        npWrite();

        while (absolute_time_diff_us(tempo_atual, get_absolute_time()) < 250000)
        {
        } // Espera 250ms sem bloquear
        tempo_atual = get_absolute_time();
    }

}

// Indica erro na sequência.
void indicaErro()
{
    for (int i = 0; i < 3; i++)
    {
        npClear();
        // Pisca os LEDs
        for (int j = 0; j < LED_COUNT; j++)
        {   
            // LEDs Vermelhos para os índices 0, 4, 6, 8, 12, 16, 18, 20 e 24 da matriz de LEDs
            if (j == 0 || j == 4 || j == 6 || j == 8 || j == 12 || j == 16 || j == 18 || j == 20 || j == 24)
            {
                npSetLED(j, 1, 0, 0);
            }
        }
        npWrite();
        sleep_ms(200);
        npClear();
        npWrite();
        sleep_ms(200);
    }
}

// Indica sucesso no sequência.
void indicaAcerto()
{
    for (int i = 0; i < 3; i++)
    {
        npClear();
        // Pisca os LEDs
        for (int j = 0; j < LED_COUNT; j++)
        {   
            // LEDs Verde para os índices 3, 5, 7, 11 e 19 da matriz de LEDs
            if (j == 3 || j == 5 || j == 7 || j == 11 || j == 19)
            {
                npSetLED(j, 0, 1, 0);
            }
        }
        npWrite();
        sleep_ms(200);
        npClear();
        npWrite();
        sleep_ms(200);
    }
}

// Indica vitoria no jogo com temporizadores de hardware.
void indicaVitoria()
{
    while (!debounceBotao(BT_A_PIN))
    {   
        absolute_time_t start_time = get_absolute_time();
        while (absolute_time_diff_us(start_time, get_absolute_time()) < 100000) // 100ms
        {
            // Pisca os LEDs
            npClear();
            for (int j = 0; j < LED_COUNT; j++)
            {
                int aleatorio = rand() % 2;
                int aleatorio2 = rand() % 2;
                int aleatorio3 = rand() % 2;

                // Se todos os aleatórios forem 0, muda para 1 para evitar LEDs Apagados e Brancos
                if (aleatorio == 0 && aleatorio2 == 0 && aleatorio3 == 0)
                {
                    aleatorio = 1;
                }
                npSetLED(j, aleatorio, aleatorio2, aleatorio3);
            }
            npWrite();
        }

        start_time = get_absolute_time();
        while (absolute_time_diff_us(start_time, get_absolute_time()) < 100000) // 100ms
        {
            // Apaga os LEDs
            npClear();
            npWrite();
        }
    }
}

// Reseta o jogo.
void reinicializarJogo()
{
    nivel = 1;
    tamanho_sequencia = 1;
    indice_jogador = 0;

    memset(acertos, 0, sizeof(acertos)); // Zera os acertos

    sleep_ms(500);
    char nivelMsg[20];
    sprintf(nivelMsg, "Nivel: %d", nivel);
    displayMensagem(nivelMsg, "Memorize os LEDs", "Mova o Joystick", "Aperte B para", "Confirmar o LED");
    sleep_ms(1000);

    sequenciaAleatoria();
    exibirSequencia();
}

// Função para inicializar o jogo
void inicializarJogo()
{
    // Inicializa o jogo da memória com uma semente aleatória
    uint32_t seed = time(NULL) ^ adc_read(); // Combina tempo com leitura do ADC
    srand(seed);
    npWrite();
    npClear();
    displayMensagem("Bem Vindo ao", "Jogo da Memoria.", "=)", "", "");
    sleep_ms(3000);
    displayMensagem("Grave a ordem", "correta de LEDs", "para ganhar.", "Aperte Botao A", "Para Iniciar");

    // Aguarda o jogador pressionar o botão A para iniciar o jogo.
    while (!debounceBotao(BT_A_PIN)){}

    // Inicializa o jogo
    reinicializarJogo();
}

// Verifica se o jogador acertou a sequência.
void verificarJogada()
{   
    // Pega o índice do LED selecionado pelo jogador
    int index = pegarIndiceLED(led_x, led_y);

    // Se o jogador acertou o LED
    if (index == sequencia[indice_jogador])
    {
        beep_suave(BUZZER_PIN, 250);
        acertos[index] = true;
        npSetLED(index, 0, 1, 0);
        npWrite();
        indice_jogador++;

        // Se o jogador acertou toda a sequência
        if (indice_jogador == tamanho_sequencia)
        {
            // Se o jogador chegar ao nível 5, ele venceu
            if (nivel == 5)
            {
                displayMensagem("Parabens =D", "Voce venceu!", "", "Aperte Botao A", "para reiniciar");
                indicaVitoria();
                inicializarJogo();
                return;
            }

            indicaAcerto();

            displayMensagem("Nivel Concluido", "Se esta pronto", "Aperte Botao A", "Para iniciar ", "sequencia");

            while (!debounceBotao(BT_A_PIN)){}

            nivel++;
            tamanho_sequencia++;
            indice_jogador = 0;
            memset(acertos, 0, sizeof(acertos)); // Zera os acertos

            sleep_ms(500);
            char nivelMsg[20];
            sprintf(nivelMsg, "Nivel: %d", nivel);
            displayMensagem(nivelMsg, "Memorize os LEDs", "Mova o Joystick", "Aperte B para", "confirmar o LED");
            sleep_ms(1000);
            sequenciaAleatoria();
            exibirSequencia();
        }
    }
    // Se o jogador errou o LED
    else
    {
        beep_grave(BUZZER_PIN, 250);
        indicaErro();
        displayMensagem("Errou =(", "Aperte Botao A", "para tentar", "novamente", "");
        while (!debounceBotao(BT_A_PIN)){}
        reinicializarJogo();
    }
}

#endif