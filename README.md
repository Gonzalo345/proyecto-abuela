# Proyecto-ajenda
## Ajenda para mi abuela

Exercise 2: Create an agenda for my grandmother

My grandmother has very bad memory. She has alzheimer and always forgets what she has done and
also what she has to do. Unfortunately I live in the city and cannot help her, but I believe that creating a
scheduling program can help her a lot in the daily life.

She needs a tool that works as a interactive agenda. This interactive agenda will answer you with the
activity you supposed to be doing in a exact time. It will also advertise you when an scheduled activity
is starting and also 10 minutes before it finish (not in all the cases)

The schedules activities has an internal state: done and undone. All the activities are in “undone” state
in the beginning.

When you write down a time, the agenda is answering with the activity you are supposed to do. If the
activity is not done, then the agenda should ask if you are doing it. If you answer “yes” then the agenda
should change the internal state from “undone” to “done. If you answer “no” then the internal state
should not change.
There should be a 3 second interval time between agenda printed outputs.

The program should keep in a silent state, there are 3 cases that the program should create an output
(some printed words):
After the user write a time (to ask of what to do).
When a scheduled task just start.
10 minutes before a scheduled task finish (only if the task is “undone”)

Example 1: If I enter “8:35” in the program the answer would be “Breakfast time”. In case that the
program has the breakfast as an undone task, the program would ask after 3 seconds “Are you having
breakfast?” and then my grandma would answer “yes” if she is having, so the state of the breakfast
time would change to “done”. If she will answer with “no” then the state of breakfast time would stay
“undone”.

Example 2: If I enter “now” and the task is “having lunch” and the task is already done, then the
program should answer something like “Chill, you already have lunch”.

- Task 1:
Draw a flowchart with the agenda specifications.
Create a C program according to this flowchart. It should be able to read the input (through terminal).
Using printf for output it is enough, no graphical interface is needed.

I don’t want my grandma to get bored, so I would like you to create a schedule at least with 8 activities
perfectly scheduled in a 0-24h clock.

- Task 2:
I am not my grandmother, so if you can add a way to run the day faster. Adding a speed factor when
executing the program (speed factor is =1, time run normally, speed =2 double speed...)
This is just the solution I found to a problem. If you think you have one better, please program it. Also,
new useful features are welcome.
The code must be done in a clear, organic and modular way, even if it is a small project.
