// See https://aka.ms/new-console-template for more information
using System.Collections;
using System.ComponentModel;
using Microsoft.VisualBasic.CompilerServices;


Console.WriteLine("Hello, World!");
var c = new MyCompo(){ValueType= 0, RefType="Init"};

for (int i = 1; i< 30; i ++)
{
    Console.WriteLine($"FrameEnter {i}");
    Global.Count = i;
    c.ValueType = i * i;
    c.RefType = $"count{i} and {new string('*', i)}";
    c.Update();
    Console.WriteLine($"FrameOut {i}");
}


public static class Global{
    public static int Count;
}

public class MyCompo
{
    public int ValueType;
    public object RefType;
    private CoroutineWalker? coroutine = null;

    public void Update(){
        if(this.coroutine.IsNullOrCompleted())
        {
            Console.WriteLine($"Swap");
            this.coroutine = this.GetOneTwoThree(Global.Count).AsWalker();
        }
    
        var c = this.coroutine.Value;
        c.Update();
        CoroutineWalker.Update(ref this.coroutine.Value);
        this.coroutine = c;
    }

    private /*Must be Private*/ IEnumerable GetOneTwoThree(int count) {
        Console.WriteLine($"Entered : {count}");
        Console.WriteLine($"{this.ValueType} {this.RefType} {Global.Count}");
        yield return null;
        Console.WriteLine($"{this.ValueType} {this.RefType} {Global.Count}");
        yield return null;
        
        Console.WriteLine($"Exit : {count}");

    }

}

public struct CoroutineWalker(IEnumerator e)
{
    public bool Completed {get; private set;}
    private object lastYielded;

    public static void Update(ref CoroutineWalker w) => w.UpdateReal();
    private void UpdateReal()
    {
        if(this.Completed)
        {
            return;
        }

        switch(lastYielded)
        {
            //other case (ex: wait seconds) -> return;
            case null: break; //go
        }

        if (e.MoveNext()){
            this.lastYielded = e.Current;
        }
        else{
            this.Completed = true;
            Console.WriteLine("TrulyCompleted");
        }
    }
}

public static class CoroutineEX{
    public static CoroutineWalker AsWalker(this IEnumerable routine) => new CoroutineWalker(routine.GetEnumerator());
    public static bool IsNullOrCompleted(ref this CoroutineWalker? walker) => walker == null || walker.Value.Completed;
}