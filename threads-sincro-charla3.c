/*
 * Ejemplo de Threads sin sincronización utilizado en la 3er de TP.
 *
 * Aclaración: el uso de usleep en este ejemplo es meramente una licencia poetica que nos tomamos para lograr observar
 * de forma más facil los problemas de ejecución que puede generar la no sincronización de threads. Con esto queremos
 * decir lo siguiete: Nunca intenten sincronizar cosas con usleep dado que algunas veces puede funcionar pero les aseguramos
 * que en muchos casos no. Si los comentan y ejecutan el programa, notarán que el planificador de linux seleccionará
 * siempre el thread que ejecuta la función hacerFalta hasta que termine para luego dar lugar al otro. Si bien el resultado
 * que obtenemos en cualquiera de los dos casos es el mismo, la ejecución no lo es y en ambos casos tampoco es la esperada.
 * Esto es lo que debería interesarnos y hacernos pensar en que deberíamos sincronizar los threads :)
*/
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_t tid[2];
int amarillas;

void* hacerFalta(void *arg)
{
    unsigned int i = 0;

    for(i=0; i<(150);i++){
    	usleep(150);
    	amarillas += 1;
    	printf("\nPablo Pérez recibió una amarilla. Cantidad acumulada: %d\n", amarillas);
    }

    return NULL;
}

void* sacarAmarilla(void *arg)
{
    unsigned int i = 0;

    for(i=0; i<(150);i++){
    	usleep(150);
    	amarillas -= 1;
    	printf("\nAngelici ha eliminado una amarilla de Pablo Pérez del sistema\n");
    }

    return NULL;
}

int main(void)
{
    int err;

    err = pthread_create(&(tid[0]), NULL, hacerFalta, NULL);
    if (err != 0){
    	printf("\nHubo un problema al crear el thread Pablo Pérez:[%s]", strerror(err));
    	return err;
    }
    printf("\nEl thread Pablo Pérez inició su ejecución\n");

    err = pthread_create(&(tid[1]), NULL, sacarAmarilla, NULL);
    if (err != 0){
    	printf("\nHubo un problema al crear el thread Angelici:[%s]", strerror(err));
    	return err;
    }
    printf("\nEl thread Angelici inició su ejecución\n");

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    return 0;
}
