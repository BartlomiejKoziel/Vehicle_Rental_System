# Vehicle Rental System

The project is a console information system designed to support the operation of a vehicle rental company.  
It allows managing different types of vehicles, handling private and business customers, and performing vehicle rentals and returns with automatic cost calculation.

The application was developed as part of the *Object-Oriented Programming Languages* course.

## Main Features

- Fleet management:
  - Passenger cars (combustion and electric)
  - Motorcycles
  - Trucks
- Customer management:
  - Private and business customers
- Rental handling:
  - Vehicle rental for a specified time
  - Vehicle return with final cost calculation
- Text-based user interface with input validation

## Requirements

- Windows 10 or newer
- Visual Studio Build Tools  
  *(Desktop development with C++)*
- CMake 3.20 or newer

---

## Build Instructions (Windows / MSVC)

The project uses the MSVC compiler and must be built from the **x64 Native Tools Command Prompt for Visual Studio**.

### Build steps:

```bat
cd path\to\Vehicle_base
mkdir build
cd build
cmake .. -G "NMake Makefiles"
cmake --build .
