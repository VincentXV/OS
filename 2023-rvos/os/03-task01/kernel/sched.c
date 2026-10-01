#include "os.h"

/* defined in entry.S */
extern void switch_to(struct context *next);
extern taskCB_t TCBRdy;
extern taskCB_t * TCBRunning; 

void sched_init()
{
	w_mscratch(0);
}

static taskCB_t * _getNextTask() {     
	//get next task ctx_t in readyQueue
	taskCB_t *nextTask= (taskCB_t*)TCBRdy.node.next;
	list_remove((list_t*)nextTask);
    return nextTask;
}

static void _toRdyQ(taskCB_t *currentTask) {
	currentTask->state = TASK_READY;
	list_insert_before((list_t*)&TCBRdy, (list_t*)currentTask);    
}

void schedule()
{
	taskCB_t *nextTask= _getNextTask();
	ctx_t *next = &nextTask->ctx;
	//current task into ready queue
	if (TCBRunning != NULL)//kernel
    	_toRdyQ(TCBRunning);
	
	TCBRunning = nextTask;
	nextTask->state = TASK_RUNNING;
	switch_to(next);
}

