STR_P2_Hilos
Práctica 2: Hilos

3.3 Ejercicio 3: Multiplicación booleana de matrices con hilos

3.3.1 Descripción: Se desea implementar un programa que realice la multiplicación booleana de dos matrices de enteros binarios (valores 0 o 1). En este tipo de multiplicación: • El producto de dos valores se define como la operación lógica AND (∧). • La suma se define como la operación lógica OR (∨). Formalmente, si C = A ⊗ B, cada elemento c[i][j] se calcula como: c[i][j] = (a[i][0] ∧ b[0][j]) ∨ (a[i][1] ∧ b[1][j]) ∨ ... ∨ (a[i][n-1] ∧ b[n-1][j])

3.3.2 Especificaciones:

El programa debe leer dos matrices de tamaño n × n con valores 0 o 1.
El proceso padre debe calcular la matriz resultado delegando cada elemento c[i][j] a un hilo hijo.
Cada hijo calculará el valor del elemento que se le asigne y guardará el resultado en el elemento correspondiente de la matriz resultado. (Las matrices pueden ser variables globales creadas por el padre.)
El padre debe: o Controlar cuántos hilos simultáneos se ejecutan, con un límite máximo definido (por ejemplo, 4 hijos a la vez). o El padre debe mostrar la matriz resultado por pantalla, cuando esté seguro de que todos los hilos han finalizado.
3.3.3 Preguntas adicionales

¿Qué pasa si la fila y la columna del elemento que debe calcular cada hilo son variables globales en lugar de parámetros de la función que ejecuta el hijo?
¿Sería posible pasar al hilo hijo la dirección de las matrices en lugar de utilizar variables globales?
