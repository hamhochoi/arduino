var express = require('express')
var moment = require('moment')
var app = express()

app.get('/', function (req, res, next) {
    res.send('Http Esp8266 server')
});

app.get('/watchdog', function (req, res, next) {
    var t = moment.duration(parseInt(req.param('uptime'), 'milliseconds'))
    console.log("param",req.param('uptime'))
    var _message = req.param('ip') + " uptime " + t.hours() + "h " + t.minutes() + "m " + t.seconds() + "s"
    console.log("watchdog from ", _message)
    res.send("You are alive!!")
})

app.listen(8080, function() {
    console.log("server listen at port 8080");
}) 