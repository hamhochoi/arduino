var mongoose = require('mongoose');
var Schema = mongoose.Schema;


var MotorSchema = new Schema({
    direction: {
        type: String,
        required: true
    }
}) 

var Motor = module.exports =  mongoose.model('motor', MotorSchema);