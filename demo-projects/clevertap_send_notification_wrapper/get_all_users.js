require("dotenv").config();
const axios = require("axios");
const fs = require("fs");
const headers = {
	"X-CleverTap-Account-Id": process.env.CLEVERTAP_ACCOUNT_ID,
	"X-CleverTap-Passcode": process.env.CLEVERTAP_ACCOUNT_PASSCODE,
	"Content-Type": "application/json",
};
const cursor = "ZiZiNwMHAwBvbmd6b28uO20BBgFlbGRzZWprcwACTQVgb2B9YWJgewsIAwYraGN8endjNwJMAANlbmp%2FYmtqfk5AbgVgb2B9YWJgewsIAwYra2V%2BZWxkcwAACAxlaC55Zm1%2FZgNMAUhmbWB%2Fb25negoFTUQIa2V%2BZWxkcwAACAxlaC56YG9gfQQIAwRuYmB5K2hjfB8dAEhnJmN8ZW5qfwcBCQErKg16YG9gfQQIAwRuYmB5K2tlfgAGBwxlamtzZWgueQMHHBlmJmI3Zm1gfwoEBAVvby47CGtlfgAGBwxlamtzZWguegUFAwJhYmB7bmJgeU4CAAN6d2M3ZyZjfAAECQBia2p%2BKyoNegUFAwJhYmB7bmJgeU4BBgFlbGRzZWprcwACTQZmbX9mZiZiNwMHAwBvbmd6b28uO20BBgFlbGRzZWprcwACTQVgb2B9YWJgewsIAwYraGN8endjNwJMAANlbmp%2FYmtqfk5AbgVgb2B9YWJgewsIAwYra2V%2BZWxkcwAACAxlaC55Zm1%2FZgNMAUhmbWB%2Fb25negoFTUQIa2V%2BZWxkcwAACAxlaC56YG9gfQQIAwRuYmB5K2hjfB8dAEhnJmN8ZW5qfwcBCQErKg16YG9gfQQIAwRuYmB5K2tlfgAGBwxlamtzZWgueQMHHBlmJmI3Zm1gfwoEBAVvby47CGtlfgAGBwxlamtzZWguegUFAwJhYmB7bmJgeU4CAAN6d2M3ZyZjfAAECQBia2p%2BKyoNegUFAwJhYmB7bmJgeU4BBgFlbGRzZWprcwACTQZmbX9mZiZiNwMHAwBvbmd6b28uO20BBgFlbGRzZWprcwACTQVgb2B9YWJgewsIAwYraGN8endjNwJMAANlbmp%2FYmtqfk5AbgVgb2B9YWJgewsIAwYra2V%2BZWxkcwAACAxlaC55Zm1%2FZgNMAUhmbWB%2Fb25negoFTUQIa2V%2BZWxkcwAACAxlaC56YG9gfQQIAwRuYmB5K2hjfB8dAEhnJmN8ZW5qfwcBCQErKg16YG9gfQQIAwRuYmB5K2tlfgAGBwxlamtzZWgueQMHHBlmJmI3Zm1gfwoEBAVvby47CGtlfgAGBwxlamtzZWguegUFAwJhYmB7bmJgeU4CAAN6d2M3ZyZjfAAECQBia2p%2BKyoNegUFAwJhYmB7bmJgeU4BBgFlbGRzZWprcwACTQZmbX9mZiZiNwMHAwBvbmd6b28uO20BBgFlbGRzZWprcwACTQVgb2B9YWJgewsIAwYraGN8endjNwJMAANlbmp%2FYmtqfk5AbgVgb2B9YWJgewsIAwYra2V%2BZWxkcwAACAxlaC55Zm1%2FZgNMAUhmbWB%2Fb25negoFTUQIa2V%2BZWxkcwAACAxlaC56YG9gfQQIAwRuYmB5K2hjfB8dAEhnJmN8ZW5qfwcBCQErKg16YG9gfQQIAwRuYmB5K2tlfgAGBwxlamtzZWgueQMHHBlmJmI3Zm1gfwoEBAVvby47CGtlfgAGBwxlamtzZWguegUFAwJhYmB7bmJgeU4CAAN6dw%3D%3D"
axios
	.post(`https://eu1.api.clevertap.com/1/profiles.json?cursor=${cursor}`,{}, { headers })
	.then((res) => {
		console.log("Success:", res.data);
        fs.writeFileSync("response", JSON.stringify(res.data))
	})
	.catch((err) => {
		console.error("Error:", err.response?.data || err.message);
	});

