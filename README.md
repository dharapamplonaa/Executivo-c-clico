# Executivo Cíclico

## Visão Geral

O sistema de escalonamento cíclico é projetado para gerenciar a execução de tarefas em sistemas embarcados ou de tempo real, onde a previsibilidade e a eficiência são extremamentes importantes. O objetivo é garantir que todas as tarefas sejam executadas dentro de seus períodos especificados, utilizando o mínimo múltiplo comum (MMC) para definir o ciclo maior (tempo de ciclo primário) e o máximo divisor comum (MDC) para determinar o ciclo menor (tempo de ciclo secundário), otimizando assim a execução das tarefas.

## Componentes Principais

### Estrutura usada para as Tarefas

Cada tarefa é representada por uma estrutura contendo:

- **ID:** Identificador único da tarefa.
- **Período:** Intervalo de tempo entre inícios consecutivos da tarefa.
- **Tempo de Execução:** Duração que a tarefa leva para ser concluída.
- **Prioridade:** Importância relativa da tarefa, usada para resolver conflitos de escalonamento.

## Lógica do Programa

### Inicialização e Leitura de Dados

O programa começa lendo o conjunto de tarefas de um arquivo JSON, populando a estrutura de dados de tarefas com IDs, períodos, tempos de execução e prioridades.

### Cálculo de Ciclos

Após a leitura dos dados, o programa calcula o ciclo maior usando MMC de todos os períodos das tarefas. O ciclo menor é inicialmente o MDC dos períodos, mas é ajustado para atender a requisitos específicos que garantem que todas as tarefas possam ser escalonadas adequadamente.

### Teste e Seleção do Ciclo Menor

O programa testa diferentes valores para o ciclo menor para encontrar um que maximize a eficiência e atenda aos critérios de escalonamento sem violar os períodos das tarefas. Isso é feito verificando se o ciclo menor proposto pode ser repetido dentro do ciclo maior sem conflitos e atendendo a todas as tarefas com seus respectivos períodos e tempos de execução.

### Escalonamento de Tarefas

As tarefas são então escalonadas de acordo com a heurística selecionada, e o sistema executa simulações para mostrar como as tarefas seriam escalonadas ao longo do tempo em ciclos menores dentro do ciclo maior.

### Comparação de Heurísticas

O sistema compara os resultados de diferentes heurísticas de escalonamento, mostrando como cada uma afeta a utilização da CPU, o número de intercâmbios de tarefas e a eficiência geral do escalonamento.

## Conclusão

Este sistema de escalonamento cíclico demonstra uma abordagem robusta para o gerenciamento de tarefas em sistemas de tempo real, onde a precisão e a previsibilidade são os principais elementos para um bom desempenho do sistema. A flexibilidade nas heurísticas de escalonamento permite que o sistema seja adaptado a diferentes requisitos operacionais e restrições de tarefas.
