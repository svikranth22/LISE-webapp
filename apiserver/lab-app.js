const express = require('express');
const helmet = require('helmet');
const path = require('path');
const lise = require('./lise.js');
const cors = require('cors');

module.exports = async (app) => {

    app.use(helmet.frameguard());
    app.use(cors());
    app.set('view engine', 'pug')

    //api
    lise(app);

}