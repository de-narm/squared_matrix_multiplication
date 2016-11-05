#Java Version

This is the Java version of the project. 

##Compile

First open the /src folder. There should be 3 file Matrix.java, MatrixColumnMultiply.java and manifest.
Type:
```
javac Matrix.java MatrixColumnMultiply.java
```
Now you should have 2 .class files Matrix.class and MatrixColumnMultiply.class.
Type:
```
jar cfm Matrix.jar manifest Matrix.class and MatrixColumnMultiply.class
```
If everything went right you should have now a .jar file named Matrix.jar

##Usage

Run file with menu
```
java -jar ./Matrix.jar
```
or
```
java Matrix
```

Run benchmark from console
```
java -jar ./Matrix.jar -b [--t <maximum number of threads>] [--min <minumum number of rows/columns>][--max <maximum number of rows/columns>]
```
or
```
java Matrix -b [--t <maximum number of threads>] [--min <minumum number of rows/columns>][--max <maximum number of rows/columns>]
```

Arguments in [] are optional.

##
