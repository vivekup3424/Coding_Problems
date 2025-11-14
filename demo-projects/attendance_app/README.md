# Attendance Automation

This project automates the attendance check-in process for employees using Playwright.

## Setup

1. Install dependencies:
   ```bash
   npm install
   ```

2. Install Playwright browsers:
   ```bash
   npx playwright install
   ```

3. Update `data.json` with employee credentials.

## Usage

Run the automation script:
```bash
npm start
```

Or:
```bash
node attendance.js
```

## Configuration

- **Headless mode**: Edit `attendance.js` and set `headless: true` to run without UI
- **Speed**: Adjust `slowMo` value in `attendance.js` to control execution speed
- **Employees**: Add/remove employees in `data.json`

## Features

- ✅ Automated login for multiple employees
- ✅ Navigate to Attendance Management
- ✅ Click Check In and confirm
- ✅ Verify success message
- ✅ Logout after check-in
- ✅ Error handling for each employee
- ✅ Progress logging

## Data Format

```json
{
    "employees": [
        {
            "employee_id": 1485,
            "password": "your_password"
        }
    ]
}
```

## Notes

- The script runs with `headless: false` by default so you can see what's happening
- Each employee check-in is independent - if one fails, others will still be processed
- A 2-second delay is added between employees to avoid rate limiting
