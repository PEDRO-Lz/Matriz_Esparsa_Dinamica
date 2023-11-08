# Matriz_Esparsa_Dinamica
Uma maneira eficiente de representar estruturas com tamanho variável e/ou desconhecido é através de
alocação encadeada, utilizando listas. Vamos usar esta representação para armazenar as matrizes esparsas.
Cada coluna da matriz será representada por uma lista linear circular com uma célula cabeça. Da mesma
maneira, cada linha da matriz também será representada por uma lista linear circular com uma célula cabeça.

O campo abaixo deve ser usado para apontar o próximo elemento diferente de zero na mesma coluna. O
campo direita deve ser usado para apontar o próximo elemento diferente de zero na mesma linha. Dada
uma matriz A, para um valor A(i,j) diferente de zero, deverá haver uma célula com o campo valor contendo
A(i,j), o campo linha contendo i e o campo Coluna contendo j. Esta célula deverá pertencer à lista circular
da linha i e também deverá pertencer à lista circular da coluna j. Ou seja, cada célula pertencerá a duas listas
ao mesmo tempo. 
