var mongoose = require('mongoose');
var Schema = mongoose.Schema;

var WeatherSchema = new Schema({
    sensorType: {
        type: String
    },
    temperature: {
        type: Number,
        required: true
    },
    humidity: {
        type: Number,
        required: true
    },
    created_at: {
        type: Date,
        default: Date.now
    }
});

var Weather = module.exports = mongoose.model("weather", WeatherSchema);