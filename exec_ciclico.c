#include <string.h>     // Inclui funções de manipulação de strings.
#include <stdio.h>      // Inclui funções de entrada e saída.
#include <json-c/json.h>// Inclui funções para manipulação de objetos JSON.
#include <stdlib.h>     // Inclui funções de alocação de memória e controle de processos.
#include <limits.h>     // Inclui definições de valores limites das variáveis.

// Função que calcula o Máximo Divisor Comum (MDC) de dois inteiros.
int mdc(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Função que calcula o Mínimo Múltiplo Comum (MMC) de dois inteiros.
int mmc(int a, int b) {
    return a * (b / mdc(a, b)); // Usa o MDC calculado para determinar o MMC.
}

// Estrutura de dados para representar uma tarefa.
typedef struct {
    char id[50];          // Identificador da tarefa.
    int periodo;          // Período de repetição da tarefa.
    int tempo_execucao;   // Tempo necessário para completar a tarefa.
    int prioridade;       // Prioridade da tarefa.
} Tarefa;

// Função comparadora para o qsort, compara baseado no tempo de execução.
int comparador(const void *v1, const void *v2) {
    const Tarefa *p1 = (const Tarefa *)v1;
    const Tarefa *p2 = (const Tarefa *)v2;
    return p1->tempo_execucao - p2->tempo_execucao; // Ordena do menor para o maior tempo de execução.
}

int main() {
    // Tentativa de abrir o arquivo JSON contendo as tarefas.
    FILE *fp = fopen("tarefas5.json", "r");
    if (!fp) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        return 1;  // Retorna 1 para indicar erro.
    }

    char buffer[2048];
    fread(buffer, sizeof(buffer), 1, fp); // Lê os dados do arquivo para o buffer.
    fclose(fp); // Fecha o arquivo após a leitura.

    // Parse do conteúdo do buffer para um objeto JSON.
    struct json_object *parsed_json = json_tokener_parse(buffer);
    struct json_object *tarefas = json_object_object_get(parsed_json, "tarefas");
    size_t n_tarefas = json_object_array_length(tarefas);

    // Aloca memória para as tarefas com base no número de tarefas encontradas.
    Tarefa *lista_tarefas = malloc(n_tarefas * sizeof(Tarefa));
    int tempo_ciclo_primario = 1;
    // int tempo_ciclo_secundario = INT_MAX;

    // Loop que processa cada tarefa JSON, extrai seus dados e calcula tempos de ciclo.
    for (size_t i = 0; i < n_tarefas; i++) {
        struct json_object *tarefa = json_object_array_get_idx(tarefas, i);
        strncpy(lista_tarefas[i].id, json_object_get_string(json_object_object_get(tarefa, "id")), 49);
        lista_tarefas[i].id[49] = '\0';  // Garante que o string é terminada corretamente.
        lista_tarefas[i].periodo = json_object_get_int(json_object_object_get(tarefa, "periodo"));
        lista_tarefas[i].tempo_execucao = json_object_get_int(json_object_object_get(tarefa, "tempo_execucao"));
        lista_tarefas[i].prioridade = json_object_get_int(json_object_object_get(tarefa, "prioridade"));

        tempo_ciclo_primario = mmc(tempo_ciclo_primario, lista_tarefas[i].periodo);
        // tempo_ciclo_secundario = (i == 0) ? lista_tarefas[i].periodo : mdc(tempo_ciclo_secundario, lista_tarefas[i].periodo);
    }

    printf("Testando possíveis valores de ciclo menor:\n");
    int x = 1, f[n_tarefas], f_count = 0;

    while (x <= tempo_ciclo_primario) {
        int valid = 1;
        for (int i = 0; i < n_tarefas && valid; i++) {
            if (x > lista_tarefas[i].tempo_execucao && (2*x - mdc(lista_tarefas[i].periodo, x) <= lista_tarefas[i].periodo)) {
                if (tempo_ciclo_primario % x == 0) {
                    valid = 1;
                } else {
                    valid = 0;
                }
            } else {
                valid = 0;
            }
        }
        if (valid) {
            f[f_count++] = x;
            printf("%d ", x);
        }
        x++;
    }

    if (f_count == 0) {
        printf("Não escalonável\n");
        exit(0);
    }

    // size_t size = sizeof(x);
    int tempo_ciclo_secundario = f[f_count-1];  // Escolhendo o primeiro ciclo válido como o menor correto
    
    // Ordena as tarefas usando o comparador definido anteriormente.
    qsort(lista_tarefas, n_tarefas, sizeof(Tarefa), comparador);

    // Impressão dos detalhes do escalonamento cíclico.
    printf("Cálculo de Ciclos para o Executivo Cíclico:\n");
    printf("-------------------------------------------\n");
    printf("Tempo de Ciclo Primário: %d unidades de tempo\n", tempo_ciclo_primario);
    printf("Tempo de Ciclo Secundário: %d unidades de tempo\n", tempo_ciclo_secundario);

    printf("\nEscalonamento Sugerido (Heurística: Menor Tempo de Execução Primeiro):\n");
    printf("----------------------------------------------------------------------\n");

    // Calcula o número de ciclos
    int num_ciclos = tempo_ciclo_primario / tempo_ciclo_secundario;
    int intercambios = 0;
    double utilizacao_cpu = 0.0;

    // Loop para escalonar as tarefas em ciclos baseados no tempo de ciclo secundário.
    for (int ciclo = 0; ciclo < num_ciclos; ciclo++) {
        int tempo_restante = tempo_ciclo_secundario;
        printf("Ciclo %d:\n", ciclo + 1);
        for (size_t i = 0; i < n_tarefas; i++) {
            if ((ciclo * tempo_ciclo_secundario) % lista_tarefas[i].periodo == 0) {
                if (lista_tarefas[i].tempo_execucao <= tempo_restante) {
                    printf("  - %s: tempo de execução = %d, período = %d, prioridade = %d\n", lista_tarefas[i].id, lista_tarefas[i].tempo_execucao, lista_tarefas[i].periodo, lista_tarefas[i].prioridade);
                    tempo_restante -= lista_tarefas[i].tempo_execucao;
                    utilizacao_cpu += (double)lista_tarefas[i].tempo_execucao / tempo_ciclo_primario;
                    if (i > 0) intercambios++;
                }
            }
        }
    }

    // Impressão do resumo dos resultados.
    printf("\nResumo:\n");
    printf("-------\n");
    printf("Total de Ciclos: %d\n", num_ciclos);
    printf("Total de Intercâmbios de Tarefa por Ciclo: %d\n", intercambios);
    printf("Utilização da CPU: %.2f%%\n", utilizacao_cpu * 100);

    free(lista_tarefas);  // Libera a memória alocada para as tarefas.
    json_object_put(parsed_json);  // Libera o objeto JSON.

    return 0;  // Finaliza o programa com sucesso.
}
