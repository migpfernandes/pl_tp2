XML Workbench
Neste projecto, pretende-se desenvolver uma plataforma para manipulação de documentos XML.
Esta plataforma terá dois níveis: num primeiro nível é preciso reconhecer um documento XML e construir uma sua representação em memória; num segundo nível pretende-se generalizar permitindo o carregamento de vários documentos para memória sobre os quais se poderão fazer várias operações: selecção de partes, geração de novos documentos a partir dos que estão carregados, estatísticas, ...
Podemos dividir este enunciado em 3 partes que se descrevem nas secções seguintes.
6.1 Reconhecedor de Documentos Estruturados
Como já foi referido, nesta fase o alunos deverá desenvolver um parser que valide um documento XML e crie em memória uma representação do mesmo.
A título apenas de exemplo apresenta-se uma possível gramática para um documento XML:
      Documento --> ElemList ’$’
      ElemList --> ElemList Elem
                 | Elem
￼￼￼￼￼￼17
￼￼￼￼4 5 6 7
Elem --> char
       | ’&’ id ’;’
       | ’<’ id AttrList ’>’ ElemList ’<’ ’/’ id ’>’
       | ’<’ id AttrList ’/’ ’>’
AttrList --> Attr AttrList
￼￼￼￼￼￼￼￼￼￼8 9|&
￼￼￼￼￼￼10
      Attr --> id ’=’ valor
No reconhecimento do documento, o parser desenvolvido deverá verificar os seguintes invarian- tes:
￼￼￼11 12 13
14 15 16 17 18
•
•
6.2
todas as anotações correspondentes a elementos com conteúdo são abertas e fechadas correctamente (não há marcas cruzadas e nada fica por fechar ou nada é fechado sem ter sido aberto antes);
o documento tem que obrigatoriamente começar com a abertura dum elemento (que irá englobar todo o documento).
Interpretador de Comandos
O parser desenvolvido no ponto anterior será uma peça de algo bem maior: o tal "XML Work- bench".
Pretende-se agora criar um ambiente de trabalho que aceite os seguintes comandos:
LOAD <path para o documento> id — Este comando irá usar o parser desenvolvido no ponto anterior para reconhecer e carregar um documento XML. No fim, deverá ainda criar uma entrada numa estrutura de dados interna em que o identificador id fica associado ao documento reconhecido;
LIST — Mostra no écran a lista de documentos carregados e respectivos ids;
SHOW id — Mostra no écran o documento associado ao identificador id em formato ESIS
(ou noutro formato semelhante definido por si);
EXIT — Sai do programa;
HELP — Imprime no écran um texto parecido com esta lista de comandos.
Pode usar a imaginação à vontade para acrescentar comandos a esta lista.
Considere ainda a seguinte gramática proposta para este interpretador (pode alterá-la à von- tade):
￼￼￼￼￼Interp --> ComList
ComList --> Comando
          | ComList Comando
Comando --> LOAD fich-id id
          | SHOW id
          | LIST
          | EXIT
          | HELP
￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼18
6.3 Document Query Language
Neste ponto, todos grupos de trabalho deverão estar munidos dum interpretador de comandos que permite carregar documentos, visualizá-los, fornecendo assim um primeiro conjunto de facilidades básicas num sistema documental.
Nesta fase, vamos adicionar um novo comando à lista dos já existentes:
19
20 21 22
23
￼￼￼￼￼QLE: [selector de documentos] [query-exp]
[selector de documentos] --> * "todos os docs carregados"
                           | id "apenas o doc com ident=id"
                           | id1,id2,...,idn
