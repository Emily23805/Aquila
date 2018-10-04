#include <core/system.h>
#include <core/arch.h>
#include <sys/proc.h>
#include <sys/sched.h>
#include <ds/queue.h>

#define DEBUG_SLEEP_QUEUE

int thread_new(proc_t *proc, thread_t **ref)
{
    thread_t *thread = kmalloc(sizeof(thread_t));
    memset(thread, 0, sizeof(thread_t));

    thread->owner = proc;
    proc->threads_nr++;
    thread->tid = proc->threads_nr;

    enqueue(&proc->threads, thread);

    if (ref)
        *ref = thread;

    return 0;
}

int thread_kill(thread_t *thread)
{
    /* Free resources */
    arch_thread_kill(thread);
    thread->state = ZOMBIE;
    return 0;
}

int thread_queue_sleep(queue_t *queue)
{
#ifdef DEBUG_SLEEP_QUEUE
    printk("[%d:%d] %s: Sleeping on queue %p\n", cur_thread->owner->pid, cur_thread->tid, cur_thread->owner->name, queue);
#endif

    struct queue_node *sleep_node = enqueue(queue, cur_thread);

    cur_thread->sleep_queue = queue;
    cur_thread->sleep_node  = sleep_node;
    cur_thread->state = ISLEEP;
    arch_sleep();

    /* Woke up */
    if (cur_thread->state != ISLEEP) {
        /* A signal interrupted the sleep */
#ifdef DEBUG_SLEEP_QUEUE
        printk("[%d:%d] %s: Sleeping was interrupted by a signal\n", cur_thread->owner->pid, cur_thread->tid, cur_thread->owner->name);
#endif
        return -1;
    } else {
        cur_thread->state = RUNNABLE;
        return 0;
    }
}

void thread_queue_wakeup(queue_t *queue)
{
    while (queue->count) {
        thread_t *thread = dequeue(queue);
        thread->sleep_node = NULL;
#ifdef DEBUG_SLEEP_QUEUE
        printk("[%d:%d] %s: Waking up from queue %p\n", thread->owner->pid, thread->tid, thread->owner->name, queue);
#endif
        sched_thread_ready(thread);
    }
}

int thread_create(thread_t *thread, uintptr_t stack, uintptr_t entry, uintptr_t uentry, uintptr_t arg, uintptr_t attr __unused, thread_t **new_thread)
{
    thread_t *t = NULL;
    thread_new(thread->owner, &t);

    arch_thread_create(t, stack, entry, uentry, arg);

    if (new_thread)
        *new_thread = t;

    return 0;
}
