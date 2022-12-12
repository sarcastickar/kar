// #include <semaphore.h>
// #include <stdio.h>
// #include <pthread.h>
// #include <bits/stdc++.h>
// using namespace std;

// void *reader(void *);
// void *writer(void *);
// sem_t x, y, z, wsem, rsem;
// int readcount = 0;
// int writecount = 0;

// main()
// {
//     int a = 1, b = 1;
//     system("clear");
//     sem_init(&wsem, 0, 1);
//     sem_init(&x, 0, 1);
//     sem_init(&rsem, 0, 1);
//     sem_init(&y, 0, 1);
//     sem_init(&z, 0, 1);

//     pthread_t r, w, r1, w1, r2, r3, w2, w3;
//     pthread_create(&r, NULL, reader, (void *)a);
//     a++;
//     pthread_create(&r1, NULL, reader, (void *)a);
//     a++;
//     pthread_create(&w, NULL, writer, (void *)b);
//     b++;
//     pthread_create(&w1, NULL, writer, (void *)b);
//     b++;
//     pthread_create(&r2, NULL, reader, (void *)a);
//     a++;
//     pthread_create(&w2, NULL, writer, (void *)b);
//     b++;
//     pthread_create(&r3, NULL, reader, (void *)a);
//     a++;
//     pthread_create(&w3, NULL, writer, (void *)b);
//     pthread_join(r, NULL);
//     pthread_join(r1, NULL);
//     pthread_join(w, NULL);
//     pthread_join(w1, NULL);
//     pthread_join(r2, NULL);
//     pthread_join(w2, NULL);
//     pthread_join(r3, NULL);
//     pthread_join(w3, NULL);
//     printf("main terminated\n");
// }

// void *reader(void *arg)
// {
//     int c = (int)arg;
//     printf("\nreader %d is created", c);
//     // sleep(1);
//     sem_wait(&rsem);
//     sem_wait(&x);
//     readcount++;
//     if (readcount == 1)
//         sem_wait(&wsem);
//     sem_post(&x);
//     sem_post(&rsem);
//     // sleep(1);

//     /*Critcal Section */

//     printf("\n\nreader %d is reading\n ", c);
//     // sleep(1);
//     printf("\nreader%d finished reading\n", c);

//     /* critical section completd */
//     sem_wait(&x);
//     readcount--;
//     if (readcount == 0)
//         sem_post(&wsem);
//     sem_post(&x);
// }

// void *writer(void *arg)
// {
//     int c = (int)arg;
//     printf("\nwriter %d is created", c);
//     // sleep(1);
//     sem_wait(&y);
//     writecount++;
//     if (writecount == 0)
//         sem_wait(&rsem);
//     sem_post(&y);
//     sem_wait(&wsem);
//     printf("\nwriter %d is writing\n", c);
//     // sleep(1);
//     printf("\nwriter%d finished writing\n", c);
//     sem_post(&wsem);
//     sem_wait(&y);
//     writecount--;
//     if (writecount == 0)
//         sem_post(&rsem);
//     sem_post(&y);
// }

// Reader-Writer problem using monitors

#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

class monitor {
private:
	// no. of readers
	int rcnt;

	// no. of writers
	int wcnt;

	// no. of readers waiting
	int waitr;

	// no. of writers waiting
	int waitw;

	// condition variable to check whether reader can read
	pthread_cond_t canread;

	// condition variable to check whether writer can write
	pthread_cond_t canwrite;

	// mutex for synchronization
	pthread_mutex_t condlock;

public:
	monitor()
	{
		rcnt = 0;
		wcnt = 0;
		waitr = 0;
		waitw = 0;

		pthread_cond_init(&canread, NULL);
		pthread_cond_init(&canwrite, NULL);
		pthread_mutex_init(&condlock, NULL);
	}

	// mutex provide synchronization so that no other thread
	// can change the value of data
	void beginread(int i)
	{
		pthread_mutex_lock(&condlock);

		// if there are active or waiting writers
		if (wcnt == 1 || waitw > 0) {
			// incrementing waiting readers
			waitr++;

			// reader suspended
			pthread_cond_wait(&canread, &condlock);
			waitr--;
		}

		// else reader reads the resource
		rcnt++;
		cout << "reader " << i << " is reading\n";
		pthread_mutex_unlock(&condlock);
		pthread_cond_broadcast(&canread);
	}

	void endread(int i)
	{

		// if there are no readers left then writer enters monitor
		pthread_mutex_lock(&condlock);

		if (--rcnt == 0)
			pthread_cond_signal(&canwrite);

		pthread_mutex_unlock(&condlock);
	}

	void beginwrite(int i)
	{
		pthread_mutex_lock(&condlock);

		// a writer can enter when there are no active
		// or waiting readers or other writer
		if (wcnt == 1 || rcnt > 0) {
			++waitw;
			pthread_cond_wait(&canwrite, &condlock);
			--waitw;
		}
		wcnt = 1;
		cout << "writer " << i << " is writing\n";
		pthread_mutex_unlock(&condlock);
	}

	void endwrite(int i)
	{
		pthread_mutex_lock(&condlock);
		wcnt = 0;

		// if any readers are waiting, threads are unblocked
		if (waitr > 0)
			pthread_cond_signal(&canread);
		else
			pthread_cond_signal(&canwrite);
		pthread_mutex_unlock(&condlock);
	}

}

// global object of monitor class
M;

void* reader(void* id)
{
	int c = 0;
	int i = *(int*)id;

	// each reader attempts to read 5 times
	while (c < 5) {
		usleep(1);
		M.beginread(i);
		M.endread(i);
		c++;
	}
}

void* writer(void* id)
{
	int c = 0;
	int i = *(int*)id;

	// each writer attempts to write 5 times
	while (c < 5) {
		usleep(1);
		M.beginwrite(i);
		M.endwrite(i);
		c++;
	}
}

int main()
{
	pthread_t r[5], w[5];
	int id[5];
	for (int i = 0; i < 5; i++) {
		id[i] = i;

		// creating threads which execute reader function
		pthread_create(&r[i], NULL, &reader, &id[i]);

		// creating threads which execute writer function
		pthread_create(&w[i], NULL, &writer, &id[i]);
	}

	for (int i = 0; i < 5; i++) {
		pthread_join(r[i], NULL);
	}
	for (int i = 0; i < 5; i++) {
		pthread_join(w[i], NULL);
	}
}

