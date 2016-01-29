Exception Agent.

Tells you about every single exception thrown, caught or not, in your code.


Building

gcc -shared -fPIC main.cpp -o libagent.so -I /Library/Java/JavaVirtualMachines/jdk1.7.0_55.jdk/Contents/Home/include/ -I /Library/Java/JavaVirtualMachines/jdk1.7.0_55.jdk/Contents/Home/include/darwin/


Running

Compile sample Main
javac Main.java


java -agentpath:libagent.so Main

...

I'm a nasty method, and I will throw an exception. NOW!
Exception: Ljava/lang/Throwable;
java.lang.Throwable
at Main.doIt(Main.java:13)
at Main.main(Main.java:4)
Yum! that was a tasty exception I just swallowed

