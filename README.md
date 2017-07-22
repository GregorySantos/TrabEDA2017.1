<h1>Lista de Registros</h1>
<h3>Trabalho de Estrutura de Dados - UFBA - 2017.1</h3>

<h5>Dados do Trabalho</h5>
<p><strong>Nota Máxima:</strong> 10.0</p>
<p><strong>Peso da Média:</strong> 3</p>

<h6>Descrição:</h6>

<p>A equipe de no mínimo 2 e no máximo 3 integrantes deverá desenvolver um
programa para avaliar o tempo de execução de operações em estruturas de
dados.</p>

<p>Um arquivo do tipo csv com dados fictícios de funcionários de uma empresa será
entregue a equipe para testes, mas o programa deve poder aceitar qualquer
arquivo do mesmo tipo com o mesmo padrão de colunas. Um programa
desenvolvido em C deve importar esse arquivo para 2 tipos de estruturas dados
com apontadores: lista duplamente encadeada e árvore AVL. As estrutura de
dados devem armazenar um registro com variáveis que reflitam as colunas de
cada linha, como matrícula, nome, salário, email etc. Ambas as estruturas de
dados devem estar ordenadas de forma crescente pela variável matrícula de
cada registro já na inserção dos dados.</p>

<p>O programa deve ter um menu para acionar as seguintes operações:</p>
<ul>
  <li>Importação de todos os registros de um arquivo com nome a ser entrado
pelo usuário, que deve estar na mesma pasta onde o programa está
rodando.</li>
  <li>Exibição dos registros na ordem da matrícula</li>
  <li>Busca de um registro com determinado nome</li>
  <li>Busca de um registro com determinada matrícula</li>
  <li>Inserção de um novo registro ordenadamente pela matrícula, garantindo
que a matrícula informada pelo usuário não seja igual a nenhum outro
funcionário já inserido, pois se for igual não deve inserir</li>
  <li>Remoção de um registro com determinada matrícula</li>
</ul>

<p>Cada funcionalidade acima precisa ser uma função dentro do programa. As
funções não deve usar variáveis globais. A função de importação deve pedir ao
usuário o nome do arquivo que será importado. As operações diferentes da
importação só podem estar disponíveis depois da primeira importação. Cada
operação diferente da importação e inserção deve pedir ao usuário em qual
estrutura de dados será acionada. A importação e inserção deve ocorrer nas
duas estruturas de dados em sequência. Após a importação nas duas estruturas
o programa deve exibir a quantidade de registros importada e o tempo de
duração de importação em cada estrutura separadamente, o mesmo vale para
inserção.</p>

<p>A compilação do programa deve ser apenas em C, o que no gcc pode ser feita
pelo comando <strong><code>gcc –x c “nomedearquivo.c” –o “nomedearquivo.exe”</code></strong>.</p>

<p>Um relatório de até 4 páginas deve ser desenvolvido. O relatório deve apresentar
o programa, as operações, a quantidade e formato de dados utilizados para
testes. Testes devem ser feitos em cada operação para demonstrar os tempos
diferentes e finalmente discutir os motivos das diferenças de tempo baseadas
nas diferenças das estrutura de dados. O relatório deve ser feito no formato de
artigo da Sociedade Brasileira de Computação. O relatório deve incluir
referências a pelo menos 2 livros.</p>

<h6>Entregas e Prazos:</h6>

<ul>
  <li>Declaração dos membros da equipe - 11/07</li>
  <li>Arquivo executável no Windows e arquivo ou arquivos .c – 18/08</li>
  <li>Relatório do trabalho 01/09.</li>
  <li>Nota de 0 a 100% de cada membro do time para os demais membros do
time quanto a dedicação do mesmo ao trabalho – 02/09</li>
</ul>

<p>O respeito aos prazos será considerado na nota final. Atrasos causam multa de
20% ao dia.</p>

<p>As entregas deverão ser feitas pelo Moodle, com exceção da declaração dos
membros da equipe que será por esse <a href="https://docs.google.com/spreadsheets/d/1zjHTA3Gck3VxdcQmSr8T81m79orYCkj0gHwXnD1fUhA/edit?usp=sharing">Link</a></p>

<p>O modelo do <a href="http://www.sbc.org.br/documentos-da-sbc/summary/169-templates-para-artigos-e-capitulos-de-livros/878-modelosparapublicaodeartigos">Artigo da SBC</a> a ser seguido.</p>
