const express = require('express')
const multer  = require('multer')
const upload = multer({ dest: 'uploads/' })
const ip = require('ip')
const ipAddress = ip.address()
const port = 3000

const app = express()

app.set('views', './views')
app.set('view engine', 'pug')

app.get('/', function (req, res) {
    res.render('lise-input')
})

app.post('/input', upload.single('file'), function (req, res) {
    //run ./lise -f <uploaded file>
    //respond with results/pdbid_top10.pdb
    /* Next steps would be to show results with
     * Jsmol
     */
})

app.get('/input', function (req, res) {
    /* check if results/pdbid_top10.pdb exists
     * if it does respond with it.
     */
})

app.listen(port, function () {
    console.log('App listening on port: ' + port)
    console.log('Network access via: http://' + ipAddress + ':' + port)
})
