# Project 1 - Mail Server 

A simple simulation of a mail server using a balanced tree and a heap priority queue

## Objective

The main goal is to implement a simulator of an email server. The simulated 
system will support account management, as well as the delivery of messages 
from one user to another. The focus of the simulation will be to verify the 
correct functioning of the system when executing the various server operations.

## Input

The input to the simulation program is a text file containing, on each line, 
one operation. The simulation should end when the end of the file is reached. 
The operations are specified below, as they are present in the input file:

- REGISTER ID | It register a new user and creates its mail box. 
The ID param is an integer 0 <= ID <= 1000 
- DELETE ID | It deletes the target account and mail box if exists.
- DELIVER ID PRI MSG | It adds a new message to the mail box of the target
account with the informed priority.
- QUERY ID | It should return the first message of the target account mail 
box if the account exists and if it's not empty.

## Output

The program should perform the especified operation 
for each line and print the correspondent messages:

- REGISTER ID
-- OK: ACCOUNT ID REGISTERED
-- ERROR: ACCOUNT ID ALREADY EXISTS

- DELETE ID
-- OK: ACCOUNT ID DELETED
-- ERROR: ACCOUNT ID DOESN'T EXIST

-  DELIVER ID PRI MSG
-- OK: MESSAGE TO ACCOUNT ID DELIVERED.
-- ERROR: ACCOUNT ID DOESN'T EXIST

- QUERY ID
-- MSG: message
-- EMPTY MAIL BOX 
-- ERROR: ACCOUNT ID DOESN'T EXIST


## Data Structures

Considering the problem format, the way to get the best performance is by choosing the 
adequate data structures in terms of complexity to store and manipulate the input data.

First, the accounts server should insert, search, and delete accounts. A balanced search tree
is a good choice as it offers a fast navigation to reach a target account.

Next, the mail box should store the messages in a way that it returns the first mail at 
every query considering its priority. A good structure to implement a priority queue is a 
binary heap.


## Complexity

Below are the complexities of the operations performed by the structures described:


| Operation | AVL Tree | Binary Heap |
|-----------------------------------|----------------------------------|-----------------------------|
| **Insertion**   | `O(log n)`                      | `O(log n)`                  |
| **Search**      | `O(log n)`                      | `O(1)`                      |
| **Deletion**    | `O(log n)`                      | `O(log n)`                  |
| **Cleaning**    | `O(n)`                          | `O(n)`                      |

- The AVL Tree is a good choice here because it keeps the elements ordered which allows fast navigations in the main functions.
To destroy it all elements must be accessed though.
- Every insertion and deletion in the binary heap needs a heap construction with constant complexity of O(log n). 
The access of the first element is constant. Also, as the tree, all the elements must be accessed at the structure destruction.


## Results

This choice of structures showed good results when subjected to tests. 
The program execution ended in a short time of process use when subjected to large 
files containing a large number of operations.

## Program Execution
- Compile the program
```sh
make
```
- Check possible memory leaks
```sh
make mem-leak
```
- Run the program for the input files
```sh
make test
```
- Register proccess usage time
```sh
make usage
```
- Clean the project for another execution
```sh
make clean
```
