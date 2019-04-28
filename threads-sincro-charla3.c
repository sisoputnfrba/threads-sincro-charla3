/*
 * Ejemplo de Threads con sincronización de threads mediante el uso de semáforos utilizado en la 3er de TP.
*/
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>

pthread_t tid[2];
sem_t productor;
sem_t consumidor;
int amarillas;

void* hacerFalta(void *arg)
{
    unsigned int i = 0;

    for(i=0; i<(150);i++){
    	sem_wait(&consumidor);
    	amarillas += 1;
    	printf("\nPablo Pérez recibió una amarilla. Cantidad acumulada: %d\n", amarillas);
    	sem_post(&productor);
    }

    return NULL;
}

void* sacarAmarilla(void *arg)
{
    unsigned int i = 0;

    for(i=0; i<(150);i++){
    	sem_wait(&productor);
    	amarillas -= 1;
    	printf("\nAngelici ha eliminado las amarillas de Pablo Pérez del sistema\n");
    	sem_post(&consumidor);
    }

    return NULL;
}

int main(void)
{
    int err;

    sem_init(&productor,0,0);
    sem_init(&consumidor,0,1);

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

    sem_destroy(&productor);
    sem_destroy(&consumidor);

    return 0;
}
