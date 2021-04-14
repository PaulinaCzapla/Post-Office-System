# Post Office System
### *This project is still in progress*

A post office system, designed for use by post office empoyee. It's a window application carried out using the assumptions of object-oriented programming in C++ and implemented using [Qt Framework](https://github.com/qt). 

**Functionalities offered by the application:**
- sending letter/ parcel;
- computing shipment price based on shipment type (size, weight, country etc.);
- searching, browsing databases;
- changing shipment statuses.

**Project assumptions:**
- shipments are divided into letters and parcels;
- each shipment has a status;
- shipment with "received" status is going to be pernamently removed from database after 7 days from date of receipt;
- shipments statuses "awaiting pickup at the facility" are will be changed to "the date of receipt has expired" if shipment is not picked up on time;
- there is a hierarchy of statuses;
- the price is set only when preparing a shipment, this information is not stored in the database ;
- there are two databases - local and main (local database contains shipments that are currently handled by the branch of the post office, main database contains all shipments);
- project supports .txt and .csv files.


### Main menu
![image](https://user-images.githubusercontent.com/56382779/114763789-7da1a200-9d63-11eb-9422-24ed3b36abf7.png)


### Shipment type form

![image](https://user-images.githubusercontent.com/56382779/114763821-898d6400-9d63-11eb-91c2-ae9bccc26387.png)

![image](https://user-images.githubusercontent.com/56382779/114763856-93af6280-9d63-11eb-9dec-91605db7ff52.png)

![image](https://user-images.githubusercontent.com/56382779/114763954-ade94080-9d63-11eb-8c0c-04c136f4fe5b.png) ![image](https://user-images.githubusercontent.com/56382779/114763978-b5104e80-9d63-11eb-9ef5-a04101120c02.png)



### Personal data form
![image](https://user-images.githubusercontent.com/56382779/114763924-a4f86f00-9d63-11eb-91c5-d582478a33c2.png)

### Browsing main database
![image](https://user-images.githubusercontent.com/56382779/114764091-d1ac8680-9d63-11eb-90ff-e04621783d49.png)

