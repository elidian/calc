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
real: aceita número real
```
real val
real val2 = 10.0
real val_3 = val2
```

inteiro: aceito número natural
```
inteiro a
inteiro b = 5
inteiro c = b
```

texto: aceita um texto/string
```
texto name
texto name2 = "nome"
texto my_name = name2
```
obs:
1. O nome das variaveis devem iniciar sempre com uma letra e depois podem conter letra, numero e/ou underline (_).
2. A declaração de um mesmo tipo pode ser em linha separados por vírgula (,).

### Atribuição de valores
a = 5
b = 10
soma = a * b
name = "nome sobrenome"

### Operação de escrita
Para escrita em tela utiliza-se o comando >>
```
inteiro a = 1
real b = 5.5
texto name = "primeiro segundo"
>> "Hello Word!"
>> a
>> 5.0
>> a + b
>> name
```
A escrita pode ser em uma mesma linha separados por vírgula (,)
```
>> "Hello Word!", a, 5.0 , a + b, name
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

### Expressões matemáticas, logicos e precedência
#### Ordem de precedência
1. Parênteses
2. Exponenciação
3. Multiplicação e divisão tem mesmo grau de precedência
4. Soma e subtração tem mesmo grau de precedência
5. Expressões lógicas

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

Exemplo de logica:
```
inteiro a = 5
>> a * 2 < 5
```
saída
```
0
```

### Extruturas de decisão IF e IF ELSE
#### If
Estrutura básica:
```
inif logica
{
  # lista de codigos caso IF POSITIVO
}
```
Exemplo simples:
```
real a = 3
inteiro b = 7
inif 2*a > b {
  >> "SIM"
}
```
Saída:
```

```
#### If Else
Estrutura:
```
inif logica
{
  # lista de codigos caso IF POSITIVO
}
infi
{
  # lista de codigos caso IF NEGATIVO
}
```
Exemplo simples:
```
inteiro a = 3
real b = 7
inif a*2 > b
{
  >> "SIM"
}
infi
{
  >> "NAO"
}
```
Saída:
```
NAO
```

### Estruturas de repetição WHILE e FOR
#### While
estrutura:
```
inwhile logica
{
  # lista de codigos caso teste WHILE POSITIVO
}
```
Exemplo simples
```
inteiro x = 0
inwhile x<=10-x
{
  >> x
  x = x + 1
}
```
Saída:
```
0
1
2
3
4
5
```
#### FOR
Estrutura:
```
infor atribuição : logica : aritmetica
{
  # lista de codigos caso teste FOR POSITIVO
}
```
Exemplo:
```
infor inteiro x = 2 : x <= 10 - x : 1
{
  >> x
}
```
Saída:
```
2
3
4
5
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
