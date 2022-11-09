//Regla CON31-C. Do not destroy a mutex while it is locked

//Primero error
//El error de este código es que se destruye el mutex mientras está bloqueado. Esto puede causar un error de segmentación. Para evitar esto, se debe desbloquear el mutex antes de destruirlo.
//Esto pasa porque en la llamada de do_work solo se destruye el mutex cuando es el ultimo hilo, pero puede haber algun otro hilo que lo haya estado usando en medio de una ejecucion, con lo cual va a ser destruido cuando todavia sigue bloqueado.


#include <stdatomic.h>
#include <stddef.h>
#include <threads.h>
  
mtx_t lock;
/* Atomic so multiple threads can modify safely */
atomic_int completed = ATOMIC_VAR_INIT(0);
enum { max_threads = 5 };
 
int do_work(void *arg) {
  int *i = (int *)arg;
 
  if (*i == 0) { /* Creation thread */
    if (thrd_success != mtx_init(&lock, mtx_plain)) {
      /* Handle error */
    }
    atomic_store(&completed, 1);
  } else if (*i < max_threads - 1) { /* Worker thread */
    if (thrd_success != mtx_lock(&lock)) {
      /* Handle error */
    }
    /* Access data protected by the lock */
    atomic_fetch_add(&completed, 1);
    if (thrd_success != mtx_unlock(&lock)) {
      /* Handle error */
    }
  } else { /* Destruction thread */
    mtx_destroy(&lock);
  }
  return 0;
}
  
int main(void) {
  thrd_t threads[max_threads];
   
  for (size_t i = 0; i < max_threads; i++) {
    if (thrd_success != thrd_create(&threads[i], do_work, &i)) {
      /* Handle error */
    }
  }
  for (size_t i = 0; i < max_threads; i++) {
    if (thrd_success != thrd_join(threads[i], 0)) {
      /* Handle error */
    }
  }
  return 0;
}


//Segundo bueno
//Este si seria correcto, ya que crea el mutex en el main, y lo destruye tambien en el main, solo va a ser destruido cuando vaya a terminar el main, con lo cual todos los hilos habran finalizado y estara el mutex desbloqueado en cualquier caso.

#include <stdatomic.h>
#include <stddef.h>
#include <threads.h>
  
mtx_t lock;
/* Atomic so multiple threads can increment safely */
atomic_int completed = ATOMIC_VAR_INIT(0);
enum { max_threads = 5 };
 
int do_work(void *dummy) {
  if (thrd_success != mtx_lock(&lock)) {
    /* Handle error */
  }
  /* Access data protected by the lock */
  atomic_fetch_add(&completed, 1);
  if (thrd_success != mtx_unlock(&lock)) {
    /* Handle error */
  }
 
  return 0;
}
 
int main(void) {
  thrd_t threads[max_threads];
   
  if (thrd_success != mtx_init(&lock, mtx_plain)) {
    /* Handle error */
  }
  for (size_t i = 0; i < max_threads; i++) {
    if (thrd_success != thrd_create(&threads[i], do_work, NULL)) {
      /* Handle error */
    }
  }
  for (size_t i = 0; i < max_threads; i++) {
    if (thrd_success != thrd_join(threads[i], 0)) {
      /* Handle error */
    }
  }
 
  mtx_destroy(&lock);
  return 0;
}