# Projeto Carrinho da disciplina de microcontroladores I

Foram feitas funções para controle PWM, que através de uma ponte-H aciona os motores do lado esquerdo ou direito, para frente ou para trás, de forma individual (de cada lado) e também faz o controle da velocidade.

Para seguir as linhas foi criada uma função que tendo a resposta de dois sensores infravermelhos faz o controle para manter o carrinho sobre a fita isolante.

Para se conectar ao celular foi utilizado um módulo bluetooth e feita a comunicação através da usart.

Existe também a proteção de um sensor ultrassônico que faz a medição com obstáculos a frente, parando, ou durante alguns testes, fazendo o carrinho voltar.
