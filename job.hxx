/**
 ** \file scheduler/job.hxx
 ** \brief Inline implementation of scheduler::Job.
 */

#ifndef SCHEDULER_JOB_HXX
# define SCHEDULER_JOB_HXX

# include <cassert>
# include "scheduler/scheduler.hh"
# include "scheduler/libcoroutine/Coro.h"

namespace scheduler
{

  inline
  Job::Job (Scheduler& scheduler, const libport::Symbol& name)
    : scheduler_ (&scheduler),
      name_ (name == SYMBOL () ? libport::Symbol::fresh (SYMBOL (job)) : name),
      terminated_ (false),
      self_ (Coro_new ()),
      side_effect_free_ (false),
      pending_exception_ (0)
  {
  }

  inline
  Job::Job (const Job& model, const libport::Symbol& name)
    : scheduler_ (model.scheduler_),
      name_ (name == SYMBOL () ? libport::Symbol::fresh (model.name_get ()) : name),
      terminated_ (false),
      self_ (Coro_new ()),
      side_effect_free_ (false),
      pending_exception_ (0)
  {
  }

  inline
  Job::~Job ()
  {
    scheduler_->unschedule_job (this);
    pending_exception_ = 0;
    Coro_free (self_);
  }

  inline Scheduler&
  Job::scheduler_get () const
  {
    return *scheduler_;
  }

  inline void
  Job::terminate ()
  {
  }

  inline bool
  Job::terminated () const
  {
    return terminated_;
  }

  inline void
  Job::yield ()
  {
    scheduler_->resume_scheduler (this);
  }

  inline void
  Job::yield_front ()
  {
    scheduler_->resume_scheduler_front (this);
  }

  inline void
  Job::yield_until (libport::utime_t deadline)
  {
    scheduler_->resume_scheduler_until (this, deadline);
  }

  inline Coro*
  Job::coro_get () const
  {
    assert (self_);
    return self_;
  }

  inline void
  Job::start_job ()
  {
    scheduler_->add_job (this);
  }

  inline void
  Job::side_effect_free_set (bool s)
  {
    side_effect_free_ = s;
  }

  inline bool
  Job::side_effect_free_get () const
  {
    return side_effect_free_;
  }

  inline void
  Job::async_throw (boost::exception_ptr e)
  {
    pending_exception_ = e;
  }

  inline void
  Job::check_for_pending_exception ()
  {
    if (pending_exception_)
    {
      boost::exception_ptr to_throw;
      std::swap (to_throw, pending_exception_);
      boost::rethrow_exception (to_throw);
    }
  }

  inline void
  Job::link (Job* other)
  {
    links_.push_back (other);
    other->links_.push_back (this);
  }

  inline void
  Job::unlink (Job* other)
  {
    links_.remove (other);
    other->links_.remove (this);
  }

  inline const libport::Symbol&
  Job::name_get () const
  {
    return name_;
  }

} // namespace scheduler

#endif // !SCHEDULER_JOB_HXX
