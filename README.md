# get_next_line
With the function get_next_line you can read a file line by line.
The difficulties of the project:
* First you are not allowed to use any predefined functions but read, malloc and free.
* You should always read `BUFFERSIZE` chars. `BUFFERSIZE` is a value the user can choose. The function has to work with any `BUFFERSIZE` larger than 0.
  * This creates the problem that you often read more characters then you need. So you have to save the rest and use it in the next call of your function.
* You are not allowed to simply read the whole file, but piecewise using the `BUFFERSIZE`.
* The function `read` doesn't stop reading at `EOF` (End of File), instead it always reads the fixed chunk of `BUFFERSIZE` chars.
<br/>

### Bonus: <br/>
The following bonus requirements are fullfilled:
* You are only allowed to use one static variable for the implementation.
* The function has to work with multiple file descriptors.
