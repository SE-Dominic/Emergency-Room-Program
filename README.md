Hello and welcome to my program! This is a highly scalable emergency room program which simulates entering patients
into the emergency room queue by gathering data on the patient to judge their severity, and then putting
them into the line where the patient is sorted and seen based on patient severity levels.

Objectives:
  - Showcase my understanding and knowledge of data structures.
  - Create a program that has real world use cases.
  - Structure patients in a format based on severity (min heap) but also have a O(1) lookup time (map).

Features:
  - Add patient to line (adds patient to the back of the line)
  - See the next patient (takes next patient from line)
  - View patient information (by look up)

Future Improvements:
  - Add more menu functionality ('view all patients', 'edit patient info', etc)
  - Turn into a GUI application using QT or another framework
  - Add database functionality with SQL.
  - Implement Try/Catch to keep fluidity of application
    + current issue where input fields are strict and crash program if not inputted perfectly. 
