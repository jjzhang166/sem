#include "comm.h"

static int comm_creat_sem_set(int _sem_nums,int flag)
{
	key_t _key=ftok(_PATH_,_PROJ_ID_);
	if(_key<0)
	{
		perror("ftok");
		return -1;
	}
	int sem_id=semget(_key,_sem_nums,flag);
	if(sem_id<0)
	{
		return -1;
	}
	return sem_id;
}

int creat_sem_set(int _sem_nums)
{
	umask(0);
	int flag=IPC_CREAT|IPC_EXCL|0666;//创建一组新的唯一的信号量集
	return comm_creat_sem_set(_sem_nums,flag);
}

int get_sem_set(int _sem_nums)
{
	int flag=IPC_CREAT;
	return comm_creat_sem_set(_sem_nums,flag);
}

int init_sem_set(int _sem_id,int _sem_num,int _init_val)
{
	union semun _un;
	_un.val=_init_val;
	if(semctl(_sem_id,_sem_num,SETVAL,_un)<0)
	{ 
		perror("semctl");
		return -1;
	}
	return 0;
}

 int p_sem(int _sem_id,int _seq_num)
{
	struct sembuf _sem_buf[1];
	_sem_buf[0].sem_num=_seq_num;
	_sem_buf[0].sem_op=-1;
	_sem_buf[0].sem_flg=SEM_UNDO;
//	_sem_buf[0].sem_flg=0;
	if(semop(_sem_id,_sem_buf,1)<0)
	{
		perror("semop");
		return -1;
	}
	return 0;
}


 int v_sem(int _sem_id,int _seq_num)
{
	struct sembuf _sem_buf[1];
	_sem_buf[0].sem_num=_seq_num;
	_sem_buf[0].sem_op=1;
//	_sem_buf[0].sem_flg=0;
	_sem_buf[0].sem_flg=SEM_UNDO;
	if(semop(_sem_id,_sem_buf,1)<0)
	{
		perror("semop");
		return -1;
	}
	return 0;
}
//static int comm_op_sem(int _sem_id,int _seq_num,int _op)
//{
//	struct sembuf _sem_buf[1];
//	_sem_buf[0].sem_num=_seq_num;
//	_sem_buf[0].sem_op=_op;
//	_sem_buf[0].sem_flg=0;
//	if(semop(_sem_id,_sem_buf,1)<0)
//	{
//		perror("semop");
//		return -1;
//	}
//	return 0;
//}

//int p_sem(int _sem_id,int _seq_num)
//{
//	return comm_op_sem(_sem_id,_seq_num,-1);
//}
//
//int v_sem(int _sem_id,int _seq_num)
//{
//	return comm_op_sem(_sem_id,_seq_num,1);
//}
//
int destroy_sem_set(int _sem_id)
{
	if(semctl(_sem_id,0,IPC_RMID,NULL)<0)
	{
		perror("semctl");
		return -1;
	}
	return 0;
}
