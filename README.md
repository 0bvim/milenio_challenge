# Processador de CSV

Este desafio visa avaliar suas habilidades técnicas e capacidade de solucionar problemas reais, desenvolvendo uma biblioteca compartilhada ou _shared object_ (.so) que será utilizada por uma aplicação em C.

## Objetivo

Implementar uma biblioteca que processe arquivos CSV, aplicando filtros e selecionando colunas conforme especificado. A solução deve ser capaz de integrar com a interface definida em C abaixo.

```c
/**
 * Process the CSV data by applying filters and selecting columns.
 *
 * @param csv The CSV data to be processed.
 * @param selectedColumns The columns to be selected from the CSV data.
 * @param rowFilterDefinitions The filters to be applied to the CSV data.
 *
 * @return void
 */
void processCsv(const char[], const char[], const char[]);

/**
 * Process the CSV file by applying filters and selecting columns.
 *
 * @param csvFilePath The path to the CSV file to be processed.
 * @param selectedColumns The columns to be selected from the CSV data.
 * @param rowFilterDefinitions The filters to be applied to the CSV data.
 *
 * @return void
 */
void processCsvFile(const char[], const char[], const char[]);
```
processCsv
- csv: String com os dados do CSV, onde cada linha representa um registro e as colunas são separadas por vírgulas.
    - Exemplo: `"header1,header2,header3\n1,2,3\n4,5,6"`
- selectedColumns: Uma string onde os nomes das colunas a serem selecionadas são separados por vírgulas.
    - Exemplo: `"header1,header3"`
- rowFilterDefinitions: Uma string onde cada filtro é definido em uma nova linha, no formato `header(comparador)valor`.
    - Exemplo: `"header1>1\nheader2=2\nheader3<6"`

processCsvFile
- csvFilePath: String com o caminho do arquivo CSV.
    - Exemplo: `"path/to/csv_file.csv"`
- selectedColumns: Uma string onde os nomes das colunas a serem selecionadas são separados por vírgulas.
    - Exemplo: `"header1,header3"`
- rowFilterDefinitions: Uma string onde cada filtro é definido em uma nova linha, no formato `header(comparador)valor`.
    - Exemplo: `"header1>1\nheader2=2\nheader3<6"`


Exemplo:

```c
const char csv[] = "header1,header2,header3\n1,2,3\n4,5,6\n7,8,9";
processCsv(csv, "header1,header3", "header1>1\nheader3<8");

// output
// header1,header3
// 4,6

const char csv_file[] = "path/to/csv_file.csv";
processCsvFile(csv_file, "header1,header3", "header1>1\nheader3<8");

// output
// header1,header3
// 4,6
```

## Funcionalidades Obrigatórias e Requisitos


O candidato deve focar nos requisitos obrigatórios, pois o descumprimento de qualquer um deles acarreta na desclassificação do processo seletivo.

Para os exemplos abaixo, considere sempre o seguinte CSV:

```csv
header1,header2,header3
1,2,3
4,5,6
7,8,9
```

- **O CSV processado deve ser escrito no stdout**

- **A primeira linha do CSV sempre será um header**

- **O CSV processado deverá incluir o header do CSV considerando a seleção de coluna**

- **A sua implementação deve tratar CSVs com quantidades arbitrárias de caractéres**

- **A sua implementação deve tratar CSVs onde as colunas tem quantidades arbitrárias de caractéres**

- **Uma string de seleção de colunas vazia é equivalente a selecionar todas as colunas**

- **No mínimo, o candidato deve implementar filtros para maior (>), menor (<) e igual (=)**

- **As strings de seleção de colunas e filtro sempre terão a mesma ordem que aparecem no CSV**

    Exemplo:
    - `"header1,header3"` ou `"header1=4\nheader3>3"` &rarr; OK
    - `"header3,header1"` ou `"header3>3\nheader1=4"` &rarr; NÃO OK

- **Vírgulas sempre delimitam uma coluna, aspas não têm nenhuma interpretação especial**

    Exemplo: No CSV abaixo, o nome da primeira coluna é `'hea"der1'`

    ```csv
    hea"der1,header2,header3
    1,2,3
    ```

