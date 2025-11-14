const { chromium } = require('playwright');
const fs = require('fs');

// Read employee data from data.json
const data = JSON.parse(fs.readFileSync('data.json', 'utf8'));

// Configuration
const CONFIG = {
    url: 'https://keus.akriviahcm.com',
    geolocation: { latitude: 17.4328197, longitude: 78.3782946 },
    timeouts: {
        short: 1000,
        medium: 2000,
        long: 3000,
        page: 30000
    }
};

/**
 * Navigate to login page and perform login
 */
async function login(page, employee) {
    console.log('  ↳ Navigating to login page...');
    await page.goto(`${CONFIG.url}/login`, { waitUntil: 'networkidle' });

    console.log('  ↳ Logging in...');
    await page.fill('input[name="username"], input[type="text"]', employee.employee_id.toString());
    await page.fill('input[name="password"], input[type="password"]', employee.password);
    await page.waitForTimeout(CONFIG.timeouts.short);

    await page.click('button:has-text("Login")');
    console.log('  ↳ Clicked login button');

    console.log('  ↳ Location permission granted via browser context');
    await page.waitForTimeout(CONFIG.timeouts.medium);
}

/**
 * Navigate to Attendance Management page
 */
async function navigateToAttendance(page) {
    console.log('  ↳ Waiting for dashboard...');
    await page.waitForURL('**/dashboard/dashboard', { timeout: CONFIG.timeouts.page });
    await page.waitForTimeout(CONFIG.timeouts.medium);

    console.log('  ↳ Opening Attendance Management...');
    await page.click('app-user-dashboard-v4-modules >> text=Attendance Management');

    console.log('  ↳ Navigating to attendance page...');
    await page.waitForURL('**/time-attendance/ess-attendance-dashboard', { timeout: CONFIG.timeouts.page });
    await page.waitForTimeout(CONFIG.timeouts.medium);
}

/**
 * Perform check-in action
 */
async function performCheckIn(page) {
    console.log('  ↳ Clicking Check In button...');
    await page.click('button:has-text("Check In")');

    console.log('  ↳ Waiting for confirmation dialog...');
    await page.waitForTimeout(CONFIG.timeouts.medium);

    console.log('  ↳ Confirming check in...');
    await page.click('button#request-cancel');
    console.log('  ↳ Clicked confirm button');
}

/**
 * Close success dialog after check-in
 */
async function closeSuccessDialog(page) {
    console.log('  ↳ Waiting for success confirmation...');
    await page.waitForTimeout(CONFIG.timeouts.long);

    console.log('  ↳ Closing success dialog...');
    await page.click('button#request-submit-close');
    console.log('  ↳ Clicked close button');
    await page.waitForTimeout(CONFIG.timeouts.short);
}

/**
 * Try to click an element using multiple selectors
 */
async function tryMultipleSelectors(page, selectors, actionName) {
    for (const selector of selectors) {
        try {
            const element = await page.locator(selector).first();
            if (await element.isVisible({ timeout: 2000 })) {
                await element.click();
                console.log(`  ↳ Clicked ${actionName}`);
                return true;
            }
        } catch (e) {
            continue;
        }
    }
    return false;
}

/**
 * Logout from the application
 */
async function logout(page) {
    console.log('  ↳ Logging out...');
    try {
        // Click on the user profile dropdown
        const profileSelectors = [
            'div.ah-header-navbar-actions-user',
        ];

        console.log('  ↳ Looking for user profile menu...');
        const profileClicked = await tryMultipleSelectors(page, profileSelectors, 'user profile menu');
        if (!profileClicked) {
            console.log('  ↳ Could not find profile menu, skipping logout');
            return;
        }

        await page.waitForTimeout(CONFIG.timeouts.medium);

        // Click on Logout button from dropdown
        const logoutSelectors = [
            'div#ah-header-navbar-user-dp-set-sub-logot',
        ];

        console.log('  ↳ Looking for logout button...');
        const logoutClicked = await tryMultipleSelectors(page, logoutSelectors, 'logout button');
        if (!logoutClicked) {
            console.log('  ↳ Could not find logout button');
            return;
        }

        await page.waitForTimeout(CONFIG.timeouts.medium);

        // Confirm logout
        console.log('  ↳ Looking for logout confirmation...');
        await page.click('button:has-text("Confirm")');
        console.log('  ↳ Confirmed logout');

        await page.waitForURL('**/login', { timeout: 10000 });
    } catch (error) {
        console.log(`  ↳ Logout error: ${error.message}`);
    }
}

/**
 * Main function to check in an employee
 */
async function checkInEmployee(browser, employee) {
    const context = await browser.newContext({
        geolocation: CONFIG.geolocation,
        permissions: ['geolocation']
    });
    const page = await context.newPage();

    await context.grantPermissions(['geolocation'], { origin: CONFIG.url });

    try {
        console.log(`\n🔄 Processing employee ID: ${employee.employee_id}`);

        await login(page, employee);
        await navigateToAttendance(page);
        await performCheckIn(page);
        await closeSuccessDialog(page);
        await logout(page);

        console.log(`✅ Successfully checked in employee ID: ${employee.employee_id}`);

    } catch (error) {
        console.error(`❌ Error processing employee ID ${employee.employee_id}:`, error.message);
    } finally {
        await context.close();
    }
} async function main() {
    console.log('🚀 Starting attendance automation...');
    console.log(`📋 Found ${data.employees.length} employee(s) to process\n`);

    const browser = await chromium.launch({
        headless: true, // Set to true to run without UI
        slowMo: 500 // Slow down by 500ms for better visibility
    });

    for (const employee of data.employees) {
        await checkInEmployee(browser, employee);
        // Add a delay between employees to avoid rate limiting
        await new Promise(resolve => setTimeout(resolve, 2000));
    }

    await browser.close();
    console.log('\n✨ Attendance automation completed!');
}

main().catch(error => {
    console.error('Fatal error:', error);
    process.exit(1);
});
