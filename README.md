
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
![image](https://user-images.githubusercontent.com/56382779/117596677-24e7de00-b144-11eb-96fe-21c530c4876f.png)


### Shipment type form

![image](https://user-images.githubusercontent.com/56382779/117596792-6ed0c400-b144-11eb-86e2-7b8f1f07334e.png)
![image](https://user-images.githubusercontent.com/56382779/117596943-cbcc7a00-b144-11eb-81d9-c287dd66b2b4.png)
![image](https://user-images.githubusercontent.com/56382779/117596927-c2431200-b144-11eb-9be3-b00ebd27d7c4.png)
![image](https://user-images.githubusercontent.com/56382779/117596903-b5262300-b144-11eb-8ae7-15d2907f6afb.png)


### Personal data form
![image](https://user-images.githubusercontent.com/56382779/117597221-6e84f880-b145-11eb-9c23-2dd58df83bec.png)
![image](https://user-images.githubusercontent.com/56382779/117597208-69c04480-b145-11eb-9418-4f837946987d.png)
![image](https://user-images.githubusercontent.com/56382779/117597362-b572ee00-b145-11eb-942b-39b93146ebc4.png)


### Browsing main database
![image](https://user-images.githubusercontent.com/56382779/117597383-c02d8300-b145-11eb-9697-231cdec51708.png)