- **Apenas linhas que condizem com todos os filtros devem ser selecionadas**

    Exemplo: Aplicando os filtros `"header1=4\nheader2>3"` e selecionando as colunas header1 e header3. Somente a linha 4,5,6 `(header1 = 4 AND header2 > 3)` deve ser selecionada, pois todas as condições dos filtros devem ser atendidas. Output do filtro abaixo:

    ```csv
    header1,header3
    4,6
    ```

- **Nunca serão fornecidos filtros inválidos ou colunas inexistentes**

    Exemplo:
    - Coluna inexistente: `"header4"`
    - Filtro inválido: `"header1#2"`

- **Nunca será fornecido mais de 1 filtro por coluna**

    Exemplo: Se o filtro for `"header1=2"`, não haverá outro filtro para `"header1"` na mesma operação.

- **O CSV de entrada terá no máximo 256 colunas**

- **O nome de cada coluna é único**

- **Os comparadores nos filtros devem seguir a ordem lexicográfica conforme a implementação da [strcmp](https://www.man7.org/linux/man-pages/man3/strcmp.3.html) da stdlibc**

- **A arquitetura alvo é x86_64**

- **Não é permitida a execução de processos externos. Seu código não deve usar chamadas de sistema para executar outros programas**

- **Não é permitido o uso de bibliotecas externas para converter o CSV em estruturas de dados intermediárias (libs de lexers e tokenizers podem ser utilizadas)**


## Funcionalidades Bônus

Se o candidato terminar todos os pontos obrigatórios e ainda dispor de tempo livre, a seguir estão algumas funcionalidades bônus que contarão como critério de desempate.

Para todos os exemplos abaixo, considere sempre o seguinte CSV:
```csv
header1,header2,header3
1,2,3
4,5,6
7,8,9
```

1) **Desenvolver testes unitários**
2) **As colunas que aparecem na string de colunas selecionadas podem estar em ordem arbitrária**
    Exemplo: Se a string de colunas selecionadas é `"header3,header1"`, sua implementação deve selecionar as colunas nesta ordem.

    ```csv
    header1,header2,header3
    1,2,3
    4,5,6
    7,8,9
    ```

    E a string de colunas selecionadas: `"header3,header1"`, o resultado deve ser:

    ```csv
    header1, header3
    1,3
    4,6
    7,9
    ```

3) **As colunas na string de filtros podem aparecer em ordem arbitrária**

    Se os filtros são fornecidos como `"header2>3\nheader1=4"`, sua implementação deve aplicar esses filtros corretamente, independentemente da ordem, conforme output abaixo:

    ```csv
    header1,header2,header3
    4,5,6
    ```

4) **Colunas que não existem podem aparecer na seleção de colunas e nos filtros**

    Se a string de colunas selecionadas inclui `"header4"` e o CSV não tem um header header4, ou se os filtros incluem `"header5=10"` e o CSV não tem um header header5, sua implementação deve tratar esses casos adequadamente, escrevendo no stderr com a mensagem `"Header 'header4' not found in CSV file/string"` ou `"Header 'header5' not found in CSV file/string"`, respectivamente, encerrando a execução.


5) **Tratamento de erro para filtros inválidos**

    Se for fornecido um filtro inexistente ou inválido, como `header1#2`, sua implementação deve tratar esses casos escrevendo no stderr com a mensagem `"Invalid filter: 'header1#2'"`.

6) **Aceitar mais de 1 filtro por header**

    Permitir que múltiplos filtros sejam aplicados a um mesmo header, como `"header1=1\nheader1=4\nheader2>3\nheader3>4"`, e tratar esses filtros de forma adequada. Para essa implementação, o candidato deverá implementar a lógica OR para filtros no mesmo header.
    O filtro de exemplo será considerado como: `(header1=1 OR header1=4) AND header2>3 AND header3>4`, resultando no output abaixo:

    ```csv
    header1,header2,header3
    4,5,6
    ```

7) **Implementar os operadores diferente (!=), Maior ou igual que (>=), e Menor ou igual que (<=)**

    Permitir que filtros utilizem operadores de diferença, maior ou igual, e menor ou igual, como `"header1!=2\nheader2>=5\nheader3<=6"`, e tratar esses filtros de forma adequada resultando no output abaixo:

    ```csv
    header1,header2,header3
    4,5,6
    ```
---
