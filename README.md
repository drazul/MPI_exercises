##Práctica sobre MPI (Lenguaje C)

#Introducción.

Conocida una función f(x) mediante una secuencia de N pares (x<sub>i</sub>,f(x<sub>i</sub>)) , tal que x<sub>i-1</sub> < x<sub>i</sub> .

Se conoce como:

**Suma de Riemann por la izquierda.**

S<sub>izquierda</sub> = Sumatorio(i=1, i=N-1) (f(x<sub>i-1</sub>) * (x<sub>i</sub> - x <sub>i-1</sub>))

**Suma de Riemann por la derecha.**

S<sub>derecha</sub> = Sumatorio(i=1, i=N-1) (f(x<sub>i</sub>) * (x<sub>i</sub> - x <sub>i-1</sub>))

**Suma de Riemann trapezoidal.**

S<sub>trapezoidal</sub> = Sumatorio(i=1, i=N-1) ((f(x<sub>i-1</sub>) + f(x<sub>i</sub>)/2) * (x<sub>i</sub> - x <sub>i-1</sub>))

#Enunciado.

Desarrollar un programa en C con MPI que calcule de forma paralela, en un entorno con P procesadores,  los valores S<sub>izquierda</sub>, S<sub>derecha</sub> y S<sub>trapezoidal</sub> de una función definida por puntos almacenada en un fichero secuencial *data.dat* de N puntos, y muestre el tiempo que ha tardado en ejecutarse. El fichero almacena los puntos por parejas [x<sub>0</sub>,f(x<sub>0</sub>),x<sub>1</sub>,f(x<sub>1</sub>), ...., ,x<sub>N-1</sub>,f(X<sub>N-1</sub>)}. Todos los valores son de tipo double.

#Nota

Realizar la implementación mediante un proceso inicial que lee el fichero y distribuye los datos entre los demas procesos, para finalmente mostrar el resultado.

El tiempo de ejecución a calcular, será el transcurrido a partir de recibir todos los procesos sus datos.

#Entrega.

* **Documento Teoria.pdf.** En este documento se explicita los pasos necesarios para realizar el algoritmos paralelo: división, comunicaciones, agrupación y asignación. Támbien se uncluirá una breve descripción del algoritmo y su implementación.

* **Fichero fuente Riemann.c**  Este fichero deberá de compilarse **mpic -o riemann Riemann.c**  sin errores para poder ejecutar sin error el siguiente comando: **mpirun -np numero_procesadores riemann tamaño_del_problema Fichero.dat**. El resultado deberá ser:
 * Sizq = Valor
 * Sder = Valor
 * Strap = Valor
 * Tiempo máximo de ejecución = Valor segundos.
