# Arquimedes

Trata-se de um protótipo que se baseia na cooperação entre dois controladores Arduíno dividindo tarefas. Os dois arduínos se comunicam através da biblioteca Softwareserial.

Arduíno 1:

Lida com os sensores de linha, sensores de cor verde, do botão para obstáculos e controle da ponte-H.

Arduíno 2:

Lida com o giroscopio, com os sensores de distância (ultrassônicos) e com o controle dos servos da pá para recolhimento de vítimas.


# Estágio atual

Atualmente o protótipo já é totalmente capaz de seguir linha, inclusive em curvas com ângulos bem fechados, supera gaps na linha com facilidade, faz isso com muita precisão e confiabilidade. Também é capaz de desviar de obstáculos usando o botão em sua dianteira para detectá-lo e o giroscopio para ajustar o ângulo das curvas e andar reto mesmo sem linha.


# O que precisa ser implementado/melhorado:

Comunicação serial partindo do Arduíno 1 para o Arduíno 2, atualmente é feito atráves do pino 12 (HIGH/LOW).

Melhorar a documentação e a organização do código principal.

Implementação de funções para reconhecimento dos indicativos de trajetoria (quadrado verde). Inclusive com rotinas de "certeza".

Implementação do hardware da garra para coleta de "vitimas"

Implementação do software da sala de resgate.

Melhoras no hardware para superar redutores de velocidade.

Melhoras no hardware para subir bem a rampa, podendo ser implementado código para aumento de torque dos motores em determinada inclinação usando o giroscopio.
