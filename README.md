# Executivo Cíclico

## Link para o Vídeo

O projeto foi explicado em um video no link: [Video no Youtube](https://youtu.be/D41Fi84FVlA)

## Objetivo do Projeto

Este projeto desenvolve um sistema de executivo cíclico que lê configurações de tarefas de um arquivo JSON e as organiza com base em uma heurística de escalonamento. O principal objetivo é calcular os tempos de ciclo primário e secundário para um conjunto de tarefas e sugerir um escalonamento que otimize a execução das tarefas dentro desses ciclos, maximizando a eficiência e a utilização da CPU.

## Como Funciona

### Entrada de Dados
As tarefas são definidas em um arquivo JSON, onde cada tarefa contém as seguintes propriedades:
- **ID**: Identificador único da tarefa.
- **Período**: Frequência com que a tarefa deve ser executada.
- **Tempo de Execução**: Tempo necessário para completar a tarefa.
- **Prioridade**: Prioridade da tarefa, que pode influenciar a ordem de execução em algumas heurísticas.

### Processamento
O programa realiza os seguintes passos:
1. **Leitura do Arquivo JSON**: As tarefas são extraídas do arquivo JSON.
2. **Cálculo dos Tempos de Ciclo**:
   - **Tempo de Ciclo Primário**: Calculado como o mínimo múltiplo comum (MMC) dos períodos das tarefas.
   - **Tempo de Ciclo Secundário**: Determinado como o máximo divisor comum (MDC) dos períodos.
3. **Escalonamento das Tarefas**:
   - As tarefas são ordenadas usando `qsort` baseado na heurística escolhida (Menor Tempo de Execução Primeiro, por padrão).
   - As tarefas são escalonadas para execução nos ciclos calculados.

### Heurísticas de Escalonamento
- **Menor Tempo de Execução Primeiro**: Prioriza tarefas que requerem menos tempo para serem concluídas, buscando reduzir o tempo médio de espera.
- **Maior Tempo de Execução Primeiro**: Incluído como uma alternativa para comparação, prioriza tarefas que levam mais tempo, potencialmente útil para certos tipos de cargas de trabalho.

## Análise dos Resultados

Após a execução, o programa imprime:
- **Tempos de Ciclo**: Os valores calculados para os tempos de ciclo primário e secundário.
- **Escalonamento Detalhado por Ciclo**: Mostra como as tarefas são alocadas em cada ciclo de acordo com a heurística aplicada.
- **Resumo Estatístico**:
  - **Total de Ciclos**: Quantidade de ciclos completos necessários para executar todas as tarefas dentro de um ciclo primário.
  - **Total de Intercâmbios de Tarefa por Ciclo**: Conta quantas vezes as tarefas são trocadas dentro dos ciclos, o que pode indicar a complexidade do escalonamento.
  - **Utilização da CPU**: Calculada como a porcentagem do tempo total de execução das tarefas em relação ao tempo total disponível no ciclo primário. Uma maior utilização indica um escalonamento mais eficiente.

### Considerações sobre a Utilização da CPU

Uma utilização da CPU significativamente abaixo de 100% pode indicar que:
- Há períodos de inatividade consideráveis devido à natureza das tarefas e seus períodos.
- A heurística de escalonamento pode não ser ideal para o conjunto específico de tarefas.

Alterar as tarefas, ajustar seus períodos e tempos de execução, ou escolher uma heurística diferente podem ser estratégias para melhorar essa métrica.

## Conclusão

Este sistema de escalonamento cíclico demonstra uma abordagem robusta para o gerenciamento de tarefas em sistemas de tempo real, onde a precisão e a previsibilidade são os principais elementos para um bom desempenho do sistema. A flexibilidade nas heurísticas de escalonamento permite que o sistema seja adaptado a diferentes requisitos operacionais e restrições de tarefas.
