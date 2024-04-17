##### Reference
- [Stack Overflow](https://stackoverflow.com/questions/4269034/what-is-the-meaning-of-prepended-double-colon)

This ensures that resolution occurs from the global namespace, instead of starting at the namespace you're currently in. For instance, if you had two different classes called Configuration as such:

```c++
class Configuration; // class 1, in global namespace
namespace MyApp
{
    class Configuration; // class 2, different from class 1
    function blah()
    {
        // resolves to MyApp::Configuration, class 2
        Configuration::doStuff(...) 
        // resolves to top-level Configuration, class 1
        ::Configuration::doStuff(...)
    }
}
```

Basically, it allows you to traverse up to the global namespace since your name might get clobbered by a new definition inside another namespace, in this case MyApp.

