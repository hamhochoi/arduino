var express = require('express');
var router = express.Router();
var Motor = require('../model/motor');

/* GET home page. */
router.post('/direction', function (req, res, next) {
  var direction = req.body.direction;
  Motor.findOne({}, function (err, doc) {
    if (err) {
      console.log("something went wrong when findOne");
      next(err);
    }
    if (doc == null) {
      var newMotor = new Motor({
        "direction": direction
      });
      newMotor.save(function (err, docSave) {
        if (err) {
          console.log("something went wrong when save");
          next(err);
        }

        console.log("docSave: ", docSave);
        res.status(200).json(docSave);
      });
    } else {
      Motor.findOneAndUpdate({}, {
        $set: {
          "direction": direction
        }
      }, {
        new: true
      }, function (err, docUpdate) {
        if (err) {
          console.log("something went wrong when findOneAndUpdate");
          next(err);
        }
        console.log("docUpdate: ", docUpdate);
        res.status(200).json(docUpdate);
      })
    }
  });

});

router.get('/direction', function(req, res, next) {
  Motor.findOne({}, function(err, doc) {
    if(err) {
      console.log("something went wrong whend findOne");
      next(err);
    }
    console.log("doc: ", doc);
    res.status(200).json(doc);
  });
});

module.exports = router;