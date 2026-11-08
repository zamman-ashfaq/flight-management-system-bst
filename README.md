# Flight Management System (BST)

This is my DSA lab project. It is a C++ program that keeps flight records in a Binary Search Tree (BST). The tree is ordered by Flight ID, and every Flight ID has to be unique. If I try to add an ID that already exists, the program says so and does not add it.

## What the program can do
- Add a new flight
- Search a flight by its ID
- Delete a flight by its ID
- Show all flights in ascending order of Flight ID (inorder traversal)
- Calculate the ETA of every flight (departure time + duration) and show if it is On-Time, Early or Delayed
- Surprise feature: search flights by airline name and show how many were found
- Save all flights to `flights.txt`
- Load flights from `flights.txt` (this also happens automatically when the program starts)

## How to run
1. Open `main.cpp` in Visual Studio (or any C++ compiler).
2. Keep `flights.txt` in the same folder as the program.
3. Build and run. A menu will appear. Type the number of the option and press Enter.

## How to enter data
- Times are written as `HH:MM`, for example `09:30`.
- Duration is written as `H:MM`, for example `1:45`.
- Please do not use commas inside any field, because commas are used to separate the fields in the file.

## File format
Each flight is on its own line in `flights.txt`:

`Flight ID, Source, Destination, Airline, Departure, Arrival, Duration, Price, Status`

Example: `50,Lahore,Karachi,PIA,09:30,11:15,1:45,18000,Scheduled`

I save the flights in preorder (parent first, then left, then right). This way, when the file is loaded again, the tree gets the same shape as before, so I can test deleting a leaf node, a node with one child and a node with two children.

## Things the program does not do
- It does not check if the times and duration are typed in the correct format, so they must be entered as shown above.
- The airline search is case-sensitive, so `PIA` and `pia` are different.
