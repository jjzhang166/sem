#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>


#define _PATH_ "."
#define _PROJ_ID_ 0x6666

union semun
{
	int val;    /* Value for SETVAL */
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;  /* Array for GETALL, SETALL */
	struct seminfo  *__buf;  /* Buffer for IPC_INFO*/
};

int creat_sem_set(int _sem_nums);
int get_sem_set(int _sem_nums);
int init_sem_set(int _sem_id,int _sem_nums,int _init_val);
int p_sem(int _sem_id,int _seq_num);
int v_sem(int _sem_id,int _seq_num);
int destroy_sem_set(int _sem_id);
