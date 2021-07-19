# Blood Bank Management System

This system is made to ease the handling of the recipient and the donor blood using an encrypted login system in C++.

## Requirements
##### To run the Executable, no pre-requisites are required, it will work on all Windows System
##### To Run the C++ Code, following are the requirements,
- g++ 9.2.0
- C++ 17
- Filesystem.h
- Json.hpp [Github](https://github.com/nlohmann/json)
- ```g++ -std=c++17 main.cpp && a.exe```

## Start-Up

On execution of the software, the following options are presented:
1. Admin Login
2. Patient Login
3. Exit

### Admin Login
This method takes in the admin password and sends it to a dynamic encryption hashing algorithm to encrypt the password while decrypting the original stored password and dynamically re-hashing it to match with the entered password.
![Login Encryption System](https://github.com/kartikeya72001/Blood-Bank-Management/blob/master/Images/AdminLogin.jpg?raw=true)

## Admin Functionality
- Check Blood Availability
- Search Patient by Name
- Display all Patients
- Generate a Combined Report for all Hospital Patients
- View and Accept/Reject Blood Requests
- Change Admin Password(Encrypted)

#### Check Blood Availability
This system function displays all the types of blood available with the hospital with their respective quantities.
#### Search Patient
It enables the admin to search for a patient by the first name. It returns all the patients matching the input first name string.
#### Display
This method displays all the donor and well all recipient patients registered with the portal.
#### Generate Hospital Report
This method exports a comma-separated file for all the registered patients in the hospital system.
### View Requests
This function enables the admin to manage all the recipient requests that are registered in the system. all the requests are displayed along with the available quantities of blood.
#### Change Admin Password
This method takes admin input via a private variable encrypts the input and stores the input into a file for future references.
![Password Reset](https://github.com/kartikeya72001/Blood-Bank-Management/blob/master/Images/ResetPwd.jpg?raw=true)


## License
[MIT](https://choosealicense.com/licenses/mit/)
