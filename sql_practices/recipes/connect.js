const pg = require("pg");
const pool = new pg.Pool({
  user: "postgres",
  host: "localhost",
  database: "recipes",
  password: "postgres",
});

const {rows} = await pool.query(`SELECT * FROM ingredients;`);

