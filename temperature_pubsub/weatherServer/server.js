var express = require('express');
var path = require('path');
var favicon = require('serve-favicon');
var logger = require('morgan');
var cookieParser = require('cookie-parser');
var bodyParser = require('body-parser');
var mongoose = require("mongoose");

var app = express();

// uncomment after placing your favicon in /public
//app.use(favicon(path.join(__dirname, 'public', 'favicon.ico')));
app.use(logger('dev'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

// connect to database
mongoose.connect("mongodb://duyle:1234@ds135514.mlab.com:35514/weather_esp8266");
var db = mongoose.connection;
// db.on('err', console.error.bind(console, "Connection error"));
// db.on('open', function() {
//   console.log("Successfully connect to database");
// });

var index = require('./routes/index');
var weather = require('./routes/weather');

app.use('/', index);
app.use('/weather', weather);

// catch 404 and forward to error handler
app.use(function(req, res, next) {
  var err = new Error('Not Found');
  err.status = 404;
  next(err);
});

// error handler
app.use(function(err, req, res, next) {
  // set locals, only providing error in development
  res.locals.message = err.message;
  res.locals.error = req.app.get('env') === 'development' ? err : {};

  // render the error page
  res.status(err.status || 500);
  res.render('error');
});

var listener = app.listen(8080, function() {
    console.log("Server listen at port ", listener.address().port);
});

module.exports = app;
