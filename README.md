# Ribbon, a lightweight POSIX thread wrapper which tries to look like Java threads

I got bored one day and decided to make my life easier by writing a pthread wrapper. It's really simple to use. 


There's the ```Runnable``` interface, which forces any inheriting object to implement a run() method; and then there's the Thread -- a Thread object acts like an OOP thread and can "run" any Runnable object like so:

```
Thread thread;
Runnable thing;

thread.start(thing);
thread.join();
```

And the thread will run whatever your Runnable object tells it to run under the overloaded run() method.

However, the Thread class also implements Runnable. This means that the following code is valid and will work:

```
class Whatever : public Thread {
public:
    ...
    
    void run() {
    //  maybe call the init functions?
    //  maybe load and check all required resources?
    //  literally whatever.
    
        std::cout << "Hey there!" << std::endl;
    }
}

Whatever obj;
obj.start();
obj.join();
```

Guess what the output of that program will be!