[query-exp] --> "definida mais à frente"
￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼O resto do enunciado irá descrever através da apresentação de exemplos as várias facetas das expressões de query que se pretendem suportar.
6.3.1 Interrogando os Documentos
A operação de seleccionar os elementos com os quais se quer fazer alguma coisa, ou aos quais se quer aplicar algum processamento, tem sido, desde há algum tempo, uma preocupação das pessoas que trabalham nesta área. Começou por surgir na transformação e na formatação: era preciso seleccionar os elementos que se queriam transformar, ou que se queriam mapear num ou mais objectos com características gráficas (formatação). Este esforço é visível no DSSSL ; o primeiro elemento das suas regras é uma expressão de "query"que selecciona os elementos aos quais será aplicado o processamento especificado. Por último, esta necessidade surgiu ligada às linguagens de "query"para documentos estruturados, como as que foram propostas na conferência dedicada a esse tópico.
Assim se chegou, rapidamente, à conclusão de que a operação de selecção necessária para a transformação ou formatação era muito semelhante à necessária nos sistemas de bases de dados documentais para a realização de "queries".
Depois de algum tempo de discussão (moderada pelo W3C - World Wide Web Consortium), começa a emergir algum consenso na utilização do XSLT , uma sublinguagem de padrões presente no XSL - a proposta de normalização para a especificação de estilos a associar a documentos XML. O XSLT tornou-se um standard e foi já alvo de um estudo formal por parte de Wadler , apresentado na conferência mundial da área ("Markup Technologies 99"), e onde ele define a linguagem usando semântica denotacional (formalismo de cariz funcional utilizado para especificar a sintaxe e a semântica de linguagens).
Depois dum estudo de algumas destas linguagens (em particular todas as que já foram referidas), foi fácil constatar que o XSLT é um denominador comum de uma grande parte delas, aquelas que foram desenvolvidas a pensar em documentos estruturados, tratando-se portanto de uma linguagem específica. Houve, no entanto, uma linguagem que cativou a atenção do autor, pela sua simplicidade e recurso à teoria de conjuntos, a linguagem proposta por Tim Bray na QL’98 - The Query Languages Workshop designada por Element Sets. Um estudo mais atento da linguagem e do seu historial, revelou ser esta a especificação por detrás do conhecido motor de procura Pat comercializado pela OpenText e utilizado na maior parte dos primeiros portais da Internet.
19
Enquanto as linguagens do tipo XSLT assentam numa sintaxe concreta e específica, a Element Sets define uma notação abstracta baseada em cinco operadores da teoria de conjuntos: contido (within), contém (including), união (+), intersecção (ˆ) e diferença (−). Bray argumenta ser capaz de especificar uma grande percentagem de queries que possam ser necessárias num sistema de arquivo documental à custa da combinação daqueles cinco operadores. Numa primeira análise e a título comparativo, apresentam-se a seguir dois exemplos, uma query simples e uma mais complicada que irão ser especificadas respectivamente recorrendo a XSLT e a Element Sets.
Query Simples Pretende-se seleccionar todos os parágrafos (PARA) pertencentes à introdu- ção (INTROD) que contenham uma ou mais notas de rodapé (FOOTNOTE) ou uma ou mais referências (REF) a outros elementos no documento.
Em Element Sets a query seria:
1 2 3 4
1
￼￼￼￼￼set1 = Set(’PARA’) within Set(’INTROD’)
set2 = set1 including Set(’FOOTNOTE’)
set3 = set1 including Set(’REF’)
set4 = (set2 + set3) - (set2 ^ set3)
￼￼￼￼￼￼￼￼￼Apesar de complexa, foi fácil especificar esta query. Bastou excluir (diferença de conjuntos) os elementos resultantes da query anterior que continham ambos os elementos (intersecção de conjuntos), REF e FOOTNOTE.
Temos agora, a especificação em XSLT:
￼￼￼￼￼INTROD/PARA[(FOOTNOTE and (not REF)) or (REF and (not FOOTNOTE))]
￼￼￼Do estudo comparativo realizado entre os dois tipos de linguagem, e do qual os dois exemplos acima fazem parte, podemos concluir que, em termos da operação de selecção, são mais ou menos equivalentes, não se tendo encontrado nenhuma situação que uma solucionasse e a outra não. Vão diferir é no método como fazem a selecção: o XSLT usa a árvore documental e toda a operação de selecção é feita em função dessa estrutura; a Element Sets, por outro lado, não usa a árvore documental, manipula o documento como um conjunto de elementos usando uma sintaxe mais universal. Mas esta diferença existe apenas perante o utilizador que usa a linguagem porque em termos de implementação não se pode fugir às travessias da árvore documental.
Ao contrário do que o leitor poderia supor nesta altura, a escolha não recaiu sobre a Element Sets mas sim sobre uma linguagem do tipo XSLT, a XQL - XML Query Language . Os motivos por detrás desta escolha são muito simples. Apesar dos paradigmas, em termos de selecção, serem equivalentes, as linguagens do tipo XSLT vão além da selecção, permitem ter um segundo nível de selecção baseado em restrições sobre o conteúdo.
6.3.2 A Linguagem para o Projecto
A linguagem XSLT fornece um método bastante simples para descrever a classe de nodos que se quer seleccionar. É declarativa em lugar de procedimental. Apenas é preciso especificar o tipo dos nodos a procurar usando um tipo de padrões simples baseado na notação de directorias dum sistema de ficheiros (a sua estrutura é equivalente à de uma árvore documental). Por exemplo,
livro/autor, significa: seleccionar todos os elementos do tipo autor contidos em elementos livro. 20
A XQL é uma extensão do XSLT. Adiciona operadores para a especificação de filtros, operações lógicas sobre conteúdo, indexação em conjuntos de elementos, e restrições sobre o conteúdo dos elementos. Basicamente, é uma notação para a especificação de operações de extracção de informação de documentos estruturados.
Como já foi dito, vamos começar por descrever operadores relacionados com a selecção mas a linha divisória entre selecção e restrição irá sendo diluída ao longo do texto, confundindo-se até, para os casos em que a integração das duas é muito forte.
Padrões e Contexto Uma expressão de selecção é sempre avaliada em função dum contexto de procura. Um contexto de procura é um conjunto de nodos a que uma expressão se pode aplicar de modo a calcular o resultado. Todos os nodos no contexto de procura são filhos do mesmo nodo pai; o contexto de procura é constituído por todos os nodos que são filhos deste nodo pai e respectivos atributos mais os atributos do nodo pai.
As expressões de selecção poderão ser absolutas (o contexto é seleccionado em função do nodo raíz - "/"), ou relativas (o contexto é seleccionado em função do contexto actual - "."). Na es- pecificação do contexto pode ainda ser usado o operador "//"com o significado de descendência recursiva.
Exemplos:
Seleccionar todos os elementos autor no contexto actual :
1 2 3
Seleccionar o elemento raíz (report) deste documento : 1
Seleccionar todos os elementos autor em qualquer ponto do documento actual : 1
Seleccionar todos os elementos capítulo cujo atributo tema é igual ao atributo especialidade
:
1
Seleccionar todos os elementos título que estejam um ou mais níveis abaixo do contexto act
:
1
21
￼￼￼￼￼./autor ou
autor
￼￼￼￼￼￼￼￼￼￼￼￼/report
￼￼￼￼￼￼￼￼//autor
￼￼￼￼￼￼￼￼capítulo[/report/@especialidade = @tema]
￼￼￼￼￼￼￼￼.//título
￼￼￼
Quantificador: todos O operador "*"quando usado numa expressão de selecção selecciona todos os elementos nesse contexto.
Exemplos:
Seleccionar todos os elementos filhos de autor :
1
Seleccionar todos os elementos nome que sejam netos de report : 1
Seleccionar todos os elementos netos do contexto actual :
1 2 3
Seleccionar todos os elementos que tenham o atributo identificador : 1
Atributos Como já se pôde observar nalguns exemplos, o nome de atributos é precedido por "@". Os atributos são tratados como subelementos, imparcialmente, sempre que possível. De notar que os atributos não podem ter subelementos pelo que não poderão ter operadores de contexto aplicados ao seu conteúdo (tal resultaria numa situação de erro sintáctico). Os atributos também não têm conceito de ordem, são por natureza anárquicos pelo que nenhum operador de indexação deverá ser-lhes aplicado.
Exemplos:
Seleccionar o atributo valor no contexto actual :
1
Seleccionar o atributo dólar de todos os elementos preço no contexto actual : 1
Seleccionar todos os elementos capítulo que tenham o atributo língua : 1
Seleccionar o atributo língua de todos os elementos capítulo : 1
￼￼￼￼￼autor/*
￼￼￼￼￼￼￼￼report/*/nome
￼￼￼￼￼￼￼￼*/* ou
./*/*
￼￼￼￼￼￼￼￼￼￼￼￼*[@identificador]
￼￼￼￼￼￼￼￼@valor
￼￼￼￼￼￼￼￼preço/@dólar
￼￼￼￼￼￼￼￼capítulo[@língua]
￼￼￼￼￼￼￼￼capítulo/@língua
￼￼22
￼
Exemplo inválido : 1
Filtro subquery O resultado duma query pode ser refinado através de uma subquery (restri- ção aplicada ao resultado da query principal), indicada entre "["e "]"(nos exemplos anteriores já apareceram várias sem nunca se ter explicado a sua sintaxe e semântica).
A subquery é equivalente à cláusula SQL WHERE.
O valor resultante da aplicação de uma subquery é booleano e os elementos para os quais o valor final seja verdadeiro farão parte do resultado final.
Há operadores nas subqueries que permitem testar o conteúdo de elementos e atributos.
Exemplos:
Seleccionar todos os elementos capítulo que contenham pelo menos um elemento excerto
:
1
Seleccionar todos os elementos título pertencentes a elementos capítulo que tenham pelo m
:
1
Seleccionar todos os elementos autor pertencentes a elementos artigo que tenham pelo men
:
1
Seleccionar todos os elementos artigo que contenham elementos autor com email : 1
Seleccionar todos os elementos artigo que tenham um autor e um título : 1
Como se pode observar nalguns destes exemplos, algumas das restrições que pretendemos co- locar sobre os documentos podem ser especificadas com os construtores e operadores já apre- sentados. A linha divisória entre a selecção e a restrição parece já um pouco diluída.
￼￼￼￼￼preço/@dólar/total
￼￼￼￼￼￼￼￼capítulo[excerto]
￼￼￼￼￼￼￼￼capítulo[excerto]/titulo
￼￼￼￼￼￼￼￼artigo[excerto]/autor[email]
￼￼￼￼￼￼￼￼artigo[autor/email]
￼￼￼￼￼￼￼￼artigo[autor][titulo]
￼￼￼23
e
Expressões booleanas As expressões booleanas podem ser usadas nas subqueries e estas, já nos permitem especificar condições contextuais como a restrição de valores a um domínio. Uma expressão booleana tem a seguinte forma:
1
Os operadores são normalmente binários, tomam como argumentos um valor à esquerda e um valor à direita: or, and e not (este é unário tomando o valor à direita).
Com estes operadores e o agrupamento por parentesis podem especificar-se queries bastante complexas.
Exemplos:
Seleccionar todos os elementos autor que tenham um email e um url :
1
Seleccionar todos os elementos autor que tenham um email e um url : 1
No universo das queries, o resultado seria o conjunto de autores que tivessem email e url
Seleccionar todos os elementos autor que tenham um email ou um url e pelo menos uma pu
:
1
Seleccionar todos os elementos autor que tenham um email e nenhuma publicação
:
1
Seleccionar todos os elementos autor que tenham pelo menos uma publicação e não tenham
:
1
Equivalência A igualdade é notada por = e a desigualdade por ! =.
Podemos usar strings nas expressões desde que limitadas por aspas simples ou duplas.
Exemplos:
Seleccionar todos os autores que têm o subelemento organização preenchido com o valor ’U
:
1
24
￼￼￼￼￼val-esquerda operador val-direita
￼￼￼￼￼￼￼￼autor[email and url]
￼￼￼￼￼￼￼￼autor[email and url]
￼￼￼￼￼￼￼￼autor[(email or url) and publicação]
￼￼￼￼￼￼￼￼autor[email and not publicação]
￼￼￼￼￼￼￼￼autor[publicação and not (email or url)]
￼￼￼￼￼￼￼￼autor[organização = ’U.Minho’]
￼￼￼
Seleccionar todos os elementos que têm o atributo língua preenchido com o valor ’pt’
:
1
A linguagem possui todos os operadores relacionais habituais, cuja utilização não foi aqui exemplificada, porém, a sua semântica é bem conhecida e este enunciado já tem um grau de complexidade elevado. Fica ao critério dos grupos de trabalho a sua implementação.