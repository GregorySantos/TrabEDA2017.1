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

<h2>Padrão para o Uso do GitHub</h2>

<p>Para baixar o repositório na sua máquina execute: <code>git clone https://github.com/GregorySantos/TrabEDA2017.1</code></p>
<p>Para criar uma Branch corretamente é preciso seguir alguns passos. Primeiro entre na Branch que tem a funcionalidade que você queria melhorar, <b>é recomendável sempre criar uma Branch a partir do master</b>(<i>Caso o master ainda não tenha as funcionalidades necessárias para a implementação que deseja realizar, solicite ao dono da Branch onde as funcionalidades já foram criadas para atualizar a master</i>), e execute <code>git checkout -b "nomeDaBranch#IdIssue"</code>. Um exemplo prático: <code>git checkout -b Menu#5</code>.</p>
<p>Para atualizar o repositório no seu computador execute: <code>git pull origin nomeDaBranch</code></p>
<p>Para enviar as suas alterações para o GitHub execute: <code>git push origin nomeDaBranch</code></p>
<p>Para entrar em alguma Branch execute <code>git checkout nomeDaBranch</code>.</p>
<p>Para visualizar a lista das Branchs que o seu Git já conhece e a Branch que você esta atualmente execute: <code>git branch</code>.</p>
<p>Para entrar em alguma Branch execute: <code>git checkout nomeDaBranch</code>.</p>
<p>Para atualizar ou mesclar as mudanças da Branch atual com outra Branch execute: <code>git merge outraBranch</code>.(<i>Dica: Utilize esse comando para Atualizar somente a sua Branch com as funcionalidades já implementadas na master</i>)</p>
<p>Para atualizar a master com as funcionalidades da sua Branch, abra um <strong>Pull Request no GitHub</strong>!!!</p>
<h2>Regras de Etiqueta de Desenvolvimento:</h2>
<ul>
<li>Não edite nada na Branch que não pertence a você!</li>
<li>Não edite nada diretamente da Master!</li>
<li>Revise seu código antes de atualizar a master com as suas funcionalidades!</li>
<li>Assine as Issues para informar a equipe que você está desenvolvendo aquela funcionalidade.</li>
<li>Realize testes em sua Branch antes de atualizar a master com as suas funcionalidades.</li>
<li>Antes de desenvolver uma nova funcionalidade ou corrigir algum bug, verifique se ela está citada em alguma Issue para referenciar a sua Branch. Caso não esteja, cria uma Issue da funcionalidade ou Bug que deseja implementar ou corrigir.</li>
<li>Somente atualize a master através de requisições do Pull Request para a equipe acompanhar as implementações!!!</li>
<li><strong>Não aceite o seu próprioPull Request!</strong> Comunique-se com a Equipe de Desenvolvimento antes!</li>
</ul>
