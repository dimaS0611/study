# Project name: "Car fleet"
Description
------------------
["Car fleet"](https://drive.google.com/file/d/1mTpACcfwxSDH3V1FytcW6ebkyOUowVAZ/view) The car fleet provides services for orders for the transportation of goods, using its fleet of vehicles and its drivers for this purpose. The driver who completes the order receives 20 % of the cost of transportation.

Instalation
---------------
Firstly run "Makefile" using the "make" command
and then run the executable file "../bin/CarFleet"

Usage
------------------
Car fleet management has the following structure:
Table | Fields
-------------|----------------------------------------------------------------------------------------------------------- 
🚙 Information about cars | vehicle number, brand, mileage at the time of purchase, capacity
🧔 Information about drivers | service number, driver's name, category, length of service, address, date of birth
📃 Information about orders | date, driver's name, car number, mileage, weight of cargo, cost of transportation

💻 The application has the following functionality:
----------------------------------------------------------------------------------------------------------- 
The driver of the fleet can find out information: about his car, only his data - marked with `*`

1. Using the Select statement returns the following information:
   
   1. 📌 for the specified driver list of completed orders for the specified period `*`;                                              
   1. 📌 the total distance travelled and the total weight of the transported goods by car `*`;
   1. 📌 for each driver the total number of trips, total weight transported goods and the amount of earned money `*`;   
   1. 📌 the driver who made the smallest amount of trips, all information and the amount of the money;
   1. 📌 for car with the highest total mileage – all information`*`; 
  
  --------------------------------------------------------------------------------------------------------------
2. Provides an update of the information in the specified tables using the Insert, Update, and Delete statements.

-------------------------------------------------------------------------------------
3. The function that, when adding information to the order table,
checks whether the weight of the load does not exceed the load capacity of the car, and if so, prohibits putting information in the table `*`.

----------------------------------------------------------------------------------------
4. The function that determines the amount of money accrued to each driver for transportation during the specified period.

----------------------------------------------------------------------------------------------
5. The function that determines the amount of money credited to the specified driver for transportation during the specified period.
-------------------------------------------------------
### Contributing:
Name | Responsibilites
------------|-------------
   A.Bokun | DB & documentation
   N.Korosteleva | UML, Report, Documentation
   D.Semenovich | Application, Kanban, Unit-tests

Project Presentation 
------------------
https://docs.google.com/presentation/d/16VyFU6_tEN4-aXj1F2JgpevwKh3QTbvzvioiTIwF_mU/edit?usp=sharing
