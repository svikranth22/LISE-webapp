const path = require('path')
const { exec } = require('child_process')
const express = require('express')
const multer  = require('multer')
const helmet = require('helmet')

const ip = require('ip')
const ipAddress = ip.address()
const port = 3100
const app = express()


//Specifies the folder tmp as the location to store uploaded files, 
//and to store them with their original name
const storage = multer.diskStorage({
  destination: function(req, file, cb) {
    cb(null, 'tmp/')
  }, 
  filename : function (req, file, cb) {
    cb(null, file.originalname)
  }
})
const upload = multer({ storage: storage })


app.use(express.static(path.join(__dirname, 'public')))
app.use(helmet.frameguard())
app.set('views', path.join(__dirname,'views'))
app.set('view engine', 'pug')

app.get('/', function (req, res) {
    res.status(200).render('lise-input')
})

app.post('/input', upload.single('file'), function (req, res) {

    //run ./lise -f <uploaded file>
    exec(`/Users/isaacmartinez/a.out ${path.join(__dirname, '..', "tmp", req.file.originalname)}`, (error, stdout, stderr) => {
        if (error) {
          console.error(`exec error: ${error}`);
          return;
        }
        console.log(`exec stdout: ${stdout}`);
           
      });  
    console.log(req.file.originalname.substring(0, 4));
    res.status(200).render('results', { pdb_file: "1a6w" });
    //respond with results/pdbid_top10.pdbs
})

app.get('/input', function (req, res) {

    /* check if results/pdbid_top10.pdb exists
     * if it does respond with it.
     */
    /* Next steps would be to show results with
     * Jsmol
     */
})



app.listen(port, function () {
  console.log('App listening on port: ' + port)
  console.log('Network access via: http://' + ipAddress + ':' + port)
})

