# get_next_line
With the function get_next_line you can read in a file line by line. One of the difficulties is that you are only not allowed to use any predefined functions but read, malloc and free.
The difficulties and traps of the project:

* You should always read Buffersize signs. Buffersize is a value the executor can choose. The function has to work with any Buffersize except from 0.
  * This creates the Problem that you often read more characters then you need. So you have to save the rest and use it at the next call of your function.
* You are not allowed to simply read the whole file, but as less as possible with considering the Buffersize.
* the function read doesn't stop reading at EOF (End of File), instead it continues reading the last Buffersize chars.
<br/>

### Bonus: <br/>
There are 2 Bonus tasks:
* You are only allowed to use one static variable.
* The function has to work with multiple file descriptors.
