import { Client } from "ssh2";

const conn = new Client();
conn.on('ready', () => {
  console.log('Client :: ready');
  conn.exec('uptime', (err, stream) => {
    if (err) throw err;
    //@ts-ignore
    stream.on('close', (code, signal) => {
      console.log('Stream :: close :: code: ' + code + ', signal: ' + signal);
      conn.end();
    //@ts-ignore
    }).on('data', (data) => {
      console.log('STDOUT: ' + data);
    }).stderr.on('data', (data) => {
      console.log('STDERR: ' + data);
    });
  });
}).connect({
  host: '100.101.26.42',
  port: 22,
  username: 'keus',
  password: "gateway2021"
});