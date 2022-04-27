const express = require('express')
const app = express()

const ip = require('ip')
const ipAddress = ip.address()
const port = 3000

app.set('views', './views')
app.set('view engine', 'pug')

app.get('/', (req, res) => {
    res.render('lise-input')
})

app.listen(port, () => {
    console.log('App listening on port: ' + port)
    console.log('Network access via: ' + ipAddress + ':' + port)
})
