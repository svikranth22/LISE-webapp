const multer  = require('multer');
const path = require('path');
const { spawn } = require('child_process');
const { abort } = require('process');
const ENV_PATH = "/usr/local/bin/python3";
const LISE_PATH = "/Users/isaacmartinez/Desktop/LISEPROJECT/apiserver/LISE";

const storage = multer.diskStorage({
    //Specifies the folder tmp as the location to store uploaded files, 
    //and to store them with their original name
    destination: function(req, file, cb) {
      cb(null, path.join(LISE_PATH, 'tmp'));
    }, 
    filename : function (req, file, cb) {
      cb(null, file.originalname)
    }
});
const upload = multer({ storage: storage });


module.exports = (app) => {

    app.get('/lise/:id', async (req, res, next) => {
        //Connects to LISE service with pdb code as id
        //Expected output:
        //  Finished Python program
        //  Finished C program 
        //  Sent {name}.pdb
        //
        try {
            //Executes the LISE program 
            upload.single('file');
            spawn(ENV_PATH, [path.join(LISE_PATH, "prep.py"), '-i', `${req.params.id}`], (error, stdout, stderr) => {
                if (error) {
                    console.error(`Python exec error:\n ${error}\n${stderr}`);
                } else {
                    console.log("Finished Python program");
                }
                console.log(`Python output:\n ${stdout}`);
            });
            console.log("initiating C program");
            spawn(path.join(LISE_PATH, "a.out"), [`${req.params.id}`], (error, stdout , stderr) => {
                if (error) {
                    console.error(`C exec error:\n ${error}\n${stderr}`);
                } else {
                    console.log("Finished C program");
                }
                console.log(`C ouput:\n ${stdout}`);
                res.sendFile(path.join(LISE_PATH, `results/${req.params.id}.pdb`), (err) => {
                    if (err) {
                        console.log(`Error sending file: ${err}`);
                    } else {
                        console.log(`Sent: ${req.params.id}.pdb`);
                    }
                });
            });
            
        } catch (err) {
            console.error(`Request error: ${err}`);
            res.end();
        }
    });

    app.get('/test/:id', async (req,res, next) => {
        //Test connection to server API
        res.status(200);
        console.log(req.params.id);
    });
}
