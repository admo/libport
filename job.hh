/**
 ** \file scheduler/job.hh
 ** \brief Definition of scheduler::Job.
 */

#ifndef SCHEDULER_JOB_HH
# define SCHEDULER_JOB_HH

# include <libport/ufloat.hh>

# include "scheduler/fwd.hh"
# include "scheduler/libcoroutine/Coro.h"

namespace scheduler
{

  class Job
  {
  public:
    Job (const Job&);
    explicit Job (Scheduler& scheduler);
    virtual ~Job ();

    Scheduler& scheduler_get () const;

    /// Get the underlying coroutine corresponding to this job.
    Coro* coro_get () const;

    /// Has this job terminated?
    bool terminated () const;

    /// Run the job -- called from the scheduler.
    void run ();

    /// Kill the job -- called from the scheduler.
    void terminate_now ();

    /// Register this Job on its Scheduler so that it is rescheduled next
    /// cycle. This should be called from the currently scheduled job
    /// only but must be kept visible to be callable from the primitives.
    void yield ();

    /// Ditto, but put the job at the front of the execution queue.
    void yield_front ();

    /// Ditto, but ask not to be woken up before the deadline.
    void yield_until (libport::ufloat deadline);

    /// Wait for another job to terminate before resuming execution of
    /// the current one. If the other job has already terminated, the
    /// caller will continue its execution.
    void yield_until_terminated (Job&);

  protected:

    /// Must be implemented to do something useful. If an exception is
    /// raised, it will be lost.
    virtual void work () = 0;

    /// Will be called if the job is killed prematurely or arrives at
    /// its end. It is neither necessary nor advised to call yield
    /// from this function. Any exception raised here will be lost.
    void terminate ();

  private:
    /// Scheduler in charge of this job.  Do not delete.
    Scheduler* scheduler_;

    /// Has the coroutine terminated? Set by run ().
    bool terminated_;

    /// Other jobs to wake up when we terminate.
    jobs to_wake_up_;

    /// Coro structure corresponding to this job
    Coro* self_;
  };

} // namespace scheduler

# include "scheduler/job.hxx"

#endif // !SCHEDULER_JOB_HH
