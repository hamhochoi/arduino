var express = require("express");
var weatherRouter = express.Router();
var Weather = require('../model/weather');

weatherRouter.post('/', function(req, res, next){
    console.log("req.body: ", req.body);
    res.status(200).json(req.body);
    var weather = new Weather(req.body);
    weather.save(function(err, weather) {
        if(err) {
            console.log("Error while saving weather");
        }
    });
});

weatherRouter.get('/', function(req, res, next) {
    Weather.findOne().sort({"created_at": -1}).limit(1)
        .exec(function(err, weather) {
            if(err) {
                console.log("Error in getting weather infor");
                next(err);
            } 

            res.status(200).json(weather);
        })
})

module.exports = weatherRouter;