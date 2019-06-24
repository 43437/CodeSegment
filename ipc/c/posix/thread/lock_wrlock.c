#include <stdio.h>
#include <pthread.h>
#include "err_handle.h"

struct job
{
    struct job* j_next;
    struct job* j_prev;
    pthread_t j_id;         /*tells which thread handles this job */
};

struct queue
{
    struct job* q_head;
    struct job* q_tail;
    pthread_rwlock_t q_lock;
};

/**
 * Initialize a queue
 */
int queue_ini(struct queue *qp)
{
    int err;
    qp->q_head = NULL;
    qp->q_tail = NULL;
    err=pthread_rwlock_init(&qp->q_lock, NULL);
    if (0 != err)
    {
        return (err);
    }
    return (0);
}

/**
 * Insert a job at the head of queue.
 */
void job_insert(struct queue* qp, struct job* jp)
{
    pthread_rwlock_wrlock(&qp->q_lock);
    jp->j_next = qp->q_head;
    jp->j_prev = NULL;
    if (NULL != qp->q_head)
    {
        qp->q_head->j_prev=jp;
    }
    else
    {
        qp->q_tail=jp;      /*list before insert is empty. */
    }
    
    qp->q_head = jp;
    pthread_rwlock_unlock(&qp->q_lock);
}

/**
 * Append a job on the tail of the queue.
 */
void job_append(struct queue* qp, struct job* jp)
{
    pthread_rwlock_wrlock(&qp->q_lock);
    jp->j_next = NULL;
    jp->j_prev = qp->q_tail;
    if (NULL != qp->q_tail)
    {
        qp->q_tail->j_next = jp;
    }
    else
    {
        qp->q_head = jp;     /*list before append is empty. */
    }
    qp->q_tail = jp;
    pthread_rwlock_unlock(&qp->q_lock);
}

/**
 * Remove the given job from a queue.
 */
void job_remove(struct queue* qp, struct job* jp)
{
    pthread_rwlock_wrlock(&qp->q_lock);
    if (jp == qp->q_head)
    {
        qp->q_head = jp->j_next;
        if (jp == qp->q_tail)
        {
            qp->q_tail = NULL;
        }
        else
        {
            jp->j_next->j_prev = jp->j_prev;
        }
    }
    else if(jp == qp->q_tail)
    {
        jp->j_prev->j_next = NULL;
        qp->q_tail = jp->j_prev;
    }
    else
    {
        jp->j_prev->j_next = jp->j_next;
        jp->j_next->j_prev = jp->j_prev;
    }
    pthread_rwlock_unlock(&qp->q_lock);
}

/**
 * Find a job for given thread ID.
 */
struct job* job_find(struct queue* qp, pthread_t id)
{
    struct job* jp;
    if (pthread_rwlock_rdlock(&qp->q_lock) != 0)
    {
        return NULL;
    }
    
    for (jp = qp->q_head; jp != NULL; jp = jp->j_next)
    {
        if (pthread_equal(jp->j_id, id))
        {
            break;
        }
    }

    pthread_rwlock_unlock(&qp->q_lock);
    return jp;
}

int main(void)
{
    int err = 0;
    struct queue q;
    err = queue_ini(&q);
    if (0!=err)
    {
        err_exit(err, "queue initial failed.\n");
    }

    struct job j1, j2, j3;
    j1.j_id=1;
    j2.j_id=2;
    job_append(&q, &j1);
    job_insert(&q, &j2);
    job_insert(&q, &j3);
    struct job* jp=job_find(&q, 2);
    if (NULL!=jp)
    {
        printf("get job %d\n", jp->j_id);
    }
    else
    {
        printf("can't get job 2.");
    }
    
    
    
    return 0;
}