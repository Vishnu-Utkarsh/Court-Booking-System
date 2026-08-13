# Court-Booking-System
A Court Booking System is a software application designed to manage reservations for sports courts like badminton, LawnTennis, or basketball, leveraging object-oriented programming (OOP) principles for modularity and scalability.

## Key Features

### Booking Availability System
- **Real-time Availability**: View available time slots for today and for next few days
- **Hourly Time Slots**: Courts can be booked in intervals of 1-hour by default (from 6 AM to 10 PM)
- **Multiple Bookings**: Users can book different courts at different times
- **Visual Slot Selection**: Easy-to-use interface for selecting dates and times

### User Actions
- Create and manage user accounts with authentication
- Track user bookings and booking history
- Support for authorized and banned user statuses
- Persistent user data storage

### Court Management
Six types of courts available:
1. Badminton Court** (Indoor)
2. Basketball Court** (Outdoor)
3. Volleyball Court** (Indoor)
4. Football Ground** (Ground)
5. Cricket Ground** (Ground)
6. Lawn Tennis** (Outdoor)

Each court type can have multiple numbered instances.

- Create and manage user accounts with authentication
- Track of bookings as per slot
- Persistent court data storage
- Support for different court statuses:
   - Available: Court is free to book by anyone.
   - Reserved: Court is already reserved for specific purpose (like- practice for Inter-IIT or General Championship).
   - Maintainance: Court is not available to be used because of any temporary construction / renovation work going on.
    


### Administrative Functions
- **User Management**: Approve or ban user accounts
- **Court Management**: Add, remove, or modify court information
- **Booking Management**: View and manage all bookings with Adaptive Filter


## Compilation and Usage

### Prerequisites
Make sure a C++ compiler such as GCC/G++ with C++11 or C++14 support is installed.
Run the following command in Terminal in directory where the project source code is to be stored

### Clone Repository
```bash
git clone https://github.com/Vishnu-Utkarsh/Court-Booking-System.git
```

### Compile
```bash
g++ -std=c++17 code/main.cpp -o court_booking
```

### Run
```bash
./court_booking
```

## How to Use

### Login as Admin
1. Login with admin credentials [Case Sensitive]
```txt
  Admin name: Admin
  Password: QWERTY
```
2. Access the admin dashboard

### Creating User Account
1. Select "Create new user account" from the main menu
2. Enter a unique username
3. Create a secure password
4. Now you can Login with same credentials next time when you want to login again

### Booking a Court
1. Login with your credentials
2. Select "Book Court" from the user menu
3. Choose a court from the available options
4. Select a date from the next 5 days (including today)
5. Choose a time slot from the available hours
6. Select sports equipment to issue if required (optional)
7. Confirm your booking

### Viewing Your Bookings
1. After logging in, select "Bookings Tab"
2. View all your active bookings with:
   - Court name and number
   - Date and time
   - Duration (1 hour default)
   - See equipments issued (if choosen)
3. Option to cancel bookings

## Technical Architecture

### Core Components

#### Court Management (`court.cpp`)
- **TimeSlot Structure**: Stores individual booking time slots
  - Date (YYYY-MM-DD format)
  - Hour (0-23)
  - Username of booker
- **Court Class**: Base class with multi-day booking support
  - Tracks bookings in a map: `date → hour → TimeSlot`
  - Methods for checking and initiate bookings
- **Derived Classes**: Badminton, Basketball, Volleyball, Football, Cricket, LawnTennis courts with specific attributes
  - Inherited functions from Abstract Class "Court"
  - Constructors for each derived class
  - Optional feature function to issue sports equipments

#### User Interface (`user.cpp`)
- **User::book()**: Interactive booking interface with:
  - 5-day availability display
  - Date selection
  - Time slot selection with visual formatting
  - Booking confirmation
- **User::bookings()**: Display all user's bookings

#### Admin Interface (`admin.cpp`)
- **Admin::manageUsers()**: View and manage user accounts
- **Admin::manageCourts()**: Add, remove, or modify court information
- **Admin::manageBookings()**: View and manage all bookings

#### Login Portal (`operation.cpp`)
- **Login System**: Authenticate users and admins
- **Menu Navigation**: Direct users to appropriate interfaces based on role

### Data Persistence

#### Files
- **userData.csv**: User credentials and status
  - Format: `username, password, status`
- **courtData.csv**: Court information
  - Format: `CourtName, CourtNumber, status`
- **bookings.csv**: All time slot bookings
  - Format: `CourtName, CourtNumber, Date, Hour, Username`

#### Data Operations (`data.cpp`)
- `readUserData()`: Load users from CSV
- `readCourtData()`: Load courts from CSV
- `readBookings()`: Load all bookings from CSV
- `saveUserData()`: Persist users to CSV
- `saveCourtData()`: Persist courts to CSV
- `saveBookings()`: Persist bookings to CSV

## Operating Hours
- **Daily Booking Window**: 6:00 AM to 10:00 PM
- **Booking Duration**: 1 hours per slot
- **Availability Window**: 5 days (including current day)

## System Constants
```cpp
const int durationLimit = 1;  // Hours per booking
const int maxDayLimit = 5;    // Number of days in advance for booking
```

## Project Structure
```
CourtBookingSystem/
|
├── code/
|   ├── utilities.cpp     // Elementary utility funcitons
|   ├── court.cpp         // Court implementation
|   ├── user.cpp          // User implementation
|   ├── admin.cpp         // Admin implementation
|   ├── operation.cpp     // User interactions and booking logic
|   ├── data.cpp          // CSV I/O operations
|   └── main.cpp          // Entry point
|
├── headers/
|   ├── storage.hpp       // Global data storage variables and constants
|   ├── court.hpp         // Court classes and TimeSlot structure
|   ├── user.hpp          // User class and management
|   └── admin.hpp         // Admin class and management
|
├── data/
│   ├── userData.csv      // User data storage
│   ├── courtData.csv     // Court data storage
│   └── bookings.csv      // Booking data storage
|
├── .gitignore            // Files to be Ignored
└── README.md             // About Project -> This file
```

## Future Enhancements
- Adding Graphical User Interface
- Booking history and statistics
- Booking feature for meeting rooms to be booked by society secrataries
- Multiple Admins
- Multi-user bookings for same slot
- Restriction on excess bookings
- Email notifications