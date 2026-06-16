/*****     Explanation when pointers should be used in C ****
*
*   http://c.learncodethehardway.org/book/ex15.html
*
*   - Ask the OS for a chunk of memory and use a pointer to work with it.
*    This includes strings and structs.
*
*   - Passing large blocks of memory (like large structs) to functions with
*   a pointer so you don't have to pass the  whole thing to them.
*
*   - Taking the address of a function so you can use it as a dynamic callback.
*
*   - Complex scanning of chunks of memory such as converting bytes off
*    a network socket into data structures or parsing files.
*
*/

