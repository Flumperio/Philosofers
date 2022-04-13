# Philosofers

Qué debes entender para completar correctamente el proyecto:
- Uno o más filósofos se sientan en una mesa redonda ya sea comiendo, pensando, o durmiendo. Mientras comen, no piensan o duermen. Mientras piensan, ni comen ni duermen. Por supuesto, mientras duermen, no comen o piensan.
- Los filósofos se sientan en una mesa redonda con un gran bol de espaguetis en el centro.
- Hay algunos tenedores en la mesa. Servir y comer espaguetis con un solo tenedor puede llegar a ser complejo, así que los filósofos comerán con dos tenedores. Uno en cada mano.
 -Cada vez que un filósofo termine de comer, dejará los tenedores y empezará a dormir. Cuando terminen de dormir, empezarán a pensar. La simulación terminará tras la muerte de un filósofo.
- Todos los filósofos necesitan comer y nunca deben morirse de hambre.
- Los filósofos no se comunican entre ellos.
- Los filósofos no saben cuándo otro filósofo va a morir.
 -No debería hacer falta decir que todos deben evitar morir.

Debes escribir este programa para la parte obligatoria y otro para la parte bonus pero ambos seguirán el mismo conjunto de reglas básicas:
- Las variables globales están prohibidas.
- El programa debe aceptar los siguientes argumentos:
- number_of_philosophers: es el número de filósofos, pero también el número de tenedores.
- time_to_die:enmilisegundos,siunfilósofonoempiezaacomer“time_to_die” milisegundos después de su última comida (o el principio de la simulación), muere.
- time_to_eat: en milisegundos, es el tiempo que tiene un filósofo para comer. Durante ese tiempo tendrá ambos tenedores ocupados.
- time_to_sleep: en milisegundos, es el tiempo que el filósofo utilizará para dormir.
- number_of_times_each_philosopher_must_eat: el argumento es opcional, si
todos los filósofos comen al menos “number_of_times_each_philosopher_must_eat” la simulación se detendrá. Si no se especifica, la simulación se detendrá con la muerte de un filósofo.
- Cada filósofo tendrá asignado un número del 1 al “number_of_philosophers”.
- El filósofo número 1 se sienta al lado del filósofo “number_of_philosophers”. Todos
los filósofos (N) se sientan entre otros dos filósofos (N - 1 y N + 1).

Sobre los logs de tu programa:
- Cualquier cambio de estado de un filósofo debe escribirse de la siguiente manera (cambia X por el número del filósofo y timestamp_in_ms por la marca temporal en milisegundos):
- timestamp_in_ms X has taken a fork ◦ timestamp_in_ms X is eating
- timestamp_in_ms X is sleeping
- timestamp_in_ms X is thinking
- timestamp_in_ms X died
- El estado impreso no debe estar roto o alterado por el estado de otros filósofos.
- No puedes tener más de 10ms entre la muerte de un filósofo y el momento en el que imprime su muerte.
- De nuevo, los filósofos deben evitar morir.
