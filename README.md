# InMemoryDb

## Prerequisites
Make sure you are able to compile C++ code, i.e. have a compiler like g++ installed.

## Run
Clone the repo and cd into the directory. Run ``make`` and the required command to run an executable on your OS.\
Windows: ``.\db.exe``\
Unix/Linux: ``./db``

## Improvements
A detailed rubric could be provided, outlining the specific criteria and expectations for each part of the assignment. Additionally, the instructions could suggest potential test cases that students can use to validate the correctness of their implementations or leave that as an exercise for the student. To add to this assignment, the student could implement a method to delete a key from the database, ``delete(key)``, which should remove the key-value pair and handle errors if a transaction is happening. Another addition could be to implement serialization/deserialization methods to save the state of the DB to a file.