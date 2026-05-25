//Separate output statements don’t result in separate lines of output on the console.
//Output a newline whenever a line of output is complete.


/* Using std::endl is often inefficient, as it actually does two jobs: it outputs a newline
(moving the cursor to the next line of the console), and it flushes the buffer (which is slow).
If we output multiple lines of text ending with std::endl, we will get multiple flushes, 
which is slow and probably unnecessary. */

//To output a newline without flushing the output buffer, we use \n


/* In a prior section, we noted that outputting data is actually a two stage process:

    1. The data from each output request is added (to the end) of an output buffer.
    2. Later, data from (the front of) the output buffer is flushed to the output device (the console). 
    
    FIFO
*/


/* cin is also buffered in the same way as cout
Each line of input data in the input buffer is terminated by a '\n' character.
so if we input 5 the buffer stores, 5\n.
when we extract the input, it takes input and stops as it reaches the newline character
the input buffer discards any whitespace, tabs etc. */


/* Here’s what happens in a three different input cases:

    1. If the user types 5a and enter, 5a\n will be added to the buffer. 5 will be extracted,
    converted to an integer, and assigned to variable x. a\n will be left in the input buffer
    for the next extraction.

    2. If the user types ‘b’ and enter, b\n would be added to the buffer. Because b is not a valid integer,
    no characters can be extracted, so this is an extraction failure. Variable x would be set to 0, and 
    future extractions will fail until the input stream is cleared.

    3. If std::cin is not in a good state due to a prior failed extraction, nothing happens here. 
    The value of variable x is not altered. 
*/