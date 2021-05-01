# Elidian Alencar -- Compiladores -- Flex-Bison -- Codigo Calc
Esta linguagem está sendo desenvolvida na disciplina de compiladores.

### Marcadores de início e fim do programa
```
in
    # código 
    # ...
ni
```

### Comentários
#para comentar uma linha, adicione # no inicio do comentário

### Tipos e Declarações de variaveis
real: aceita um número
```
real val, val2 = 10.0
real val_3 = val2
real val-4
```
texto: aceita um texto/string
```
texto name = "nome", name2
texto my1name = &name
```
obs:
1. Para acessar valor de variavel tipo TEXTO deve-se utilizar o modificador &.
2. O nome das variaveis devem iniciar sempre com uma letra e depois podem conter letra, numero, underline (_) e/ou hífen (-).
3. A declaração de um mesmo tipo pode ser em linha separados por vírgula (,).

### Atribuição de valores
a = 5
b = 10
soma = a * b

### Operação de escrita
Para escrita em tela utiliza-se o comando >>
```
>> "Hello Word!"
>> a
>> 5.0
>> a + b
>> &name
```
A escrita pode ser em uma mesma linha separados por vírgula (,)
```
>> "Hello Word!", a, 5.0 , a + b, &name
```

### Operação de leitura
Para receber informação da tela utiliza-se o comando <<
```
real idade
>> "Digite sua idade: "
idade <<
```

### Operações matemáticas
```
>> "Soma: ", 5.0 + 10 
>> "Subtração: ", 5.0 - 10
>> "Multiplicação: ", 5.0 * 10
>> "Divisão: ", 5.0 / 10
>> "Resto de divisão: ", 5 % 2
>> "Exponenciação: ", 5.0 ^ 10
>> "Radiciação: ", raiz(4)
>> "Seno: ", sin(5)
>> "Cosseno: ", cos(5)
>> "Módulo: ", |-15|
```

### Expressões matemáticas e precedência
#### Ordem de precedência
1. Parênteses
2. Exponenciação
3. Multiplicação e divisão tem mesmo grau de precedência
4. Soma e subtração tem mesmo grau de precedência

Em uma equação simples:
```
>> a / b + a * b - 1
```
A precedencia é feita como segue abaixo:
```
>> (((a / b) + (a * b)) - 1)
```
Passo a passo:
```
>> (a/b) # divisao
>> (a*b) # produto
>> (a/b + a*b) # soma
>> ((a/b + a*b) - 1) # subtração
```

### Exemplo
```
in

  real b, h, area

  >> "Calculo da area do retangulo"
  >> "" # pular linha

  >> "Digite a base: "
  b <<

  >> "Digite a altura: "
  h <<

  >> ""
  area = h * b
  >> "A area do retangulo eh: ", area

ni
```
