using System;
using System.Runtime.CompilerServices;
using System.Runtime.ExceptionServices;

namespace dotnetToy;

public struct AsyncFiberMethodBuilder<T>
{
    private Fiber<T>? fiber;
    
    #region mandatory methods for async state machine builder
    
    public static AsyncFiberMethodBuilder<T> Create() => default;
    
    public Fiber<T> Task => fiber ??= new Fiber<T>();
    
    public void SetException(Exception e) => Task.TrySetException(e);
    
    public void SetResult(T result) =>  Task.TrySetResult(result);
    public void AwaitOnCompleted<TAwaiter, TStateMachine>(ref TAwaiter awaiter, ref TStateMachine stateMachine)
        where TAwaiter : INotifyCompletion
        where TStateMachine : IAsyncStateMachine
    {
        awaiter.OnCompleted(stateMachine.MoveNext);
    }
    
    public void AwaitUnsafeOnCompleted<TAwaiter, TStateMachine>(ref TAwaiter awaiter, ref TStateMachine stateMachine)
        where TAwaiter : ICriticalNotifyCompletion
        where TStateMachine : IAsyncStateMachine
    {
        awaiter.UnsafeOnCompleted(stateMachine.MoveNext);
    }
    public void Start<TStateMachine>(ref TStateMachine stateMachine) where TStateMachine : IAsyncStateMachine
    {
        Action move = stateMachine.MoveNext;
        ThreadPool.QueueUserWorkItem(_ =>
        {
            move();
        });
    }
    public void SetStateMachine(IAsyncStateMachine stateMachine)
    {
        // nothing to do
    }
    
    #endregion
}
public readonly struct FiberAwaiter<T> : INotifyCompletion
{
    private readonly Fiber<T> fiber;
    public FiberAwaiter(Fiber<T> fiber)
    {
        this.fiber = fiber;
    }
    #region mandatory awaiter methods 
    public bool IsCompleted => fiber.IsCompleted;
    public T GetResult() => fiber.Result;
    public void OnCompleted(Action continuation) => fiber.RegisterContinuation(continuation);
    #endregion
}
public enum FiberStatus
{
    Pending = 0,
    Success = 1,
    Failed  = 2
}

[AsyncMethodBuilder(typeof(AsyncFiberMethodBuilder<>))]
public sealed class Fiber<T>
{
    private FiberStatus status;
    private T result;
    private Action continuation;
    
    public Fiber(T result)
    {
        this.status = FiberStatus.Success;
        this.result = result;
    }
    public Fiber(Exception exception)
    {
        this.status = FiberStatus.Failed;
        this.Exception = exception;
    }
    public Fiber()
    {
        this.status = FiberStatus.Pending;
    }
    public T Result
    {
        get
        {
            switch (status)
            {
                case FiberStatus.Success: return result;
                case FiberStatus.Failed:
                    ExceptionDispatchInfo.Capture(Exception).Throw();
                    return default;
                default:
                    throw new InvalidOperationException("Fiber didn't complete");
            }
        }
    }
    public Exception Exception { get; private set; }
    public bool IsCompleted => status != FiberStatus.Pending;
    public FiberAwaiter<T> GetAwaiter() => new FiberAwaiter<T>(this);
    internal bool TrySetResult(T result)
    {
        if (status != FiberStatus.Pending) return false;
        else
        {
            status = FiberStatus.Success;
            this.result = result;
            this.continuation?.Invoke();
            return true;
        }
    }
    internal bool TrySetException(Exception exception)
    {
        if (status != FiberStatus.Pending) return false;
        else
        {
            status = FiberStatus.Failed;
            this.Exception = exception;
            this.continuation?.Invoke();
            return true;
        }
    }
    internal void RegisterContinuation(Action cont)
    {
        if (status == FiberStatus.Pending)
        {
            if (this.continuation is null)
            {
                this.continuation = cont;  
            }
            else
            {
                var prev = this.continuation;
                this.continuation = () =>
                {
                    prev();
                    cont();
                };
            }
        }
        else
        {
            cont();
        }
    }
}