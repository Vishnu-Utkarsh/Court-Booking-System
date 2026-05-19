# Court-Booking-System
A Court Booking System is a software application designed to manage reservations for sports courts like badminton, tennis, or squash, leveraging object-oriented programming (OOP) principles for modularity and scalability.

## Key Features

### 🗓️ 2-Day Booking Availability System
- **Real-time Availability**: View available time slots for today and tomorrow
- **Hourly Time Slots**: Courts can be booked in 1-hour increments (6 AM to 11 PM)
- **Automatic Duration**: Each booking is for 3 hours by default
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

## How to Use

### Creating an Account
1. Select "Create new user account" from the main menu
2. Enter a unique username
3. Create a secure password

### Booking a Court
1. Login with your credentials
2. Select "Book Court" from the user menu
3. Choose a court from the available options
4. Select a date (today or tomorrow)
5. Choose a time slot from the available hours
6. Confirm your booking

### Viewing Your Bookings
1. After logging in, select "Bookings Tab"
2. View all your active bookings with:
   - Court name and number
   - Date and time
   - Duration (3 hours default)

## Technical Architecture

### Core Components

#### Court Management (`court.hpp`)
- **TimeSlot Structure**: Stores individual booking time slots
  - Date (YYYY-MM-DD format)
  - Hour (0-23)
  - Username of booker
- **Court Class**: Base class with multi-day booking support
  - Tracks bookings in a map: `date → hour → TimeSlot`
  - Methods for checking and making bookings
- **Derived Classes**: Badminton, Basketball, Volleyball, Football, Cricket

#### Booking Methods
```cpp
bool bookSlot(const string &date, int hour, const string &username);
bool isSlotAvailable(const string &date, int hour) const;
vector<TimeSlot> getAvailableSlots(const string &date) const;
```

#### User Interface (`operation.cpp`)
- **User::book()**: Interactive booking interface with:
  - 2-day availability display
  - Date selection
  - Time slot selection with visual formatting
  - Booking confirmation
- **User::bookings()**: Display all user's bookings

#### Utility Functions (`court.hpp`)
- `getTodayDate()`: Get today's date in YYYY-MM-DD format
- `getDateOffset(days)`: Get date N days in the future
- `getNextTwoDays()`: Get array of next 2 dates for availability

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
- **Daily Booking Window**: 6:00 AM to 11:00 PM
- **Booking Duration**: 3 hours per slot
- **Availability Window**: Current day + 1 day (48-hour rolling window)

## System Constants
```cpp
const int durationLimit = 3;     // Hours per booking
const int bookingLimit = 2;      // Max bookings per user
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
├── court.hpp         // Court classes and TimeSlot structure
├── user.hpp          // User class and management
├── operation.cpp     // User interactions and booking logic
├── data.cpp          // CSV I/O operations
├── storage.hpp       // Global data structures
├── Template.hpp      // Debug and utility templates
├── main.cpp          // Entry point
├── userData.csv      // User data storage
├── courtData.csv     // Court data storage
├── bookings.csv      // Booking data storage
└── README.md         // This file
```

## Future Enhancements
- Booking cancellation system
- Court maintenance scheduling
- Advanced filtering by court type
- Booking history and statistics
- Multi-user bookings for same slot
- Price/rate management
- Email notifications
