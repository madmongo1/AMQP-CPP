/**
 *  DeferredDelete.h
 *
 *  Deferred callback for instructions that delete or purge queues, and that
 *  want to report the number of deleted messages.
 *
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace AMQP {

/**
 *  We extend from the default deferred and add extra functionality
 */
class DeferredDelete : public Deferred
{
private:
    /**
     *  Callback to execute when the instruction is completed
     *  @var    DeleteCallback
     */
    DeleteCallback _deleteCallback;

    /**
     *  Report success for queue delete and queue purge messages
     *  @param  messagecount    Number of messages that were deleted
     *  @return Deferred        Next deferred result
     */
    virtual Deferred *reportSuccess(uint32_t messagecount) const override
    {
        // skip if no special callback was installed
        if (!_deleteCallback) return Deferred::reportSuccess();
        
        // call the callback
        _deleteCallback(messagecount);
        
        // call finalize callback
        if (_finalizeCallback) _finalizeCallback();
        
        // return next object
        return _next;
    }


    /**
     *  The channel implementation may call our
     *  private members and construct us
     */
    friend class ChannelImpl;
    friend class ConsumedMessage;
    
protected:
    /**
     *  Protected constructor that can only be called
     *  from within the channel implementation
     *
     *  @param  boolean     are we already failed?
     */
    DeferredDelete(bool failed = false) : Deferred(failed) {}

public:
    /**
     *  Register a function to be called when the queue is deleted or purged
     *
     *  Only one callback can be registered. Successive calls
     *  to this function will clear callbacks registered before.
     *
     *  @param  callback    the callback to execute
     */
    DeferredDelete &onSuccess(const DeleteCallback &callback)
    {
        // store callback
        _deleteCallback = callback;
        
        // allow chaining
        return *this;
    }

    /**
     *  Register the function that is called when the queue is deleted or purged
     *  @param  callback
     */
    DeferredDelete &onSuccess(const SuccessCallback &callback)
    {
        // call base
        Deferred::onSuccess(callback);
        
        // allow chaining
        return *this;
    }
};

/**
 *  End namespace
 */
}
