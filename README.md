# Court-Booking-System
A Court Booking System is a software application designed to manage reservations for sports courts like badminton, tennis, or basketball, leveraging object-oriented programming (OOP) principles for modularity and scalability.

## Key Features

### 🗓️ Booking Availability System
- **Real-time Availability**: View available time slots for today and for next few days
- **Hourly Time Slots**: Courts can be booked in 1-hour intervals (from 6 AM to 10 PM)
- **Automatic Duration**: Each booking is for 1 hours by default
- **Multiple Bookings**: Users can book different courts at different times
- **Visual Slot Selection**: Easy-to-use interface for selecting dates and times

### 👤 User Management
- Create and manage user accounts with authentication
- Track user bookings and booking history
- Support for authorized and banned user statuses
- Persistent user data storage

### 🏟️ Court Management
Five types of courts available:
- **Badminton Court** (Indoor)
- **Basketball Court** (Outdoor)
- **Volleyball Court** (Indoor)
- **Football Ground** (Ground)
- **Cricket Ground** (Ground)

Each court type can have multiple numbered instances.

### 🤖 Administrative Functions
- **User Management**: Approve or ban user accounts
- **Court Management**: Add, remove, or modify court information
- **Booking Management**: View and manage all bookings

## How to Use

### Login as Admin
1. Login with admin credentials
```txt
  Admine name: Admin
  Password: QWERTY
```
2. Access the admin dashboard

### Creating User Account
1. Select "Create new user account" from the main menu
2. Enter a unique username
3. Create a secure password

### Booking a Court
1. Login with your credentials
2. Select "Book Court" from the user menu
3. Choose a court from the available options
4. Select a date from the next 5 days (including today)
5. Choose a time slot from the available hours
6. Confirm your booking

### Viewing Your Bookings
1. After logging in, select "Bookings Tab"
2. View all your active bookings with:
   - Court name and number
   - Date and time
   - Duration (1 hour default)
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
  - Methods for checking and making bookings
- **Derived Classes**: Badminton, Basketball, Volleyball, Football, Cricket courts with specific attributes

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
  - Format: `username,password,status`
- **courtData.csv**: Court information
  - Format: `CourtName,CourtNumber`
- **bookings.csv**: All time slot bookings
  - Format: `CourtName,CourtNumber,Date,Hour,Username`

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
- **Availability Window**: Current day + 5 days

## System Constants
```cpp
const int durationLimit = 1;  // Hours per booking
const int maxDayLimit = 5;    // Number of days in advance for booking
```

## Compilation
```bash
g++ -std=c++17 main.cpp -o court_booking
```

## Usage
```bash
./court_booking
```

## Project Structure
```
├── storage.hpp       // Global data structures and constants
├── court.hpp         // Court classes and TimeSlot structure
├── court.cpp         // Court implementation
├── user.hpp          // User class and management
├── user.cpp          // User implementation
├── admin.hpp         // Admin class and management
├── admin.cpp         // Admin implementation
├── operation.cpp     // User interactions and booking logic
├── data.cpp          // CSV I/O operations
├── main.cpp          // Entry point
|
├── data
│   ├── userData.csv      // User data storage
│   ├── courtData.csv     // Court data storage
│   └── bookings.csv      // Booking data storage
└── README.md         // This file
```

## Future Enhancements
- Booking history and statistics
- Multi-user bookings for same slot
- Price/rate management
- Email notifications
