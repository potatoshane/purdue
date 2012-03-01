/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

/************************************************************************/
/*																		*/
/* main - main program for testing Xinu									*/
/*																		*/
/************************************************************************/

void producer(pipid32 pip)
{
	int i;
	for (i = 0; i < 10; i++)
	{
		pipwrite(pip, "matt is cool", 12);
	}
}

void consumer(pipid32 pip)
{
	int i;
	for (i = 0; i < 10; i++)
	{
		char *buf;
		pipwrite(pip, buf, 12);

		kprintf(buf);
    	kprintf("\r\n");
	}
}

int main(int argc, char **argv)
{
	pipid32 pip = pipcreate();

    pid32 prpid = create(producer, 500, 20, "producer", 1, pip);
    pid32 copid = create(consumer, 500, 20, "consumer", 1, pip);

    pipconnect(pip, prpid, copid);

    resume(prpid);
	resume(copid);

	pipdisconnect(pip);
	pipdelete(pip);
    
    return OK;
}
