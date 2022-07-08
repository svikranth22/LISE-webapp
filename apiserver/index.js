const express = require('express');
const labApp = require('./lab-app');
const PORT = 3100;
const ip = require('ip')


const StartServer = async () => {

    const app = express();
    const ipAddress = ip.address();

    await labApp(app);

    app.listen(PORT, () => {
        console.log(`listening on port: ${PORT}`);
        console.log('Network access via: http://' + ipAddress + ':' + PORT);
    })
    .on('error', (err) => {
        console.log(err);
        process.exit()
    })
}

StartServer();