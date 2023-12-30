
# SQL DATABASE - QUEENCY TAN

# PROGRAM VIDEOS

# Making/Inserting Into Table Video
https://github.com/barkeshli-CS008-classroom/99_99_final_project-QueencyT/assets/122432408/e6cfb4d3-ba29-487e-9f22-1de80ad202d6

# Selecting From Table Video
https://github.com/barkeshli-CS008-classroom/99_99_final_project-QueencyT/assets/122432408/aa8d1bd7-4af8-4874-93c2-7fa719281c9d

# PROJECT DESCRIPTION
This project is an SQL Database made from scratch. Users can input SQL commands such as MAKE TABLE, SELECT, and INSERT INTO in order to create and modify their tables. For example, if the user inputted a command such as ‘make table student fields fname, lname, age’ a table with the name student will be created with the fields fname, name, and age. The other commands are equally straightforward. If the user inputted a command such as ‘select * from student where age > 21’, the program will find all your records with an age greater than 21, put it into a table, and display it for you. You can also choose to display only certain fields by inputting a command such as ‘select age,lname from student where age > 21’. This command will retrieve the same values as the previous select command except instead of displaying all the fields, it will display only the ‘age’ and ‘lname’ of the selected records. Lastly, if the user inputted a command such as ‘insert into student values Jane, Doe, 24’, the program will create a new record with those values and insert it into your table.

If after making multiple tables, you forget the field names of a certain table, you can use the ‘GET FIELDS’ command and the program will give you the field names of that given table provided that the table already exists. For example, inputting the command ‘get fields from student’ will get you the field names of the student table you created. 

If you are not familiar with the syntax of SQL commands, there is no need to worry. This project also includes an ‘Error_Handler’ class that will help you troubleshoot any syntax errors you might have. Furthermore, you can always enter '?' in order to see the help menu for explanations and examples of the syntax. 

# How This Project Was Built: 
This project uses data structures such as BPlusTrees, MultiMaps, and Maps for their ability to efficiently sort, store, and look-up records. This project also uses stacks, and queues in tandem with RPN and ShuntingYard algorithms in order to evaluate the user’s inputted commands.

# Insert Command: 
![Alt text](image-10.png)

# Select Command:
![Alt text](image-8.png)
![Alt text](image-9.png)

# Get Fields Command: 
![Alt text](image-13.png)

# Help Desk:
Picture of Help Desk (which you can get by entering '?')
![Alt text](image-2.png)
A Guide to all the Commands (which you can get by entering 'A')
![Alt text](image-3.png) 

https://github.com/barkeshli-CS008-classroom/99_99_final_project-QueencyT/assets/122432408/f1747632-3361-4040-9c20-60962fc57a9e

# Error Checking: 
Sample of some error-checking features
![Alt text](image-14.png)

https://github.com/barkeshli-CS008-classroom/99_99_final_project-QueencyT/assets/122432408/79d79651-8a52-4e7c-8555-75733eac81a7

## EXTRA INFO: 
# Technical Details: 
All user inputs are tokenized using my ‘Stokenizer’ class into a vector of strings. Then that vector of strings is passed into my ‘Parser’ class which will parse the user’s input according to a state machine I designed. The ‘Parser’ class includes a map of all this project’s keywords (select,from,where,etc.) along with the column/row number they correspond to in the adjacency matrix. Anything that is not a number is treated as a ‘SYMBOL’ (table names, field names, etc) which my state machine will deal with accordingly. The purpose of the parser class is to create a multimap that stores/organizes the user’s input. I call this multimap the “statement tree”. An example of how this multimap would look like after parsing is this: 

![Alt text](image-11.png)

This multimap is later passed into my SQL class which will create a table to display to the user. The table is created according to the commands/conditions etc stored in the multimap/statement tree. 

All data is stored in binary files using the ‘write’ function of my ‘FileRecord’ class and retrieved using the ‘read’ function of my FileRecord class. All data storage and retrieval happens within this project’s Table class which uses read and write to manipulate the binary files. When the table class reads from the binary file, it stores the data into a vector of multimap<string,long>. Each Multimap represents a field (age, fname, lname,etc) and within those multimaps are specific values of that field (the age multimap would have  values like “21" : [vector of recnos], “20” : [vector of recnos], etc). Long is for the record numbers that contain those values. For example, “21” : [10,15,16] means records 10,15, and 16 all have an age of 21.

Storing my data this way allows me to use the iterator functions of my Multimap class ('upper_bound', 'lower_bound', 'begin', and 'end'). The function ‘upper_bound’ and ‘lower_bound’ will return an iterator to the upper and lower bounds of any value you enter while 'end' and 'begin' will return an iterator to the “smallest” value and “largest” value in the Multimap respectively. I use these iterator functions to efficiently select the appropriate values according to the user’s condition. For example, if the user wanted to find all the records with “age > 21”, I would first obtain the upper bound of 21 and then I’d iterate from the upper bound to the end, which would give me all the values greater than 21 along with the record numbers that have those values. I do similar things to evaluate the other relational operators (>,<,etc). 

# Challenges I Faced when Making this Project 

One challenge I faced was when I was designing the ‘Interaction’ and ‘Error_Handler’ classes. When designing them, I wasn't sure whether I should have my Interaction class own an ‘Error_Handler’ object and do all my error checking/correction in my interaction class, so my SQL class only ever receives completely valid commands or to have my SQL class do its own error-checking, meaning I would allow nonsense user input to be passed into SQL. Originally, I thought it would be more intuitive to have my interaction class own an error handler object, so I could have code like this

![Alt text](image-12.png)

But doing so meant that even in the best case scenario (user inputs a valid command first try), I would be parsing the user's input twice. Once during the initial check for errors, and then again when I pass the user string into SQL. There were a couple workarounds I could think of to continue error handling in the Interaction class while avoiding the double-parsing problem, but I felt the solutions were a bit clumsy. Ultimately, I decided to go with the second route, having the SQL class do its own error-checking, which avoids the double parsing problem while still being a relatively clean solution. 

<br><br>

<br><br>

<br><br>

<br><br>
