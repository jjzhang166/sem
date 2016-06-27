 #include "comm.h"

//int main()
//{
//	int sem_id=creat_sem_set(1);
//	pid_t id=fork();
//	if(id<0)
//	{
//		perror("fork");
//		return -1;
//	}
//	else if (id==0)
//	{
//		while(1)
//		{
//			printf("A");
//			sleep(1);
//			fflush(stdout);
//			printf("A");
//			sleep(3);
//			fflush(stdout);
//		}
//	}
//	else
//	{
//		while(1)
//		{
//			printf("B");
//			sleep(1);
//			fflush(stdout);
//			printf("B");
//			sleep(2);
//			fflush(stdout);
//		}
//		waitpid(id,NULL,0);
//	}
//
//	destroy_sem_set(sem_id);
//
//	return 0;
//}
int main()
{
	int sem_id=creat_sem_set(1);
	init_sem_set(sem_id,0,1);
	pid_t id=fork();
	if(id <0)
	{
		perror("fork");
		exit(1);
	}
	else if(id==0)
	{
		int childid=getpid();
		int fatherid=getppid();
		printf("childid:%d,fatherid:%d\n",childid,fatherid);
		int sem_id=get_sem_set(0);//由于我们前面已经创建了一个信号量集，我们这里只需获取就行了，所以把参数设置为0
		while(1)
		{
		    p_sem(sem_id,0);
			printf("child wrinting\n");
			sleep(1);
			fflush(stdout);
			printf("child finish post\n");
			sleep(10);
			fflush(stdout);
		    v_sem(sem_id,0);
		}
	}
	else
	{
		while(1)
		{
			p_sem(sem_id,0);
			printf("father wrinting\n");
			sleep(1);
			fflush(stdout);
			printf("father finish post\n");
			sleep(1);
			fflush(stdout);
			v_sem(sem_id,0);
		}

	}

	destroy_sem_set(sem_id);
	return 0;
}
