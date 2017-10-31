Keno Game
=====================================================================================

Versão 1.0.0 - Domingo, 3 de abril de 2016

Autor: Thiago César M. D. de Lucena


Introdução
--------------------------------------------------------------------------------------

Keno Game é um jogo de apostas estilo loteria no qual o jogador seleciona certa
quantia de dinheiro e escolhe até 15 números entre 1 e 80 para compor sua aposta. 
Então, são sorteados 20 números no mesmo intervalo e compara-se os números sorteados 
com os números escolhidos pelo jogador. Por fim, o jogador recebe um retorno em 
dinheiro de acordo com a quantidade de números acertados.

O Keno Game geralmente é jogado em cassinos. As regras a respeito da quantidade 
mínima de números que o jogador pode escolher e os valores de pagamento variam de 
acordo com cada estabelecimento.


Instalação
--------------------------------------------------------------------------------------

Para executar o programa deve-se descompactar o arquivo "Projeto_Keno_Game.
zip", navegar até a pasta extraída através do terminal (a pasta contêm 
as pastas "bin", "data", "include" e "src") e compilar o programa 
através do seguinte comando:

	g++ -std=c++11 -I include/ src/drive.cpp src/keno_functions.cpp -o bin/output 

Logo após, basta executar o jogo usando o seguinte comando:
	
	bin/output data/*nome_do_arquivo.dat*

É importante que *nome_do_arquivo.dat* seja substituido pelo nome do
arquivo de aposta no tipo ".dat", ".txt" ou similar presente na pasta 'data'.


Observações
--------------------------------------------------------------------------------------

O jogador deve preparar o arquivo de aposta com a seguinte estrutura: a primeira
linha deve indicar a quantidade de dinheiro que deseja-se apostar; a segunda linha
deve indicar quantas rodadas serão jogadas, de forma que o valor da aposta será 
dividido pelo número de rodadas; e a terceira linha deve conter os números escolhidos
pelo jogador, sendo 1 a quantidade mínima e 15 a quantidade máxima.

As taxas de pagamento seguem as regras da tabela que pode ser acessada através do 
arquivo "projeto_keno.pdf", contido na pasta principal do projeto.

Todo código implementado está em inglês e com comentários em inglês.


Bugs e limitações
--------------------------------------------------------------------------------------

É imprescindível que o arquivo de aposta siga as regras descritas acima.

Serão ignorados:

- Números na mesma linha e à direita dos valores de aposta e de número de rodadas.

- Números em conjunção com caracteres e outros símbolos.

Exemplo de uma aposta padrão:

1000
4
13 22 45 59 78

Exemplo de uma aposta válida:

asas
jshdj
dkkdkk


600 13 hgh -8

3 -10 sajsj

13 '11' aassa 32 24 24 13 32 89 100

Nesse caso, o programa considerará:
600 como aposta
3 como número de rodadas
13 24 32 como números da aposta
