const pg = require("pg");

const pool = new pg.Pool({
  user: "postgres",
  host: "localhost",
  database: "postgres",
  password: "lol",
  port: 5432,
});
async function fetchData() {
  const result = await pool.query("SELECT * FROM ingredients;");
  const { rows } = result;
  console.log(rows);
  return result;
}
const result = fetchData();
console.log(result);
